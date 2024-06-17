//
// Created by ianpo on 16/06/2024.
//

#include "App/Camera.hpp"

using namespace Math;

namespace App {
   Camera::Camera() = default;
   Camera::~Camera() = default;


   // ===== GETTER / SETTERS =====

   float Camera::getFov() const { return m_Fov; }

   void Camera::setFov(float fov) { m_Fov = fov; }

   float Camera::getAspectRatio() const { return m_AspectRatio; }

   void Camera::setAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }

   float Camera::getZNear() const { return m_ZNear; }

   void Camera::setZNear(float zNear) { m_ZNear = zNear; }

   float Camera::getZFar() const { return m_ZFar; }

   void Camera::setZFar(float zFar) { m_ZFar = zFar; }

   Math::Vec3 Camera::getPosition() const { return m_Position; }

   void Camera::setPosition(const Math::Vec3 &position) { m_Position = position; }

   Math::Quat Camera::getRotation() const { return m_Rotation; }

   void Camera::setRotation(const Math::Quat &rotation) { m_Rotation = rotation; }

   // ===== Matrix =====

   Math::Mat4 Camera::CalculateViewMatrix() const {
      Math::Mat4 trs;
      Math::Translate(trs, m_Position);
      Math::Rotate(trs, m_Rotation);
      trs = trs.Inverse();
      return trs;
   }

   Math::Mat4 Camera::CalculateProjectionMatrix() const {
      return Math::Perspective<Real>(m_Fov, m_AspectRatio, m_ZNear, m_ZFar);
   }


} // App