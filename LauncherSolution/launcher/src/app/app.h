#pragma once


namespace App
{
	constexpr int windows_width = 1280;
	constexpr const int windows_height = 720;
	constexpr const char* windows_name = "ImGui App";

	void init();
	void update();
	void destroy();
}
