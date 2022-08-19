add_executable(nrf24l01
        nrf24l01.cpp
        )

include(../lib/RF24/CMakeLists.txt)

# pull in common dependencies
target_link_libraries(nrf24l01 PRIVATE pico_stdlib hardware_resets hardware_irq hardware_spi RF24)

# create map/bin/hex file etc.
pico_add_extra_outputs(nrf24l01)

