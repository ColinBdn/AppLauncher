#include "imgui_image.h"

#define NOMINMAX
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_opengl3_loader.h"

#include <iostream>
#include <algorithm>



// The two next function was found in the ImGui github wiki.
// Simple helper function to load an image into a OpenGL texture with common settings
bool loadTextureFromMemory(const void* data, size_t data_size, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

// Open and read a file, then forward to loadTextureFromMemory()
bool loadTextureFromFile(const char* file_name, GLuint* out_texture, int* out_width, int* out_height)
{
    FILE* f = nullptr;
    if (fopen_s(&f, file_name, "rb") != 0 || f == nullptr)  return false;
    fseek(f, 0, SEEK_END);
    size_t file_size = (size_t)ftell(f);
    if (file_size == -1) return false;
    fseek(f, 0, SEEK_SET);
    void* file_data = IM_ALLOC(file_size);
    fread(file_data, 1, file_size, f);
    fclose(f);
    bool ret = loadTextureFromMemory(file_data, file_size, out_texture, out_width, out_height);
    IM_FREE(file_data);
    return ret;
}






bool Image::init(const char* path)
{
    if (m_initialized)
    {
        glDeleteTextures(1, &m_imageTexId);
        m_imageTexId = 0;
    }

    if (!loadTextureFromFile(path, &m_imageTexId, &m_width, &m_height))
    {
        std::cerr << "Failed to load texture\n";
        m_initialized = false;
        m_width = 1;
        m_height = 1;
        return false;
    }
    m_initialized = true;
    return true;
}

void Image::addPoints(const std::vector<PointInfo>& points, float refWidth, float refHeight)
{
    for (const auto& point : points)
    {
        PointInfo adjustedPoint = point;
        if (refWidth > 0 && refHeight > 0)
        {
            adjustedPoint.pos.x = point.pos.x * m_width / refWidth;
            adjustedPoint.pos.y = point.pos.y * m_height / refHeight;
        }
        m_tempPoints.push_back(adjustedPoint);
    }
}

void Image::addPoint(const PointInfo point, float refWidth, float refHeight)
{
    PointInfo adjustedPoint = point;
    if (refWidth > 0 && refHeight > 0)
    {
        adjustedPoint.pos.x = point.pos.x * m_width / refWidth;
        adjustedPoint.pos.y = point.pos.y * m_height / refHeight;
    }
    m_tempPoints.push_back(adjustedPoint);
}

void Image::show()
{
    ImGui::BeginChild("ImageRegion", ImVec2(0, 0));

    float u0 = m_panX / m_width;
    float v0 = m_panY / m_height;
    float u1 = (m_panX + m_width / m_zoom) / m_width;
    float v1 = (m_panY + m_height / m_zoom) / m_height;

    m_windowPos = { ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y };
    m_windowSize = { ImGui::GetWindowSize().x, ImGui::GetWindowSize().y };
    m_ratioToWindow = std::min(m_windowSize.x / m_width, m_windowSize.y / m_height);

    if (m_initialized)
    {
        ImGui::Image((void*)(intptr_t)m_imageTexId, ImVec2(m_width * m_ratioToWindow, m_height * m_ratioToWindow), ImVec2(u0, v0), ImVec2(u1, v1));
    }
    else
    {
        ImGui::Text("No Image");
    }


    ImGuiIO io = ImGui::GetIO();
    if (ImGui::IsItemHovered())
    {
        ImGuiWindow* Window = ImGui::GetCurrentWindow();
        Window->Flags |= ImGuiWindowFlags_NoMove;

        float wheel = io.MouseWheel;
        ImVec2 mousePos = io.MousePos;
        ImVec2 relativeMousePos = ImVec2((mousePos.x - m_windowPos.x) / m_ratioToWindow, (mousePos.y - m_windowPos.y) / m_ratioToWindow);
        if (wheel != 0.0f)
        {
            float zoomFactor = 1.1f;
            if (wheel > 0)
            {
                m_zoom *= zoomFactor;
                m_panX += wheel / abs(wheel) * (relativeMousePos.x * 0.1) / m_zoom;
                m_panY += wheel / abs(wheel) * (relativeMousePos.y * 0.1) / m_zoom;
            }
            else
            {
                m_panX += wheel / abs(wheel) * (relativeMousePos.x * 0.1) / m_zoom;
                m_panY += wheel / abs(wheel) * (relativeMousePos.y * 0.1) / m_zoom;
                m_zoom /= zoomFactor;
            }
        }
    }

    if (ImGui::IsItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
    {
        m_panX -= io.MouseDelta.x / (m_zoom * m_ratioToWindow);
        m_panY -= io.MouseDelta.y / (m_zoom * m_ratioToWindow);
    }

    if (m_zoom < 1.f) m_zoom = 1.0f;
    m_panX = std::clamp(m_panX, 0.0f, m_width - m_width / m_zoom);
    m_panY = std::clamp(m_panY, 0.0f, m_height - m_height / m_zoom);



    ImVec2 windowsPos = ImGui::GetWindowPos();
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    for (const auto& point : m_tempPoints)
    {
        if (m_zoom * 100.f < point.minimumZoomPercent) continue;
        float px = (point.pos.x - m_panX) * m_ratioToWindow * m_zoom;
        float py = (point.pos.y - m_panY) * m_ratioToWindow * m_zoom;

        if (point.shape == PointInfo::Shape::Square)
        {
            if (point.filled)
            {
                drawList->AddRectFilled(ImVec2(px - point.size + windowsPos.x, py - point.size + windowsPos.y), ImVec2(px + point.size + windowsPos.x, py + point.size + windowsPos.y), IM_COL32(point.color.x, point.color.y, point.color.z, 255));
            }
            else
            {
                drawList->AddRect(ImVec2(px - point.size + windowsPos.x, py - point.size + windowsPos.y), ImVec2(px + point.size + windowsPos.x, py + point.size + windowsPos.y), IM_COL32(point.color.x, point.color.y, point.color.z, 255), 0, 0, point.thickness);
            }
        }
        else if (point.shape == PointInfo::Shape::Triangle)
        {
            ImVec2 p1 = ImVec2(px + windowsPos.x, py - point.size + windowsPos.y);
            ImVec2 p2 = ImVec2(px - point.size + windowsPos.x, py + point.size + windowsPos.y);
            ImVec2 p3 = ImVec2(px + point.size + windowsPos.x, py + point.size + windowsPos.y);
            if (point.filled)
            {
                drawList->AddTriangleFilled(p1, p2, p3, IM_COL32(point.color.x, point.color.y, point.color.z, 255));
            }
            else
            {
                drawList->AddTriangle(p1, p2, p3, IM_COL32(point.color.x, point.color.y, point.color.z, 255), point.thickness);
            }
        }
        else if (point.shape == PointInfo::Shape::Cross)
        {
            ImVec2 p1 = ImVec2(px + windowsPos.x, py - point.size + windowsPos.y);
            ImVec2 p2 = ImVec2(px + windowsPos.x, py + point.size + windowsPos.y);
            ImVec2 p3 = ImVec2(px - point.size + windowsPos.x, py + windowsPos.y);
            ImVec2 p4 = ImVec2(px + point.size + windowsPos.x, py + windowsPos.y);
            drawList->AddLine(p1, p2, IM_COL32(point.color.x, point.color.y, point.color.z, 255), point.thickness);
            drawList->AddLine(p3, p4, IM_COL32(point.color.x, point.color.y, point.color.z, 255), point.thickness);
        }
        else
        {
            if (point.filled)
            {
                drawList->AddCircleFilled(ImVec2(px + windowsPos.x, py + windowsPos.y), point.size, IM_COL32(point.color.x, point.color.y, point.color.z, 255));
            }
            else
            {
                drawList->AddCircle(ImVec2(px + windowsPos.x, py + windowsPos.y), point.size, IM_COL32(point.color.x, point.color.y, point.color.z, 255), 0, point.thickness);
            }
            if (point.border)
            {
                drawList->AddCircle(ImVec2(px + windowsPos.x, py + windowsPos.y), point.size + point.borderThickness / 2, IM_COL32(0, 0, 0, 255), 0, point.borderThickness);
            }
            if (point.showDirection)
            {
                float angle = point.yaw;
                angle = angle * 3.14159265f / 180.0f;
                float lineLength = point.size * 2.5f;
                ImVec2 endPoint = ImVec2(px + cos(angle) * lineLength + windowsPos.x, py + sin(angle) * lineLength + windowsPos.y);
                drawList->AddLine(ImVec2(px + windowsPos.x, py + windowsPos.y), endPoint, IM_COL32(point.color.x, point.color.y, point.color.z, 255), point.thickness);
            }
        }
    }
    m_tempPoints.clear();


    ImGui::EndChild();
}

Vec2 Image::getRelativeMousePos(float refWidth, float refHeight) const
{
    ImGuiIO io = ImGui::GetIO();
    ImVec2 mousePos = io.MousePos;

    float screenX = mousePos.x - m_windowPos.x;
    float screenY = mousePos.y - m_windowPos.y;

    float imgX = m_panX + (screenX / (m_ratioToWindow * m_zoom));
    float imgY = m_panY + (screenY / (m_ratioToWindow * m_zoom));

    float finalX = imgX;
    float finalY = imgY;

    if (m_width > 0 && m_height > 0)
    {
        finalX = imgX * (refWidth / m_width);
        finalY = imgY * (refHeight / m_height);
    }

    return Vec2(finalX, finalY);
}

uint32_t Image::getTexId()
{
    return m_imageTexId;
}
