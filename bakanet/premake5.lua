project "bakanet"
	kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"
    staticruntime "on"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs 
    {
        "%{IncludeDirs.spdlog}",
        "%{IncludeDirs.bakanet}",
        "%{IncludeDirs.bakatools}"
    }

    files 
    {
        "%{prj.location}/src/bakanet/**.h",
        "%{prj.location}/src/bakanet/**.cpp",
        "%{prj.location}/src/baknetpch.h",
    }

    links 
    {
        "bakatools"
    }

    filter "system:windows"
        defines
        {
            "BK_PLATFORM_WINDOWS"
        }

        files
        {
            "%{prj.location}/src/platform/windows/**.h",
            "%{prj.location}/src/platform/windows/**.cpp",
        }

        links
        {
            "WS2_32.lib"
        }
    
    filter "system:linux"
        defines
        {
            "BK_PLATFORM_LINUX"
        }

        files
        {
            "%{prj.location}/src/platform/linux/**.h",
            "%{prj.location}/src/platform/linux/**.cpp",
        }
    
    filter "configurations:Debug"
        defines 
        { 
            "BK_DEBUG",
            "DEBUG"
        }
        runtime "Debug"
        symbols "on"


    filter "configurations:Release"
        defines 
        { 
            "BK_RELEASE",
            "NDEBUG"
        }
        runtime "Release"
        optimize "on"