set(CMAKE_AUTOMOC ON)

function(add_lingmo_shell_core_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE Lingmo::ShellCore Qt6::Test)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

add_lingmo_shell_core_test(tst_ShellRuntime)
add_lingmo_shell_core_test(tst_SurfaceManager)
add_lingmo_shell_core_test(tst_PluginManager)
add_lingmo_shell_core_test(tst_AppletManager)
