#include "app.h"


#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define GLFW_EXPOSE_NATIVE_WIN32
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/implot.h"
#include "utils/logger.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include <iostream>
#include <filesystem>




namespace App
{
	GLFWwindow* window;
	int screenWidth, screenHeight;
	float screenScaleWidth, screenScaleHeight;
	ImGuiViewport* viewport;
	ImGuiIO* io;
	HWND window_hwnd;



	// ----------------------------------------------------------------
	// ----------------------------------------------------------------
	// ----------------------------------------------------------------


	void init()
	{
		io = &ImGui::GetIO();
		//ImFont* font_normal = io->Fonts->AddFontFromFileTTF("fonts/Satoshi-Variable.ttf", 18.0f, NULL, io->Fonts->GetGlyphRangesDefault());
		//ImFont* font_italic = io->Fonts->AddFontFromFileTTF("fonts/Satoshi-VariableItalic.ttf", 18.0f, NULL, io->Fonts->GetGlyphRangesDefault());

		const std::filesystem::path sandbox{"fonts"};
		for (auto const& dir_entry : std::filesystem::directory_iterator{ sandbox })
		{
			io->Fonts->AddFontFromFileTTF(dir_entry.path().string().c_str());
		}

		io->FontDefault = io->Fonts->Fonts[13];

		viewport = ImGui::GetMainViewport();
		window = glfwGetCurrentContext();
		window_hwnd = glfwGetWin32Window(window);

		glfwGetMonitorPhysicalSize(glfwGetPrimaryMonitor(), &screenWidth, &screenHeight);
		glfwSetWindowPos(window, screenWidth, screenHeight);
		glfwGetMonitorContentScale(glfwGetPrimaryMonitor(), &screenScaleWidth, &screenScaleHeight);

		Logger::infoBig("App initialized");
	}



	// ----------------------------------------------------------------
	// ----------------------------------------------------------------
	// ----------------------------------------------------------------

	void handleDrag()
	{
		if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
		{
			ReleaseCapture();
			SendMessage(window_hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
			SendMessage(window_hwnd, WM_LBUTTONUP, 0, 0);
		}
	}


	void update()
	{

		ImGui::SetWindowPos("Dear ImGui Demo", { viewport->Pos.x - 1, viewport->Pos.y - 1 }, ImGuiCond_Once);
		ImGui::ShowDemoWindow();


		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);

		ImGui::Begin("test", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove);
		handleDrag();


		ImGui::End();
	}




	// ----------------------------------------------------------------
	// ----------------------------------------------------------------
	// ----------------------------------------------------------------

	void destroy()
	{
		Logger::infoBig("App destroyed");
	}
}