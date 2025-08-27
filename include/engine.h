#ifndef ENGINE_H
#define ENGINE_H

#include "window.h"
#include "shader.h"

#include "../modules/camera/camera.h"
#include "world.h"

class Engine
{
public:
    Engine(int width, int height, const char* title);

    void Run();

private:
    static double CalculateDeltaTime();

    Window window_;
    Shader shader_;
    Camera camera_;
    World world_;
};

#endif // ENGINE_H
