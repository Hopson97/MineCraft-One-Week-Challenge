add_library(
    imgui_sfml
    imgui_impl_opengl3.cpp
    imgui-SFML.cpp
)   

target_link_libraries(imgui_sfml PRIVATE
    sfml-system sfml-graphics sfml-window
    imgui::imgui
)