SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 0)
SET(VERSION_PATCH 0)

PKG_CHECK_MODULES(GIO gio-unix-2.0 REQUIRED)
PKG_CHECK_MODULES(MT meegotouch REQUIRED)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/libmeego-panel
    ${MX_INCLUDE_DIRS}
    ${DBUS_INCLUDE_DIRS}
    )

#ADD_CUSTOM_COMMAND(
#   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/foo.c
#   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/bar.c ${CMAKE_CURRENT_BINARY_DIR}/foo.c
#   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/bar.c
#   )


SET (LIBRARY meego-panel)

SET(LIBRARY_SRCS 
        gdkapplaunchcontext-x11.c
        mpl-app-launch-context.c
        mpl-app-launches-query.c
        mpl-app-launches-store.c
        mnb-enum-types.c
        mpl-content-pane.c
        mpl-entry.c
        mpl-icon-theme.c
        mpl-panel-background.c
        mpl-panel-client.c
        mpl-panel-clutter.c
        mpl-panel-gtk.c
        mpl-panel-windowless.c
        mpl-app-bookmark-manager.c
        mpl-utils.c
    )

SET(LIBRARY_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-app-launch-context.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-app-launches-query.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-app-launches-store.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-content-pane.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-entry.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-icon-theme.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-panel-client.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-panel-clutter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-panel-common.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-panel-gtk.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-panel-windowless.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-app-bookmark-manager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-utils.h
        ${CMAKE_CURRENT_BINARY_DIR}/mpl-version.h
    )
SET(PRIVATE_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/gdkapplaunchcontext-x11.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-app-launches-store-priv.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mpl-panel-background.h
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
########### Add pkgconfig target ###############
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/mpl-version.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/mpl-version.h"
  IMMEDIATE @ONLY)

########### Add enum target ###############
ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mnb-enum-types.h
   COMMAND glib-mkenums --template ${CMAKE_SOURCE_DIR}/src/mnb-enum-types.h.in ${LIBRARY_HEADERS} ${PRIVATE_HEADERS} > ${CMAKE_CURRENT_BINARY_DIR}/mnb-enum-types.h
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
   #DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/mnb-enum-types.h
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

ADD_DEFINITIONS(-DGETTEXT_PACKAGE="mutter-meego-netbook-plugin")
ADD_DEFINITIONS(-DMX_CACHE="$(MUTTER_MEEGO_THEME_DIR)/meego-panel/mx.cache")
ADD_DEFINITIONS(-DDATADIR="$(datadir)")
ADD_DEFINITIONS(-DTHEMEDIR="$(MUTTER_MEEGO_THEME_DIR)/meego-panel")
ADD_DEFINITIONS(-DMEEGO_APP_LAUNCHES_STORE="$(libexecdir)/meego-app-launches-store")

ADD_LIBRARY(${LIBRARY} SHARED ${LIBRARY_SRCS} ${MOC_FILES} ${LIBRARY_MOC_HEADERS} ${MARSHALS} ${DBUS_GLUE})

SET_TARGET_PROPERTIES( ${LIBRARY} PROPERTIES
     SOVERSION 0
     VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
   )


TARGET_LINK_LIBRARIES(${LIBRARY}
    ${MX_LIBRARIES}
    ${GTK_LIBRARIES}
    ${DBUS_LIBRARIES}
    )

INSTALL(TARGETS ${LIBRARY} DESTINATION ${PKG_LIBDIR})


SET (PROGRAMS meego-launch)

SET(PROGRAM_SRCS
    meego-launch.c
    )

SET(PROGRAM_HEADERS
    )

ADD_EXECUTABLE(${PROGRAMS} ${PROGRAM_SRCS} ${PROGRAM_HEADERS})

   
TARGET_LINK_LIBRARIES(${PROGRAMS}
    meego-panel
    )

INSTALL(TARGETS ${PROGRAMS} RUNTIME DESTINATION ${PKG_BINDIR})

SET (LIBEXEC_PROGRAMS meego-app-launches-store)

SET(LIBEXEC_PROGRAM_SRCS
    meego-app-launches-store.c
    )

SET(LIBEXEC_PROGRAM_HEADERS
    )

ADD_EXECUTABLE(${LIBEXEC_PROGRAMS} ${LIBEXEC_PROGRAM_SRCS} ${LIBEXEC_PROGRAM_HEADERS})


TARGET_LINK_LIBRARIES(${LIBEXEC_PROGRAMS}
    meego-panel
    )

INSTALL(TARGETS ${LIBEXEC_PROGRAMS} RUNTIME DESTINATION ${PKG_LIBEXECDIR})
