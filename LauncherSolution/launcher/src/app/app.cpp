#include "app.h"


#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define GLFW_EXPOSE_NATIVE_WIN32
#include "imgui/imgui.h"
#include "imgui/implot.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "imgui/imgui_stdlib.h"

#include "utils/logger.h"
#include "appLibrary.h"


#include <iostream>
#include <filesystem>




GLFWwindow* window;
int screenWidth, screenHeight;
float screenScaleWidth, screenScaleHeight;
ImGuiViewport* viewport;
ImGuiIO* io;
HWND window_hwnd;
AppLibrary* library;


// ----------------------------------------------------------------
// ----------------------------------------------------------------
// ----------------------------------------------------------------


void init()
{
	io = &ImGui::GetIO();

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



	library = new AppLibrary("./");


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

	//ImGui::SetWindowPos("Dear ImGui Demo", { viewport->Pos.x - 1, viewport->Pos.y - 1 }, ImGuiCond_Once);
	//ImGui::ShowDemoWindow();


	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::Begin("test", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	handleDrag();

	static std::string searchInput = "";
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x*0.5f);
	float itemWidth = ImGui::CalcItemWidth();
	ImGui::SetCursorPosX((ImGui::GetWindowWidth() - itemWidth) * 0.5f);
	ImGui::InputText("##search", &searchInput);

	std::vector<App> apps = library->searchApps(searchInput);
	for (const App& app : apps)
	{
		ImGui::Text(app.name.c_str());
	}


	ImGui::End();
}




// ----------------------------------------------------------------
// ----------------------------------------------------------------
// ----------------------------------------------------------------

void destroy()
{
	delete library;
	Logger::infoBig("App destroyed");
}