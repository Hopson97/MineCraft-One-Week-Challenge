add_library(
    imgui_sfml
    imgui_impl_opengl3.cpp
    imgui-SFML.cpp
)   

target_link_libraries(imgui_sfml PRIVATE
    SFML::System SFML::Graphics SFML::Window
    imgui::imgui
)
target_compile_features(imgui_sfml PUBLIC cxx_std_17)
