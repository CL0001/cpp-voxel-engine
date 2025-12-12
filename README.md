<img width="1305" height="625" alt="veng_logo_v2" src="https://github.com/user-attachments/assets/76b9a2d4-7ba3-458a-876a-dcbb094697f3" />

# About

VEng is a lightweight voxel engine built with **C++20** and **OpenGL3**, using minimal third-party libraries to create a playable, procedurally generated world.


# Features

- **Procedural World Generation:** Infinite terrain generated using custom layered simplex noise.  
- **Optimized Mesh Generation:** Only visible faces are rendered for efficiency.  
- **Efficient Memory Management:** Engine objects use stack-based lifetimes for efficiency.
- **High-Performance Rendering:** Capable of handling large view distances at a stable ~1000 FPS.  


# LTS Gameplay Demo

https://github.com/user-attachments/assets/4e2f7ab4-2ee8-43cb-9a92-3b0964ca3a74


# Getting Started

This project has been primarily tested with MinGW and Visual Studio 2022; therefore, they are the recommended compilers.
However, it should successfully build and run on all major platforms and compilers.

One other requirement to build the project is to have CMake installed (version 3.15 – 4.0 excluded).

<ins>**1. Download the source:**</ins>

You can either clone the repository:

```
git clone https://github.com/CL0001/cpp-voxel-engine.git
```

or download it as a .zip file from GitHub and extract it.

<ins>**2. Build the project:**</ins>

The repository includes a Python build script at `tools/build.py`.
Run it from the root of the project directory for convenience:

```python
python ./tools/build.py
```

Without any flags, the script will simply build the project.
The following optional flags can also be used:

| Flag         | Description                                                             |
| ------------ | ----------------------------------------------------------------------- |
| `--build`    | Choose the build type. Options: `Debug` or `Release`. Default: `Debug`. |
| `--run`      | Run the binary directly after building.                                 |
| `--clean`    | Remove the build directory before building.                             |
| `--generate` | Specify the CMake generator. Currently only supports `vs2022`.          |

Example:

```
python ./tools/build.py --run
```

If Python is not installed, you can build the project manually using CMake:

```cmake
cmake -S . -B build
cmake --build build
```

<ins>**3. Run the executable:**</ins>

After a successful build, the compiled binary should be located at:

```
./build/source/app/Debug/VoxelEngine.exe
```
