# CMakeList.txt : CMakeLists.txt for Lab1
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Add source to this project's executable.
add_executable (Lab1 "main.cpp" "replace.cpp" "stream_processor.cpp")
   
   # Rename the executable to replace.exe
   set_target_properties(Lab1 PROPERTIES OUTPUT_NAME "replace")
   
   if (CMAKE_VERSION VERSION_GREATER 3.12)
     set_property(TARGET Lab1 PROPERTY CXX_STANDARD 20)
   endif()