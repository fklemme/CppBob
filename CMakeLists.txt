cmake_minimum_required(VERSION 3.11)

# Program name
project(cppbob)

# Define target
add_executable(${PROJECT_NAME})

# Use modern C++
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
# (Do not set C++ standard globally as SFML 2.5 is still using std::auto_ptr which has been removed in C++17)

# Add sources and include directory
file(GLOB_RECURSE hdr "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE src "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_sources(${PROJECT_NAME} PRIVATE ${hdr} PRIVATE ${src})
# For Visual Studio filters
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Header Files" FILES ${hdr})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files" FILES ${src})

if(WIN32)
	# Wordaround: Put Exe and Dlls into same directory, so they are found at run-time.
    set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

# TODO: There should be a cleaner solution for this!?
#       (I think this is only needed when not using default CMake)
#list(APPEND CMAKE_MODULE_PATH /usr/share/SFML/cmake/Modules)

# SFML
find_package(SFML 2 COMPONENTS system window graphics audio QUIET)
if(NOT SFML_FOUND)
    message(STATUS "SFML not found. Fetching from Github...")
    include(FetchContent)
    FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
    )
    if(${CMAKE_VERSION} VERSION_LESS 3.14)
        # CMake 3.11+
        FetchContent_GetProperties(sfml)
        if(NOT sfml_POPULATED)
            FetchContent_Populate(sfml)
            add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
        endif()
    else()
        # CMake 3.14+
        FetchContent_MakeAvailable(sfml)
    endif()
endif()
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)

# Threads, also used by SFML
find_package(Threads REQUIRED)
if(Threads_FOUND)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
endif()

if(WIN32)
	# Wordaround: Put Exe and Dlls into same directory, so they are found at run-time.
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        file(COPY ${sfml_SOURCE_DIR}/extlibs/bin/x64/openal32.dll
		     DESTINATION ${CMAKE_BINARY_DIR})
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        file(COPY ${sfml_SOURCE_DIR}/extlibs/bin/x86/openal32.dll
		     DESTINATION ${CMAKE_BINARY_DIR})
    endif()
endif()

# Copy game resources to build directory.
file(COPY resources DESTINATION .)
