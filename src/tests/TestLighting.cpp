#include "Renderer.h"
#include "Imgui/imgui.h"

#include "TestLighting.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test {

    TestLighting::TestLighting()
        : m_Proj(glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f))),
        cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)), cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), cameraUp(glm::vec3(0.0f, 1.0f, 0.0f))
    {
        float positions[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
        };

        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, sizeof(positions));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_Shader = std::make_unique<Shader>("res/shaders/Lighting.shader");
        m_Shader->Bind();
        m_Texture = std::make_unique<Texture>("res/textures/container2.png");
        m_Shader->SetUniform1i("material.diffuse", 0);
        m_Texture1 = std::make_unique<Texture>("res/textures/container2_specular.png");
        m_Shader->SetUniform1i("material.specular", 1);
    }

    TestLighting::~TestLighting()
    {
    }



    void TestLighting::OnUpdate(GLFWwindow* window, float deltaTime)
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

    void TestLighting::OnRender()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        Renderer renderer;
        //m_VAO->Bind();
        m_Texture->Bind(0);
        m_Texture1->Bind(1);
        {
            m_Shader->SetUniform3f("light.ambient", 0.2f, 0.2f, 0.2f);
            m_Shader->SetUniform3f("light.diffuse", 0.8f, 0.8f, 0.8f);
            m_Shader->SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f);

            // The camera shoots the spotlight
            m_Shader->SetUniform3f("light.position", cameraPos.x, cameraPos.y, cameraPos.z);
            m_Shader->SetUniform3f("light.direction", cameraFront.x, cameraFront.y, cameraFront.z);
            m_Shader->SetUniform1f("light.cutOff", glm::cos(glm::radians(12.5)));
            m_Shader->SetUniform1f("light.outerCutOff", glm::cos(glm::radians(17.5f)));

            // cover distance of 50m scene
            m_Shader->SetUniform1f("light.constant", 1.0f);
            m_Shader->SetUniform1f("light.linear", 0.09f);
            m_Shader->SetUniform1f("light.quadratic", 0.032f);

            m_Shader->SetUniform1f("material.shininess", 64.0f);           

            m_Shader->SetUniform3f("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);

            glm::vec3 direction;
            direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            direction.y = sin(glm::radians(pitch));
            direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            cameraFront = glm::normalize(direction);
            m_View = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

            m_Proj = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

            // calculate the model matrix for each object and pass it to shader before drawing
            for (unsigned int i = 0; i < 10; i++) {
                glm::mat4 model = glm::mat4(1.0f);
                float angle = 20.0f;
                model = glm::translate(model, cubePositions[i]);
                glm::mat4 mvp = m_Proj * m_View * model;
                //m_Shader->Bind();
                m_Shader->SetUniformMat4f("u_Model", model);
                m_Shader->SetUniformMat4f("u_MVP", mvp);
                glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));
                m_Shader->SetUniformMat3f("u_NormalMatrix", normalMatrix);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }

    }

    void TestLighting::OnImGuiRender()
    {
        ImGui::SliderFloat("Rotate x", &yaw, -270.0f, 90.0f);
        ImGui::SliderFloat("Rotate y", &pitch, -180.0f, 180.0f);
        ImGui::SliderFloat("Zoom", &fov, 1.0f, 90.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0F / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }



}