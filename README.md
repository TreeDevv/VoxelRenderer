# Voxel Renderer

A lightweight C++/OpenGL voxel renderer with chunk-based world generation, multithreaded meshing, per-vertex ambient occlusion, dynamic lighting, and distance-based fog. Built as a learning project focused on real-time rendering and concurrent systems programming.

---

## Features

- **Chunk-based world**
  - 3D voxel world split into fixed-size chunks (e.g. 16×256×16)
  - View-dependent loading/unloading based on player position and render distance
  - Efficient mesh generation per chunk

- **Multithreaded pipeline**
  - Background generation and meshing of chunks
  - Generic thread pool used for CPU-heavy tasks
  - Keeps the main render thread responsive even while streaming new terrain

- **Thread pool**
  - Simple worker-thread pool abstraction
  - Task-based API for scheduling generation and meshing jobs
  - Graceful shutdown and exception handling in worker threads

- **Mesh generation**
  - Per-face mesh creation driven by block data
  - Only visible faces are emitted (basic occlusion culling)
  - Supports per-vertex attributes:
    - Position
    - Normal
    - Ambient occlusion factor
    - Texture coordinates

- **Lighting & Ambient Occlusion**
  - Basic directional lighting in the fragment or vertex shader
  - Per-vertex ambient occlusion baked during meshing for softer lighting in corners and crevices
  - Tunable AO strength via shader uniforms

- **Fog**
  - Distance-based fog for depth perception and atmosphere
  - Configurable fog color and density
  - Integrated into the main lighting shader

- **Rendering**
  - OpenGL 3.3 core pipeline
  - Separate model, view, and projection matrices
  - Support for a texture atlas (single texture with multiple block faces)
  - Camera system suitable for first-person style navigation

---

## Tech Stack

- **Language:** C++ (C++17 or later)
- **Graphics API:** OpenGL 3.3
- **Math:** GLM
- **Windowing / Input:** GLFW 
- **Build System:** CMake

> For the exact list of dependencies and versions, see `CMakeLists.txt` and the project source.

---

## Getting Started

### Prerequisites

- A C++17-compatible compiler (e.g. `clang`, `gcc`, or MSVC)
- CMake (recommended >= 3.20)

This project is cross platform but these instructions are windows specific

Simply run the install script in scripts/ this will install vcpkg and vcpkg + CMake will handle the rest.
