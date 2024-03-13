workspace "socket_unix"
   	architecture "x64"
    configurations { "Debug", "Release" }
    startproject "server"
    flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

IncludeDirs = {}

IncludeDirs["bakanet"] = "%{wks.location}/bakanet/src/"

project "server"
    location "./sandbox/server"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs 
    {
        "%{IncludeDirs.bakanet}",
        "./sandbox/"
    }

    files 
    {
        "%{prj.location}/**.h",
        "%{prj.location}/**.cpp",
        "./sandbox/commun.h"
    }

    links
    {
        "bakanet"
    }



project "client"
    location "./sandbox/client"
    kind "ConsoleApp"
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
        "%{prj.location}/**.h",
        "%{prj.location}/**.cpp",
        "./sandbox/commun.h"
    }
    
    links
    {
        "bakanet"
    }