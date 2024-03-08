workspace "winsock_test"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

    -- startproject "winsock_test"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include projects
include "bakanet"
include "sandbox/client"
include "sandbox/server"

    