//
// Created by Jkurt on 7/4/2026.
//

#include "Renderer.h"
#include <raylib.h>
#include "GridVisuals.h"
#include "GridLogic.h"
#include <algorithm>
#include <array>
#include <map>

#include "InputManager.h"
#include "TiledMap.h"

Renderer::Renderer(int width, int height) {
 this->width = width;
 this->height = height;
}

namespace
{
 constexpr int BaseRenderWidth = 1600;
 constexpr int BaseRenderHeight = 900;

 Color colorForTeam(const TEAM team)
 {
  switch (team)
  {
   case PLAYER:
    return BLUE;
   case ENEMY:
    return RED;
   case CIVILIAN:
    return GREEN;
   case NEUTRAL:
    return GRAY;
   default:
    return WHITE;
  }
 }

 const std::array<Rectangle, 4>& framesForAnimationState(const CombatUnit& combatUnit)
 {
  const UnitSpriteSheet& spriteSheet = combatUnit.unit.spriteSheet;

  switch (combatUnit.animationState)
  {
   case UnitAnimationState::Damaged:
    return spriteSheet.damagedFrames;
   case UnitAnimationState::Healed:
    return spriteSheet.healedFrames;
   case UnitAnimationState::Highlighted:
    return spriteSheet.highlightedFrames;
   case UnitAnimationState::Idle:
   default:
    return spriteSheet.idleFrames;
  }
 }

 Rectangle currentFrameForUnit(const CombatUnit& combatUnit)
 {
  const UnitSpriteSheet& spriteSheet = combatUnit.unit.spriteSheet;
  const std::array<Rectangle, 4>& frames = framesForAnimationState(combatUnit);
  const int frameIndex = combatUnit.animationFrame % static_cast<int>(frames.size());
  Rectangle frame = frames[frameIndex];

  if (frame.width <= 0.0f || frame.height <= 0.0f)
  {
   frame = spriteSheet.idleFrames[0];
  }

  return frame;
 }

 bool hasDrawableFrame(const CombatUnit& combatUnit)
 {
  const Rectangle frame = currentFrameForUnit(combatUnit);
  return combatUnit.unit.spriteSheet.texture.id != 0 && frame.width > 0.0f && frame.height > 0.0f;
 }
}

void Renderer::render() const {
 std::map<coord, cell> gridmap = this->gridlogic->gridmap;
 gridlayout layout = getGridLayout();
 int startX = layout.startX;
 int startY = layout.startY;
 gridvisuals->gridLayout = layout;
 // draw the map first
 if (tiledMap != nullptr)
 {
  tiledMap->draw(startX, startY, layout.tileSize);
 }
 // draw highlights above the map
 gridvisuals->drawHighlightedCells(layout);
 // draw the current hovered cell over highlights

 // render units above the current hovered cell.
 if (activeUnits != nullptr)
 {
  for (const CombatUnit& combatUnit : *activeUnits)
  {
   const float unitX = static_cast<float>(startX + combatUnit.position.x * layout.tileSize);
   const float unitY = static_cast<float>(startY + combatUnit.position.y * layout.tileSize);

   if (hasDrawableFrame(combatUnit))
   {
    const Rectangle source = currentFrameForUnit(combatUnit);
    const Rectangle dest = {
     unitX,
     unitY,
     static_cast<float>(layout.tileSize),
     static_cast<float>(layout.tileSize)
    };

    DrawTexturePro(
     combatUnit.unit.spriteSheet.texture,
     source,
     dest,
     Vector2{0.0f, 0.0f},
     0.0f,
     WHITE);
   }
   else
   {
    const float padding = static_cast<float>(layout.tileSize) * 0.18f;
    DrawRectangleRounded(
     Rectangle{
      unitX + padding,
      unitY + padding,
      static_cast<float>(layout.tileSize) - padding * 2.0f,
      static_cast<float>(layout.tileSize) - padding * 2.0f
     },
     0.2f,
     6,
     colorForTeam(combatUnit.unit.team));
   }
  }
 }

 // then render objects since we want objects over units

 // draw grid outline last so it always shows the grid.
 gridvisuals->updateVisuals(gridmap, layout);
 auto hoveredcell = this->inputmanager->getHoveredCell();
 gridvisuals->drawHoveredCell(hoveredcell, layout);
};

gridlayout Renderer::getGridLayout() const
{
 gridlayout gridLayout;
 const int baseTileSize = static_cast<int>(gridvisuals->tileSize * renderScale);
 const float resolutionScale = std::min(
  static_cast<float>(width) / static_cast<float>(BaseRenderWidth),
  static_cast<float>(height) / static_cast<float>(BaseRenderHeight));
 int scaledTileSize = std::max(1, static_cast<int>(static_cast<float>(baseTileSize) * resolutionScale));
 int gridPixelWidth = gridlogic->gridwidth * scaledTileSize;
 int gridPixelHeight = gridlogic->gridheight * scaledTileSize;
 int startX = (width - gridPixelWidth) /2;
 int startY = (height - gridPixelHeight) /2;
 gridLayout.gridHeight = this->gridlogic->gridheight;
 gridLayout.gridWidth = this->gridlogic->gridwidth;
 gridLayout.startX = startX;
 gridLayout.startY = startY;
 gridLayout.tileSize = scaledTileSize;
 return gridLayout;
}

void Renderer::setTileMap(TiledMap *tilemap) {
 this->tiledMap = tilemap;
}

void Renderer::setActiveUnits(const std::vector<CombatUnit>* units)
{
 this->activeUnits = units;
}
