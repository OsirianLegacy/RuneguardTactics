//
// Created by Jkurt on 7/10/2026.
//

#ifndef RUNEGUARDTACTICS_EDITORUI_H
#define RUNEGUARDTACTICS_EDITORUI_H


class GameUI;
class InputManager;
class GameState;
class GameEvents;

class EditorUI
{
public:
    void draw(GameState& state, GameEvents& events, GameUI& gameUI, InputManager& inputManager);

private:
    bool showEditor = true;
    bool showDebugPanel = true;
    bool showUILayoutPanel = false;

    void drawMainMenu();
    void drawDebugPanel(GameState& state, GameEvents& events, InputManager& inputManager);
    void drawUILayoutPanel(GameUI& gameUI);
};


#endif //RUNEGUARDTACTICS_EDITORUI_H
