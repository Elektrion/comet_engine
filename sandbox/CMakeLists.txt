add_executable(sandbox)
target_link_libraries(sandbox PRIVATE comet)
install(TARGETS sandbox)

target_compile_options(sandbox PRIVATE ${COMET_GLOBAL_COMPILE_OPTIONS})
target_sources(sandbox PRIVATE
  "src/main.cpp"
)
