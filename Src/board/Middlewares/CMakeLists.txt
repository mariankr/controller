## add source
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/ MIDDLEWARE_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F MIDDLEWARE_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/portable/MemMang MIDDLEWARE_SOURCES)
target_sources(${TARGET} PUBLIC ${MIDDLEWARE_SOURCES})
