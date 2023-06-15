#include "Timer.h"

Timer* Timer::s_Instance = nullptr;

Timer::Timer() {

}

void Timer::Tick()
{
	m_DeltaTime = (SDL_GetTicks() - m_LastTime) * (TARGET_FPS / 1000.0f);

	if (m_DeltaTime > TARGET_FRAMERATE) {
		m_DeltaTime = TARGET_FRAMERATE;
	}

	m_LastTime = (float)SDL_GetTicks();
}
