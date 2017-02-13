cmake_minimum_required(VERSION 3.6)
project(bluebird CXX C ASM)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


add_definitions(-DSTM32F107xC)
add_definitions(-mcpu=cortex-m3)
add_definitions(-DDEBUG )


include_directories(Drivers/CMSIS/Include)
include_directories(Drivers/CMSIS/Device/ST/STM32F1xx/Include)
include_directories(Inc)
include_directories(Drivers/STM32F1xx_HAL_Driver/Inc)

# FreeRTOS
include_directories(Middlewares/Third_Party/FreeRTOS/Source/include)
include_directories(Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3)
include_directories(Middlewares/Third_Party/CMSIS_RTOS)

# ViewTool Ficus F107 BSP
include_directories(BSP/VIEWTOOL_F107)

# libuavcan
include_directories(libuavcan/libuavcan/include)
include_directories(libuavcan/libuavcan/include/dsdlc_generated)
include_directories(libuavcan/libuavcan_drivers/stm32/driver/include)


add_definitions(-DUAVCAN_PLATFORM=stm32)
add_definitions(-DUAVCAN_STM32_FREERTOS=1)
add_definitions(-DUAVCAN_STM32_NUM_IFACES=1) # TODO make 2
#add_definitions(-DUAVCAN_USE_EXTERNAL_SNPRINTF=1)

add_definitions(-DUAVCAN_STM32_TIMER_NUMBER=3) # TODO check this TIM

set(UAVCAN_FILES
        libuavcan/libuavcan/src/driver/uc_can.cpp
        libuavcan/libuavcan/src/marshal/uc_bit_array_copy.cpp
        libuavcan/libuavcan/src/marshal/uc_bit_stream.cpp
        libuavcan/libuavcan/src/marshal/uc_float_spec.cpp
        libuavcan/libuavcan/src/marshal/uc_scalar_codec.cpp
        libuavcan/libuavcan/src/node/uc_generic_publisher.cpp
        libuavcan/libuavcan/src/node/uc_generic_subscriber.cpp
        libuavcan/libuavcan/src/node/uc_global_data_type_registry.cpp
        libuavcan/libuavcan/src/node/uc_scheduler.cpp
        libuavcan/libuavcan/src/node/uc_service_client.cpp
        libuavcan/libuavcan/src/node/uc_timer.cpp
        libuavcan/libuavcan/src/protocol/uc_dynamic_node_id_client.cpp
        libuavcan/libuavcan/src/protocol/uc_node_status_provider.cpp
        libuavcan/libuavcan/src/transport/uc_can_acceptance_filter_configurator.cpp
        libuavcan/libuavcan/src/transport/uc_can_io.cpp
        libuavcan/libuavcan/src/transport/uc_crc.cpp
        libuavcan/libuavcan/src/transport/uc_dispatcher.cpp
        libuavcan/libuavcan/src/transport/uc_frame.cpp
        libuavcan/libuavcan/src/transport/uc_outgoing_transfer_registry.cpp
        libuavcan/libuavcan/src/transport/uc_transfer.cpp
        libuavcan/libuavcan/src/transport/uc_transfer_buffer.cpp
        libuavcan/libuavcan/src/transport/uc_transfer_listener.cpp
        libuavcan/libuavcan/src/transport/uc_transfer_receiver.cpp
        libuavcan/libuavcan/src/transport/uc_transfer_sender.cpp
        libuavcan/libuavcan/src/transport/uc_outgoing_transfer_registry.cpp
        libuavcan/libuavcan/src/uc_data_type.cpp
        libuavcan/libuavcan/src/uc_dynamic_memory.cpp
        libuavcan/libuavcan/src/uc_error.cpp

        libuavcan/libuavcan_drivers/stm32/driver/src/uc_stm32_can.cpp
        libuavcan/libuavcan_drivers/stm32/driver/src/uc_stm32_clock.cpp
        libuavcan/libuavcan_drivers/stm32/driver/src/uc_stm32_thread.cpp
        libuavcan/libuavcan_drivers/stm32/driver/src/libstubs.cpp)

set(SOURCE_FILES
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_can.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
#    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
#    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c
#    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi_ex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
    Middlewares/Third_Party/CMSIS_RTOS/cmsis_os.c
    Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c
#    Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    Middlewares/Third_Party/FreeRTOS/Source/croutine.c
    Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
    Middlewares/Third_Party/FreeRTOS/Source/list.c
    Middlewares/Third_Party/FreeRTOS/Source/queue.c
    Middlewares/Third_Party/FreeRTOS/Source/tasks.c
    Middlewares/Third_Party/FreeRTOS/Source/timers.c
    BSP/VIEWTOOL_F107/stm32f107_viewtool.c
    Src/can.c
    Src/freertos.c
    Src/gpio.c
    Src/i2c.c
    Src/main.c
#    Src/spi.c
    Src/stm32f1xx_hal_msp.c
    Src/stm32f1xx_hal_timebase_TIM.c
    Src/stm32f1xx_it.c
    Src/system_stm32f1xx.c
    Src/tim.c
    Src/usart.c
    startup/startup_stm32f107xc.s
        Src/can_reader_task.cpp)

add_executable(bluebird ${SOURCE_FILES} ${UAVCAN_FILES})

add_executable(${PROJECT_NAME}.elf ${UAVCAN_FILES} ${SOURCE_FILES} ${LINKER_SCRIPT})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.map")
set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.bin)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")