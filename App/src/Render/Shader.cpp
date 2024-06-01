//
// Created by ianpo on 01/06/2024.
//

#include "Render/Shader.hpp"
#include <glad/glad.h>

namespace Render {

   GLenum ShaderSourceTypeToGLType(Shader::Type sst)
   {
      switch (sst) {

         case Shader::Type::COMPUTE: return GL_COMPUTE_SHADER;
         case Shader::Type::VERTEX: return GL_VERTEX_SHADER;
         case Shader::Type::TESS_CONTROL: return GL_TESS_CONTROL_SHADER;
         case Shader::Type::TESS_EVALUATION: return GL_TESS_EVALUATION_SHADER;
         case Shader::Type::GEOMETRY: return GL_GEOMETRY_SHADER;
         case Shader::Type::FRAGMENT: return GL_FRAGMENT_SHADER;
      }
      CORE_ASSERT(false, "Unknown ShaderSource type {}", (int)sst);
      return 0;
   }

   Core::Ref<Shader> Shader::Create(std::unordered_map<Type, std::string> sources)
   {
      return Core::CreateRef<Shader>(sources);
   }

   Core::Ref<Shader> Shader::Create(std::string vertexShader, std::string fragmentShader)
   {
      return Core::CreateRef<Shader>(vertexShader, fragmentShader);
   }

   Shader::Shader(std::unordered_map<Shader::Type, std::string> sources)
   {
      for (int i = 0; i < TypeCount; ++i) {
         m_Sources[i] = std::move(sources[(Type)i]);
      }
      CORE_ASSERT(!m_Sources.empty(), "No can be created as there is no source.");
      CompileShaders();
      LinkShaders();
   }

   Shader::Shader(std::string vertexShader, std::string fragmentShader)
   {
      m_Sources[Type::FRAGMENT] = std::move(fragmentShader);
      m_Sources[Type::VERTEX] = std::move(vertexShader);
      CORE_ASSERT(!m_Sources.empty(), "No can be created as there is no source.");
      CompileShaders();
      LinkShaders();
   }

   bool Shader::CompileShaders() {
      CORE_ASSERT(!m_Sources.empty(), "No can be created as there is no source.");
      if(m_Sources.empty()) return false;

      for (uint8_t i = 0; i < TypeCount; ++i)
      {
         Type type = (Type)i;
         const std::string& source = m_Sources[i];
         CORE_ASSERT(!source.empty(), "The shader type {} is empty.", ShaderSourceTypeToString(type));
         if(source.empty()) continue;

         m_Shaders[type] = glCreateShader(ShaderSourceTypeToGLType(type));
         const char* c_source = m_Sources[type].c_str();
         CORE_ASSERT(m_Sources[type].size() < INT_MAX, "Cannot handle shader source greater than {}.", INT_MAX);
         int size = static_cast<int>(m_Sources[type].size());
         glShaderSource(m_Shaders[type].value(), 1, &c_source, &size);
         glCompileShader(m_Shaders[type].value());

         GLint vertex_compiled;
         glGetShaderiv(m_Shaders[type].value(), GL_COMPILE_STATUS, &vertex_compiled);
         if (vertex_compiled != GL_TRUE)
         {
            GLint TotalLenght=0;
            glGetShaderiv(m_Shaders[type].value(), GL_INFO_LOG_LENGTH, &TotalLenght);
            std::vector<char> logs(TotalLenght);
            glGetShaderInfoLog(m_Shaders[type].value(), TotalLenght, nullptr, logs.data());
            CORE_ERROR("{} - Shader Compilation Failed:\n{}", ShaderSourceTypeToString(type), logs.data());
            return false;
         }
      }

      return true;
   }

   bool Shader::LinkShaders() {
      m_RenderID = glCreateProgram();

      for (const auto& shader : m_Shaders) {
         if(shader) {
            glAttachShader(m_RenderID, shader.value());
         }
      }

      glLinkProgram(m_RenderID);

      GLint program_linked;
      GLint vertex_compiled;
      glGetProgramiv(m_RenderID, GL_LINK_STATUS, &vertex_compiled);
      if (vertex_compiled != GL_TRUE)
      {
         GLint TotalLenght=0;
         glGetShaderiv(m_RenderID, GL_INFO_LOG_LENGTH, &TotalLenght);
         std::vector<char> logs(TotalLenght);
         glGetProgramInfoLog(m_RenderID, TotalLenght, nullptr, logs.data());
         CORE_ERROR("Shader Linking Failed:\n{}", logs.data());
         return false;
      }
      return true;
   }

   Shader::~Shader() {
      for (auto& shader : m_Shaders) {
         if (shader) {
            glDeleteShader(shader.value());
            shader = std::nullopt;
         }
      }
      glDeleteProgram(m_RenderID);
   }

   void Shader::Bind()
   {
      glUseProgram(m_RenderID);
   }

   void Shader::Unbind()
   {
      glUseProgram(0);
   }

   uint32_t Shader::GetRenderID() const
   {
      return m_RenderID;
   }

   std::string ShaderSourceTypeToString(Shader::Type sst) {
      switch (sst) {

         case Shader::Type::COMPUTE:           return "COMPUTE";
         case Shader::Type::VERTEX:            return "VERTEX";
         case Shader::Type::TESS_CONTROL:      return "TESS_CONTROL";
         case Shader::Type::TESS_EVALUATION:   return "TESS_EVALUATION";
         case Shader::Type::GEOMETRY:          return "GEOMETRY";
         case Shader::Type::FRAGMENT:          return "FRAGMENT";
      }
      CORE_ASSERT(false, "Unknown ShaderSource type {}", (int)sst);
      return "UNKNOWN";
   }
} // Render