project(fileviewboxplugin)

find_package(KDE4 REQUIRED)
find_package(LibKonq REQUIRED)
include(KDE4Defaults)

include_directories(${KDE4_INCLUDE_DIR} ${QT_INCLUDES} ${LIBKONQ_INCLUDE_DIR})

set(fileviewboxplugin_SRCS fileviewboxplugin.cpp)
kde4_add_plugin(fileviewboxplugin  ${fileviewboxplugin_SRCS})
target_link_libraries(fileviewboxplugin ${KDE4_KIO_LIBS} ${LIBKONQ_LIBRARY})

install(FILES fileviewboxplugin.desktop DESTINATION ${SERVICES_INSTALL_DIR})
install(TARGETS fileviewboxplugin DESTINATION ${PLUGIN_INSTALL_DIR})
