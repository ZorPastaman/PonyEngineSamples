add_library(Sample STATIC)

# Set includes and sources.
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
	"Source/Game-GameTicker.cppm"
	"Source/Game-GameModule.cppm"
)

set_target_properties(Sample PROPERTIES 
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(Sample PUBLIC 
	PonyEngine.Application
)
target_link_libraries(Sample PRIVATE
	PonyEngine.Core
	PonyEngine.Job
	PonyEngine.Log
)
