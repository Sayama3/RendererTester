//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include <tracy/Tracy.hpp>

#ifndef CORE_DONT_PROFILE

#define CORE_PROFILE_BEGIN_SESSION(name, filepath)
#define CORE_PROFILE_END_SESSION()
#define CORE_FRAME_START() FrameMark//FrameMarkStart(s_MainFrame)
#define CORE_FRAME_END() //FrameMarkEnd(s_MainFrame)
#define CORE_PROFILE_SCOPE(name) ZoneScopedN(name)
#define CORE_PROFILE_FUNCTION() ZoneScoped

#else

#define CORE_PROFILE_BEGIN_SESSION(name, filepath)
#define CORE_PROFILE_END_SESSION()
#define CORE_FRAME_START()
#define CORE_FRAME_END()
#define CORE_PROFILE_SCOPE(name)
#define CORE_PROFILE_FUNCTION()

#endif