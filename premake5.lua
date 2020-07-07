workspace "hazel"
	architecture "x64"
	startproject "sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "hazel/vendor/GLFW/include"
IncludeDir["Glad"] = "hazel/vendor/Glad/include"
IncludeDir["ImGui"] = "hazel/vendor/imgui"
IncludeDir["glm"] = "hazel/vendor/glm"

group "Dependencies"
	include "hazel/vendor/GLFW"
	include "hazel/vendor/Glad"
	include "hazel/vendor/imgui"
group ""

project "hazel"
	location "hazel"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin_int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.hpp"
	pchsource "hazel/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
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
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

	defines
	{
		"HZ_PLATFORM_WINDOWS",
		"HZ_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}

	filter "configurations:Debug"
		defines  "HZ_DEBUG"
		runtime  "Debug"
		symbols  "on"

	filter "configurations:Release"
		defines	 "HZ_RELEASE"
		runtime	 "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"

project "sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin_int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"hazel/vendor/spdlog/include",
		"hazel/src",
		"hazel/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"hazel"
	}

	filter "system:windows"
		systemversion "latest"

	defines
	{
		"HZ_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols  "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"
