<img width="1520" height="725" alt="veng" src="https://github.com/user-attachments/assets/dc18b733-d08a-4d62-8ed1-3ba4c720e62e"/>

# About

VEng is a lightweight voxel engine built with **C++20** and **OpenGL3**, using minimal third-party libraries to create a playable, procedurally generated world.

# Features

- **Procedural World Generation:** Infinite terrain generated using custom layered simplex noise.  
- **Optimized Mesh Generation:** Only visible faces are rendered for efficiency.  
- **Efficient Memory Management:** Engine objects use stack-based lifetimes for efficiency.
- **High-Performance Rendering:** Capable of handling large view distances at a stable ~1000 FPS.  

# LTS Gameplay Demo

https://github.com/user-attachments/assets/0bd28fd9-4836-4c9d-b9b3-f48fb4117b57

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
