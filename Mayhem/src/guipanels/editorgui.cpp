#include  "EditorGUI.hpp"

static char holder[64];

void Mayhem::Utils::GUI::EditorGUI::onEditorGuiUpdate() {
    if (Window::getCurrentScene()->sceneType != Scenes::Scene::EDITORSCENE) { return; }

    ImGui::Begin("Editor Scene");

    if (ImGui::CollapsingHeader("Scene Hyerarchy")) {
        for (auto& go : Window::getCurrentScene()->GetGameObjects()) {
            if (ImGui::TreeNode(go.second->getName().c_str())) {
                ImGui::Text("ID: %s", go.second->getID().id().c_str());

                // GameObject state
                switch (go.second->state) {
                    case GameObject::SELECTED: {
                        ImGui::Text("State: Selected");
                        break;
                    }
                    case GameObject::MOUSEHOVER: {
                        ImGui::Text("State: Hovered");
                        break;
                    }
                    case GameObject::DEFAULT: {
                        ImGui::Text("State: Default");
                        break;
                    }
                }

                // Components

                if (ImGui::CollapsingHeader("Properties")) {
                    float lineHeight = ImGui::GetFont()->FontSize + ImGui::GetStyle().FramePadding.y * 2.0f;

                    ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

                    // Transform

                    ImGui::Text("Transform");
                    ImGui::Text("Position");
                    ImGui::SameLine();
                    if (ImGui::Button("X", buttonSize))
                        go.second->transform->position.x = 0.0f;
                    ImGui::SameLine();
                    ImGui::PushItemWidth(50);
                    ImGui::DragFloat("##X", &go.second->transform->position.x, 0.1f);
                    ImGui::PopItemWidth();
                    ImGui::SameLine();

                    if (ImGui::Button("Y", buttonSize))
                        go.second->transform->position.y = 0.0f;
                    ImGui::SameLine();
                    ImGui::PushItemWidth(50);
                    ImGui::DragFloat("##Y", &go.second->transform->position.y, 0.1f);
                    ImGui::PopItemWidth();
                    ImGui::SameLine();

                    if (ImGui::Button("Z", buttonSize))
                        go.second->transform->position.z = 0.0f;
                    ImGui::SameLine();
                    ImGui::PushItemWidth(50);
                    ImGui::DragFloat("##Z", &go.second->transform->position.z, 0.1f);
                    ImGui::PopItemWidth();

                    // Scale

                    ImGui::Text("Scale");
                    ImGui::SameLine();
                    if (ImGui::Button("X", buttonSize))
                        go.second->transform->scale.x = 0.0f;
                    ImGui::SameLine();
                    ImGui::PushItemWidth(50);
                    ImGui::DragFloat("###X", &go.second->transform->scale.x, 0.1f);
                    ImGui::PopItemWidth();
                    ImGui::SameLine();

                    if (ImGui::Button("Y", buttonSize))
                        go.second->transform->scale.y = 0.0f;
                    ImGui::SameLine();
                    ImGui::PushItemWidth(50);
                    ImGui::DragFloat("###Y", &go.second->transform->scale.y, 0.1f);
                    ImGui::PopItemWidth();
                    ImGui::SameLine();

                    if (ImGui::Button("Z", buttonSize))
                        go.second->transform->scale.z = 0.0f;
                    ImGui::SameLine();
                    ImGui::PushItemWidth(50);
                    ImGui::DragFloat("###Z", &go.second->transform->scale.z, 0.1f);
                    ImGui::PopItemWidth();

                    // Sprite renderer

                    if (go.second->HasComponent<SpriteRenderer>()) {
                        ECS::Components::SpriteRenderer* spr = go.second->GetComponent<SpriteRenderer>();
                        ImGui::Text("Sprite Renderer");
                        ImGui::SameLine();
                        if (ImGui::Button("R", buttonSize))
                            spr->color.x = 0.0f;

                        ImGui::SameLine();
                        ImGui::PushItemWidth(50);
                        ImGui::DragFloat("##R", &spr->color.x, 0.1f);
                        ImGui::PopItemWidth();
                        ImGui::SameLine();

                        if (ImGui::Button("G", buttonSize))
                            spr->color.y = 0.0f;
                        ImGui::SameLine();
                        ImGui::PushItemWidth(50);
                        ImGui::DragFloat("##G", &spr->color.y, 0.1f);
                        ImGui::PopItemWidth();
                        ImGui::SameLine();

                        if (ImGui::Button("B", buttonSize))
                            spr->color.z = 0.0f;
                        ImGui::SameLine();
                        ImGui::PushItemWidth(50);
                        ImGui::DragFloat("##B", &spr->color.z, 0.1f);
                        ImGui::PopItemWidth();
                        ImGui::SameLine();

                        if (ImGui::Button("A", buttonSize))
                            spr->color.w = 0.0f;
                        ImGui::SameLine();
                        ImGui::PushItemWidth(50);
                        ImGui::DragFloat("##A", &spr->color.w, 0.1f);
                        ImGui::PopItemWidth();
                    }

                }

                if (ImGui::Button("Add SpriteRenderer")) {
                    //go.second->AddComponent(SpriteRenderer(Window::getCurrentScene()->GetGameObject("Player")->GetComponent<SpriteRenderer>()->shader, Vector4f(1.0f, 0.0f, 0.0f, 1.0f)));
                }

                ImGui::TreePop();

            }
            ImGui::Spacing();
        }
    }

    ImGui::NewLine();

    // Adding GameObjects to scene

    if (ImGui::InputText("Add Entity", holder, 64, ImGuiInputTextFlags_EnterReturnsTrue)) {
        Window::getCurrentScene()->addGameObjectToScene(new GameObject((std::string)holder));
    }


    ImGui::End();
}
