set(NAME emlib)

add_library(${NAME} STATIC
    src/startup_efm32gg.S
    src/system_efm32gg.c
    src/em_cmu.c
    src/em_emu.c
    src/em_gpio.c
    src/em_system.c
)

target_include_directories(${NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)