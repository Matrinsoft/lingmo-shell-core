set(PUBLIC_HEADERS
    ${CMAKE_SOURCE_DIR}/include/LingmoShellCore/ShellRuntime.h
    ${CMAKE_SOURCE_DIR}/include/LingmoShellCore/SurfaceManager.h
)

set(PRIVATE_HEADERS
    LingmoShellCore/private/ShellRuntime_p.h
    LingmoShellCore/private/SurfaceManager_p.h
)

set(SOURCES
    LingmoShellCore/Runtime/ShellRuntime.cpp
    LingmoShellCore/Surface/SurfaceManager.cpp
)

set(CMAKE_AUTOMOC ON)

# ── Shared library ────────────────────────────────────────
add_library(LingmoShellCore SHARED ${SOURCES} ${PUBLIC_HEADERS} ${PRIVATE_HEADERS})
add_library(Lingmo::ShellCore ALIAS LingmoShellCore)

target_include_directories(LingmoShellCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(LingmoShellCore
    PUBLIC
        Qt6::Core
        Qt6::DBus
    PRIVATE
        Lingmo::IPC
        Lingmo::Config
        Lingmo::Plugin
        Lingmo::Theme
        Lingmo::Utils
)

target_compile_definitions(LingmoShellCore PRIVATE LINGMOSHELLCORE_LIBRARY)

set_target_properties(LingmoShellCore PROPERTIES
    SOVERSION 1
    VERSION ${PROJECT_VERSION}
    DEFINE_SYMBOL LINGMOSHELLCORE_LIBRARY
    OUTPUT_NAME LingmoShellCore
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

# ── Generated headers ─────────────────────────────────────
configure_file(
    "${CMAKE_SOURCE_DIR}/include/LingmoShellCore/LingmoShellCoreExport.h.in"
    "${CMAKE_BINARY_DIR}/include/LingmoShellCore/LingmoShellCoreExport.h"
)

configure_file(
    "${CMAKE_SOURCE_DIR}/include/LingmoShellCore/LingmoShellCoreVersion.h.in"
    "${CMAKE_BINARY_DIR}/include/LingmoShellCore/LingmoShellCoreVersion.h"
)

# ── Executable ────────────────────────────────────────────
add_executable(lingmo-shell-core main.cpp)
target_link_libraries(lingmo-shell-core PRIVATE LingmoShellCore)

# ── Install ───────────────────────────────────────────────
install(TARGETS LingmoShellCore
    EXPORT LingmoShellCoreTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(TARGETS lingmo-shell-core
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBEXECDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/LingmoShellCore/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/LingmoShellCore
    FILES_MATCHING PATTERN "*.h"
    PATTERN "*.h.in" EXCLUDE
)

install(FILES
    "${CMAKE_BINARY_DIR}/include/LingmoShellCore/LingmoShellCoreExport.h"
    "${CMAKE_BINARY_DIR}/include/LingmoShellCore/LingmoShellCoreVersion.h"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/LingmoShellCore
)

install(EXPORT LingmoShellCoreTargets
    FILE LingmoShellCoreTargets.cmake
    NAMESPACE Lingmo::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/LingmoShellCore
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_SOURCE_DIR}/cmake/LingmoShellCoreConfig.cmake.in"
    "${CMAKE_BINARY_DIR}/LingmoShellCoreConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/LingmoShellCore
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR
)

write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/LingmoShellCoreConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_BINARY_DIR}/LingmoShellCoreConfig.cmake"
    "${CMAKE_BINARY_DIR}/LingmoShellCoreConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/LingmoShellCore
)

# ── systemd service ───────────────────────────────────────
install(FILES ${CMAKE_SOURCE_DIR}/systemd/lingmo-shell-core.service
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/systemd/user)
install(FILES ${CMAKE_SOURCE_DIR}/systemd/lingmo-shell-core.target
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/systemd/user)
