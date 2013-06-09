INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/libmeego-panel
    ${MX_INCLUDE_DIRS}
    ${DBUS_INCLUDE_DIRS}
    )
ADD_DEFINITIONS(-DTHEMEDIR="${MUTTER_MEEGO_THEME_DIR}")
ADD_DEFINITIONS(-DCSS_DIR=".")

SET (PROGRAMS test)

SET(PROGRAM_SRCS
#    test-panel-clutter.c
#    test-content-pane.c
#     test-entry.c //failed
#     test-icon-theme.c
#     test-panel-gtk.c
     test-entry.c
    )

SET(PROGRAM_HEADERS
    )

ADD_EXECUTABLE(${PROGRAMS} ${PROGRAM_SRCS} ${PROGRAM_HEADERS})

   
TARGET_LINK_LIBRARIES(${PROGRAMS}
    meego-panel
    )

INSTALL(TARGETS ${PROGRAMS} RUNTIME DESTINATION ${PKG_BINDIR})

