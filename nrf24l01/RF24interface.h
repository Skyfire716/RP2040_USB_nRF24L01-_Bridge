#ifndef RF24INTERFACE_H // include guard
#define RF24INTERFACE_H


typedef enum
{
    CRF24_PA_MIN = 0,
    CRF24_PA_LOW,
    CRF24_PA_HIGH,
    CRF24_PA_MAX,
    CRF24_PA_ERROR
} rf24_pa_dbm_ec;
 
typedef enum
{
    CRF24_1MBPS = 0,
    CRF24_2MBPS,
    CRF24_250KBPS
} rf24_datarate_ec;
 
typedef enum
{
    CRF24_CRC_DISABLED = 0,
    CRF24_CRC_8,
    CRF24_CRC_16
} rf24_crclength_ec;

#endif /* RF24INTERFACE_H */
