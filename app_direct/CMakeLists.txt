set(NAME app_direct)

set(EMLIB ${CMAKE_SOURCE_DIR}/libs/emlib)

add_executable(${NAME}
    main.cpp
    ${EMLIB}/src/startup_efm32gg.S
    ${EMLIB}/src/system_efm32gg.c
    ${EMLIB}/src/em_cmu.c
    ${EMLIB}/src/em_emu.c
    ${EMLIB}/src/em_gpio.c
    ${EMLIB}/src/em_system.c
)

target_include_directories(${NAME}
    PUBLIC
        ${EMLIB}/inc
)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/link.ld)

set_property(TARGET ${NAME} APPEND_STRING PROPERTY LINK_FLAGS  "-Wl,-T${LINKER_SCRIPT}")
set_property(TARGET ${NAME} APPEND_STRING PROPERTY LINK_FLAGS  " -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${NAME}.map")
set_property(TARGET ${NAME} APPEND_STRING PROPERTY LINK_FLAGS  "-Os")

set(BIN_FILE ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.bin)

add_custom_command(OUTPUT ${BIN_FILE}
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${NAME}> ${BIN_FILE}
    DEPENDS $<TARGET_FILE:${NAME}>
)
add_custom_target(${NAME}.dump_bin DEPENDS ${BIN_FILE})
