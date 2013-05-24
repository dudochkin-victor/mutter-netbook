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

SET(EFFECTS_SRCS
        effects/mnb-switch-zones-effect.c
		effects/mnb-switch-zones-effect.h
		effects/mnb-fancy-bin.c
		effects/mnb-fancy-bin.h
		effects/mnb-zones-preview.c
		effects/mnb-zones-preview.h
    )

SET(ALTTAB_SRCS
        alttab/mnb-alttab.c
		alttab/mnb-alttab.h
		alttab/mnb-alttab-keys.c
		alttab/mnb-alttab-keys.h
		alttab/mnb-alttab-overlay.c
		alttab/mnb-alttab-overlay.h
		alttab/mnb-alttab-overlay-private.h
		alttab/mnb-alttab-overlay-app.c
		alttab/mnb-alttab-overlay-app.h
		alttab/penge-magic-texture.c
		alttab/penge-magic-texture.h
    )
    
SET(NOTIFICATION_SRCS
        notifications/meego-netbook-notify-store.c 
		notifications/meego-netbook-notify-store.h 
		notifications/mnb-notification-gtk.c 
		notifications/mnb-notification-gtk.h
		notifications/ntf-notification.c
		notifications/ntf-notification.h
		notifications/ntf-overlay.c
		notifications/ntf-overlay.h
		notifications/ntf-source.c
		notifications/ntf-source.h
		notifications/ntf-tray.c
		notifications/ntf-tray.h
		notifications/ntf-libnotify.c
		notifications/ntf-libnotify.h
		notifications/ntf-wm.c
		notifications/ntf-wm.h
    )
SET(PRESENCE_SRCS
        presence/mnb-presence.c
    	presence/mnb-presence.h
    	presence/gs-idle-monitor.c
    	presence/gs-idle-monitor.h
    	presence/gsm-presence.c
    	presence/gsm-presence.h
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
        ${CMAKE_CURRENT_BINARY_DIR}/notification-manager-glue.h
        ${CMAKE_CURRENT_BINARY_DIR}/gsm-presence-glue.h
)


########### Add dbus target ###############
ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gsm-presence-glue.h
   COMMAND dbus-binding-tool --mode=glib-server --output=${CMAKE_CURRENT_BINARY_DIR}/gsm-presence-glue.h --prefix=gsm_presence ${CMAKE_SOURCE_DIR}/src/presence/org.gnome.SessionManager.Presence.xml
   )
   
########### Add dbus target ###############
ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/notification-manager-glue.h
   COMMAND dbus-binding-tool --mode=glib-server --output=${CMAKE_CURRENT_BINARY_DIR}/notification-manager-glue.h --prefix=notification_manager ${CMAKE_SOURCE_DIR}/src/notifications/notification-manager.xml
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
ADD_DEFINITIONS(-DMX_CACHE="${MUTTER_MEEGO_THEME_DIR}/mx.cache")
ADD_DEFINITIONS(-DTHEMEDIR="${MUTTER_MEEGO_THEME_DIR}")
ADD_DEFINITIONS(-DPANELSDIR="${MUTTER_MEEGO_PANELS_DIR}")
ADD_DEFINITIONS(-DGETTEXT_PACKAGE="mutter-meego-netbook-plugin")
ADD_DEFINITIONS(-DVERSION="1.0")
ADD_DEFINITIONS(${MUTTER_CFLAGS})

ADD_LIBRARY(${LIBRARY} SHARED ${LIBRARY_SRCS} 
    ${DBUS_GLUE} ${MARSHALS} 
    ${NOTIFICATION_GLUE}
    ${EFFECTS_SRCS}
    ${ALTTAB_SRCS}
    ${NOTIFICATION_SRCS}
    ${PRESENCE_SRCS}
    )

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
    ${SCRNSAVER_LIBRARIES}
    )

INSTALL(TARGETS ${LIBRARY} DESTINATION ${MUTTER_PLUGIN_DIR})
