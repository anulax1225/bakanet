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

newaction {
    trigger     = "clean",
    description = "Clean the build",
    execute = function()
        print("Cleaning...")
        os.rmdir("./bin")
        os.rmdir("./bin-int")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        print("Done.")
    end
}
    