#include "Engine.h"
#include "Graphics/AssetManager.h"

Engine* Engine::s_Instance = nullptr;
Ghost* ghost = nullptr;
Properties* ghostProperties = nullptr;

Engine::Engine(): m_window(nullptr), m_renderer(nullptr), m_IsRunning(false), m_EventsHandler(nullptr), m_LevelMap(nullptr) {
	SDL_Log("The engine now has the one and only instance.");
}

Engine* Engine::GetInstance()
{
	return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
}

bool Engine::Init()
{
	// Check
	m_IsRunning = InitCheck();
	if (!m_IsRunning) { return m_IsRunning; }

	// Set window flags
	auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
	
	// Initialize display window
	m_window = new Window("Egg Engine", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_VULKAN);

	// Initialize renderer in the window
	m_renderer = new Renderer(m_window->GetInstance(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_IsRunning = m_window->IsRunning() && m_renderer->IsRunning();

	m_EventsHandler = new EventsHandler();

	if (MapParser::GetInstance()->Load()) {
		SDL_Log("Failed to load the map. Error: %s", SDL_GetError());
	}

	m_LevelMap = MapParser::GetInstance()->GetMap("MAP");

	// Load character textures
	m_IsRunning = AssetManager::GetInstance()->LoadTexture("ghost-floating", "../ghost-sheet.png");
	m_IsRunning = AssetManager::GetInstance()->LoadTexture("ghost-running", "../ghost-run-sheet.png");
	ghostProperties = new Properties("ghost-floating", 100.0f, 50.0f, 50, 55);
	ghost = new Ghost(ghostProperties);
	
	Transform transform;
	transform.Log("This transformation is: ");
	
	return m_IsRunning;
}

bool Engine::Clean()
{
	if (ghost) {
		ghost->Clean();
		delete ghost;
		SDL_Log("The textures now have been cleaned.");
	}

	if (m_EventsHandler) {
		delete m_EventsHandler;
		SDL_Log("The events handler now has been cleaned.");
	}

	if (m_renderer) {
		SDL_DestroyRenderer(m_renderer->GetInstance());
		delete m_renderer;
		SDL_Log("The renderer now has been cleaned.");
	}

	if (m_window) {
		SDL_DestroyWindow(m_window->GetInstance());
		delete m_window;
		SDL_Log("The window now has been cleaned.");
	}

	AssetManager::GetInstance()->CleanTexture();
	SDL_Log("The asset manager now has been cleaned.");

	IMG_Quit();
	SDL_Quit();

	if (s_Instance) {
		delete s_Instance;
		SDL_Log("The engine now has been cleaned.");
		return true;
	}

	SDL_Log("The engine has trouble clean up everything.");
	return false;
}

void Engine::Quit()
{
	m_IsRunning = false;
	SDL_Log("The engine is quiting...");
}

void Engine::Update()
{
	float deltaTime = Timer::GetInstance()->GetDeltaTime();
	m_LevelMap->Update();
	ghost->Update(deltaTime);
}

void Engine::Render()
{
	//SDL_Log("The engine is rendering images.");
	SDL_SetRenderDrawColor(m_renderer->GetInstance(), 124, 218, 254, 255);
	SDL_RenderClear(m_renderer->GetInstance());
	m_LevelMap->Render();
	ghost->Render();
	SDL_RenderPresent(m_renderer->GetInstance());
}

void Engine::Events()
{	
	// Listening to game events
	InputSystem::GetInstance()->Listen();
}

bool Engine::InitCheck() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	SDL_Log("The engine is initialized and running.");
	return true;
}


SDL_Renderer* Engine::GetRenderer()
{
	return m_renderer->GetInstance();
}