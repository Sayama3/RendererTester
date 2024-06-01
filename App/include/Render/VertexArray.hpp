//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include "Buffer.hpp"
#include "Core/Buffer.hpp"
#include <cstdint>
#include <optional>

namespace Render {

   class VertexArray {
   public:
      [[nodiscard]] static Core::Ref<VertexArray> Create();
   public:
      VertexArray();
      ~VertexArray();
      VertexArray(const VertexArray&) = delete;
      VertexArray operator=(const VertexArray&) = delete;
   public:
      void Bind();
      void Unbind();

      std::optional<uint32_t> AddVertexBuffer(Core::Ref<VertexBuffer> vb);
      bool SetVertexBuffer(uint32_t index, Core::Ref<VertexBuffer> vb);
      void RemoveVertexBuffer(uint32_t index);

      void SetIndexBuffer(Core::Ref<IndexBuffer> vb);
      [[nodiscard]] uint32_t GetRenderID() const;

      uint32_t GetDrawCount() const;
   private:
      uint32_t m_RenderID;
      std::vector<Core::Ref<VertexBuffer>> m_VertexBuffer {};
      Core::Ref<IndexBuffer> m_IndexBuffer = nullptr;
   };

} // Render
