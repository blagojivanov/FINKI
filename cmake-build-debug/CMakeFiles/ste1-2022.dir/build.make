# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\Blagoj\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8214.51\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Blagoj\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8214.51\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Blagoj\CLionProjects\FINKI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Blagoj\CLionProjects\FINKI\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ste1-2022.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ste1-2022.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ste1-2022.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ste1-2022.dir/flags.make

CMakeFiles/ste1-2022.dir/SP/Vezbi_II_Kol/ste1-2022.c.obj: CMakeFiles/ste1-2022.dir/flags.make
CMakeFiles/ste1-2022.dir/SP/Vezbi_II_Kol/ste1-2022.c.obj: C:/Users/Blagoj/CLionProjects/FINKI/SP/Vezbi_II_Kol/ste1-2022.c
CMakeFiles/ste1-2022.dir/SP/Vezbi_II_Kol/ste1-2022.c.obj: CMakeFiles/ste1-2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Blagoj\CLionProjects\FINKI\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ste1-2022.dir/SP/Vezbi_II_Kol/ste1-2022.c.obj"
	C:\Users\Blagoj\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8214.51\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ste1-2022.dir/SP/Vezbi_II_Kol/ste1-2022.c.obj -MF CMakeFiles\ste1-2022.dir\SP\Vezbi_II_Kol\ste1-2022.c.obj.d -o CMakeFiles\ste1-2022.dir\SP\Vezbi_II_Kol\ste1-2022.c.obj -c C:\Users\Blagoj\CLionProjects\FINKI\SP\Vezbi_II_Kol\ste1-2022.c

CMakeFiles/ste1-2022.dir/SP/Vezbi_II_Kol/ste1-2022.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ste1-2022.dir/SP/Vezbi_II_Kol/ste1-2022.c.i"
	C:\Users\Blagoj\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8214.51\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Blagoj\CLionProjects\FINKI\SP\Vezbi_II_Kol\ste1-2022.c > CMakeFiles\ste1-2022.dir\SP\Vezbi_II_Kol\ste1-2022.c.i

CMakeFiles/ste1-2022.dir/SP/Vezbi_II_Kol/ste1-2022.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ste1-2022.dir/SP/Vezbi_II_Kol/ste1-2022.c.s"
	C:\Users\Blagoj\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8214.51\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Blagoj\CLionProjects\FINKI\SP\Vezbi_II_Kol\ste1-2022.c -o CMakeFiles\ste1-2022.dir\SP\Vezbi_II_Kol\ste1-2022.c.s

# Object files for target ste1-2022
ste1__2022_OBJECTS = \
"CMakeFiles/ste1-2022.dir/SP/Vezbi_II_Kol/ste1-2022.c.obj"

# External object files for target ste1-2022
ste1__2022_EXTERNAL_OBJECTS =

ste1-2022.exe: CMakeFiles/ste1-2022.dir/SP/Vezbi_II_Kol/ste1-2022.c.obj
ste1-2022.exe: CMakeFiles/ste1-2022.dir/build.make
ste1-2022.exe: CMakeFiles/ste1-2022.dir/linklibs.rsp
ste1-2022.exe: CMakeFiles/ste1-2022.dir/objects1.rsp
ste1-2022.exe: CMakeFiles/ste1-2022.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Blagoj\CLionProjects\FINKI\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ste1-2022.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ste1-2022.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ste1-2022.dir/build: ste1-2022.exe
.PHONY : CMakeFiles/ste1-2022.dir/build

CMakeFiles/ste1-2022.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ste1-2022.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ste1-2022.dir/clean

CMakeFiles/ste1-2022.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Blagoj\CLionProjects\FINKI C:\Users\Blagoj\CLionProjects\FINKI C:\Users\Blagoj\CLionProjects\FINKI\cmake-build-debug C:\Users\Blagoj\CLionProjects\FINKI\cmake-build-debug C:\Users\Blagoj\CLionProjects\FINKI\cmake-build-debug\CMakeFiles\ste1-2022.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ste1-2022.dir/depend

