project(fileviewboxplugin)

FIND_PACKAGE(KDE4 REQUIRED)
FIND_PACKAGE(LibKonq REQUIRED)
INCLUDE(KDE4Defaults)

include_directories(${QT_INCLUDES} ${LIBKONQ_INCLUDE_DIR})

set(fileviewboxplugin_SRCS fileviewboxplugin.cpp)
kde4_add_plugin(fileviewboxplugin  ${fileviewboxplugin_SRCS})
target_link_libraries(fileviewboxplugin ${KDE4_KIO_LIBS} ${LIBKONQ_LIBRARY})

install(FILES fileviewboxplugin.desktop DESTINATION ${SERVICES_INSTALL_DIR})
install(TARGETS fileviewboxplugin DESTINATION ${PLUGIN_INSTALL_DIR})
