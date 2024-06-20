//
// Created by Sayama on 17/06/2024.
//

#pragma once

#include <cstdint>

namespace App {

	class ImGuiContext {
	public:
		ImGuiContext(const void* window, const char* glsl_version);
		~ImGuiContext();
		ImGuiContext(const ImGuiContext&) = delete;
		ImGuiContext operator=(const ImGuiContext&) = delete;
		ImGuiContext(ImGuiContext&&) = delete;
		ImGuiContext operator=(ImGuiContext&&) = delete;

	public:
		void NewFrame();
		void EndFrame(uint32_t width, uint32_t height);
	private:
	};

} // App
