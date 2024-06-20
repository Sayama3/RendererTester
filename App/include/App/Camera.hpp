//
// Created by ianpo on 16/06/2024.
//

#pragma once

#include "Math/Math.hpp"

namespace App {

   class Camera {
   public:
      Camera();
      ~Camera();

   public:
      // FOV getters and setters
      [[nodiscard]] float getFov() const;
      void setFov(float fov);

      // Aspect Ratio getters and setters
      [[nodiscard]] float getAspectRatio() const;
      void setAspectRatio(float aspectRatio);

      // ZNear getters and setters
      [[nodiscard]] float getZNear() const;
      void setZNear(float zNear);

      // ZFar getters and setters
      [[nodiscard]] float getZFar() const;
      void setZFar(float zFar);

      // Position getters and setters
      [[nodiscard]] Math::Vec3 getPosition() const;
      void setPosition(const Math::Vec3& position);

      // Forward getters and setters
      [[nodiscard]] Math::Vec3 getForward() const;
      void setForward(const Math::Vec3& forward);

      // Up getters and setters
      [[nodiscard]] Math::Vec3 getUp() const;
      void setUp(const Math::Vec3& up);

   public:
      [[nodiscard]] Math::Mat4 CalculateViewMatrix() const;
      [[nodiscard]] Math::Mat4 CalculateProjectionMatrix() const;

   private:
      float m_Fov = 60.0f;
      float m_AspectRatio = 900.0f / 600.0f;
      float m_ZNear = 0.1f, m_ZFar = 100.f;

      Math::Vec3 m_Position {0};
      Math::Vec3 m_Forward {{0, 0, 1}};
      Math::Vec3 m_Up {{0, 1, 0}};
   };

} // App
