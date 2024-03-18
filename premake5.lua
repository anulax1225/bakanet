workspace "BakaraNet"
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
IncludeDirs["bakatools"] = "%{wks.location}/vendor/bakatools/src/"

group "NetCore"
	include "bakanet"
group ""

group "BakaModules"
	include "vendor/bakatools"
group ""

group "Sandbox"
	include "sandbox"
group ""