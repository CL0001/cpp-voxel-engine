#include "spdlog/spdlog.h"

#include "engine.hpp"

int main()
{
    try
    {
        VEng::Engine engine(1280, 720, "Voxel Engine");
        engine.Run();
    }
    catch (const std::exception& e)
    {
        spdlog::critical("Fatal failure: {}", e.what());
        return EXIT_FAILURE;
    }
}
