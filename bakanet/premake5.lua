project "bakanet"
    location "./bakanet"
	kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs 
    {
        "%{IncludeDirs.bakanet}"
    }

    files 
    {
        "%{prj.location}/src/bakanet/**.h",
        "%{prj.location}/src/bakanet/**.cpp",
        "%{prj.location}/src/bakanet.h",
        "%{prj.location}/src/baknetpch.h",
    }

    filter "system:windows"
        defines
        {
            "BK_PLAFORM_WINDOWS"
        }

        files
        {
            "%{prj.location}/src/plaform/windows/**.h",
            "%{prj.location}/src/plaform/windows/**.cpp",
        }

        links
        {
            "WS2_32.lib"
        }
    
    filter "system:linux"
        defines
        {
            "BK_PLAFORM_LINUX"
        }

        files
        {
            "%{prj.location}/src/plaform/linux/**.h",
            "%{prj.location}/src/plaform/linux/**.cpp",
        }
