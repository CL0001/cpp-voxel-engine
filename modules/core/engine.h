#ifndef ENGINE_H
#define ENGINE_H

#include "camera.h"
#include "gui.h"
#include "renderer.h"
#include "window.h"
#include "world.h"

class Engine
{
public:
    Engine(int width, int height, const char* title);

    void Run();

private:
    Window window_;
    Camera camera_;
    World world_;
    Renderer renderer_;
    GUI gui_;
};

#endif // ENGINE_H
