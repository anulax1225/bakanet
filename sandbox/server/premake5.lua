project "server"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "src/**.h",
        "src/**.cpp"
    }

    links { "bakanet"}