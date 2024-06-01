//
// Created by ianpo on 01/06/2024.
//

#include "Render/Mesh.hpp"

namespace Render {

   const BufferLayout& Vertex::GetBufferLayout() {
      static BufferLayout bl = {
            {BufferDataType::FLOAT3, "Position"},
            {BufferDataType::FLOAT3, "Normal"},
            {BufferDataType::FLOAT2, "TexCoord"},
            {BufferDataType::FLOAT4, "Color"},
      };
      return bl;
   }

   Core::Ref<Mesh> Mesh::Create(const std::vector<Vertex> &vertex) {
      return Core::CreateRef<Mesh>(vertex);
   }

   Core::Ref<Mesh> Mesh::Create(const std::vector<Vertex> &vertex, std::vector<uint32_t> &indices) {
      return Core::CreateRef<Mesh>(vertex, indices);
   }

   Mesh::Mesh(const std::vector<Vertex> &vertex) {
      CORE_PROFILE_FUNCTION();
      std::vector<uint32_t> indices(vertex.size());
      for (int i = 0; i < vertex.size(); ++i) indices[i] = i;
      CreateMesh(vertex, indices);
   }

   Mesh::Mesh(const std::vector<Vertex> &vertex, std::vector<uint32_t> &indices) {
      CreateMesh(vertex, indices);
   }


   Core::Ref<VertexArray> Mesh::GetVertexArray() const {
      return m_VertexArray;
   }

   void Mesh::CreateMesh(const std::vector<Vertex> &vertex, std::vector<uint32_t> &indices)
   {
      CORE_PROFILE_FUNCTION();
      m_VertexArray = Core::CreateRef<VertexArray>();

      Core::Ref<IndexBuffer> indexBuffer = Core::CreateRef<IndexBuffer>(Core::Buffer{indices.data(), indices.size()});
      m_VertexArray->SetIndexBuffer(indexBuffer);

      Core::Ref<VertexBuffer> vertexBuffer = Core::CreateRef<VertexBuffer>(Core::Buffer{const_cast<Vertex*>(vertex.data()), vertex.size()});
      vertexBuffer->SetLayout(Vertex::GetBufferLayout());
      m_VertexArray->AddVertexBuffer(vertexBuffer);
   }

   Mesh::~Mesh() = default;

} // Render