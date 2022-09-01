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
IncludeDir["stb_image"] = "LostSouls/vendor/stb_image"

include "LostSouls/vendor/GLFW"
include "LostSouls/vendor/Glad"
include "LostSouls/vendor/imgui"

project "LostSouls"
    location "LostSouls"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
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
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LS_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "LS_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "LostSouls/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "LostSouls"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "LS_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "LS_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LS_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "LS_DIST"
        runtime "Release"
        optimize "on"
