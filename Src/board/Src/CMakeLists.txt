## add source
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} APP_SOURCES)
target_sources(${TARGET} PUBLIC ${APP_SOURCES})
