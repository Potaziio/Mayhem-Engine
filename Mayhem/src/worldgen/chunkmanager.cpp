#include "ChunkManager.hpp"


namespace Mayhem::WorldGen {
	ChunkManager::~ChunkManager() {
		for (int x = 0; x < CHUNK_NUMBER; x++) {
			glDeleteVertexArrays(1, &VAOs[x]);
			glDeleteBuffers(1, &EBOs[x]);
			glDeleteBuffers(1, &VBOs[x]);
			
			delete chunks[x];
			delete &VAOs[x];
			delete &EBOs[x];
			delete &VBOs[x];
		}
	}
	
	Chunk* ChunkManager::GetChunkAt(int x) {
		int fx = std::floor(x / 16);
		
		if (fx < CHUNK_NUMBER && fx > -1) 
			return chunks[(int)round(fx)];
		else 
			return nullptr;
	}
	
	void ChunkManager::RegenerateChunkAt(int x) {
		GetChunkAt(x)->generate();
		glBindVertexArray(VAOs[(int)std::floor(x / 16)]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[(int)std::floor(x / 16)]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, GetChunkAt(x)->data.vertexSizeBytes, GetChunkAt(x)->data.vertices);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	void ChunkManager::RegenerateChunk(Chunk* chunk) {
		chunk->generate();
		
		float x = chunk->offset.x;
		
		glBindVertexArray(VAOs[(int)std::floor(x / 16)]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[(int)std::floor(x / 16)]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, chunk->data.vertexSizeBytes, chunk->data.vertices);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	void ChunkManager::RegenerateAllChunks() {
		for (int i = 0; i < CHUNK_NUMBER; i++) {
			chunks[i]->generate();
			glBindVertexArray(VAOs[i]);
			glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
			glBufferSubData(GL_ARRAY_BUFFER, 0, chunks[i]->data.vertexSizeBytes, chunks[i]->data.vertices);
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
	
	void ChunkManager::GenerateChunks() {
		VAOs = new unsigned int[sizeof(unsigned int) * CHUNK_NUMBER];
		EBOs = new unsigned int[sizeof(unsigned int) * CHUNK_NUMBER];
		VBOs = new unsigned int[sizeof(unsigned int) * CHUNK_NUMBER];
		
		for (int x = 0; x < CHUNK_NUMBER; x++) {
			chunks.push_back(new Chunk(Math::Vector3f((x * 16.0f), 0.0f, -20.0f)));
			chunks[x]->generate();
			glGenVertexArrays(1, &VAOs[x]);
			glGenBuffers(1, &VBOs[x]);
			glGenBuffers(1, &EBOs[x]);
			
			glBindVertexArray(VAOs[x]);
			glBindBuffer(GL_ARRAY_BUFFER, VBOs[x]);
			glBufferData(GL_ARRAY_BUFFER, chunks[x]->data.vertexSizeBytes, chunks[x]->data.vertices, GL_DYNAMIC_DRAW);
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[x]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunks[x]->data.elementSizeBytes, chunks[x]->data.indices, GL_DYNAMIC_DRAW);
			
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			glEnableVertexAttribArray(0);
			
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			
			glVertexAttribPointer(2, 1, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float) + 2 * sizeof(float)));
			glEnableVertexAttribArray(2);
			
			glBindVertexArray(0);
		}
	}
	
	void ChunkManager::UpdateChunks() {
		for (int x = 0; x < CHUNK_NUMBER; x++) {
			glBindVertexArray(VAOs[x]);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			
			glDrawElements(GL_TRIANGLES, chunks[x]->data.totalVertices, GL_UNSIGNED_INT, 0);
			
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
		}
	}
}
