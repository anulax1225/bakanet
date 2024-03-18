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
        "bakanet"
    }

    filter "system:linux"
        defines
        {
            "BK_PLAFORM_LINUX"
        }

    filter "system:windows"
        defines
        {
            "BK_PLAFORM_WINDOWS"
        }


