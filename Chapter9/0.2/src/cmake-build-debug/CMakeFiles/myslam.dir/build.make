# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/haotian/clion-2018.1.5/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/haotian/clion-2018.1.5/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/myslam.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/myslam.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/myslam.dir/flags.make

CMakeFiles/myslam.dir/frame.cpp.o: CMakeFiles/myslam.dir/flags.make
CMakeFiles/myslam.dir/frame.cpp.o: ../frame.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/myslam.dir/frame.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myslam.dir/frame.cpp.o -c /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/frame.cpp

CMakeFiles/myslam.dir/frame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myslam.dir/frame.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/frame.cpp > CMakeFiles/myslam.dir/frame.cpp.i

CMakeFiles/myslam.dir/frame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myslam.dir/frame.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/frame.cpp -o CMakeFiles/myslam.dir/frame.cpp.s

CMakeFiles/myslam.dir/frame.cpp.o.requires:

.PHONY : CMakeFiles/myslam.dir/frame.cpp.o.requires

CMakeFiles/myslam.dir/frame.cpp.o.provides: CMakeFiles/myslam.dir/frame.cpp.o.requires
	$(MAKE) -f CMakeFiles/myslam.dir/build.make CMakeFiles/myslam.dir/frame.cpp.o.provides.build
.PHONY : CMakeFiles/myslam.dir/frame.cpp.o.provides

CMakeFiles/myslam.dir/frame.cpp.o.provides.build: CMakeFiles/myslam.dir/frame.cpp.o


CMakeFiles/myslam.dir/mappoint.cpp.o: CMakeFiles/myslam.dir/flags.make
CMakeFiles/myslam.dir/mappoint.cpp.o: ../mappoint.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/myslam.dir/mappoint.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myslam.dir/mappoint.cpp.o -c /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/mappoint.cpp

CMakeFiles/myslam.dir/mappoint.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myslam.dir/mappoint.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/mappoint.cpp > CMakeFiles/myslam.dir/mappoint.cpp.i

CMakeFiles/myslam.dir/mappoint.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myslam.dir/mappoint.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/mappoint.cpp -o CMakeFiles/myslam.dir/mappoint.cpp.s

CMakeFiles/myslam.dir/mappoint.cpp.o.requires:

.PHONY : CMakeFiles/myslam.dir/mappoint.cpp.o.requires

CMakeFiles/myslam.dir/mappoint.cpp.o.provides: CMakeFiles/myslam.dir/mappoint.cpp.o.requires
	$(MAKE) -f CMakeFiles/myslam.dir/build.make CMakeFiles/myslam.dir/mappoint.cpp.o.provides.build
.PHONY : CMakeFiles/myslam.dir/mappoint.cpp.o.provides

CMakeFiles/myslam.dir/mappoint.cpp.o.provides.build: CMakeFiles/myslam.dir/mappoint.cpp.o


CMakeFiles/myslam.dir/map.cpp.o: CMakeFiles/myslam.dir/flags.make
CMakeFiles/myslam.dir/map.cpp.o: ../map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/myslam.dir/map.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myslam.dir/map.cpp.o -c /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/map.cpp

CMakeFiles/myslam.dir/map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myslam.dir/map.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/map.cpp > CMakeFiles/myslam.dir/map.cpp.i

CMakeFiles/myslam.dir/map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myslam.dir/map.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/map.cpp -o CMakeFiles/myslam.dir/map.cpp.s

CMakeFiles/myslam.dir/map.cpp.o.requires:

.PHONY : CMakeFiles/myslam.dir/map.cpp.o.requires

CMakeFiles/myslam.dir/map.cpp.o.provides: CMakeFiles/myslam.dir/map.cpp.o.requires
	$(MAKE) -f CMakeFiles/myslam.dir/build.make CMakeFiles/myslam.dir/map.cpp.o.provides.build
.PHONY : CMakeFiles/myslam.dir/map.cpp.o.provides

CMakeFiles/myslam.dir/map.cpp.o.provides.build: CMakeFiles/myslam.dir/map.cpp.o


CMakeFiles/myslam.dir/camera.cpp.o: CMakeFiles/myslam.dir/flags.make
CMakeFiles/myslam.dir/camera.cpp.o: ../camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/myslam.dir/camera.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myslam.dir/camera.cpp.o -c /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/camera.cpp

CMakeFiles/myslam.dir/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myslam.dir/camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/camera.cpp > CMakeFiles/myslam.dir/camera.cpp.i

CMakeFiles/myslam.dir/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myslam.dir/camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/camera.cpp -o CMakeFiles/myslam.dir/camera.cpp.s

CMakeFiles/myslam.dir/camera.cpp.o.requires:

.PHONY : CMakeFiles/myslam.dir/camera.cpp.o.requires

CMakeFiles/myslam.dir/camera.cpp.o.provides: CMakeFiles/myslam.dir/camera.cpp.o.requires
	$(MAKE) -f CMakeFiles/myslam.dir/build.make CMakeFiles/myslam.dir/camera.cpp.o.provides.build
.PHONY : CMakeFiles/myslam.dir/camera.cpp.o.provides

CMakeFiles/myslam.dir/camera.cpp.o.provides.build: CMakeFiles/myslam.dir/camera.cpp.o


CMakeFiles/myslam.dir/config.cpp.o: CMakeFiles/myslam.dir/flags.make
CMakeFiles/myslam.dir/config.cpp.o: ../config.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/myslam.dir/config.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myslam.dir/config.cpp.o -c /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/config.cpp

CMakeFiles/myslam.dir/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myslam.dir/config.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/config.cpp > CMakeFiles/myslam.dir/config.cpp.i

CMakeFiles/myslam.dir/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myslam.dir/config.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/config.cpp -o CMakeFiles/myslam.dir/config.cpp.s

CMakeFiles/myslam.dir/config.cpp.o.requires:

.PHONY : CMakeFiles/myslam.dir/config.cpp.o.requires

CMakeFiles/myslam.dir/config.cpp.o.provides: CMakeFiles/myslam.dir/config.cpp.o.requires
	$(MAKE) -f CMakeFiles/myslam.dir/build.make CMakeFiles/myslam.dir/config.cpp.o.provides.build
.PHONY : CMakeFiles/myslam.dir/config.cpp.o.provides

CMakeFiles/myslam.dir/config.cpp.o.provides.build: CMakeFiles/myslam.dir/config.cpp.o


# Object files for target myslam
myslam_OBJECTS = \
"CMakeFiles/myslam.dir/frame.cpp.o" \
"CMakeFiles/myslam.dir/mappoint.cpp.o" \
"CMakeFiles/myslam.dir/map.cpp.o" \
"CMakeFiles/myslam.dir/camera.cpp.o" \
"CMakeFiles/myslam.dir/config.cpp.o"

# External object files for target myslam
myslam_EXTERNAL_OBJECTS =

libmyslam.so: CMakeFiles/myslam.dir/frame.cpp.o
libmyslam.so: CMakeFiles/myslam.dir/mappoint.cpp.o
libmyslam.so: CMakeFiles/myslam.dir/map.cpp.o
libmyslam.so: CMakeFiles/myslam.dir/camera.cpp.o
libmyslam.so: CMakeFiles/myslam.dir/config.cpp.o
libmyslam.so: CMakeFiles/myslam.dir/build.make
libmyslam.so: CMakeFiles/myslam.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX shared library libmyslam.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myslam.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/myslam.dir/build: libmyslam.so

.PHONY : CMakeFiles/myslam.dir/build

CMakeFiles/myslam.dir/requires: CMakeFiles/myslam.dir/frame.cpp.o.requires
CMakeFiles/myslam.dir/requires: CMakeFiles/myslam.dir/mappoint.cpp.o.requires
CMakeFiles/myslam.dir/requires: CMakeFiles/myslam.dir/map.cpp.o.requires
CMakeFiles/myslam.dir/requires: CMakeFiles/myslam.dir/camera.cpp.o.requires
CMakeFiles/myslam.dir/requires: CMakeFiles/myslam.dir/config.cpp.o.requires

.PHONY : CMakeFiles/myslam.dir/requires

CMakeFiles/myslam.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/myslam.dir/cmake_clean.cmake
.PHONY : CMakeFiles/myslam.dir/clean

CMakeFiles/myslam.dir/depend:
	cd /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/cmake-build-debug /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/cmake-build-debug /home/haotian/CLionProjects/Learn_SLAM/Chapter9/0.1/src/cmake-build-debug/CMakeFiles/myslam.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/myslam.dir/depend

