//
// Created by Jkurt on 7/10/2026.
//

#include "EditorUI.h"

#include <imgui.h>
#include <raylib.h>
#include "GameState.h"
#include "GameEvents.h"
#include <algorithm>

void EditorUI::draw(GameState &state, GameEvents &events, GameUI &gameUI, InputManager &inputManager)
{
    if (IsKeyPressed(KEY_F1))
    {
        showEditor = !showEditor;
    }

    if (!showEditor)
    {
        return;
    }

    drawMainMenu();

    if (showDebugPanel)
    {
        drawDebugPanel(state, events, inputManager);
    }

    if (showUILayoutPanel)
    {
        drawUILayoutPanel(gameUI);
    }
}

void EditorUI::drawMainMenu()
{
    ImGui::Begin("RuneEditor");

    ImGui::Checkbox("Debug Panel", &showDebugPanel);
    ImGui::Checkbox("UI Layout Panel", &showUILayoutPanel);

    ImGui::Text("F1 toggles editor visibility.");

    ImGui::End();
}

void EditorUI::drawDebugPanel(GameState &state, GameEvents &events, InputManager &inputManager)
{
    ImGui::Begin("Runeguard Debug");

    ImGui::Text("FPS: %d", std::clamp(GetFPS(), 0, 120));
    ImGui::Text("Game State: %s", toString(state.getGameState()).c_str());
    ImGui::Text("Mouse: %.0f, %.0f", GetMouseX(), GetMouseY());
    ImGui::Text("Game Event: %s", toString(events.currentGameEvent).c_str());

    ImGui::End();
}

void EditorUI::drawUILayoutPanel(GameUI& gameUI)
{
    ImGui::Begin("UI Layout");
    ImGui::Text("UI layout editing goes here next.");
    ImGui::End();
}

