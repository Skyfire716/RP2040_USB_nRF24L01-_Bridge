#include "pico/stdlib.h"  // printf(), sleep_ms(), getchar_timeout_us(), to_us_since_boot(), get_absolute_time()
#include "pico/bootrom.h" // reset_usb_boot()
#include <RF24.h>         // RF24 radio object, rf24_min()
#include "defaultPins.h"  // board presumptive default pin numbers for CE_PIN and CSN_PIN
#include "RF24interface.h"

RF24 radio(CE_PIN, CSN_PIN);

extern "C" bool radio_begin(); 
extern "C" bool radio_begini(uint16_t _cepin, uint16_t _cspin);
extern "C" bool radio_isChipConnected();
extern "C" void radio_startListening(void);
extern "C" void radio_stopListening(void);
extern "C" bool radio_available(void);
extern "C" void radio_read(void *buf, uint8_t len);
extern "C" bool radio_write(const void *buf, uint8_t len);
extern "C" void radio_openWritingPipe(const uint8_t *address);
extern "C" void radio_openReadingPipe(uint8_t number, const uint8_t *address);


extern "C" bool radio_failureDetected();
extern "C" void radio_printDetails (void);
extern "C" void radio_printPrettyDetails (void);
extern "C" void radio_encodeRadioDetails (uint8_t *encoded_status);
extern "C" bool radio_availablePN(uint8_t *pipe_num);
extern "C" bool radio_rxFifoFull ();
extern "C" uint8_t radio_isFifo (bool about_tx);
extern "C" bool radio_isFifoE(bool about_tx, bool check_empty);
extern "C" void radio_powerDown (void);
extern "C" void radio_powerUp (void);
extern "C" bool radio_writeMC(const void *buf, uint8_t len, const bool multicast);
extern "C" bool radio_writeFast (const void *buf, uint8_t len);
extern "C" bool radio_writeFastMC(const void *buf, uint8_t len, const bool multicast);
extern "C" bool radio_writeBlocking (const void *buf, uint8_t len, uint32_t timeout);
extern "C" bool radio_txStandBy ();
extern "C" bool radio_txStandByT(uint32_t timeout);
extern "C" bool radio_writeAckPayload (uint8_t pipe, const void *buf, uint8_t len);
extern "C" void radio_whatHappened (bool &tx_ok, bool &tx_fail, bool &rx_ready);
extern "C" void radio_startFastWrite (const void *buf, uint8_t len, const bool multicast);
extern "C" bool radio_startWrite (const void *buf, uint8_t len, const bool multicast);
extern "C" void radio_reUseTX ();
extern "C" uint8_t radio_flush_tx (void);
extern "C" uint8_t radio_flush_rx (void);
extern "C" bool radio_testCarrier (void);
extern "C" bool radio_testRPD (void);
extern "C" bool radio_isValid ();
extern "C" void radio_closeReadingPipe (uint8_t pipe);


extern "C" uint32_t radio_txDelay();
extern "C" uint32_t radio_csDelay();
extern "C" void radio_setAddressWidth (uint8_t a_width);
extern "C" void radio_setRetries (uint8_t delay, uint8_t count);
extern "C" void radio_setChannel (uint8_t channel);
extern "C" uint8_t radio_getChannel (void);
extern "C" void radio_setPayloadSize (uint8_t size);
extern "C" uint8_t radio_getPayloadSize (void);
extern "C" uint8_t radio_getDynamicPayloadSize (void);
extern "C" void radio_enableAckPayload (void);
extern "C" void radio_disableAckPayload (void);
extern "C" void radio_enableDynamicPayloads (void);
extern "C" void radio_disableDynamicPayloads (void);
extern "C" void radio_enableDynamicAck ();
extern "C" bool radio_isPVariant (void);
extern "C" void radio_setAutoAck (bool enable);
extern "C" void radio_setAutoAckP(uint8_t pipe, bool enable);
extern "C" void radio_setPALevel (uint8_t level);
extern "C" uint8_t radio_getPALevel (void);
extern "C" uint8_t radio_getARC (void);
extern "C" bool radio_setDataRate (rf24_datarate_ec speed);
extern "C" rf24_datarate_ec radio_getDataRate (void);
extern "C" void radio_setCRCLength (rf24_crclength_ec length);
extern "C" rf24_crclength_ec radio_getCRCLength (void);
extern "C" void radio_disableCRC (void);
extern "C" void radio_maskIRQ (bool tx_ok, bool tx_fail, bool rx_ready);
extern "C" void radio_startConstCarrier (rf24_pa_dbm_ec level, uint8_t channel);
extern "C" void radio_stopConstCarrier (void);
extern "C" void radio_toggleAllPipes (bool isEnabled);
extern "C" void radio_setRadiation (uint8_t level, rf24_datarate_ec speed);


rf24_pa_dbm_ec convertCPADBM2PADBM(rf24_pa_dbm_e level){
    if(level == CRF24_PA_MIN){
        return rf24_pa_dbm_ec.CRF24_PA_MIN;
    }else if (level == CRF24_PA_LOW){
        return rf24_pa_dbm_ec.CRF24_PA_LOW;
    }else if(level == CRF24_PA_HIGH){
        return rf24_pa_dbm_ec.CRF24_PA_HIGH;
    }else if(level == CRF24_PA_MAX){
        return rf24_pa_dbm_ec.CRF24_PA_MAX;
    }else if(level == CRF24_PA_ERROR){
        return rf24_pa_dbm_ec.CRF24_PA_ERROR;
    }
}



bool radio_begin()
{
    return radio.begin();
}

bool radio_begini(uint16_t _cepin, uint16_t _cspin){
    return radio.begin(_cepin, _cspin);
}

bool radio_isChipConnected(){
    return radio.isChipConnected();
}

void radio_startListening(void){
    radio.startListening();
}

void radio_stopListening(void){
    radio.stopListening();
}

bool radio_available(void){
    return radio.available();
}

void radio_read(void *buf, uint8_t len){
    radio.read(buf, len);
}

bool radio_write(const void *buf, uint8_t len){
    return radio.write(buf, len);
}

void radio_openWritingPipe(const uint8_t *address){
    radio.openWritingPipe(address);
}

void radio_openReadingPipe (uint8_t number, const uint8_t *address){
    radio.openReadingPipe(number, address);
}

bool radio_failureDetected(){
    return radio.failureDetected;
}

void radio_printDetails(void){
    radio.printDetails();
}

void radio_printPrettyDetails(void){
    radio.printPrettyDetails();
}

void radio_encodeRadioDetails (uint8_t *encoded_status){
    radio.encodeRadioDetails(encoded_status);
}

bool radio_availablePN(uint8_t *pipe_num){
    return radio.available(pipe_num);
}

bool radio_rxFifoFull (){
    return radio.rxFifoFull();
}

uint8_t radio_isFifo (bool about_tx){
    return radio.isFifo(about_tx);
}

bool radio_isFifoE(bool about_tx, bool check_empty){
    return radio.isFifo(about_tx, check_empty);
}

void radio_powerDown (void){
    radio.powerDown();
}

void radio_powerUp (void){
    radio.powerUp();
}

bool radio_writeMC(const void *buf, uint8_t len, const bool multicast) {
    return radio.write(buf, len, multicast);
}

bool radio_writeFast (const void *buf, uint8_t len){
    return radio.writeFast(buf, len);
}

bool radio_writeFastMC(const void *buf, uint8_t len, const bool multicast){
    return radio.writeFast(buf, len, multicast);
}

bool radio_writeBlocking (const void *buf, uint8_t len, uint32_t timeout){
    return radio.writeBlocking(buf, len, timeout);
}

bool radio_txStandBy (){
    return radio.txStandBy();
}

bool radio_txStandByT(uint32_t timeout){
    return radio.txStandBy(timeout);
}

bool radio_writeAckPayload (uint8_t pipe, const void *buf, uint8_t len){
    return radio.writeAckPayload(pipe, buf, len);
}

void radio_whatHappened (bool &tx_ok, bool &tx_fail, bool &rx_ready){
    radio.whatHappened(tx_ok, tx_fail, rx_ready);
}

void radio_startFastWrite (const void *buf, uint8_t len, const bool multicast){
    radio.startFastWrite(buf, len, multicast);
}

bool radio_startWrite (const void *buf, uint8_t len, const bool multicast){
    return radio.startWrite(buf, len, multicast);
}

void radio_reUseTX (){
    radio.reUseTX();
}

uint8_t radio_flush_tx (void){
    return radio.flush_tx();
}

uint8_t radio_flush_rx (void){
    return radio.flush_rx();
}

bool radio_testCarrier (void){
    return radio.testCarrier();
}

bool radio_testRPD (void){
    return radio.testRPD();
}

bool radio_isValid (){
    return radio.isValid();
}

void radio_closeReadingPipe (uint8_t pipe){
    radio.closeReadingPipe(pipe);
}

uint32_t radio_txDelay(){
    return radio.txDelay;
}

uint32_t radio_csDelay(){
    return radio.csDelay;
}

void radio_setAddressWidth (uint8_t a_width){
    radio.setAddressWidth(a_width);
}

void radio_setRetries (uint8_t delay, uint8_t count){
    radio.setRetries(delay, count);
}

void radio_setChannel (uint8_t channel){
    radio.setChannel(channel);
}

uint8_t radio_getChannel (void){
    return radio.getChannel();
}

void radio_setPayloadSize (uint8_t size){
    radio.setPayloadSize(size);
}

uint8_t radio_getPayloadSize (void){
    return radio.getPayloadSize();
}

uint8_t radio_getDynamicPayloadSize (void){
    return radio.getDynamicPayloadSize();
}

void radio_enableAckPayload (void){
    radio.enableAckPayload();
}

void radio_disableAckPayload (void){
    radio.disableAckPayload();
}

void radio_enableDynamicPayloads (void){
    radio.enableDynamicPayloads();
}

void radio_disableDynamicPayloads (void){
    radio.disableDynamicPayloads();
}

void radio_enableDynamicAck (){
    radio.enableDynamicAck();
}

bool radio_isPVariant (void){
    return radio.isPVariant();
}

void radio_setAutoAck (bool enable){
    radio.setAutoAck(enable);
}

void radio_setAutoAckP(uint8_t pipe, bool enable){
    radio.setAutoAck(pipe, enable);
}

void radio_setPALevel (uint8_t level){
    radio.setPALevel(level);
}

uint8_t radio_getPALevel (void){
    return radio.getPALevel();
}

uint8_t radio_getARC (void){
    return radio.getARC();
}

bool radio_setDataRate (rf24_datarate_ec speed){
    return radio.setDataRate(speed);
}

rf24_datarate_ec radio_getDataRate (void){
    return radio.getDataRate();
}

void radio_setCRCLength (rf24_crclength_ec length){
    radio.setCRCLength(length);
}

rf24_crclength_ec radio_getCRCLength (void){
    return radio.getCRCLength();
}

void radio_disableCRC (void){
    radio.disableCRC();
}

void radio_maskIRQ (bool tx_ok, bool tx_fail, bool rx_ready){
    radio.maskIRQ(tx_ok, tx_fail, rx_ready);
}

void radio_startConstCarrier (rf24_pa_dbm_ec level, uint8_t channel){
    radio.startConstCarrier(level, channel);
}

void radio_stopConstCarrier (void){
    radio.stopConstCarrier(); 
}

void radio_toggleAllPipes (bool isEnabled){
    radio.toggleAllPipes(isEnabled);
}

void radio_setRadiation (uint8_t level, rf24_datarate_ec speed){
    radio.setRadiation(level, speed);
}
