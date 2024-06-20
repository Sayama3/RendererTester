//
// Created by ianpo on 16/06/2024.
//

#include "App/Camera.hpp"

using namespace Math;

namespace App {
	Camera::Camera() = default;
	Camera::~Camera() = default;


	// ===== GETTER / SETTERS =====

	[[nodiscard]] float Camera::getFov() const { return m_Fov; }

	void Camera::setFov(float fov) { m_Fov = fov; }

	[[nodiscard]] float Camera::getAspectRatio() const { return m_AspectRatio; }

	void Camera::setAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }

	[[nodiscard]] float Camera::getZNear() const { return m_ZNear; }

	void Camera::setZNear(float zNear) { m_ZNear = zNear; }

	[[nodiscard]] float Camera::getZFar() const { return m_ZFar; }

	void Camera::setZFar(float zFar) { m_ZFar = zFar; }

	[[nodiscard]] Math::Vec3 Camera::getPosition() const { return m_Position; }

	void Camera::setPosition(const Math::Vec3 &position) { m_Position = position; }

	// ===== Matrix =====

	[[nodiscard]] Math::Mat4 Camera::CalculateProjectionMatrix() const {
		return Math::Perspective<Real>(Math::DegToRad(m_Fov), m_AspectRatio, m_ZNear, m_ZFar);
	}

	Math::Vec3 Camera::getForward() const {
		return m_Forward;
	}

	void Camera::setForward(const Vec3 &forward) {
		m_Forward = forward;
		if(m_Forward.SqrMagnitude() < 1e-6f) {
			m_Forward = {{0,0, 1}};
		}
		else {
			m_Forward.Normalize();
		}

		auto right = Math::Cross(m_Up, m_Forward);
		right.Normalize();

		m_Up = Math::Cross(m_Forward, right);
		m_Up.Normalize();

	}

	Math::Vec3 Camera::getUp() const {
		return m_Up;
	}

	void Camera::setUp(const Vec3 &up) {
		m_Up = up;
		if(m_Up.SqrMagnitude() < 1e-6f) {
			m_Up = {{0,1,0}};
		} else {
			m_Up.Normalize();
		}

		auto right = Math::Cross(m_Up, m_Forward);
		right.Normalize();

		m_Forward = Math::Cross(right, m_Up);
		m_Forward.Normalize();

	}


} // App