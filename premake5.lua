workspace "LostSouls"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include diectories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "LostSouls/vendor/GLFW/include"
IncludeDir["Glad"] = "LostSouls/vendor/Glad/include"
IncludeDir["ImGui"] = "LostSouls/vendor/imgui"
IncludeDir["glm"] = "LostSouls/vendor/glm"

include "LostSouls/vendor/GLFW"
include "LostSouls/vendor/Glad"
include "LostSouls/vendor/imgui"

project "LostSouls"
    location "LostSouls"
    kind "SharedLib"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    pchheader "lspch.h"
    pchsource "LostSouls/src/lspch.cpp"

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "LS_PLATFORM_WINDOWS",
            "LS_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{Copy} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
    
    filter "configurations:Debug"
        defines "LS_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "LS_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "LS_DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "LostSouls/vendor/spdlog/include",
        "LostSouls/src",
        "LostSould/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "LostSouls"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "LS_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "LS_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "LS_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "LS_DIST"
        buildoptions "/MD"
        optimize "On"
