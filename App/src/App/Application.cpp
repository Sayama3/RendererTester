//
// Created by ianpo on 01/06/2024.
//

#include "App/Application.hpp"
#include "Render/Renderer.hpp"
#include "Core/Core.hpp"

#include <filesystem>
#include <glad/glad.h>
#include "App/ImGuiLib.hpp"
#include <vendor/stb_image.h>

namespace App {

	Application::Application(const WindowParameters &parameters) : m_Window(parameters), m_ImGui(m_Window.GetNativeWindow<void>(), "#version 450")
	{
	}

	void Application::Run() {
		Render::Renderer::Initialize();
		Render::Renderer::SetClearColor({{0.8f}});

		std::string vertexShader = R"(
#version 450 core

uniform mat4 u_ProjectionMatrix = mat4(1);

uniform vec3 u_CamPos = vec3(0);
uniform vec3 u_CamFwd = vec3(0,0,1);
uniform vec3 u_CamUp = vec3(0,1,0);

uniform mat4 u_ModelMatrix = mat4(1);
uniform mat4 u_NormalMatrix = mat4(1);

in vec3 a_Position;
in vec3 a_Normal;
in vec2 a_TexCoord;
in vec4 a_Color;

out vec3 v_Position;
out vec3 v_Normal;
out vec2 v_TexCoord;
out vec4 v_Color;


void main() {
	vec3 right = normalize(cross(u_CamFwd, u_CamUp));

	mat4 view;
	view[0] = vec4(right, 0);
	view[1] = vec4(u_CamUp, 0);
	view[2] = vec4(u_CamFwd, 0);
	view[3] = vec4(u_CamPos, 1);
	view = inverse(view);

    gl_Position = u_ProjectionMatrix * view * u_ModelMatrix * vec4(a_Position, 1.0);
    v_Position = (u_ModelMatrix * vec4(a_Position, 1.0)).xyz;

    v_Normal = normalize((u_NormalMatrix * vec4(a_Normal, 1.0)).xyz);
    v_TexCoord = a_TexCoord;
    v_Color = a_Color;
}
)";
		std::string fragmentShader = R"(
#version 450 core

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_ModelMatrix;
uniform mat4 u_NormalMatrix;

uniform sampler2D u_Texture;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;
in vec4 v_Color;

out vec4 o_Color;

void main()
{
   o_Color = vec4((v_Normal + 1.0) * 0.5, 1.0);
   o_Color *= texture2D(u_Texture, v_TexCoord);
//	o_Color = vec4(1);
}
)";

		std::vector<Render::Vertex> cube {
				//Front Face
				Render::Vertex(Math::Vec3({-0.5f, -0.5f, +0.5f}), Math::Vec3({0,0,+1}), Math::Vec2({0,0}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 0
				Render::Vertex(Math::Vec3({+0.5f, -0.5f, +0.5f}), Math::Vec3({0,0,+1}), Math::Vec2({0,1}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 1
				Render::Vertex(Math::Vec3({+0.5f, +0.5f, +0.5f}), Math::Vec3({0,0,+1}), Math::Vec2({1,1}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 2
				Render::Vertex(Math::Vec3({-0.5f, +0.5f, +0.5f}), Math::Vec3({0,0,+1}), Math::Vec2({1,0}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 3
				//Front Face
				Render::Vertex(Math::Vec3({-0.5f, -0.5f, -0.5f}), Math::Vec3({0,0,-1}), Math::Vec2({0,0}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 4
				Render::Vertex(Math::Vec3({+0.5f, -0.5f, -0.5f}), Math::Vec3({0,0,-1}), Math::Vec2({0,1}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 5
				Render::Vertex(Math::Vec3({+0.5f, +0.5f, -0.5f}), Math::Vec3({0,0,-1}), Math::Vec2({1,1}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 6
				Render::Vertex(Math::Vec3({-0.5f, +0.5f, -0.5f}), Math::Vec3({0,0,-1}), Math::Vec2({1,0}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 7
				//Up Face
				Render::Vertex(Math::Vec3({-0.5f, +0.5f, -0.5f}), Math::Vec3({0,+1, 0}), Math::Vec2({0,0}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 8
				Render::Vertex(Math::Vec3({+0.5f, +0.5f, -0.5f}), Math::Vec3({0,+1, 0}), Math::Vec2({0,1}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 9
				Render::Vertex(Math::Vec3({+0.5f, +0.5f, +0.5f}), Math::Vec3({0,+1, 0}), Math::Vec2({1,1}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 10
				Render::Vertex(Math::Vec3({-0.5f, +0.5f, +0.5f}), Math::Vec3({0,+1, 0}), Math::Vec2({1,0}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 11
				//Down Face
				Render::Vertex(Math::Vec3({-0.5f, -0.5f, -0.5f}), Math::Vec3({0,-1, 0}), Math::Vec2({0,0}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 12
				Render::Vertex(Math::Vec3({+0.5f, -0.5f, -0.5f}), Math::Vec3({0,-1, 0}), Math::Vec2({0,1}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 13
				Render::Vertex(Math::Vec3({+0.5f, -0.5f, +0.5f}), Math::Vec3({0,-1, 0}), Math::Vec2({1,1}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 14
				Render::Vertex(Math::Vec3({-0.5f, -0.5f, +0.5f}), Math::Vec3({0,-1, 0}), Math::Vec2({1,0}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 15
				//Right Face
				Render::Vertex(Math::Vec3({+0.5f, -0.5f, -0.5f}), Math::Vec3({+1, 0, 0}), Math::Vec2({0,0}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 16
				Render::Vertex(Math::Vec3({+0.5f, +0.5f, -0.5f}), Math::Vec3({+1, 0, 0}), Math::Vec2({0,1}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 17
				Render::Vertex(Math::Vec3({+0.5f, +0.5f, +0.5f}), Math::Vec3({+1, 0, 0}), Math::Vec2({1,1}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 18
				Render::Vertex(Math::Vec3({+0.5f, -0.5f, +0.5f}), Math::Vec3({+1, 0, 0}), Math::Vec2({1,0}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 19
				//Left Face
				Render::Vertex(Math::Vec3({-0.5f, -0.5f, -0.5f}), Math::Vec3({-1, 0, 0}), Math::Vec2({0,0}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 20
				Render::Vertex(Math::Vec3({-0.5f, +0.5f, -0.5f}), Math::Vec3({-1, 0, 0}), Math::Vec2({0,1}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 21
				Render::Vertex(Math::Vec3({-0.5f, +0.5f, +0.5f}), Math::Vec3({-1, 0, 0}), Math::Vec2({1,1}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 22
				Render::Vertex(Math::Vec3({-0.5f, -0.5f, +0.5f}), Math::Vec3({-1, 0, 0}), Math::Vec2({1,0}), Math::Vec4({0.8, 0.2, 0.3, 1.0})), // 23
		};

		std::vector<uint32_t> vertices {
				// Front
				0,2,1,
				0,3,2,
				// Back
				4,5,6,
				4,6,7,
				// Up
				8,9,10,
				8,10,11,
				// Down
				12,14,13,
				12,15,14,
				// Front
				16,18,17,
				16,19,18,
				// Back
				20,21,22,
				20,22,23,
		};

//      std::vector<Render::Vertex> cube {
//            Render::Vertex(Math::Vec3({-0.5f, -0.5f, 0.0f}), Math::Vec3({0,0,1}), Math::Vec2({0,0})), // 0
//            Render::Vertex(Math::Vec3({+0.5f, -0.5f, 0.0f}), Math::Vec3({0,0,1}), Math::Vec2({1,0})), // 1
//            Render::Vertex(Math::Vec3({+0.5f, +0.5f, 0.0f}), Math::Vec3({0,0,1}), Math::Vec2({1,1})), // 2
//            Render::Vertex(Math::Vec3({-0.5f, +0.5f, 0.0f}), Math::Vec3({0,0,1}), Math::Vec2({0,1})), // 3
//      };
//
//      std::vector<uint32_t> vertices {
//            0,1,2,
//            0,2,3
//      };

		m_Shader = Render::Shader::Create(vertexShader, fragmentShader);
		m_Mesh = Render::Mesh::Create(cube, vertices);
		while (!m_Window.ShouldClose())
		{
			CORE_FRAME_START();
			m_Window.PollEvents();

			Render::Renderer::Clear();

			UpdateApplication();

			UpdateImGui();

			m_Window.SwapBuffers();
			CORE_FRAME_END();
		}

	}

	void Application::UpdateImGui() {
		m_ImGui.NewFrame();

		static bool s_Open = true;
		if(s_Open) ImGui::ShowDemoWindow(&s_Open);


		ImGui::Begin("Camera");
		{
			Math::Vec3 position = m_Camera.getPosition();

			if(ImGui::DragFloat3("Position", position.get(), 0.1f))
			{
				m_Camera.setPosition(position);
			}

			Math::Vec3 forward = m_Camera.getForward();

			if(ImGui::DragFloat3("Forward", forward.get(), 0.1f))
			{
				m_Camera.setForward(forward);
			}

			Math::Vec3 up = m_Camera.getUp();

			if(ImGui::DragFloat3("Up", up.get(), 0.1f))
			{
				m_Camera.setUp(up);
			}
		}
		ImGui::End();

		static std::string m_Path{};
		ImGui::Begin("Texture Creator");
		{
			ImGui::InputText("Path To Texture", &m_Path);
			if(ImGui::Button("Load")) {
				std::filesystem::path path(m_Path);
				if(!std::filesystem::exists(path)) {
					CORE_ERROR("Invalid path to texture.");
				}
				else {
					m_Path = path.generic_string();
					const char* c_path = m_Path.c_str();
					int width, height, channels;
					Core::Buffer buff;
					stbi_set_flip_vertically_on_load(true);
					buff.data = stbi_load(c_path, &width, &height, &channels, 0);
					if(buff.data) {
						buff.size = width * height * channels;
						Render::Texture2DSpecification spec;
						spec.width = width;
						spec.height = height;
						spec.channels = channels;
						spec.pixelType = Render::PixelType::PX_8;
						spec.pixelFormat = (Render::PixelFormat)channels;
						m_Texture = Render::Texture::Create(spec, buff);
						buff.Release();
					}

				}
			}
		}
		ImGui::End();


		m_ImGui.EndFrame(m_Window.GetWidth(), m_Window.GetHeight());
	}

	Application::~Application()
	{
	}

	void Application::UpdateApplication() {
		auto vao = m_Mesh->GetVertexArray();

		m_Shader->Bind();

		Math::Mat4 p = m_Camera.CalculateProjectionMatrix();
		Math::Mat4 m = Math::Mat4::Identity();
		m[3] = Math::Vec4({0, 0, -2.0f, 1});

		Math::Mat4 n = Math::Mat4::Identity();
		m_Shader->SetUniformVec3("u_CamPos", m_Camera.getPosition());
		m_Shader->SetUniformVec3("u_CamFwd", m_Camera.getForward());
		m_Shader->SetUniformVec3("u_CamUp", m_Camera.getUp());

		if(m_Texture) {
			m_Texture->Bind();
			m_Shader->SetUniformTexture("u_Texture", 0);
		}

		m_Shader->SetUniformMat4("u_ProjectionMatrix", p);
		m_Shader->SetUniformMat4("u_ModelMatrix", m);
		m_Shader->SetUniformMat4("u_NormalMatrix", n);

		vao->Bind();

		glDrawElements(GL_TRIANGLES, vao->GetDrawCount(), GL_UNSIGNED_INT, nullptr);

		vao->Unbind();
		m_Shader->Unbind();
	}
} // App