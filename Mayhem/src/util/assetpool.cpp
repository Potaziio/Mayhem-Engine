#include "AssetPool.hpp"


namespace Mayhem::Utils {
	AssetPool::~AssetPool() {
		std::cout << "Deleting assets in asset pool" << std::endl;
		
		for (auto& shader : Shaders) {
			delete shader.second;
		}
		
		for (auto& texture : Textures) {
			delete texture.second;
		}
	}
	
	AssetPool::AssetPool() {}
	
	void AssetPool::AddShader(const char* shaderName) {
		Shaders[shaderName] = new Shader();
	}
	
	void AssetPool::AddTexture(const char* textureName) {
		Textures[textureName] = new Texture();
	}
	
	void AssetPool::InitAssets() {
		for (auto& shader : Shaders) {
			shader.second->init(shader.first);
			shader.second->compile();
		}
		
		for (auto& texture : Textures) {
			texture.second->init(texture.first);
		}
	}
	
	Shader* AssetPool::GetShader(const char* shaderName) {
		return Shaders.at(shaderName);
	}
	
	Texture* AssetPool::GetTexture(const char* textureName) {
		return Textures.at(textureName);
	}
}