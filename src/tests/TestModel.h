#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Test.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <memory>

namespace test {

	class TestModel : public Test {
	public:
		TestModel();
		TestModel(char* path);
		~TestModel();

		void OnUpdate(GLFWwindow* window, float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:

		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;
		glm::mat4 m_Proj, m_View;

		float yaw = -90.0f;
		float pitch = 0.0f;
		float fov = 45.0f;

	};

}