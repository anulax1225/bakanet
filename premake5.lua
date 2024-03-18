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
IncludeDirs["spdlog"] = "%{wks.location}/vendor/spdlog/include"

group "BakaModules"
	include "vendor/bakatools"
group ""

group "NetCore"
	include "bakanet"
group ""

group "Sandbox"
	include "sandbox"
group ""