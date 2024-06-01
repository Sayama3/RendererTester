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

)";
      std::string fragmentShader = R"(

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

      m_Shader = Render::Shader::Create(vertexShader, fragmentShader);
      m_Mesh = Render::Mesh::Create(cube, vertices);
      auto vao = m_Mesh->GetVertexArray();
      while (!m_Window.ShouldClose())
      {
         CORE_FRAME_START();
         m_Window.PollEvents();

         Render::Renderer::Clear();
         m_Shader->Bind();
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