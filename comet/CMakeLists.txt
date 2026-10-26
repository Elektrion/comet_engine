add_library(comet)
target_include_directories(comet PUBLIC "src")
install(TARGETS comet)

target_compile_options(comet PRIVATE ${COMET_GLOBAL_COMPILE_OPTIONS})
target_sources(comet PUBLIC FILE_SET HEADERS FILES
	"src/comet_std_include.hpp"
)
target_sources(comet PUBLIC FILE_SET CXX_MODULES FILES
	"src/comet.ixx"
	"src/application/application.ixx"
	"src/application/application-component.ixx"
)
