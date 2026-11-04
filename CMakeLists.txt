cmake_minimum_required (VERSION 3.31)
message(STATUS "Configuring Pony Engine sample")

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
include("CMake/Tools.cmake")

# Configuring Sample
add_subdirectory(${PONY_SAMPLE_PATH})

# Post configuration
include("CMake/EngineModulePostConfiguration.cmake")
