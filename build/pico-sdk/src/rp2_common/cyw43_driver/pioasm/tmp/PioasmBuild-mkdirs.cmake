# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-src/tools/pioasm"
  "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/pioasm"
  "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm"
  "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/tmp"
  "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src"
  "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
