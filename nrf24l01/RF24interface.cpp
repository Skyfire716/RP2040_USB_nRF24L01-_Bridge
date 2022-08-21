#include "pico/stdlib.h"  // printf(), sleep_ms(), getchar_timeout_us(), to_us_since_boot(), get_absolute_time()
#include "pico/bootrom.h" // reset_usb_boot()
#include <RF24.h>         // RF24 radio object, rf24_min()
#include "defaultPins.h"  // board presumptive default pin numbers for CE_PIN and CSN_PIN
#include "RF24interface.h"

RF24 radio(CE_PIN, CSN_PIN);

extern "C" bool radio_begin(); 
extern "C" bool radio_isChipConnected();


bool radio_begin()
{
    return radio.begin();
}

bool radio_isChipConnected(){
    return radio.isChipConnected();
}
