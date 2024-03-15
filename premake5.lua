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

group "NetCore"
	include "bakanet"
group ""

group "Sandbox"
	include "sandbox"
group ""