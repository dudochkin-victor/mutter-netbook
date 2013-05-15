FIND_PACKAGE(ZLIB REQUIRED)

SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 0)
SET(VERSION_PATCH 0)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/libmeego-panel
    ${GCONF_INCLUDE_DIRS}
    ${MUTTER_INCLUDE_DIRS}
    ${MX_INCLUDE_DIRS}
    ${SN_INCLUDE_DIRS}
    )

SET (LIBRARY meego-netbook)

SET(LIBRARY_SRCS
        mnb-enum-types.c
        meego-netbook.c
        meego-netbook-constraints.c
        meego-netbook-mutter-hints.c
        mnb-spinner.c
        marshal.c
        mnb-input-manager.c
        mnb-toolbar.c
        mnb-toolbar-applet.c
        mnb-toolbar-button.c
        mnb-toolbar-icon.c
        mnb-toolbar-clock.c
        mnb-panel.c
        mnb-panel-frame.c
        mnb-panel-oop.c
    )

SET(LIBRARY_HEADERS
        ${CMAKE_CURRENT_BINARY_DIR}/marshal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../libmeego-panel/meego-panel/mpl-panel-common.h
        ${CMAKE_CURRENT_SOURCE_DIR}/meego-netbook.h
        ${CMAKE_CURRENT_SOURCE_DIR}/meego-netbook-constraints.h
        ${CMAKE_CURRENT_SOURCE_DIR}/meego-netbook-mutter-hints.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mnb-spinner.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mnb-input-manager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mnb-toolbar.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mnb-toolbar-applet.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mnb-toolbar-button.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mnb-toolbar-clock.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mnb-toolbar-icon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mnb-panel.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mnb-panel-frame.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mnb-panel-oop.h

)
SET(MARSHALS
        ${CMAKE_CURRENT_BINARY_DIR}/marshal.h
        ${CMAKE_CURRENT_BINARY_DIR}/marshal.c
)

SET(DBUS_GLUE
        ${CMAKE_CURRENT_BINARY_DIR}/mnb-panel-dbus-glue.h
        ${CMAKE_CURRENT_BINARY_DIR}/mnb-toolbar-dbus-glue.h
        ${CMAKE_CURRENT_BINARY_DIR}/mnb-panel-dbus-bindings.h
        ${CMAKE_CURRENT_BINARY_DIR}/mnb-toolbar-dbus-bindings.h
)

########### Add enum target ###############
ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mnb-enum-types.h
   COMMAND glib-mkenums --template ${CMAKE_SOURCE_DIR}/src/mnb-enum-types.h.in ${LIBRARY_HEADERS} ${PRIVATE_HEADERS} > ${CMAKE_CURRENT_BINARY_DIR}/mnb-enum-types.h
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/marshal.h
   )

ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mnb-enum-types.c
   COMMAND glib-mkenums --template ${CMAKE_SOURCE_DIR}/src/mnb-enum-types.c.in ${LIBRARY_HEADERS} ${PRIVATE_HEADERS} > ${CMAKE_CURRENT_BINARY_DIR}/mnb-enum-types.c
   DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/mnb-enum-types.h
   )

########### Add marshal target ###############
ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/marshal.h
   COMMAND glib-genmarshal --prefix=meego_netbook_marshal --header ${CMAKE_SOURCE_DIR}/src/marshal.list > ${CMAKE_CURRENT_BINARY_DIR}/marshal.h
   )

ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/marshal.c
   COMMAND glib-genmarshal --prefix=meego_netbook_marshal --body ${CMAKE_SOURCE_DIR}/src/marshal.list --body > ${CMAKE_CURRENT_BINARY_DIR}/marshal.c
   DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/marshal.h
   )

########### Add dbus target ###############
ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mnb-panel-dbus-glue.h
   COMMAND dbus-binding-tool --mode=glib-server --output=${CMAKE_CURRENT_BINARY_DIR}/mnb-panel-dbus-glue.h --prefix=mnb_panel_dbus ${CMAKE_SOURCE_DIR}/src/mnb-panel-dbus.xml
   )

ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mnb-toolbar-dbus-glue.h
   COMMAND dbus-binding-tool --mode=glib-server --output=${CMAKE_CURRENT_BINARY_DIR}/mnb-toolbar-dbus-glue.h --prefix=mnb_toolbar_dbus ${CMAKE_SOURCE_DIR}/src/mnb-toolbar-dbus.xml
   )

########### Add glue target ###############
ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mnb-panel-dbus-bindings.h
   COMMAND dbus-binding-tool --mode=glib-client --output=${CMAKE_CURRENT_BINARY_DIR}/mnb-panel-dbus-bindings.h --prefix=mnb_panel_dbus ${CMAKE_SOURCE_DIR}/src/mnb-panel-dbus.xml
   )

ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mnb-toolbar-dbus-bindings.h
   COMMAND dbus-binding-tool --mode=glib-client --output=${CMAKE_CURRENT_BINARY_DIR}/mnb-toolbar-dbus-bindings.h --prefix=mnb_toolbar_dbus ${CMAKE_SOURCE_DIR}/src/mnb-toolbar-dbus.xml
   )

ADD_DEFINITIONS(-DPLUGIN_LOCALEDIR="$(localedir)")
ADD_DEFINITIONS(-DMX_CACHE="$(MUTTER_MEEGO_THEME_DIR)/mx.cache")
ADD_DEFINITIONS(-DTHEMEDIR="$(MUTTER_MEEGO_THEME_DIR)")
ADD_DEFINITIONS(-DPANELSDIR="$(MUTTER_MEEGO_PANELS_DIR)")
ADD_DEFINITIONS(-DGETTEXT_PACKAGE="mutter-meego-netbook-plugin")
ADD_DEFINITIONS(${MUTTER_CFLAGS})

ADD_LIBRARY(${LIBRARY} SHARED ${LIBRARY_SRCS} ${DBUS_GLUE} ${MARSHALS})

SET_TARGET_PROPERTIES( ${LIBRARY} PROPERTIES
     SOVERSION 0
     VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
   )


TARGET_LINK_LIBRARIES(${LIBRARY}
    ${MX_LIBRARIES}
    ${GCONF_LIBRARIES}
    ${MUTTER_LIBRARIES}
    ${MX_LIBRARIES}
    ${SN_LIBRARIES}
    )

INSTALL(TARGETS ${LIBRARY} DESTINATION ${MUTTER_PLUGIN_DIR})
