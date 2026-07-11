//
// Created by Jkurt on 7/10/2026.
//

#include "Panel.h"

#include <utility>
#include <raylib.h>

Panel::Panel(PanelData inData)
    : data(std::move(inData))
{
}

void Panel::draw() const
{
    if (!data.visible)
    {
        return;
    }

    Texture2D textureToDraw = data.idleTexture;
    if (isHovered && data.hoverTexture.id != 0)
    {
        textureToDraw = data.hoverTexture;
    }

    if (textureToDraw.id != 0)
    {
        DrawTexture(textureToDraw, static_cast<int>(data.position.x), static_cast<int>(data.position.y), WHITE);
    }
}

void Panel::update(Vector2 mousePosition)
{
    if (!data.visible)
    {
        isHovered = false;
        return;
    }

    isHovered = CheckCollisionPointRec(mousePosition, getBounds());
}

void Panel::setData(PanelData inData)
{
    data = std::move(inData);
}

const PanelData& Panel::getData() const
{
    return data;
}

PanelData& Panel::getData()
{
    return data;
}

void Panel::setPosition(Vector2 newPosition)
{
    data.position = newPosition;
}

Vector2 Panel::getPosition() const
{
    return data.position;
}

Rectangle Panel::getBounds() const
{
    return Rectangle{
        data.position.x,
        data.position.y,
        static_cast<float>(data.idleTexture.width),
        static_cast<float>(data.idleTexture.height)
    };
}

bool Panel::getIsHovered() const
{
    return isHovered;
}
