#pragma once
#include "utils_vector.h"
#include <stdint.h>
#include <vector>

class Image
{
public:
	struct PointInfo
	{
		Vec2 pos = { 0, 0 };
		Vec3 color = { 255, 255, 255 };
		float size = 2.f;
		float thickness = 1.5f;
		float minimumZoomPercent = 100.f;
		bool filled = true;
		float yaw = 0.0;
		bool showDirection = false;

		bool border = false;
		float borderThickness = 1.5f;

		enum class Shape
		{
			Circle,
			Square,
			Triangle,
			Cross
		};
		Shape shape = Shape::Circle;
	};

	bool init(const char* path);
	void addPoints(const std::vector<PointInfo>& points, float refWidth = -1, float refHeight = -1);
	void addPoint(const PointInfo point, float refWidth = -1, float refHeight = -1);
	void show();
	Vec2 getRelativeMousePos(float refWidth = -1, float refHeight = -1) const;

	uint32_t getTexId();

private:
	bool m_initialized = false;

	std::vector<PointInfo> m_tempPoints;
	uint32_t m_imageTexId = 0;
	int m_width = 1;
	int m_height = 1;
	float m_zoom = 1.0f;
	float m_panX = 0.0f;
	float m_panY = 0.0f;
	Vec2 m_windowSize = { 0.0f, 0.0f };
	Vec2 m_windowPos = { 0.0f, 0.0f };
	float m_ratioToWindow = 1.0f;
};