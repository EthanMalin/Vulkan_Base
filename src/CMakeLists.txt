set(EXE power)

file(GLOB POWER_SRC "*.cpp" "*.h")
add_executable(power ${POWER_SRC})

target_link_libraries(${EXE} glfw)
target_link_libraries(${EXE} Vulkan::Vulkan)

