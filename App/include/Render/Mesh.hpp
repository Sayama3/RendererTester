//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include "Core/Core.hpp"
#include "VertexArray.hpp"

namespace Render {

   struct Vertex {
      Math::Vec3 Position;
      Math::Vec3 Normal;
      Math::Vec2 TexCoord;
      Math::Vec4 Color = {1.0f};

      static const BufferLayout& GetBufferLayout();
   };

   class Mesh {
   public:
      [[nodiscard]] static Core::Ref<Mesh> Create(const std::vector<Vertex>& vertex);
      [[nodiscard]] static Core::Ref<Mesh> Create(const std::vector<Vertex>& vertex, std::vector<uint32_t>& indices);
   public:
      Mesh(const std::vector<Vertex>& vertex);
      Mesh(const std::vector<Vertex>& vertex, std::vector<uint32_t>& indices);
      ~Mesh();
      Mesh(const Mesh&) = delete;
      Mesh& operator=(const Mesh&) = delete;
   public:
      [[nodiscard]] Core::Ref<VertexArray> GetVertexArray() const;
   private:
      void CreateMesh(const std::vector<Vertex>& vertex, std::vector<uint32_t>& indices);
   private:
      Core::Ref<VertexArray> m_VertexArray = nullptr;
   };

} // Render
