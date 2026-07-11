//
// Created by Jkurt on 7/10/2026.
//

#ifndef RUNEGUARDTACTICS_PANEL_H
#define RUNEGUARDTACTICS_PANEL_H

#include "../Data/UIData.h"

class Panel
{
public:
    Panel() = default;
    explicit Panel(PanelData inData);

    void draw() const;
    void update(Vector2 mousePosition);

    void setData(PanelData inData);
    [[nodiscard]] const PanelData& getData() const;
    [[nodiscard]] PanelData& getData();

    void setPosition(Vector2 newPosition);
    [[nodiscard]] Vector2 getPosition() const;
    [[nodiscard]] Rectangle getBounds() const;
    [[nodiscard]] bool getIsHovered() const;

private:
    PanelData data;
    bool isHovered = false;
};

#endif //RUNEGUARDTACTICS_PANEL_H
