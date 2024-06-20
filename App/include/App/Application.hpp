//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include "App/Window.hpp"
#include "App/Camera.hpp"
#include "App/ImGuiContext.hpp"
#include "Core/SmartPointers.hpp"
#include "Render/Mesh.hpp"
#include "Render/Shader.hpp"

namespace App {

	class Application {
	public:
		Application(const WindowParameters& parameters);
		~Application();
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;
	public:
		void Run();
		void UpdateApplication();
		void UpdateImGui();
	private:
		Window m_Window;
		ImGuiContext m_ImGui;
	private:
		//TODO: Remove as not clean.
		Core::Ref<Render::Shader> m_Shader = nullptr;
		Core::Ref<Render::Mesh> m_Mesh = nullptr;

	private:

		Camera m_Camera;
	};

} // App
