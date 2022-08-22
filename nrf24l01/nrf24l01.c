/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

// Pico
#include "pico/stdlib.h"

// For memcpy
#include <string.h>

// Include descriptor struct definitions
#include "usb_common.h"
// USB register definitions from pico-sdk
#include "hardware/regs/usb.h"
// USB hardware struct definitions from pico-sdk
#include "hardware/structs/usb.h"
// For interrupt enable and numbers
#include "hardware/irq.h"
// For resetting the USB controller
#include "hardware/resets.h"

// Device descriptors
#include "nrf24l01.h"
#include "RF24interface.h"

#define usb_hw_set hw_set_alias(usb_hw)
#define usb_hw_clear hw_clear_alias(usb_hw)


#define LED_PIN PICO_DEFAULT_LED_PIN

bool radio_begin(); 
bool radio_begini(uint16_t _cepin, uint16_t _cspin);
bool radio_isChipConnected();
void radio_startListening(void);
void radio_stopListening(void);
bool radio_available(void);
void radio_read(void *buf, uint8_t len);
bool radio_write(const void *buf, uint8_t len);
void radio_openWritingPipe(const uint8_t *address);
void radio_openReadingPipe(uint8_t number, const uint8_t *address);
bool radio_failureDetected();
void radio_printDetails (void);
void radio_printPrettyDetails (void);
void radio_encodeRadioDetails (uint8_t *encoded_status);
bool radio_availablePN(uint8_t *pipe_num);
bool radio_rxFifoFull ();
uint8_t radio_isFifo (bool about_tx);
bool radio_isFifoE(bool about_tx, bool check_empty);
void radio_powerDown (void);
void radio_powerUp (void);
bool radio_writeMC(const void *buf, uint8_t len, const bool multicast);
bool radio_writeFast (const void *buf, uint8_t len);
bool radio_writeFastMC(const void *buf, uint8_t len, const bool multicast);
bool radio_writeBlocking (const void *buf, uint8_t len, uint32_t timeout);
bool radio_txStandBy ();
bool radio_txStandByT(uint32_t timeout);
bool radio_writeAckPayload (uint8_t pipe, const void *buf, uint8_t len);
void radio_whatHappened(bool tx_ok, bool tx_fail, bool rx_ready);
void radio_startFastWrite (const void *buf, uint8_t len, const bool multicast);
bool radio_startWrite (const void *buf, uint8_t len, const bool multicast);
void radio_reUseTX ();
uint8_t radio_flush_tx (void);
uint8_t radio_flush_rx (void);
bool radio_testCarrier (void);
bool radio_testRPD (void);
bool radio_isValid ();
void radio_closeReadingPipe (uint8_t pipe);
uint32_t radio_txDelay();
uint32_t radio_csDelay();
void radio_setAddressWidth (uint8_t a_width);
void radio_setRetries (uint8_t delay, uint8_t count);
void radio_setChannel (uint8_t channel);
uint8_t radio_getChannel (void);
void radio_setPayloadSize (uint8_t size);
uint8_t radio_getPayloadSize (void);
uint8_t radio_getDynamicPayloadSize (void);
void radio_enableAckPayload (void);
void radio_disableAckPayload (void);
void radio_enableDynamicPayloads (void);
void radio_disableDynamicPayloads (void);
void radio_enableDynamicAck ();
bool radio_isPVariant (void);
void radio_setAutoAck (bool enable);
void radio_setAutoAckP(uint8_t pipe, bool enable);
void radio_setPALevel (uint8_t level);
uint8_t radio_getPALevel (void);
uint8_t radio_getARC (void);
bool radio_setDataRate (rf24_datarate_ec speed);
rf24_datarate_ec radio_getDataRate (void);
void radio_setCRCLength (rf24_crclength_ec length);
rf24_crclength_ec radio_getCRCLength (void);
void radio_disableCRC (void);
void radio_maskIRQ (bool tx_ok, bool tx_fail, bool rx_ready);
void radio_startConstCarrier (rf24_pa_dbm_ec level, uint8_t channel);
void radio_stopConstCarrier (void);
void radio_toggleAllPipes (bool isEnabled);
void radio_setRadiation (uint8_t level, rf24_datarate_ec speed);



uint8_t address[][6] = { "1Node", "2Node" };
// It is very helpful to think of an address as a path instead of as
// an identifying device destination
 
// to use different addresses on a pair of radios, we need a variable to
// uniquely identify which address this radio will use to transmit
bool radioNumber = 1;  // 0 uses address[0] to transmit, 1 uses address[1] to transmit
 
// Used to control whether this node is sending or receiving
bool role = false;  // true = TX role, false = RX role
 
// For this example, we'll be using a payload containing
// a single float number that will be incremented
// on every successful transmission
float payload = 0.0;

bool changeRole = 0;
char changeRoleTo = ' ';
#define COMBUFSN 5
uint8_t comBuf[COMBUFSN][MAXPACKETSIZE];
int currentComBuf = 0;
int clearedTillComBuf = 0;




// Function prototypes for our device specific endpoint handlers defined
// later on
void ep0_in_handler(uint8_t *buf, uint16_t len);
void ep0_out_handler(uint8_t *buf, uint16_t len);
void ep1_out_handler(uint8_t *buf, uint16_t len);
void ep2_in_handler(uint8_t *buf, uint16_t len);

// Global device address
static bool should_set_address = false;
static uint8_t dev_addr = 0;
static volatile bool configured = false;

static volatile int blinkCounter = 0;

// Global data buffer for EP0
static uint8_t ep0_buf[MAXPACKETSIZE];

// Struct defining the device configuration
static struct usb_device_configuration dev_config = {
        .device_descriptor = &device_descriptor,
        .interface_descriptor = &interface_descriptor,
        .config_descriptor = &config_descriptor,
        .lang_descriptor = lang_descriptor,
        .descriptor_strings = descriptor_strings,
        .endpoints = {
                {
                        .descriptor = &ep0_out,
                        .handler = &ep0_out_handler,
                        .endpoint_control = NULL, // NA for EP0
                        .buffer_control = &usb_dpram->ep_buf_ctrl[0].out,
                        // EP0 in and out share a data buffer
                        .data_buffer = &usb_dpram->ep0_buf_a[0],
                },
                {
                        .descriptor = &ep0_in,
                        .handler = &ep0_in_handler,
                        .endpoint_control = NULL, // NA for EP0,
                        .buffer_control = &usb_dpram->ep_buf_ctrl[0].in,
                        // EP0 in and out share a data buffer
                        .data_buffer = &usb_dpram->ep0_buf_a[0],
                },
                {
                        .descriptor = &ep1_out,
                        .handler = &ep1_out_handler,
                        // EP1 starts at offset 0 for endpoint control
                        .endpoint_control = &usb_dpram->ep_ctrl[0].out,
                        .buffer_control = &usb_dpram->ep_buf_ctrl[1].out,
                        // First free EPX buffer
                        .data_buffer = &usb_dpram->epx_data[0 * MAXPACKETSIZE],
                },
                {
                        .descriptor = &ep2_in,
                        .handler = &ep2_in_handler,
                        .endpoint_control = &usb_dpram->ep_ctrl[1].in,
                        .buffer_control = &usb_dpram->ep_buf_ctrl[2].in,
                        // Second free EPX buffer
                        .data_buffer = &usb_dpram->epx_data[1 * MAXPACKETSIZE],
                }
        }
};

/**
 * @brief Given an endpoint address, return the usb_endpoint_configuration of that endpoint. Returns NULL
 * if an endpoint of that address is not found.
 *
 * @param addr
 * @return struct usb_endpoint_configuration*
 */
struct usb_endpoint_configuration *usb_get_endpoint_configuration(uint8_t addr) {
    struct usb_endpoint_configuration *endpoints = dev_config.endpoints;
    for (int i = 0; i < USB_NUM_ENDPOINTS; i++) {
        if (endpoints[i].descriptor && (endpoints[i].descriptor->bEndpointAddress == addr)) {
            return &endpoints[i];
        }
    }
    return NULL;
}

/**
 * @brief Given a C string, fill the EP0 data buf with a USB string descriptor for that string.
 *
 * @param C string you would like to send to the USB host
 * @return the length of the string descriptor in EP0 buf
 */
uint8_t usb_prepare_string_descriptor(const unsigned char *str) {
    // 2 for bLength + bDescriptorType + strlen * 2 because string is unicode. i.e. other byte will be 0
    uint8_t bLength = 2 + (strlen((const char *)str) * 2);
    static const uint8_t bDescriptorType = 0x03;

    volatile uint8_t *buf = &ep0_buf[0];
    *buf++ = bLength;
    *buf++ = bDescriptorType;

    uint8_t c;

    do {
        c = *str++;
        *buf++ = c;
        *buf++ = 0;
    } while (c != '\0');

    return bLength;
}

/**
 * @brief Take a buffer pointer located in the USB RAM and return as an offset of the RAM.
 *
 * @param buf
 * @return uint32_t
 */
static inline uint32_t usb_buffer_offset(volatile uint8_t *buf) {
    return (uint32_t) buf ^ (uint32_t) usb_dpram;
}

/**
 * @brief Set up the endpoint control register for an endpoint (if applicable. Not valid for EP0).
 *
 * @param ep
 */
void usb_setup_endpoint(const struct usb_endpoint_configuration *ep) {
    printf("Set up endpoint 0x%x with buffer address 0x%p\n", ep->descriptor->bEndpointAddress, ep->data_buffer);

    // EP0 doesn't have one so return if that is the case
    if (!ep->endpoint_control) {
        return;
    }

    // Get the data buffer as an offset of the USB controller's DPRAM
    uint32_t dpram_offset = usb_buffer_offset(ep->data_buffer);
    uint32_t reg = EP_CTRL_ENABLE_BITS
                   | EP_CTRL_INTERRUPT_PER_BUFFER
                   | (ep->descriptor->bmAttributes << EP_CTRL_BUFFER_TYPE_LSB)
                   | dpram_offset;
    *ep->endpoint_control = reg;
}

/**
 * @brief Set up the endpoint control register for each endpoint.
 *
 */
void usb_setup_endpoints() {
    const struct usb_endpoint_configuration *endpoints = dev_config.endpoints;
    for (int i = 0; i < USB_NUM_ENDPOINTS; i++) {
        if (endpoints[i].descriptor && endpoints[i].handler) {
            usb_setup_endpoint(&endpoints[i]);
        }
    }
}

/**
 * @brief Set up the USB controller in device mode, clearing any previous state.
 *
 */
void usb_device_init() {
    // Reset usb controller
    reset_block(RESETS_RESET_USBCTRL_BITS);
    unreset_block_wait(RESETS_RESET_USBCTRL_BITS);

    // Clear any previous state in dpram just in case
    memset(usb_dpram, 0, sizeof(*usb_dpram)); // <1>

    // Enable USB interrupt at processor
    irq_set_enabled(USBCTRL_IRQ, true);

    // Mux the controller to the onboard usb phy
    usb_hw->muxing = USB_USB_MUXING_TO_PHY_BITS | USB_USB_MUXING_SOFTCON_BITS;

    // Force VBUS detect so the device thinks it is plugged into a host
    usb_hw->pwr = USB_USB_PWR_VBUS_DETECT_BITS | USB_USB_PWR_VBUS_DETECT_OVERRIDE_EN_BITS;

    // Enable the USB controller in device mode.
    usb_hw->main_ctrl = USB_MAIN_CTRL_CONTROLLER_EN_BITS;

    // Enable an interrupt per EP0 transaction
    usb_hw->sie_ctrl = USB_SIE_CTRL_EP0_INT_1BUF_BITS; // <2>

    // Enable interrupts for when a buffer is done, when the bus is reset,
    // and when a setup packet is received
    usb_hw->inte = USB_INTS_BUFF_STATUS_BITS |
                   USB_INTS_BUS_RESET_BITS |
                   USB_INTS_SETUP_REQ_BITS;

    // Set up endpoints (endpoint control registers)
    // described by device configuration
    usb_setup_endpoints();

    // Present full speed device by enabling pull up on DP
    usb_hw_set->sie_ctrl = USB_SIE_CTRL_PULLUP_EN_BITS;
}

/**
 * @brief Given an endpoint configuration, returns true if the endpoint
 * is transmitting data to the host (i.e. is an IN endpoint)
 *
 * @param ep, the endpoint configuration
 * @return true
 * @return false
 */
static inline bool ep_is_tx(struct usb_endpoint_configuration *ep) {
    return ep->descriptor->bEndpointAddress & USB_DIR_IN;
}

/**
 * @brief Starts a transfer on a given endpoint.
 *
 * @param ep, the endpoint configuration.
 * @param buf, the data buffer to send. Only applicable if the endpoint is TX
 * @param len, the length of the data in buf (this example limits max len to one packet - 64 bytes)
 */
void usb_start_transfer(struct usb_endpoint_configuration *ep, uint8_t *buf, uint16_t len) {
    // We are asserting that the length is <= 64 bytes for simplicity of the example.
    // For multi packet transfers see the tinyusb port.
    assert(len <= MAXPACKETSIZE);

    printf("Start transfer of len %d on ep addr 0x%x\n", len, ep->descriptor->bEndpointAddress);

    // Prepare buffer control register value
    uint32_t val = len | USB_BUF_CTRL_AVAIL;

    if (ep_is_tx(ep)) {
        // Need to copy the data from the user buffer to the usb memory
        memcpy((void *) ep->data_buffer, (void *) buf, len);
        // Mark as full
        val |= USB_BUF_CTRL_FULL;
    }

    // Set pid and flip for next transfer
    val |= ep->next_pid ? USB_BUF_CTRL_DATA1_PID : USB_BUF_CTRL_DATA0_PID;
    ep->next_pid ^= 1u;

    *ep->buffer_control = val;
}

/**
 * @brief Send device descriptor to host
 *
 */
void usb_handle_device_descriptor(void) {
    const struct usb_device_descriptor *d = dev_config.device_descriptor;
    // EP0 in
    struct usb_endpoint_configuration *ep = usb_get_endpoint_configuration(EP0_IN_ADDR);
    // Always respond with pid 1
    ep->next_pid = 1;
    usb_start_transfer(ep, (uint8_t *) d, sizeof(struct usb_device_descriptor));
}

/**
 * @brief Send the configuration descriptor (and potentially the configuration and endpoint descriptors) to the host.
 *
 * @param pkt, the setup packet received from the host.
 */
void usb_handle_config_descriptor(volatile struct usb_setup_packet *pkt) {
    uint8_t *buf = &ep0_buf[0];

    // First request will want just the config descriptor
    const struct usb_configuration_descriptor *d = dev_config.config_descriptor;
    memcpy((void *) buf, d, sizeof(struct usb_configuration_descriptor));
    buf += sizeof(struct usb_configuration_descriptor);

    // If we more than just the config descriptor copy it all
    if (pkt->wLength >= d->wTotalLength) {
        memcpy((void *) buf, dev_config.interface_descriptor, sizeof(struct usb_interface_descriptor));
        buf += sizeof(struct usb_interface_descriptor);
        const struct usb_endpoint_configuration *ep = dev_config.endpoints;

        // Copy all the endpoint descriptors starting from EP1
        for (uint i = 2; i < USB_NUM_ENDPOINTS; i++) {
            if (ep[i].descriptor) {
                memcpy((void *) buf, ep[i].descriptor, sizeof(struct usb_endpoint_descriptor));
                buf += sizeof(struct usb_endpoint_descriptor);
            }
        }

    }

    // Send data
    // Get len by working out end of buffer subtract start of buffer
    uint32_t len = (uint32_t) buf - (uint32_t) &ep0_buf[0];
    usb_start_transfer(usb_get_endpoint_configuration(EP0_IN_ADDR), &ep0_buf[0], len);
}

/**
 * @brief Handle a BUS RESET from the host by setting the device address back to 0.
 *
 */
void usb_bus_reset(void) {
    // Set address back to 0
    dev_addr = 0;
    should_set_address = false;
    usb_hw->dev_addr_ctrl = 0;
    configured = false;
}

/**
 * @brief Send the requested string descriptor to the host.
 *
 * @param pkt, the setup packet from the host.
 */
void usb_handle_string_descriptor(volatile struct usb_setup_packet *pkt) {
    uint8_t i = pkt->wValue & 0xff;
    uint8_t len = 0;

    if (i == 0) {
        len = 4;
        memcpy(&ep0_buf[0], dev_config.lang_descriptor, len);
    } else {
        // Prepare fills in ep0_buf
        len = usb_prepare_string_descriptor(dev_config.descriptor_strings[i - 1]);
    }

    usb_start_transfer(usb_get_endpoint_configuration(EP0_IN_ADDR), &ep0_buf[0], len);
}

/**
 * @brief Sends a zero length status packet back to the host.
 */
void usb_acknowledge_out_request(void) {
    usb_start_transfer(usb_get_endpoint_configuration(EP0_IN_ADDR), NULL, 0);
}

/**
 * @brief Handles a SET_ADDR request from the host. The actual setting of the device address in
 * hardware is done in ep0_in_handler. This is because we have to acknowledge the request first
 * as a device with address zero.
 *
 * @param pkt, the setup packet from the host.
 */
void usb_set_device_address(volatile struct usb_setup_packet *pkt) {
    // Set address is a bit of a strange case because we have to send a 0 length status packet first with
    // address 0
    dev_addr = (pkt->wValue & 0xff);
    printf("Set address %d\r\n", dev_addr);
    // Will set address in the callback phase
    should_set_address = true;
    usb_acknowledge_out_request();
}

/**
 * @brief Handles a SET_CONFIGRUATION request from the host. Assumes one configuration so simply
 * sends a zero length status packet back to the host.
 *
 * @param pkt, the setup packet from the host.
 */
void usb_set_device_configuration(volatile struct usb_setup_packet *pkt) {
    // Only one configuration so just acknowledge the request
    printf("Device Enumerated\r\n");
    usb_acknowledge_out_request();
    configured = true;
}

/**
 * @brief Respond to a setup packet from the host.
 *
 */
void usb_handle_setup_packet(void) {
    volatile struct usb_setup_packet *pkt = (volatile struct usb_setup_packet *) &usb_dpram->setup_packet;
    uint8_t req_direction = pkt->bmRequestType;
    uint8_t req = pkt->bRequest;

    // Reset PID to 1 for EP0 IN
    usb_get_endpoint_configuration(EP0_IN_ADDR)->next_pid = 1u;

    if (req_direction == USB_DIR_OUT) {
        if (req == USB_REQUEST_SET_ADDRESS) {
            usb_set_device_address(pkt);
        } else if (req == USB_REQUEST_SET_CONFIGURATION) {
            usb_set_device_configuration(pkt);
        } else {
            usb_acknowledge_out_request();
            printf("Other OUT request (0x%x)\r\n", pkt->bRequest);
        }
    } else if (req_direction == USB_DIR_IN) {
        if (req == USB_REQUEST_GET_DESCRIPTOR) {
            uint16_t descriptor_type = pkt->wValue >> 8;

            switch (descriptor_type) {
                case USB_DT_DEVICE:
                    usb_handle_device_descriptor();
                    printf("GET DEVICE DESCRIPTOR\r\n");
                    break;

                case USB_DT_CONFIG:
                    usb_handle_config_descriptor(pkt);
                    printf("GET CONFIG DESCRIPTOR\r\n");
                    break;

                case USB_DT_STRING:
                    usb_handle_string_descriptor(pkt);
                    printf("GET STRING DESCRIPTOR\r\n");
                    break;

                default:
                    printf("Unhandled GET_DESCRIPTOR type 0x%x\r\n", descriptor_type);
            }
        } else {
            printf("Other IN request (0x%x)\r\n", pkt->bRequest);
        }
    }
}

/**
 * @brief Notify an endpoint that a transfer has completed.
 *
 * @param ep, the endpoint to notify.
 */
static void usb_handle_ep_buff_done(struct usb_endpoint_configuration *ep) {
    uint32_t buffer_control = *ep->buffer_control;
    // Get the transfer length for this endpoint
    uint16_t len = buffer_control & USB_BUF_CTRL_LEN_MASK;

    // Call that endpoints buffer done handler
    ep->handler((uint8_t *) ep->data_buffer, len);
}

/**
 * @brief Find the endpoint configuration for a specified endpoint number and
 * direction and notify it that a transfer has completed.
 *
 * @param ep_num
 * @param in
 */
static void usb_handle_buff_done(uint ep_num, bool in) {
    uint8_t ep_addr = ep_num | (in ? USB_DIR_IN : 0);
    printf("EP %d (in = %d) done\n", ep_num, in);
    for (uint i = 0; i < USB_NUM_ENDPOINTS; i++) {
        struct usb_endpoint_configuration *ep = &dev_config.endpoints[i];
        if (ep->descriptor && ep->handler) {
            if (ep->descriptor->bEndpointAddress == ep_addr) {
                usb_handle_ep_buff_done(ep);
                return;
            }
        }
    }
}

/**
 * @brief Handle a "buffer status" irq. This means that one or more
 * buffers have been sent / received. Notify each endpoint where this
 * is the case.
 */
static void usb_handle_buff_status() {
    uint32_t buffers = usb_hw->buf_status;
    uint32_t remaining_buffers = buffers;

    uint bit = 1u;
    for (uint i = 0; remaining_buffers && i < USB_NUM_ENDPOINTS * 2; i++) {
        if (remaining_buffers & bit) {
            // clear this in advance
            usb_hw_clear->buf_status = bit;
            // IN transfer for even i, OUT transfer for odd i
            usb_handle_buff_done(i >> 1u, !(i & 1u));
            remaining_buffers &= ~bit;
        }
        bit <<= 1u;
    }
}

/**
 * @brief USB interrupt handler
 *
 */
/// \tag::isr_setup_packet[]
void isr_usbctrl(void) {
    // USB interrupt handler
    uint32_t status = usb_hw->ints;
    uint32_t handled = 0;

    // Setup packet received
    if (status & USB_INTS_SETUP_REQ_BITS) {
        handled |= USB_INTS_SETUP_REQ_BITS;
        usb_hw_clear->sie_status = USB_SIE_STATUS_SETUP_REC_BITS;
        usb_handle_setup_packet();
    }
/// \end::isr_setup_packet[]

    // Buffer status, one or more buffers have completed
    if (status & USB_INTS_BUFF_STATUS_BITS) {
        handled |= USB_INTS_BUFF_STATUS_BITS;
        usb_handle_buff_status();
    }

    // Bus is reset
    if (status & USB_INTS_BUS_RESET_BITS) {
        printf("BUS RESET\n");
        handled |= USB_INTS_BUS_RESET_BITS;
        usb_hw_clear->sie_status = USB_SIE_STATUS_BUS_RESET_BITS;
        usb_bus_reset();
    }

    if (status ^ handled) {
        panic("Unhandled IRQ 0x%x\n", (uint) (status ^ handled));
    }
}

/**
 * @brief EP0 in transfer complete. Either finish the SET_ADDRESS process, or receive a zero
 * length status packet from the host.
 *
 * @param buf the data that was sent
 * @param len the length that was sent
 */
void ep0_in_handler(uint8_t *buf, uint16_t len) {
    if (should_set_address) {
        // Set actual device address in hardware
        usb_hw->dev_addr_ctrl = dev_addr;
        should_set_address = false;
    } else {
        // Receive a zero length status packet from the host on EP0 OUT
        struct usb_endpoint_configuration *ep = usb_get_endpoint_configuration(EP0_OUT_ADDR);
        usb_start_transfer(ep, NULL, 0);
    }
}

void ep0_out_handler(uint8_t *buf, uint16_t len) {
    ;
}

void printToUSB(uint8_t *buf, size_t n){
    while(((currentComBuf + 1) % COMBUFSN) == clearedTillComBuf){
        tight_loop_contents();
    }
    memset(comBuf[currentComBuf], 0, MAXPACKETSIZE);
    memcpy(comBuf[currentComBuf++], buf, n);
    currentComBuf %= COMBUFSN;
}

// Device specific functions
void ep1_out_handler(uint8_t *buf, uint16_t len) {
    printf("RX %d bytes from host\n", len);
    // Send data back to host
    if(buf[0] > 0){
        blinkCounter = buf[0];
    }
    if (buf[50] == 1 && changeRoleTo != buf[51]) {
        // change the role via the serial monitor
        changeRoleTo = buf[51];
        changeRole = 1;
    }
    struct usb_endpoint_configuration *ep = usb_get_endpoint_configuration(EP2_IN_ADDR);
    if(currentComBuf != clearedTillComBuf){
        usb_start_transfer(ep, comBuf[clearedTillComBuf], MAXPACKETSIZE);
        clearedTillComBuf++;
        clearedTillComBuf %= COMBUFSN;
    }else{
        usb_start_transfer(ep, buf, len);
    }
}

void ep2_in_handler(uint8_t *buf, uint16_t len) {
    printf("Sent %d bytes to host\n", len);
    // Get ready to rx again from host
    usb_start_transfer(usb_get_endpoint_configuration(EP1_OUT_ADDR), NULL, 64);
}

void floatToStr(float n, uint8_t *buf){
    int intpart = (int) n;
    float decpart = n - intpart;
    float decpart2 = decpart;
    int i = 0;
    int j = 0;
    int pot = 1;
    while(decpart2 != 0){
        decpart2 = (decpart2 - (int)decpart2) * 10;
        j++;
        pot *= 10;
    }
    n *= pot;
    while(i < 45 && n != 0){
        if(i == j){
            buf[i++] = ',';
        }else{
            n /= 10;
            intpart = (int)n;
            buf[i++] = (uint8_t)(((int)((n - intpart) * 10)) % 10);
            
        }
    }
}

void uint32_tToStr(uint32_t n, uint8_t *buf){
    int i = 0;
    while(i < 8 && n != 0){
        buf[i++] = (uint8_t)(n % 10);
        n /= 10;
    }
}

void uint_8ToStr(uint8_t n, uint8_t *buf){
    int i = 0;
    while(i < 8 && n != 0){
        buf[i++] = (uint8_t)(n % 10);
        n /= 10;
    }
}

int main(void) {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    printf("USB Device Low-Level hardware example\n");
    usb_device_init();
    
    // Wait until configured
    while (!configured) {
        tight_loop_contents();
    }

    if(!radio_begin()){
        printToUSB("No Connection to RF24\n", 22);
        while(1){
            for(int i = 0; i < 9; i++){
                gpio_put(LED_PIN, 1);
                sleep_ms((i >= 3 && i < 6) ? 500 : 250);
                gpio_put(LED_PIN, 0);
                sleep_ms((i >= 3 && i < 6) ? 500 : 250);
            }
        }
    }
    radio_setPALevel(CRF24_PA_LOW);
    radio_setPayloadSize(sizeof(payload));
    radio_openWritingPipe(address[radioNumber]);
    radio_openReadingPipe(1, address[!radioNumber]);
    if (role) {
        radio_stopListening();  // put radio in TX mode
    } else {
        radio_startListening();  // put radio in RX mode
    }
    // Get ready to rx from host
    usb_start_transfer(usb_get_endpoint_configuration(EP1_OUT_ADDR), NULL, 64);
    printToUSB("*** PRESS 'T' to begin transmitting to the other node\n", 54);
    // Everything is interrupt driven so just loop here
    while (1) {
        tight_loop_contents();
        if(blinkCounter != 0){
            for(int i = 0; i < blinkCounter; i++){
                gpio_put(LED_PIN, 1);
                sleep_ms(250);
                gpio_put(LED_PIN, 0);
                sleep_ms(250);
            }
            blinkCounter = 0;
        }
        if(changeRole){
            changeRole = 0;
            char c = changeRoleTo;
            if (c == 'T' && !role) {
                // Become the TX node
            
                role = true;
                printToUSB("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK\n", 58);
                radio_stopListening();
        
            } else if (c == 'R' && role) {
                // Become the RX node
            
                role = false;
                printToUSB("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK\n", 57);
                radio_startListening();
            }
        }
        if (role) {
            // This device is a TX node
        
            uint32_t start_timer = to_ms_since_boot(get_absolute_time());                // start the timer
            bool report = radio_write(&payload, sizeof(float));  // transmit & save the report
            uint32_t end_timer = to_ms_since_boot(get_absolute_time());                  // end the timer
        
            if (report) {
                printToUSB("Transmission successful!\n", 25);  // payload was delivered
                printToUSB("Time to transmit = \n", 20);
                uint8_t buf[50];
                uint32_tToStr((end_timer - start_timer), buf);
                printToUSB(buf, 8);  // print the timer result
                printToUSB(" us. Sent: \n", 12);
                memset(buf, 0, 50);
                floatToStr(payload, buf);
                printToUSB(buf, 50);  // print payload sent
                payload += 0.01;          // increment float payload
            } else {
                printToUSB("Transmission failed or timed out\n", 33);  // payload was not delivered
            }
        
            // to make this example readable in the serial monitor
            sleep_ms(1000);  // slow transmissions down by 1 second
        
        } else {
            // This device is a RX node
        
            uint8_t pipe;
            if (radio_availablePN(&pipe)) {              // is there a payload? get the pipe number that recieved it
                uint8_t bytes = radio_getPayloadSize();  // get the size of the payload
                radio_read(&payload, bytes);             // fetch payload from FIFO
                printToUSB("Received\n", 9);
                uint8_t buf[50];
                uint_8ToStr(bytes, buf);
                printToUSB(buf, 8);  // print the size of the payload
                printToUSB(" bytes on pipe\n", 15);
                memset(buf, 0, 50);
                uint_8ToStr(pipe, buf);
                printToUSB(buf, 50);  // print the pipe number
                printToUSB(": \n", 3);
                memset(buf, 0, 50);
                floatToStr(payload, buf);
                printToUSB(buf, 50);  // print the payload's value
            }
        }  // role
    }
    return 0;
}
