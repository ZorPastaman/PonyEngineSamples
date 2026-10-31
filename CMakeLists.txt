cmake_minimum_required (VERSION 3.31)
message(STATUS "Configuring Pony Engine sample")

# Setting variables
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# import std is still experimental in CMake. You must activate it via a special uuid.
# Refer to the CMake documentation for the correct value: https://github.com/Kitware/CMake/blob/v3.31.0/Help/dev/experimental.rst - change the version in the link to your CMake version.
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_MODULE_STD ON)

include(FetchContent)
include(ExternalProject)

# Initializing project
set(PONY_PROJECT_VERSION "${PONY_PROJECT_VERSION_MAJOR}.${PONY_PROJECT_VERSION_MINOR}.${PONY_PROJECT_VERSION_PATCH}.${PONY_PROJECT_VERSION_TWEAK}")
project("PonyEngineSample" VERSION ${PONY_PROJECT_VERSION} LANGUAGES CXX)
include("CMake/PrepareMainProject.cmake")

# Configuring Pomy Emgine
set(PONY_BUILD_MODE "Runtime")
FetchContent_Declare(
	PonyEngine
	GIT_REPOSITORY https://github.com/ZorPastaman/PonyEngine.git
	GIT_TAG develop
)
FetchContent_MakeAvailable(PonyEngine)

# Building Pony Engine Tools for the host platform
ExternalProject_Add(PonyEngineTools
	SOURCE_DIR "${PonyEngine_SOURCE_DIR}"
	BINARY_DIR "${CMAKE_BINARY_DIR}/Tools"
	CMAKE_ARGS
		-G Ninja
		-DCMAKE_BUILD_TYPE=Release
		-DCMAKE_INSTALL_PREFIX=${PONY_TOOLS_INSTALL_DIR}
		-DPONY_BUILD_MODE=Tools
	INSTALL_DIR "${PONY_TOOLS_INSTALL_DIR}"
)

# Configuring Sample
add_subdirectory(${PONY_SAMPLE_PATH})

include("CMake/EngineModulePostConfiguration.cmake")
