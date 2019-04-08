workspace "mconeweek"
    configurations {"Debug", "Release"}

project "mconeweek"
    kind "WindowedApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    links {os.findlib("sfml")}
    links {"sfml-audio", "sfml-network", "sfml-graphics", "sfml-window", "sfml-system", "pthread", "dl"}



    files {"./Source/**.cpp", "./Source/**.c", "./Source/**.h"}


filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

 filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"