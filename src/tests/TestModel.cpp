#include "TestModel.h"

#include "Renderer.h"
#include "Imgui/imgui.h"

#include "TestModel.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test {

    TestModel::TestModel()
        : m_Proj(glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f))),
        cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)), cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), cameraUp(glm::vec3(0.0f, 1.0f, 0.0f))
    {
    }

    TestModel::~TestModel()
    {
    }



    void TestModel::OnUpdate(GLFWwindow* window, float deltaTime)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        float cameraSpeed = 2.5 * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    void TestModel::OnRender()
    {

    }

    void TestModel::OnImGuiRender()
    {
        ImGui::SliderFloat("Rotate x", &yaw, -270.0f, 90.0f);
        ImGui::SliderFloat("Rotate y", &pitch, -180.0f, 180.0f);
        ImGui::SliderFloat("Zoom", &fov, 1.0f, 90.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0F / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }



}