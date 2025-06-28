workspace "HeatExchangerSimulator"
    architecture "x64"

    configurations {
        "Debug", "Release"
    }
	
	
outputDir = "%{cfg.buildcfg}-%{cfg.architecture}" 


project "CalculationEngine"
    location "CalculationEngine"
    kind "consoleApp"
    language "C++"

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("obj/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src"
    }

    libdirs {
		
    }
    
    links {
		"winmm.lib",
		"gdi32.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"

	

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

