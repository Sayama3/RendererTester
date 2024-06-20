//
// Created by ianpo on 01/06/2024.
//


#define STB_IMAGE_IMPLEMENTATION
#include <vendor/stb_image.h>

#include "Core/Core.hpp"
#include "App/Application.hpp"

int main(int argc, char** argv)
{
   Core::Logger::Init();

   App::WindowParameters params;
   auto* app = new App::Application(params);

   app->Run();

   delete app;

   Core::Logger::Destroy();
   return 0;
}