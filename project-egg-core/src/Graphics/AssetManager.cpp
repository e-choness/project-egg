#include "AssetManager.h"

AssetManager* AssetManager::s_Instance = nullptr;

AssetManager::AssetManager() {

}

bool AssetManager::LoadTexture(const char* id, const char* filename)
{
	SDL_Surface* surface = IMG_Load(filename);
	if (surface == nullptr) {
		SDL_Log("Failed to load texture: %s, %s", filename, SDL_GetError());
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
	SDL_FreeSurface(surface);

	if (texture == nullptr) {
		SDL_Log("Failed to create texture from image %s: %s", filename, SDL_GetError());
		return false;
	}

	m_TextureMap[id] = texture;
	return true;
}

void AssetManager::DrawTexture(const char* id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { 0, 0, width, height };
	SDL_Rect destRect = { x, y, width, height };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0.0, nullptr, flip);
}

void AssetManager::DrawFrame(const char* id, float x, float y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { width * frame, height * row, width, height };
	SDL_Rect destRect = { (int)x, (int)y, width, height };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0.0, nullptr, flip);
}

void AssetManager::DropTexture(const char* id)
{
	SDL_DestroyTexture(m_TextureMap[id]);
	m_TextureMap.erase(id);
}

void AssetManager::CleanTexture()
{
    for (auto it = m_TextureMap.begin(); it != m_TextureMap.end(); ++it) {
        SDL_DestroyTexture(it->second);
    }

	m_TextureMap.clear();
}


