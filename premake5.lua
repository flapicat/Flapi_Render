workspace "Flapi_Render"
    architecture "x64"
    startproject "Sandbox"

    configurations{
        "Debug",
        "Release"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["GLFW"] = "vendor/GLFW/include"
    IncludeDir["glad"] = "vendor/glad/include"
    IncludeDir["ImGui"] = "vendor/imgui"
    IncludeDir["glm"] = "vendor/glm"
    IncludeDir["stb_image"] = "vendor/stb/include"
    
group "Dependencies"
	include "vendor/GLFW"
	include "vendor/glad"
	include "vendor/imgui"
	include "vendor/stb"
group ""
        
project "Flapi_Render"
	location "Flapi_Render"
	kind "StaticLib"
	language "C++"
	cppdialect "C++23"
	staticruntime "on"
    buildoptions { "/utf-8" }

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGui}/backends",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links{ 
		"GLFW",
		"glad",
		"ImGui",
		"stb_image",
		"opengl32.lib"
	}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
	cppdialect "C++23"
	staticruntime "on"
	buildoptions "/utf-8"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/src",
		"Flapi_Render/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGui}/backends",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links{ 
		"Flapi_Render"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"