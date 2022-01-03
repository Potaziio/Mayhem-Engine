#pragma once

#include <iostream>
#include <unordered_map>

#include "Shader.hpp"
#include "Texture.hpp"

namespace Mayhem {
	namespace Utils {
		struct AssetPool {
			std::unordered_map<const char*, Shader*> Shaders;
			std::unordered_map<const char*, Texture*> Textures;
			
			AssetPool(); 
			~AssetPool();
			
			void InitAssets();
			
			void AddShader(const char* shaderName);
			void AddTexture(const char* textureName);
			
			Shader* GetShader(const char* shaderName);
			Texture* GetTexture(const char* textureName);
		};
	}
}