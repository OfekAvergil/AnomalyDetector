# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /home/ofek/clion-2021.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/ofek/clion-2021.2.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ofek/Documents

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ofek/Documents/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AnomalyDetector.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/AnomalyDetector.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AnomalyDetector.dir/flags.make

CMakeFiles/AnomalyDetector.dir/anomaly_detection_util.cpp.o: CMakeFiles/AnomalyDetector.dir/flags.make
CMakeFiles/AnomalyDetector.dir/anomaly_detection_util.cpp.o: ../anomaly_detection_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ofek/Documents/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AnomalyDetector.dir/anomaly_detection_util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AnomalyDetector.dir/anomaly_detection_util.cpp.o -c /home/ofek/Documents/anomaly_detection_util.cpp

CMakeFiles/AnomalyDetector.dir/anomaly_detection_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnomalyDetector.dir/anomaly_detection_util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ofek/Documents/anomaly_detection_util.cpp > CMakeFiles/AnomalyDetector.dir/anomaly_detection_util.cpp.i

CMakeFiles/AnomalyDetector.dir/anomaly_detection_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnomalyDetector.dir/anomaly_detection_util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ofek/Documents/anomaly_detection_util.cpp -o CMakeFiles/AnomalyDetector.dir/anomaly_detection_util.cpp.s

CMakeFiles/AnomalyDetector.dir/timeseries.cpp.o: CMakeFiles/AnomalyDetector.dir/flags.make
CMakeFiles/AnomalyDetector.dir/timeseries.cpp.o: ../timeseries.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ofek/Documents/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AnomalyDetector.dir/timeseries.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AnomalyDetector.dir/timeseries.cpp.o -c /home/ofek/Documents/timeseries.cpp

CMakeFiles/AnomalyDetector.dir/timeseries.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnomalyDetector.dir/timeseries.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ofek/Documents/timeseries.cpp > CMakeFiles/AnomalyDetector.dir/timeseries.cpp.i

CMakeFiles/AnomalyDetector.dir/timeseries.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnomalyDetector.dir/timeseries.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ofek/Documents/timeseries.cpp -o CMakeFiles/AnomalyDetector.dir/timeseries.cpp.s

CMakeFiles/AnomalyDetector.dir/SimpleAnomalyDetector.cpp.o: CMakeFiles/AnomalyDetector.dir/flags.make
CMakeFiles/AnomalyDetector.dir/SimpleAnomalyDetector.cpp.o: ../SimpleAnomalyDetector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ofek/Documents/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/AnomalyDetector.dir/SimpleAnomalyDetector.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AnomalyDetector.dir/SimpleAnomalyDetector.cpp.o -c /home/ofek/Documents/SimpleAnomalyDetector.cpp

CMakeFiles/AnomalyDetector.dir/SimpleAnomalyDetector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnomalyDetector.dir/SimpleAnomalyDetector.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ofek/Documents/SimpleAnomalyDetector.cpp > CMakeFiles/AnomalyDetector.dir/SimpleAnomalyDetector.cpp.i

CMakeFiles/AnomalyDetector.dir/SimpleAnomalyDetector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnomalyDetector.dir/SimpleAnomalyDetector.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ofek/Documents/SimpleAnomalyDetector.cpp -o CMakeFiles/AnomalyDetector.dir/SimpleAnomalyDetector.cpp.s

# Object files for target AnomalyDetector
AnomalyDetector_OBJECTS = \
"CMakeFiles/AnomalyDetector.dir/anomaly_detection_util.cpp.o" \
"CMakeFiles/AnomalyDetector.dir/timeseries.cpp.o" \
"CMakeFiles/AnomalyDetector.dir/SimpleAnomalyDetector.cpp.o"

# External object files for target AnomalyDetector
AnomalyDetector_EXTERNAL_OBJECTS =

AnomalyDetector: CMakeFiles/AnomalyDetector.dir/anomaly_detection_util.cpp.o
AnomalyDetector: CMakeFiles/AnomalyDetector.dir/timeseries.cpp.o
AnomalyDetector: CMakeFiles/AnomalyDetector.dir/SimpleAnomalyDetector.cpp.o
AnomalyDetector: CMakeFiles/AnomalyDetector.dir/build.make
AnomalyDetector: CMakeFiles/AnomalyDetector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ofek/Documents/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable AnomalyDetector"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AnomalyDetector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AnomalyDetector.dir/build: AnomalyDetector
.PHONY : CMakeFiles/AnomalyDetector.dir/build

CMakeFiles/AnomalyDetector.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AnomalyDetector.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AnomalyDetector.dir/clean

CMakeFiles/AnomalyDetector.dir/depend:
	cd /home/ofek/Documents/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ofek/Documents /home/ofek/Documents /home/ofek/Documents/cmake-build-debug /home/ofek/Documents/cmake-build-debug /home/ofek/Documents/cmake-build-debug/CMakeFiles/AnomalyDetector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AnomalyDetector.dir/depend

