#include "Chunk.hpp"

namespace Mayhem::WorldGen {
    const int CHUNK_SIZE_X = 16;
	const int CHUNK_SIZE_Y = 128;
    const int CHUNK_DIMENSIONS = CHUNK_SIZE_X * CHUNK_SIZE_Y;
	Block AIR_BLOCK;
	
	std::array<float, CHUNK_DIMENSIONS> GenerateHeightMap(Math::Vector3f offset, float frequency) {
		std::array<float, CHUNK_DIMENSIONS> heightMap;
		
		for (int x = 0; x < CHUNK_SIZE_X; x++) {
			for (int y = 0; y < CHUNK_SIZE_Y; y++) {
				float value = glm::simplex(glm::vec2((float)(x + offset.x) * frequency, (float)(y + offset.y) * frequency));
				heightMap[y * CHUNK_SIZE_X + x] = value;
			}
		}
		
		return heightMap;
	}
	
	float GetHeightMapPoint(std::array<float, CHUNK_DIMENSIONS> heightMap, int x, int y) {
		return heightMap[y * CHUNK_SIZE_X + x];
	}
	
	void GenerateTerrain(std::array<float, CHUNK_DIMENSIONS> heightMap, Chunk* chunk, int maxHeight) {
		for (int x = 0; x < CHUNK_SIZE_X; x++) {
			for (int y = 0; y < CHUNK_SIZE_Y; y++) {
				chunk->GetLocalBlockAt(x, y)->isEnabled = true;
			}
		}
		
		for (int x = 0; x < CHUNK_SIZE_X; x++) {
			float value = (GetHeightMapPoint(heightMap, x, 0.0f) * (maxHeight - 1) * 1.0f) * 1.0f;
			for (int y = 0; y < value; y++) {
				chunk->GetLocalBlockAt(x, (int)y)->isEnabled = false;
			}
		}
		
		for (int x = 0; x < CHUNK_SIZE_X; x++) {
			for (int y = 0; y < CHUNK_SIZE_Y; y++) {
				if (!chunk->GetLocalBlockAt(x, y - 1)->isEnabled) {
					// Sets Grass
					chunk->GetLocalBlockAt(x, y)->type = Block::BLOCK_TYPE::GRASS;
				} else {
					if (y > 20) {
						// Generates Rock
						if (y < 30) {
							if (Math::Utils::randInt(0, 2) == 2) {
								//Stone
								chunk->GetLocalBlockAt(x, y)->type = Block::BLOCK_TYPE::DIRT;
							} else {
								// Dirt
								chunk->GetLocalBlockAt(x, y)->type = Block::BLOCK_TYPE::DIRT;
							}
						} else {
							if (Math::Utils::randInt(0, 1) == 0) {
								// Stone
								chunk->GetLocalBlockAt(x, y)->type = Block::BLOCK_TYPE::STONE;
							} else {
								// Dirt
								chunk->GetLocalBlockAt(x, y)->type = Block::BLOCK_TYPE::DIRT;
							}
						}
					} else {
						// Generates Dirt or a chance for stone
						if (Math::Utils::randInt(0, 5) == 1 && y > 10) {
							chunk->GetLocalBlockAt(x, y)->type = Block::BLOCK_TYPE::STONE;
						}
						else {
							chunk->GetLocalBlockAt(x, y)->type = Block::BLOCK_TYPE::DIRT;
						}
					}
				}
			}
		}
	}
	
	void AddTile(Vertex* vertices, uint8_t type, int uvCursor) {
		// 0 Grass
		// 1 Dirt
		// 2 Stone
		
		switch(type) {
			case 0:
			vertices[uvCursor].uv[0] = 0.3;
			vertices[uvCursor].uv[1] = 0;
			
			vertices[uvCursor + 1].uv[0] = 0;
			vertices[uvCursor + 1].uv[1] = 0;
			
			vertices[uvCursor + 2].uv[0] = 0.3;
			vertices[uvCursor + 2].uv[1] = 1;
			
			vertices[uvCursor + 3].uv[0] = 0;
			vertices[uvCursor + 3].uv[1] = 1;
			break;
			case 1:
			vertices[uvCursor].uv[0] = 0.64;
			vertices[uvCursor].uv[1] = 0;
			
			vertices[uvCursor + 1].uv[0] = 0.34;
			vertices[uvCursor + 1].uv[1] = 0;
			
			vertices[uvCursor + 2].uv[0] = 0.64;
			vertices[uvCursor + 2].uv[1] = 1;
			
			vertices[uvCursor + 3].uv[0] = 0.34;
			vertices[uvCursor + 3].uv[1] = 1;
			break;
			case 2:
			vertices[uvCursor].uv[0] = 1;
			vertices[uvCursor].uv[1] = 0;
			
			vertices[uvCursor + 1].uv[0] = 0.68;
			vertices[uvCursor + 1].uv[1] = 0;
			
			vertices[uvCursor + 2].uv[0] = 1;
			vertices[uvCursor + 2].uv[1] = 1;
			
			vertices[uvCursor + 3].uv[0] = 0.68;
			vertices[uvCursor + 3].uv[1] = 1;
			break;
			default:
			std::cout << "This Block type does not exist-> " << type << std::endl;
			break;
		}
	}
	
	void Chunk::AddBlock(Block::BLOCK_TYPE type, int x, int y) {
	}
	
	Chunk::~Chunk() {
		delete data.vertices;
		delete data.indices;
		delete data.blocks;
	}
	
	Block* Chunk::GetLocalBlockAt(int x, int y) {
		if (x < 0 || y < 0)
			return &AIR_BLOCK;
		
		if (x < CHUNK_SIZE_X && y < CHUNK_SIZE_Y)
			return &data.blocks[y * CHUNK_SIZE_X + x];
		else 
			return &AIR_BLOCK;
	}
	
	Chunk::Chunk(Math::Vector3f offset)
		: offset(offset) {
		data.vertices = new Vertex[sizeof(Vertex) * CHUNK_DIMENSIONS * 4];
		data.blocks = new Block[sizeof(Block) * CHUNK_DIMENSIONS];
		data.indices = new unsigned int[sizeof(unsigned int) * CHUNK_DIMENSIONS * 6];
		data.vertexSizeBytes = (sizeof(Vertex) * CHUNK_DIMENSIONS * 4);
		data.elementSizeBytes = (sizeof(unsigned int) * CHUNK_DIMENSIONS * 6);
		data.totalVertices = 6 * CHUNK_DIMENSIONS;
		
		std::array<float, CHUNK_DIMENSIONS> heightMap = GenerateHeightMap(offset, 0.015f);
		GenerateTerrain(heightMap, this, 10);
	}
	
	void Chunk::generate() {
		int indexCursor = 0;
		int indexOffsetCursor = 0;
		int vertexCursor = 0; 
		int uvCursor = 0;
		int lightCursor = 0;
		int lastX = 0;
		float lightLevel = 1.0f;
		
		for (int y = 0; y > -CHUNK_SIZE_Y; y--) {
			for (int x = 0; x < CHUNK_SIZE_X; x++) {
				if (!GetLocalBlockAt(x, -y)->isEnabled) {continue;}
				
				Vertex verts[4];
				verts[0].position = glm::vec3(x + 0.0f + offset.x, y + 0.0f + offset.y, offset.z + 0.0f); // Top Left
				verts[1].position = verts[0].position + glm::vec3(1.0f, 0.0f, 0.0f);  // Top Right 
				verts[2].position = verts[0].position + glm::vec3(0.0f, 1.0f, 0.0f); // Bottom Left
				verts[3].position = verts[0].position + glm::vec3(1.0f, 1.0f, 0.0f);  // Bottom Right
				
				// Vertices
				
				AddTile(data.vertices, GetLocalBlockAt(x, -y)->type, uvCursor);
				
				data.vertices[vertexCursor].position = verts[0].position;
				data.vertices[vertexCursor + 1].position = verts[1].position;
				data.vertices[vertexCursor + 2].position = verts[2].position;
				data.vertices[vertexCursor + 3].position = verts[3].position;
				
				data.vertices[lightCursor].lightLevel = lightLevel * 10.0f;
				data.vertices[lightCursor + 1].lightLevel = lightLevel * 10.0f;
				data.vertices[lightCursor + 2].lightLevel = lightLevel * 10.0f;
				data.vertices[lightCursor + 3].lightLevel = lightLevel * 10.0f;
				
				data.indices[indexCursor + 0] = indexOffsetCursor + 2;
				data.indices[indexCursor + 1] = indexOffsetCursor + 0;
				data.indices[indexCursor + 2] = indexOffsetCursor + 1;
				
				data.indices[indexCursor + 3] = indexOffsetCursor + 2;
				data.indices[indexCursor + 4] = indexOffsetCursor + 1;
				data.indices[indexCursor + 5] = indexOffsetCursor + 3;
				
				lightCursor += 4;
				vertexCursor += 4;
				uvCursor += 4;
				indexOffsetCursor += 4;
				indexCursor += 6;
				
				lastX = x;
			}
			
			if (GetLocalBlockAt(lastX, -(y) - 1)->isEnabled && lightLevel > 0.3)
				lightLevel -= 0.1f;
		}
	}
}
