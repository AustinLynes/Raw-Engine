workspace "Raw Engine"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }


-- Raw Engine 
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
project "Raw Engine"
    location "Raw Engine"
    kind "consoleApp"
    language "c++"
    
    targetdir "bin/%{cfg.buildcfg}-%{cfg.buildsystem}-x64/%{prj.name}"
    objdir "bin/%{cfg.buildcfg}-%{cfg.buildsystem}-x64/%{prj.name}"
    
    files {
        "%{prj.name}/**.h",
        "%{prj.name}/**.hpp",
        
        "%{prj.name}/**.c",
        "%{prj.name}/**.cpp",

    }
    
    includedirs {
        -- Include Main Engine
        "Engine/src/",
        "RMath/src/",
    }
   
    links {
        "Engine",
        "RMath",
    }
    defines{
      "NO_MIN_MAX"
    }
    filter "system:windows"
        cppdialect "c++latest"
        staticruntime "off"
        systemversion "latest"

        defines {
            "WIN32",
        }
    filter "configurations:Debug"
        defines { 
            "_DEBUG"
        }
        symbols "on"
        buildoptions "/MDd"
        
    filter "configurations:Release"
        defines {
            "_DEBUG"
        }
        optimize "on"
        symbols "on"
        buildoptions "/MD"
    filter "configurations:Release"
        defines {
            "NDEBUG"
        }
        optimize "on"
        symbols "off"
        buildoptions "/MD"
    
-- Engine
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
project "Engine"                                                                -- Name of the Project
    location "Engine"                                                           -- Location of Project (Relative to File)
    kind "staticLib"                                                            -- Type of Project ( consoleapp, staticlib, sharedlib )
    language "c++"                                                              -- Language of Project

    targetdir "bin/%{cfg.buildcfg}-%{cfg.buildsystem}-x64/%{prj.name}"          
    objdir "bin/%{cfg.buildcfg}-%{cfg.buildsystem}-x64/%{prj.name}"

    files {
        "%{prj.name}/**.h",
        "%{prj.name}/**.hpp",
        
        "%{prj.name}/**.c",
        "%{prj.name}/**.cpp",

    }

    includedirs {
        "%{prj.name}/src/",	
        "RMath/src/"
    }

    links {
        "RMath"
    }
    filter "system:windows"
        cppdialect "c++latest"
        staticruntime "off"
        systemversion "latest"

        defines {
            "WIN32",
        }
    filter "configurations:Debug"
        defines { 
            "_DEBUG",
        }
        symbols "on"
        buildoptions "/MDd"
        
    filter "configurations:Release"
        defines {
            "_DEBUG",
        }
        optimize "on"
        symbols "on"
        buildoptions "/MD"

    filter "configurations:Release"
        defines {
            "NDEBUG",
        }
        optimize "on"
        symbols "off"
        buildoptions "/MD"

-- RMath
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
project "RMath"                                                                 -- Name of the Project
    location "RMath"                                                            -- Location of Project (Relative to File)
    kind "staticLib"                                                            -- Type of Project ( consoleapp, staticlib, sharedlib )
    language "c++"                                                              -- Language of Project

    targetdir "bin/%{cfg.buildcfg}-%{cfg.buildsystem}-x64/%{prj.name}"          
    objdir "bin/%{cfg.buildcfg}-%{cfg.buildsystem}-x64/%{prj.name}"

    files {
        "%{prj.name}/**.h",
        "%{prj.name}/**.hpp",
        
        "%{prj.name}/**.c",
        "%{prj.name}/**.cpp",
    }

    includedirs {
        "%{prj.name}/src/",	
    }

    filter "system:windows"
        cppdialect "c++latest"
        staticruntime "off"
        systemversion "latest"

        defines {
            "WIN32",
        }
    filter "configurations:Debug"
        defines { 
            "_DEBUG",
        }
        symbols "on"
        buildoptions "/MDd"
        
    filter "configurations:Release"
        defines {
            "_DEBUG",
        }
        optimize "on"
        symbols "on"
        buildoptions "/MD"

    filter "configurations:Release"
        defines {
            "NDEBUG",
        }
        optimize "on"
        symbols "off"
        buildoptions "/MD"