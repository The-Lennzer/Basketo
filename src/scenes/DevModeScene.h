#pragma once

#include "../Scene.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h> 
#include "imgui.h"
#include <memory>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <utility>
#include <sstream>

#include "../ecs/EntityManager.h"
#include "../ecs/ComponentManager.h"
#include "../ecs/SystemManager.h"
#include "../ecs/components/TransformComponent.h"
#include "../ecs/components/SpriteComponent.h"
#include "../ecs/components/ScriptComponent.h"
#include "../ecs/components/ColliderComponent.h"
#include "../ecs/components/NameComponent.h" 
#include "../ecs/systems/RenderSystem.h"
#include "../ecs/systems/ScriptSystem.h"
#include "../ecs/systems/MovementSystem.h"
#include "../ecs/systems/AnimationSystem.h"
#include "../ecs/systems/AudioSystem.h"
#include "../ecs/systems/CameraSystem.h"
#include "../ecs/systems/CollisionSystem.h"
#include "../AssetManager.h"
#include "../ecs/Entity.h"
#include "../../vendor/nlohmann/json.hpp"
#include "DevModeInputHandler.h"
#include "DevModeSceneSerializer.h" 
#include "InspectorPanel.h" 
#include "../utils/Console.h"

class EntityManager;
class ComponentManager;
class SystemManager; 
class RenderSystem; 
class ScriptSystem;
class MovementSystem;
class AnimationSystem; 
class CameraSystem;

const Entity NO_ENTITY_SELECTED = MAX_ENTITIES;
const int HANDLE_SIZE = 8; 

enum class ResizeHandle {
    NONE,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
};

class DevModeScene : public Scene {
public:
    DevModeScene(SDL_Renderer* ren, SDL_Window* win);
    ~DevModeScene() override;

    void handleInput(SDL_Event& event) override; 
    void update(float deltaTime) override;
    void render() override;

    void addLogToConsole(const std::string& message);

public:
    friend void handleDevModeInput(DevModeScene& scene, SDL_Event& event);

    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Rect gameViewport; 

    float cameraX = 0.0f;
    float cameraY = 0.0f;
    float cameraZoom = 1.0f;
    float cameraTargetX = 0.0f, cameraTargetY = 0.0f;

    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<ComponentManager> componentManager; 
    std::unique_ptr<SystemManager> systemManager;
    std::shared_ptr<RenderSystem> renderSystem;
    std::shared_ptr<MovementSystem> movementSystem;  
    std::shared_ptr<ScriptSystem> scriptSystem; 
    std::shared_ptr<AnimationSystem> animationSystem; 
    std::shared_ptr<AudioSystem> audioSystem;
    std::shared_ptr<CameraSystem> cameraSystem;
    std::shared_ptr<CollisionSystem> collisionSystem;

    std::vector<std::string> consoleLogBuffer;

    AssetManager& assetManager;

    float hierarchyWidthRatio = 0.18f;
    float inspectorWidthRatio = 0.22f;
    float bottomPanelHeightRatio = 0.25f;
    float topToolbarHeight = 40.0f;
    ImVec4 clear_color = ImVec4(0.27f, 0.51f, 0.71f, 1.00f);

    float spawnPosX = 100.0f;
    float spawnPosY = 100.0f;
    float spawnSizeW = 32.0f;
    float spawnSizeH = 32.0f;
    char spawnTextureId[256] = "";

    Entity selectedEntity = NO_ENTITY_SELECTED;
    char inspectorTextureIdBuffer[256] = "";
    char inspectorScriptPathBuffer[256] = ""; 

    char sceneFilePath[256] = "scene.json";

    bool isDragging = false;
    float dragStartMouseX = 0.0f; 
    float dragStartMouseY = 0.0f; 
    float dragStartEntityX = 0.0f;
    float dragStartEntityY = 0.0f;
    float gridSize = 32.0f; 
    bool snapToGrid = true; 
    bool showGrid = true; 

    bool isPlaying = false;

    bool isResizing = false;
    ResizeHandle activeHandle = ResizeHandle::NONE;
    float dragStartWidth = 0.0f;
    float dragStartHeight = 0.0f;

    bool isEditingCollider = false;
    int editingVertexIndex = -1;
    bool isDraggingVertex = false;

    bool isMouseOverEntity(float worldMouseX, float worldMouseY, Entity entity); 
    
    std::vector<std::pair<ResizeHandle, SDL_Rect>> getResizeHandles(const TransformComponent& transform);
    
    ResizeHandle getHandleAtPosition(float worldMouseX, float worldMouseY, const TransformComponent& transform);

    void renderConsolePanel();
    void renderLlmPromptPanel();

    void processLlmPrompt(const std::string& prompt); 
    Entity findEntityByName(const std::string& name); 
    DevModeInputHandler m_devModeInputHandler;

    char m_sceneNameBuffer[128];
    char m_llmPromptBuffer[256];

    std::string currentAssetDirectory = "../assets/"; 

    std::string selectedAssetPathForPreview = "";
    std::string selectedAssetTypeForPreview = "";


    void renderDevModeUI();
    std::string getComponentNameForDisplay(Entity entity);
};
