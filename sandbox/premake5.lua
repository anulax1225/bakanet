project "server"
    location "./server"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"

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
        "%{prj.location}/**.h",
        "%{prj.location}/**.cpp",
    }

    links
    {
        "bakanet",
        "bakatools"
    }

    filter "system:linux"
        defines
        {
            "BK_PLATFORM_LINUX"
        }

    filter "system:windows"
        defines
        {
            "BK_PLATFORM_WINDOWS"
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


