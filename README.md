# 🌌 Solar System – Solar System Simulation

A custom C++/OpenGL engine for simulating and visualizing the **Solar System**, built step by step to deeply understand **rendering engines, simulation systems, and supporting technologies**.

The project is designed to be educational: each subsystem (windowing, input, rendering, physics, orchestration) is implemented from scratch with minimal reliance on prebuilt frameworks.  
By the final phase, this will be a fully interactive, physically accurate solar system simulator.

---

## 🚀 Current Status

- **Phase 1 (Foundation)** – Complete ✅  
- **Phase 2 (3D Rendering)** – In Progress  
- **Phase 3+** – Planned (see Roadmap)

---

## 🏗 Architecture

```
Core Layer
├── Application   – main loop, ties everything together
├── Window        – GLFW wrapper, OpenGL context
├── Input         – keyboard & mouse manager

Renderer Layer
├── Renderer      – orchestrates draw calls
├── Shader        – GLSL program abstraction
├── Mesh          – VAO/VBO abstraction, sphere generator
├── Camera        – view/projection transforms

Simulation Layer
├── CelestialBody – planet/star entity (mass, orbit, mesh)
├── OrbitSystem   – orbital mechanics integration
├── TimeManager   – controls simulation speed & scaling

UI Layer
├── HUD/Overlay   – simulation controls, debug info
└── Interaction   – mouse picking, camera controls
```

---

## 📐 Roadmap

### ✅ Phase 1: Foundation
- [x] Window creation (GLFW wrapper)  
- [x] OpenGL context + GLAD initialization  
- [x] Input handling system (keyboard, mouse)  
- [x] Renderer setup (clear + depth test)  
- [x] Mesh & Shader abstractions  
- [x] Demo: render a simple triangle  

### 🟡 Phase 2: 3D Rendering
- [ ] Camera class (orbit & free-fly)  
- [ ] Mesh generator (UV sphere for planets)  
- [ ] Transformation system (model/view/projection)  
- [ ] Basic planet rendering with colors  

### 🔜 Phase 3: Lighting & Materials
- [ ] Phong shading with directional light (the Sun)  
- [ ] Textured planets (Earth, Mars, etc.)  
- [ ] Normal maps for realism  

### 🔜 Phase 4: Simulation Layer
- [ ] CelestialBody class (mass, orbit radius, speed)  
- [ ] Orbit mechanics (Kepler’s laws approximations)  
- [ ] Time scaling (fast forward, pause, reset)  
- [ ] Realistic planet rotations & axial tilt  

### 🔜 Phase 5: UI & Interactivity
- [ ] On-screen controls (ImGui or custom)  
- [ ] Mouse picking (click planet to inspect details)  
- [ ] Camera switching (solar system view ↔ planet view)  

### 🔜 Phase 6: Extensions
- [ ] Save/load simulation state  
- [ ] Add moons, rings, dwarf planets  
- [ ] Performance optimizations (instancing, frustum culling)  
- [ ] Multi-threaded update/render loop  

---

## 📸 Preview


---

## ⚙️ Build Instructions

### 1. Clone
```bash

```

### 2. Dependencies
- [GLFW](https://www.glfw.org/) – window & input  
- [GLAD](https://glad.dav1d.de/) – OpenGL function loader  
- [GLM](https://github.com/g-truc/glm) – math library  
- (Optional later) [ImGui](https://github.com/ocornut/imgui) – UI  

Dependencies are included via `external/` or fetched via CMake.

### 3. Build (CMake)
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### 4. Run
```bash

```

---

### System Architecture Diagram

```
┌─────────────────────────────────────────────────────────┐
│                     Application Layer                    │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌────────┐ │
│  │   Core   │  │  Window  │  │  Input   │  │  Time  │ │
│  └──────────┘  └──────────┘  └──────────┘  └────────┘ │
└─────────────────────────────────────────────────────────┘
                             │
┌─────────────────────────────────────────────────────────┐
│                    Rendering Layer                       │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌────────┐ │
│  │ Renderer │  │  Shader  │  │   Mesh   │  │Texture │ │
│  └──────────┘  └──────────┘  └──────────┘  └────────┘ │
└─────────────────────────────────────────────────────────┘
                             │
┌─────────────────────────────────────────────────────────┐
│                      Scene Layer                         │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌────────┐ │
│  │  Scene   │  │   Node   │  │Transform │  │ Camera │ │
│  └──────────┘  └──────────┘  └──────────┘  └────────┘ │
└─────────────────────────────────────────────────────────┘
                             │
┌─────────────────────────────────────────────────────────┐
│                    Game Objects Layer                    │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌────────┐ │
│  │   Sun    │  │  Planet  │  │ Asteroid │  │ Skybox │ │
│  └──────────┘  └──────────┘  └──────────┘  └────────┘ │
└─────────────────────────────────────────────────────────┘
                             │
┌─────────────────────────────────────────────────────────┐
│                     Systems Layer                        │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌────────┐ │
│  │ Physics  │  │ Particle │  │ Lighting │  │ Shadow │ │
│  └──────────┘  └──────────┘  └──────────┘  └────────┘ │
└─────────────────────────────────────────────────────────┘
```

### Directory Structure

```
CelestialEngine/
│
├── assets/
│   ├── shaders/
│   │   ├── basic.vert
│   │   ├── basic.frag
│   │   ├── phong.vert
│   │   ├── phong.frag
│   │   ├── shadow.vert
│   │   ├── shadow.frag
│   │   └── particle.vert/frag
│   ├── textures/
│   │   ├── sun/
│   │   ├── earth/
│   │   ├── mars/
│   │   └── ...
│   └── models/
│       └── sphere.obj
│
├── src/
│   ├── Core/
│   │   ├── Application.cpp
│   │   ├── Window.cpp
│   │   ├── Input.cpp
│   │   └── Time.cpp
│   ├── Renderer/
│   │   ├── Renderer.cpp
│   │   ├── Shader.cpp
│   │   ├── Mesh.cpp
│   │   ├── Texture.cpp
│   │   ├── FrameBuffer.cpp
│   │   └── UniformBuffer.cpp
│   ├── Scene/
│   │   ├── Scene.cpp
│   │   ├── SceneNode.cpp
│   │   ├── Transform.cpp
│   │   ├── Camera.cpp
│   │   └── Light.cpp
│   ├── Objects/
│   │   ├── GameObject.cpp
│   │   ├── CelestialBody.cpp
│   │   ├── Planet.cpp
│   │   ├── Sun.cpp
│   │   ├── AsteroidBelt.cpp
│   │   └── Skybox.cpp
│   ├── Systems/
│   │   ├── RenderSystem.cpp
│   │   ├── PhysicsSystem.cpp
│   │   ├── ParticleSystem.cpp
│   │   ├── LightingSystem.cpp
│   │   └── ShadowSystem.cpp
│   ├── Utils/
│   │   ├── Math.cpp
│   │   ├── ResourceManager.cpp
│   │   ├── Logger.cpp
│   │   └── Profiler.cpp
│   ├── UI/
│   │   ├── UIManager.cpp
│   │   └── DebugOverlay.cpp
│   └── main.cpp
│
├── include/
│   └── [header files matching src structure]
│
├── external/
│   ├── glfw/
│   ├── glad/
│   ├── glm/
│   ├── imgui/
│   └── stb/
│
├── build/
├── docs/
├── tests/
├── CMakeLists.txt
├── README.md
└── .gitignore
```

### Component Descriptions

#### Core Layer
- **Application**: Main loop, initialization, shutdown
- **Window**: GLFW wrapper, OpenGL context creation
- **Input**: Keyboard/mouse handling, event callbacks
- **Time**: Delta time, FPS counter, timers

#### Renderer Layer
- **Renderer**: Draw call batching, state management
- **Shader**: GLSL compilation, uniform management
- **Mesh**: VAO/VBO management, vertex attributes
- **Texture**: Image loading, sampling parameters
- **FrameBuffer**: Off-screen rendering targets
- **UniformBuffer**: Shared shader data blocks

#### Scene Layer
- **Scene**: Scene graph traversal, update loop
- **SceneNode**: Parent-child relationships, transforms
- **Transform**: Position, rotation, scale matrices
- **Camera**: View/projection matrices, frustum
- **Light**: Point/directional/spot light data

#### Objects Layer
- **GameObject**: Component container, update logic
- **CelestialBody**: Base class for space objects
- **Planet**: Orbital mechanics, surface details
- **Sun**: Emissive properties, light source
- **AsteroidBelt**: Particle system implementation
- **Skybox**: Cubemap rendering, star field

#### Systems Layer
- **RenderSystem**: Rendering pipeline orchestration
- **PhysicsSystem**: Orbital calculations, collisions
- **ParticleSystem**: Particle updates, GPU instancing
- **LightingSystem**: Light culling, shadow casters
- **ShadowSystem**: Shadow map generation, PCF

---

## 🧑‍💻 Usage

- Run the app → opens a window with current simulation view.  
- `ESC` → exit  
- `WASD` → move camera (free-fly mode)  
- Mouse drag → rotate camera  
- (Phase 4+) UI lets you adjust **time scaling** (pause, fast-forward).  
- (Phase 5+) Click a planet to inspect details.  

---

## 🤝 Contributing

This project is primarily for **learning and exploration**, but contributions are welcome.  
Please open an issue or PR for improvements, optimizations, or new features.

---

## 📜 License

MIT License © 2025. See [LICENSE](LICENSE) for details.

