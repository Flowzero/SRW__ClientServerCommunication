
cmake_minimum_required (VERSION 3.8)


if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(BOOST_ROOT "C:/boost_1_87_0/")
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

find_package(BOOST 1.87.0 REQUIRED COMPONENTS program_options REQUIRED)


if (Boost_FOUND)
    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
    link_directories (${Boost_LIBRARY_DIRS})
endif ()

project ("SRW__ClientServerCommunication")

add_subdirectory ("SRW__ClientServerCommunication")
