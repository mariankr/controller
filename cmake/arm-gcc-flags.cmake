## compiler flags

set(CPU_FLAG -mcpu=cortex-m4)
set(FPU_FLAG -mfpu=fpv4-sp-d16)
set(FLOAT_ABI -mfloat-abi=hard)
set(MCU_FLAGS "-mthumb -mabi=aapcs ${CPU_FLAG} ${FPU_FLAG} ${FLOAT_ABI}")

set(CMAKE_C_FLAGS "${MCU_FLAGS} -fno-builtin -Wall -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-unroll-loops -ffast-math -ftree-vectorize -fstack-usage --specs=nano.specs")
set(CMAKE_CXX_FLAGS "${MCU_FLAGS} -fno-builtin -Wall -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-unroll-loops -ffast-math -ftree-vectorize -fno-threadsafe-statics -fno-use-cxa-atexit -fstack-usage --specs=nano.specs")
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} -x assembler-with-cpp --specs=nano.specs")

SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections ${MCU_FLAGS}")

SET(CMAKE_C_FLAGS_DEBUG "-O0 -g -u_printf_float -u_scanf_float")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -u_printf_float -u_scanf_float")
SET(CMAKE_ASM_FLAGS_DEBUG "-g")
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "")

SET(CMAKE_C_FLAGS_RELEASE "-Os -flto")
SET(CMAKE_CXX_FLAGS_RELEASE "-Os -flto")
SET(CMAKE_ASM_FLAGS_RELEASE "")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "-flto")