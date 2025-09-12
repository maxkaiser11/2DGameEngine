#pragma once
#include "../ECS/ECS.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/HealthComponent.h"

class RenderGUISystem : public System 
{
public:
	RenderGUISystem() = default;

	void Update(SDL_Renderer* renderer, const std::unique_ptr<Registry>& registry)
	{
		// Draw all the ImGui objects
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();

		ImGui::NewFrame();

		//ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_AlwaysAutoResize;
		if (ImGui::Begin("Spawn Enemies"))
		{
			// Input for the enemy X Position
			static int enemyXPos = 0;
			ImGui::InputInt("X position", &enemyXPos);
			// Input for the enemy Y Position
			static int enemyYPos = 0;
			ImGui::InputInt("Y position", &enemyYPos);

			static ImVec2 enemyScale = ImVec2(0.0, 0.0);
			ImGui::InputFloat("X Scale", &enemyScale.x);
			ImGui::InputFloat("Y Scale", &enemyScale.y);

			static int projectileRepeatFreq = 0;
			ImGui::InputInt("Projectile Repeat Frequency", &projectileRepeatFreq);

			static const char* items[]{ "tank-image", "truck-image" };
			static int selectedItem = 0;
			ImGui::Combo("Enemy Sprite", &selectedItem, items, IM_ARRAYSIZE(items));
			// Button to create enemy Entity
			if (ImGui::Button("Create new Enemy"))
			{
				Entity enemy = registry->CreateEntity();
				enemy.Group("enemies");
				enemy.AddComponent<TransformComponent>(glm::vec2(enemyXPos, enemyYPos), glm::vec2(enemyScale.x, enemyScale.y), 0.0);
				enemy.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
				enemy.AddComponent<SpriteComponent>(items[selectedItem], 32, 32, 1);
				enemy.AddComponent<BoxColliderComponent>(25, 18, glm::vec2(5, 7));
				enemy.AddComponent<ProjectileEmitterComponent>(glm::vec2(100.0, 0.0), projectileRepeatFreq, 5000, 10, false);
				enemy.AddComponent<HealthComponent>(100);
			}
		}
		ImGui::End();

		ImGui::Render();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
	}
};