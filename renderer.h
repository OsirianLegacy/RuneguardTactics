//
// Created by Jkurt on 7/4/2026.
//

#ifndef RUNEGUARDTACTICS_RENDERER_H
#define RUNEGUARDTACTICS_RENDERER_H
#include "gridvisuals.h"
#include "gridlogic.h"

class renderer {
public:
    renderer(int width, int height);
    void render() const;
    int width;
    int height;
    gridvisuals *gridvisuals;
    gridlogic *gridlogic;
};


#endif //RUNEGUARDTACTICS_RENDERER_H