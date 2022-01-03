#pragma once

#include "../../../include/vendor/glew-2.2.0/include/GL/glew.h"
#define GLFW_INCLUDE_NONE
#include "../../../include/vendor/glfw-3.3.5/include/GLFW/glfw3.h"

#include "Chunk.hpp"

#include <vector>

namespace Mayhem {
	namespace WorldGen {
		class ChunkManager {
			private:
			unsigned int* VAOs;
			unsigned int* VBOs;
			unsigned int* EBOs;
			
			const int CHUNK_NUMBER = 60;
			std::vector<Chunk*> chunks;
			
			public:
			~ChunkManager();
			
			std::vector<Chunk*> GetChunks() {return this->chunks;}
			Chunk* GetChunkAt(int x);
			
			void RegenerateChunkAt(int x);
			void RegenerateChunk(Chunk* chunk);
			void RegenerateAllChunks();
			void GenerateChunks();
			void UpdateChunks();
		};
	}
	
}