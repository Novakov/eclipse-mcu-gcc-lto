set(NAME app)

add_executable(${NAME}
    main.cpp
)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/link.ld)

set_property(TARGET ${NAME} APPEND_STRING PROPERTY LINK_FLAGS  "-Wl,-T${LINKER_SCRIPT}")
set_property(TARGET ${NAME} APPEND_STRING PROPERTY LINK_FLAGS  " -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${NAME}.map")

target_link_libraries(${NAME}
    PUBLIC
        emlib
)

set(BIN_FILE ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.bin)

add_custom_command(OUTPUT ${BIN_FILE}
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${NAME}> ${BIN_FILE}
    DEPENDS $<TARGET_FILE:${NAME}>
)
add_custom_target(${NAME}.dump_bin DEPENDS ${BIN_FILE})

target_compile_options(${NAME} PRIVATE "-Os")