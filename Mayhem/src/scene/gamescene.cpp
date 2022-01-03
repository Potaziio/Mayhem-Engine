#include "GameScene.hpp"

#include <tuple>

// TODO: THIS WEEK

// TODO: Physics based movement

// TODO: Collision response

// TODO: AssetPool, Constructor takes in a name and a shader, (Map that has the shader name as key and the shader as val)
// When given a shader name, if it already exists it will check the key to see and the shader path to see if its the same
// If it is the same it will skip, if its a different one it will skip and warn the user

GameObject* Player = new GameObject("Player", Transform(Vector3f(0.0f, 0.0f, -20.0f), Vector3f(2.0f, 2.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f)));

GameObject* Enemy = new GameObject("Enemy", Transform(Vector3f(0.0f, 10.0f, -20.0f), Vector3f(10.0f, 2.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f)));

Texture texture;

AssetPool assetPool;

float playerSpeed = 30.0f;
float mouseMoveSpeed = 30.0f;

ImVec4 win_color = ImVec4(84.0f / 255.0f, 255.0f / 240.0f, 214.0f / 255.0f , 255.0f / 255.0f);

ChunkManager* chunkManager;

void Scenes::GameScene::Start() {
    std::cout << "On Runtime Scene" << std::endl;
	this->PerspectiveCamera = new ECS::PerspectiveCamera(Vector3f(0.0f, 0.0f, 20.0f), 75.0f, Window::getWidth(), Window::getHeight(), 0.0f, 1000.0f);
	
	chunkManager = new ChunkManager();
	chunkManager->GenerateChunks();
	
	assetPool.AddShader("../Mayhem/assets/shaders/defaultmesh.glsl");
	assetPool.AddShader("../Mayhem/assets/shaders/chunk.glsl");
	assetPool.InitAssets();
	
	texture.init("../Mayhem/assets/textures/texture_atlas.png"); 
	
	Player->AddComponent(SpriteRenderer(assetPool.GetShader("../Mayhem/assets/shaders/defaultmesh.glsl"), Vector4f(RGBANORM(255.0f, 255.0f, 0.0f, 255.0f)), Draw::Sprite2D::Rect()));
	Enemy->AddComponent(SpriteRenderer(assetPool.GetShader("../Mayhem/assets/shaders/defaultmesh.glsl"), Vector4f(RGBANORM(255.0f, 0.0f, 0.0f, 255.0f)), Draw::Sprite2D::Rect()));
	
	this->addGameObjectToScene(Enemy);
	this->addGameObjectToScene(Player);
	this->addGameObjectToScene(PerspectiveCamera);
}

void Scenes::GameScene::Update() {
	glClearColor(win_color.x, win_color.y, win_color.z, win_color.w);
	
	Vector3f velocity = Vector3f(Input::KeyboardListener::GetAxisRaw("Horizontal"), Input::KeyboardListener::GetAxisRaw("Vertical"), 0.0f);
	velocity.Normalize();
	
	Player->transform->position += (velocity * playerSpeed) * Time::deltaTime();
	
	float xOffset = Input::MouseListener::GetDeltaMousePos().x;
	float yOffset = Input::MouseListener::GetDeltaMousePos().y;
	
	this->PerspectiveCamera->transform->position.x = Player->transform->position.x;
	this->PerspectiveCamera->transform->position.y = Player->transform->position.y + 6;
	
	this->PerspectiveCamera->transform->position.z -= Input::MouseListener::GetMouseScroll();
	
	assetPool.GetShader("../Mayhem/assets/shaders/chunk.glsl")->use();
	texture.bind();
	
	assetPool.GetShader("../Mayhem/assets/shaders/chunk.glsl")->sendMat4("projection", this->PerspectiveCamera->GetProjectionMatrix());
	assetPool.GetShader("../Mayhem/assets/shaders/chunk.glsl")->sendMat4("view", this->PerspectiveCamera->GetViewMatrix());
	
	chunkManager->UpdateChunks();
	texture.unbind();
	
	assetPool.GetShader("../Mayhem/assets/shaders/chunk.glsl")->detach();
}

void Scenes::GameScene::GuiUpdate() {
	ImGui::Begin("Window");
	ImGui::ColorEdit4("Window Color", (float*)&win_color);
	ImGui::End();
	
	ImGui::Begin("Performance");
	ImGui::Text("FPS: %.1f", (0.001f / ((float)Time::deltaTime() / 1000.0f)));
	ImGui::End();
	
	ImGui::Begin("World");
	if (ImGui::Button("Reload chunks")) {
		chunkManager->RegenerateAllChunks();
	}
	ImGui::End();
}
