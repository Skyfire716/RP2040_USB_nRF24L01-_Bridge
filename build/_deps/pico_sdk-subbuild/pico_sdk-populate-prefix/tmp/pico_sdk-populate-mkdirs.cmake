# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-src"
  "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-build"
  "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix"
  "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/tmp"
  "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp"
  "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src"
  "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/jonas/Tennisschlaeger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
