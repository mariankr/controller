## add source
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src DEVICE_SOURCES)
target_sources(${TARGET} PUBLIC ${DEVICE_SOURCES})
