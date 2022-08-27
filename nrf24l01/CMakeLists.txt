add_executable(nrf24l01
        nrf24l01.c
        RF24interface.cpp
        )

# pull in common dependencies
target_link_libraries(nrf24l01 PRIVATE pico_stdlib pico_multicore hardware_resets hardware_irq hardware_spi RF24)

# create map/bin/hex file etc.
pico_add_extra_outputs(nrf24l01)

