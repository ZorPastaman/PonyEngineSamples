add_library(Sample STATIC)

target_include_directories(Sample PUBLIC
	"Include/Public"
)
target_sources(Sample PUBLIC
	"Source/Launch.cpp"
)
target_sources(Sample PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(Sample PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Game.cppm"
)

set_target_properties(Sample PROPERTIES 
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(Sample PUBLIC 
	PonyEngine.Application
)
target_link_libraries(Sample PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Resource
	PonyEngine.Resource.Pack
)

# Compiling resources.
# Making a list of load manifests. One asset may have as many loads as it needs.
pony_add_resource_load("${CMAKE_CURRENT_LIST_DIR}/Assets/TextLoadParams.toml" "${CMAKE_BINARY_DIR}/Resources/TextLoad.bin" TEXT_LOAD)
# Compiling a text asset into a resource. It produces one resource data file and as many resource load files as load manifests were added to the variable TEXT_LOAD.
pony_compile_text("${CMAKE_CURRENT_LIST_DIR}/Assets/Text.txt" "${CMAKE_CURRENT_LIST_DIR}/Assets/TextDataParams.toml" "${CMAKE_BINARY_DIR}/Resources/TextData.bin" "${TEXT_LOAD}"
	ADDITIONAL_DEPENDENCIES PonyEngineTools
)

# Packing resources.
# Making a resource list for packing.
file(REMOVE "${CMAKE_BINARY_DIR}/ResourceLists/TextList.txt")
# Every resource is just a unique ID, resource data and resource load.
pony_add_resource("Text" "${CMAKE_BINARY_DIR}/Resources/TextData.bin" "${CMAKE_BINARY_DIR}/Resources/TextLoad.bin" "${CMAKE_BINARY_DIR}/ResourceLists/TextList.txt")
# Making a list of pack manifests. One pack may be made with as many manifests as it needs.
pony_add_pack_manifest("${CMAKE_BINARY_DIR}/ResourceLists/TextList.txt" "${CMAKE_CURRENT_LIST_DIR}/Assets/PackManifestParams.toml" "${CMAKE_BINARY_DIR}/Packs/TextPackManifest.bin"
	PACK_MANIFEST)
# Packing a resource list. It produces one pack data file and as many pack manifests as pack manifests were added to the variable PACK_MANIFEST.
pony_pack_resources("${CMAKE_CURRENT_LIST_DIR}/Assets/PackDataParams.toml" "${CMAKE_BINARY_DIR}/Packs/TextPackData.bin" "${PACK_MANIFEST}"
	ADDITIONAL_DEPENDENCIES PonyEngineTools
)

# Making custom targets for CMake.
add_custom_target(Resources DEPENDS
	"${CMAKE_BINARY_DIR}/Resources/TextData.bin" "${CMAKE_BINARY_DIR}/Resources/TextLoad.bin"
)
add_custom_target(Packs DEPENDS
	Resources
	"${CMAKE_BINARY_DIR}/Packs/TextPackData.bin" "${CMAKE_BINARY_DIR}/Packs/TextPackManifest.bin"
)
add_dependencies(Sample Packs)

# Installing packs.
install(FILES "${CMAKE_BINARY_DIR}/Packs/TextPackData.bin" "${CMAKE_BINARY_DIR}/Packs/TextPackManifest.bin" DESTINATION "Packs")

