# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild

# Utility rule file for pico_sdk-populate.

# Include any custom commands dependencies for this target.
include CMakeFiles/pico_sdk-populate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pico_sdk-populate.dir/progress.make

CMakeFiles/pico_sdk-populate: CMakeFiles/pico_sdk-populate-complete

CMakeFiles/pico_sdk-populate-complete: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-install
CMakeFiles/pico_sdk-populate-complete: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-mkdir
CMakeFiles/pico_sdk-populate-complete: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-download
CMakeFiles/pico_sdk-populate-complete: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-update
CMakeFiles/pico_sdk-populate-complete: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-patch
CMakeFiles/pico_sdk-populate-complete: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-configure
CMakeFiles/pico_sdk-populate-complete: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-build
CMakeFiles/pico_sdk-populate-complete: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-install
CMakeFiles/pico_sdk-populate-complete: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'pico_sdk-populate'"
	/usr/bin/cmake -E make_directory /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/CMakeFiles
	/usr/bin/cmake -E touch /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/CMakeFiles/pico_sdk-populate-complete
	/usr/bin/cmake -E touch /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-done

pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-update:
.PHONY : pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-update

pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-build: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No build step for 'pico_sdk-populate'"
	cd /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-build && /usr/bin/cmake -E echo_append
	cd /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-build && /usr/bin/cmake -E touch /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-build

pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-configure: pico_sdk-populate-prefix/tmp/pico_sdk-populate-cfgcmd.txt
pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-configure: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "No configure step for 'pico_sdk-populate'"
	cd /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-build && /usr/bin/cmake -E echo_append
	cd /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-build && /usr/bin/cmake -E touch /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-configure

pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-download: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-gitinfo.txt
pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-download: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'pico_sdk-populate'"
	cd /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps && /usr/bin/cmake -P /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/tmp/pico_sdk-populate-gitclone.cmake
	cd /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps && /usr/bin/cmake -E touch /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-download

pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-install: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'pico_sdk-populate'"
	cd /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-build && /usr/bin/cmake -E echo_append
	cd /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-build && /usr/bin/cmake -E touch /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-install

pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'pico_sdk-populate'"
	/usr/bin/cmake -Dcfgdir= -P /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/tmp/pico_sdk-populate-mkdirs.cmake
	/usr/bin/cmake -E touch /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-mkdir

pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-patch: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'pico_sdk-populate'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-patch

pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-update:
.PHONY : pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-update

pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-test: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'pico_sdk-populate'"
	cd /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-build && /usr/bin/cmake -E echo_append
	cd /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-build && /usr/bin/cmake -E touch /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-test

pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-update: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Performing update step for 'pico_sdk-populate'"
	cd /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-src && /usr/bin/cmake -P /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/pico_sdk-populate-prefix/tmp/pico_sdk-populate-gitupdate.cmake

pico_sdk-populate: CMakeFiles/pico_sdk-populate
pico_sdk-populate: CMakeFiles/pico_sdk-populate-complete
pico_sdk-populate: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-build
pico_sdk-populate: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-configure
pico_sdk-populate: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-download
pico_sdk-populate: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-install
pico_sdk-populate: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-mkdir
pico_sdk-populate: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-patch
pico_sdk-populate: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-test
pico_sdk-populate: pico_sdk-populate-prefix/src/pico_sdk-populate-stamp/pico_sdk-populate-update
pico_sdk-populate: CMakeFiles/pico_sdk-populate.dir/build.make
.PHONY : pico_sdk-populate

# Rule to build all files generated by this target.
CMakeFiles/pico_sdk-populate.dir/build: pico_sdk-populate
.PHONY : CMakeFiles/pico_sdk-populate.dir/build

CMakeFiles/pico_sdk-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pico_sdk-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pico_sdk-populate.dir/clean

CMakeFiles/pico_sdk-populate.dir/depend:
	cd /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild /home/jonas/Nextcloud/TUMHiWiStelle/TennisSchläger/RP2040_USB_nRF24L01-_Bridge/build/_deps/pico_sdk-subbuild/CMakeFiles/pico_sdk-populate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pico_sdk-populate.dir/depend

