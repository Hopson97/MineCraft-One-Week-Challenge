add_library(
    glad
    glad.c
)   

target_compile_options(glad PRIVATE -fPIE)