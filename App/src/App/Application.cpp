//
// Created by ianpo on 01/06/2024.
//

#include "App/Application.hpp"
#include "Render/Renderer.hpp"
#include "Core/Core.hpp"

#include <glad/glad.h>
namespace App {

   Application::Application(const WindowParameters &parameters) : m_Window(parameters) {

   }

   void Application::Run() {
      Render::Renderer::SetClearColor({{0.8f, 0.2f, 0.1f}});

      std::string vertexShader = R"(
#version 450 core

uniform mat4 u_ViewProjectionMatrix = mat4(1);
uniform mat4 u_ModelMatrix = mat4(1);
uniform mat4 u_NormalMatrix = mat4(1);

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec4 a_Color;

layout (location = 0) out vec3 v_Position;
layout (location = 1) out vec3 v_Normal;
layout (location = 2) out vec2 v_TexCoord;
layout (location = 3) out vec4 v_Color;


void main() {
    gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
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


layout (location = 0) out vec4 o_Color;

layout (location = 0) in vec3 v_Position;
layout (location = 1) in vec3 v_Normal;
layout (location = 2) in vec2 v_TexCoord;
layout (location = 3) in vec4 v_Color;

void main()
{
   o_Color = vec4(v_Position, 1.0);
}
)";

      std::vector<Render::Vertex> cube {
            //Front Face
            Render::Vertex(Math::Vec3({-0.5f, -0.5f, +0.5f}), Math::Vec3({0,0,+1}), Math::Vec2({0,0})), // 0
            Render::Vertex(Math::Vec3({+0.5f, -0.5f, +0.5f}), Math::Vec3({0,0,+1}), Math::Vec2({1,0})), // 1
            Render::Vertex(Math::Vec3({+0.5f, +0.5f, +0.5f}), Math::Vec3({0,0,+1}), Math::Vec2({1,1})), // 2
            Render::Vertex(Math::Vec3({-0.5f, +0.5f, +0.5f}), Math::Vec3({0,0,+1}), Math::Vec2({0,1})), // 3
            //Front Face
            Render::Vertex(Math::Vec3({-0.5f, -0.5f, -0.5f}), Math::Vec3({0,0,-1}), Math::Vec2({0,0})), // 4
            Render::Vertex(Math::Vec3({+0.5f, -0.5f, -0.5f}), Math::Vec3({0,0,-1}), Math::Vec2({1,0})), // 5
            Render::Vertex(Math::Vec3({+0.5f, +0.5f, -0.5f}), Math::Vec3({0,0,-1}), Math::Vec2({1,1})), // 6
            Render::Vertex(Math::Vec3({-0.5f, +0.5f, -0.5f}), Math::Vec3({0,0,-1}), Math::Vec2({0,1})), // 7
            //Up Face
            Render::Vertex(Math::Vec3({-0.5f, +0.5f, -0.5f}), Math::Vec3({0,+1, 0}), Math::Vec2({0,0})), // 8
            Render::Vertex(Math::Vec3({+0.5f, +0.5f, -0.5f}), Math::Vec3({0,+1, 0}), Math::Vec2({1,0})), // 9
            Render::Vertex(Math::Vec3({+0.5f, +0.5f, +0.5f}), Math::Vec3({0,+1, 0}), Math::Vec2({1,1})), // 10
            Render::Vertex(Math::Vec3({-0.5f, +0.5f, +0.5f}), Math::Vec3({0,+1, 0}), Math::Vec2({0,1})), // 11
            //Down Face
            Render::Vertex(Math::Vec3({-0.5f, -0.5f, -0.5f}), Math::Vec3({0,-1, 0}), Math::Vec2({0,0})), // 12
            Render::Vertex(Math::Vec3({+0.5f, -0.5f, -0.5f}), Math::Vec3({0,-1, 0}), Math::Vec2({1,0})), // 13
            Render::Vertex(Math::Vec3({+0.5f, -0.5f, +0.5f}), Math::Vec3({0,-1, 0}), Math::Vec2({1,1})), // 14
            Render::Vertex(Math::Vec3({-0.5f, -0.5f, +0.5f}), Math::Vec3({0,-1, 0}), Math::Vec2({0,1})), // 15
            //Right Face
            Render::Vertex(Math::Vec3({+0.5f, -0.5f, -0.5f}), Math::Vec3({+1, 0, 0}), Math::Vec2({0,0})), // 16
            Render::Vertex(Math::Vec3({+0.5f, +0.5f, -0.5f}), Math::Vec3({+1, 0, 0}), Math::Vec2({1,0})), // 17
            Render::Vertex(Math::Vec3({+0.5f, +0.5f, +0.5f}), Math::Vec3({+1, 0, 0}), Math::Vec2({1,1})), // 18
            Render::Vertex(Math::Vec3({+0.5f, -0.5f, +0.5f}), Math::Vec3({+1, 0, 0}), Math::Vec2({0,1})), // 19
            //Left Face
            Render::Vertex(Math::Vec3({-0.5f, -0.5f, -0.5f}), Math::Vec3({-1, 0, 0}), Math::Vec2({0,0})), // 20
            Render::Vertex(Math::Vec3({-0.5f, +0.5f, -0.5f}), Math::Vec3({-1, 0, 0}), Math::Vec2({1,0})), // 21
            Render::Vertex(Math::Vec3({-0.5f, +0.5f, +0.5f}), Math::Vec3({-1, 0, 0}), Math::Vec2({1,1})), // 22
            Render::Vertex(Math::Vec3({-0.5f, -0.5f, +0.5f}), Math::Vec3({-1, 0, 0}), Math::Vec2({0,1})), // 23

      };

      std::vector<uint32_t> vertices {
            // Front
            0,1,2,
            0,2,3,
            // Back
            4,6,5,
            4,7,6,
            // Up
            8,10,9,
            8,11,10,
            // Down
            12,13,14,
            12,14,15,
            // Front
            16,17,18,
            16,18,19,
            // Back
            20,22,21,
            20,23,22,
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
      auto vao = m_Mesh->GetVertexArray();
      while (!m_Window.ShouldClose())
      {
         CORE_FRAME_START();
         m_Window.PollEvents();

         Render::Renderer::Clear();
         m_Shader->Bind();

         Math::Mat4 vp = Math::Perspective(Math::DegToRad(60.0f), 900.f/600.f, 0.1f, 100.f);
         Math::Mat4 m = Math::Mat4::Identity();
         m[3] = Math::Vec4({0.65f, 0.65f, -2.0f, 1});
         Math::Mat4 n = Math::Mat4::Identity();
         m_Shader->SetUniformMat4("u_ViewProjectionMatrix", vp);
         m_Shader->SetUniformMat4("u_ModelMatrix", m);
         m_Shader->SetUniformMat4("u_NormalMatrix", n);

         vao->Bind();

         glDrawElements(GL_TRIANGLES, vao->GetDrawCount(), GL_UNSIGNED_INT, nullptr);

         vao->Unbind();
         m_Shader->Unbind();

         m_Window.SwapBuffers();
         CORE_FRAME_END();
      }

   }

   Application::~Application()
   {
   }
} // App