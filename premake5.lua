workspace "BakaraNet"
   	architecture "x64"
    configurations { "Debug", "Release" }
    startproject "bakanet"
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