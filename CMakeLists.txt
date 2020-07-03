cmake_minimum_required(VERSION 3.5)
include(${CMAKE_SOURCE_DIR}/cmake/arm-gcc-toolchain.cmake)

project(cmake_example C CXX ASM)

set(TARGET ${PROJECT_NAME}.elf)
set(TARGET_BASE_NAME ${PROJECT_NAME})

## compile flags
include(${CMAKE_SOURCE_DIR}/cmake/arm-gcc-flags.cmake)

## CONFIGS
set(STM32_DEVICE "STM32L452xx")
string(SUBSTRING ${STM32_DEVICE} 0 7 STM32_FAMILY) # get device family, eg: STM32L4
string(TOLOWER ${STM32_DEVICE} STM32_DEVICE_LOWER)

### files
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/aux/STM32L452RETxP_FLASH.ld")    # linker scipt
set(CORTEXM4_MATH "${CMAKE_SOURCE_DIR}/aux/libarm_cortexM4lf_math.a")   # cortex m4 math library
set(CMSIS_STARTUP_SOURCE "${CMAKE_SOURCE_DIR}/aux/startup_${STM32_DEVICE_LOWER}.s") # startup file

### CMSIS
set(CMSIS_COMMON_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include")
set(CMSIS_DEVICE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/${STM32_FAMILY}xx/Include")
set(CMSIS_INCLUDE_DIR ${CMSIS_COMMON_INCLUDE_DIR} ${CMSIS_DEVICE_INCLUDE_DIR})

### HAL
set(HAL_INCLUDE_DIR 
    "${CMAKE_SOURCE_DIR}/Drivers/${STM32_FAMILY}xx_HAL_Driver/Inc" 
    "${CMAKE_SOURCE_DIR}/Drivers/${STM32_FAMILY}xx_HAL_Driver/Inc/Legacy"
)


## enabling c++
set(LD_FLAGS "--specs=nosys.specs -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LD_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")

## target executable
add_executable(${TARGET})

## adding sources
target_sources(${TARGET} PUBLIC ${CMSIS_STARTUP_SOURCE})
add_subdirectory(src/application)
add_subdirectory(src/board)

target_include_directories(${TARGET} PUBLIC 
    ${HAL_INCLUDE_DIR} 
    ${CMSIS_INCLUDE_DIR}
    "${CMAKE_SOURCE_DIR}/Inc"
)
target_compile_definitions(${TARGET} PUBLIC 
    "USE_HAL_DRIVER" 
    ${STM32_DEVICE}
)

set_target_properties(${TARGET} PROPERTIES LINK_OPTIONS -T${LINKER_SCRIPT})
set_target_properties(${TARGET} PROPERTIES CXX_STANDARD 14)
set_target_properties(${TARGET} PROPERTIES C_STANDARD 11)

## custom target
add_custom_target(${TARGET_BASE_NAME}.hex 
    DEPENDS ${TARGET} 
    COMMAND ${CMAKE_OBJCOPY} -Oihex ${TARGET} ${TARGET_BASE_NAME}.hex
)
add_custom_target(${TARGET_BASE_NAME}.bin 
    DEPENDS ${TARGET} 
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${TARGET} ${TARGET_BASE_NAME}.bin
)
add_custom_command(TARGET ${TARGET} POST_BUILD 
    COMMAND ${CMAKE_SIZE_UTIL} ${TARGET}
)

add_custom_target(flash
    DEPENDS ${TARGET} 
    COMMAND openocd 
        -f $ENV{OPENOCD_ROOT}/scripts/interface/stlink.cfg 
        -f $ENV{OPENOCD_ROOT}/scripts/target/stm32l4x.cfg 
        -c 'program ${CMAKE_SOURCE_DIR}/build/${TARGET} verify reset exit'
)