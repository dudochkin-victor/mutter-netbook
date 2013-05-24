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

SET (LIBRARY notifications)

SET(LIBRARY_SRCS
        meego-netbook-notify-store.c 
		meego-netbook-notify-store.h 
		mnb-notification-gtk.c 
		mnb-notification-gtk.h
		ntf-notification.c
		ntf-notification.h
		ntf-overlay.c
		ntf-overlay.h
		ntf-source.c
		ntf-source.h
		ntf-tray.c
		ntf-tray.h
		ntf-libnotify.c
		ntf-libnotify.h
		ntf-wm.c
		ntf-wm.h
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

SET(DBUS_GLUE
        ${CMAKE_CURRENT_BINARY_DIR}/notification-manager-glue.h
)

########### Add marshal target ###############
ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_BINARY_DIR}/src/marshal.h
   COMMAND glib-genmarshal --prefix=meego_netbook_marshal --header ${CMAKE_SOURCE_DIR}/src/marshal.list > ${CMAKE_BINARY_DIR}/src/marshal.h
   )

########### Add dbus target ###############
ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/notification-manager-glue.h
   COMMAND dbus-binding-tool --mode=glib-server --output=${CMAKE_CURRENT_BINARY_DIR}/notification-manager-glue.h --prefix=mnb_panel_dbus ${CMAKE_CURRENT_SOURCE_DIR}/notification-manager.xml
   )

ADD_DEFINITIONS(-DPLUGIN_LOCALEDIR="$(localedir)")
ADD_DEFINITIONS(-DMX_CACHE="$(MUTTER_MEEGO_THEME_DIR)/mx.cache")
ADD_DEFINITIONS(-DTHEMEDIR="$(MUTTER_MEEGO_THEME_DIR)")
ADD_DEFINITIONS(-DGETTEXT_PACKAGE="mutter-meego-netbook-plugin")
ADD_DEFINITIONS(${MUTTER_CFLAGS})

ADD_LIBRARY(${LIBRARY} STATIC ${LIBRARY_SRCS} ${DBUS_GLUE} ${CMAKE_BINARY_DIR}/src/marshal.h)

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
