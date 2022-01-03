#pragma once 

#include <iostream>
#include <array>

#include "../../../../include/vendor/glm/glm/glm.hpp"
#include "../../../../include/vendor/glm/glm/gtc/matrix_transform.hpp"
#include "../../../../include/vendor/glm/glm/gtc/type_ptr.hpp"
#include "../../../../include/vendor/glm/glm/gtx/string_cast.hpp"
#include "../../../../include/vendor/glm/glm/gtc/noise.hpp"

#include "../../../include/vendor/glew-2.2.0/include/GL/glew.h"
#define GLFW_INCLUDE_NONE
#include "../../../include/vendor/glfw-3.3.5/include/GLFW/glfw3.h"

#include "../math/MathUtils.hpp"

#include "../../../../include/vendor/FastNoiseLite/Cpp/FastNoiseLite.h"

#include "../math/vector/Vector3f.hpp"
#include "../math/vector/Vector2f.hpp"

namespace Mayhem {
    namespace WorldGen {
        struct Vertex {
            glm::vec3 position;
            float uv[2];
            uint8_t lightLevel;
        };
		
        struct Block {
            bool isTransparent;
            bool isEnabled = false;
			
			float lightLevel;
			
			enum BLOCK_TYPE {
				GRASS,
				DIRT,
				STONE
			};
			
			BLOCK_TYPE type;
        };
		
        struct ChunkData {
            Vertex* vertices;
            unsigned int* indices;
            Block* blocks;
			
            size_t vertexSizeBytes;
            size_t elementSizeBytes;
            int totalVertices;
        };
		
        struct Chunk {
            ChunkData data;
            Math::Vector3f offset;
			
            ~Chunk();
            Chunk(Math::Vector3f offset);
			
            Block* GetLocalBlockAt(int x, int y);
			void AddBlock(Block::BLOCK_TYPE type, int x, int y);
			void generate();
        };
    }
}
