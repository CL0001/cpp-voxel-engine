#include "spdlog/spdlog.h"

#include "engine.h"

int main()
{
	try
	{
		Engine engine(640, 480, "Voxel Engine");
		engine.Run();
	}
		catch (const std::exception& e)
	{
		spdlog::critical("Fatal failure: {}", e.what());
		return EXIT_FAILURE;
	}
}
