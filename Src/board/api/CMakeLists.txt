## add source
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} API_SOURCES)
target_sources(${TARGET} PUBLIC ${API_SOURCES})
