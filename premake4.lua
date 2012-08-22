solution "BlocksSolution"
    configurations { "Linux" }
    project "Blocks"
        kind "WindowedApp"
        language "C++"
        files { "src/*.h", "src/*.cpp", "src/noise/*.h", "src/noise/*.cpp" }
        
        configuration "Linux"
            location "build"
            libdirs "./lib"
            includedirs "./include"
            defines { "DEBUG" }
            flags { "Symbols" }
            links { "sfml-graphics", "sfml-window", "sfml-system", "GLEW", "GLU", "GL" }