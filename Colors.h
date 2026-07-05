//
// Created by Jkurt on 7/5/2026.
//

#ifndef RUNEGUARDTACTICS_COLORS_H
#define RUNEGUARDTACTICS_COLORS_H
#pragma once
#include <raylib.h>

namespace Palette
{
    constexpr Color Black       = {0x00, 0x00, 0x00, 0xFF};
    constexpr Color DarkNavy    = {0x22, 0x20, 0x34, 0xFF};
    constexpr Color DarkPurple  = {0x45, 0x28, 0x3C, 0xFF};
    constexpr Color BrownRed    = {0x66, 0x39, 0x31, 65};
    constexpr Color Brown       = {0x8F, 0x56, 0x3B, 0xFF};
    constexpr Color Orange      = {0xDF, 0x71, 0x26, 0xFF};
    constexpr Color Tan         = {0xD9, 0xA0, 0x66, 0xFF};
    constexpr Color Peach       = {0xEE, 0xC3, 0x9A, 0xFF};
    constexpr Color Yellow      = {0xFB, 0xF2, 0x36, 0xFF};
    constexpr Color Lime        = {0x99, 0xE5, 0x50, 0xFF};
    constexpr Color Green       = {0x6A, 0xBE, 0x30, 0xFF};
    constexpr Color TealGreen   = {0x37, 0x94, 0x6E, 0xFF};
    constexpr Color Forest      = {0x4B, 0x69, 0x2F, 0xFF};
    constexpr Color OliveBrown  = {0x52, 0x4B, 0x24, 0xFF};
    constexpr Color Charcoal    = {0x32, 0x3C, 0x39, 0xFF};
    constexpr Color Indigo      = {0x3F, 0x3F, 0x74, 0xFF};
    constexpr Color SteelBlue   = {0x30, 0x60, 0x82, 0xFF};
    constexpr Color Blue        = {0x5B, 0x6E, 0xE1, 0xFF};
    constexpr Color SkyBlue     = {0x63, 0x9B, 0xFF, 45};
    constexpr Color Cyan        = {0x5F, 0xCD, 0xE4, 0xFF};
    constexpr Color PaleBlue    = {0xCB, 0xDB, 0xFC, 0xFF};
    constexpr Color White       = {0xFF, 0xFF, 0xFF, 0xFF};
    constexpr Color LightGray   = {0x9B, 0xAD, 0xB7, 120};
    constexpr Color Gray        = {0x84, 0x7E, 0x87, 0xFF};
    constexpr Color DarkGray    = {0x69, 0x6A, 0x6A, 0xFF};
    constexpr Color DeepGray    = {0x59, 0x56, 0x52, 0xFF};
    constexpr Color Purple      = {0x76, 0x42, 0x8A, 0xFF};
    constexpr Color Red         = {0xAC, 0x32, 0x32, 45};
    constexpr Color Rose        = {0xD9, 0x57, 0x63, 0xFF};
    constexpr Color Pink        = {0xD7, 0x7B, 0xBA, 0xFF};
    constexpr Color Moss        = {0x8F, 0x97, 0x4A, 0xFF};
    constexpr Color Bronze      = {0x8A, 0x6F, 0x30, 0xFF};
}

namespace GameColors
{
    constexpr Color Background    = Palette::Black;
    constexpr Color GridLine      = Palette::LightGray;
    constexpr Color Ground        = Palette::Gray;
    constexpr Color MovementRange = Palette::SkyBlue;
    constexpr Color AttackRange   = Palette::Red;
    constexpr Color SelectedCell  = Palette::Yellow;
    constexpr Color BlockedCell   = Palette::Red;
}

#endif //RUNEGUARDTACTICS_COLORS_H