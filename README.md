# 🌌 Solar System – Solar System Simulation

A custom C++/OpenGL engine for simulating and visualizing the **Solar System**, built step by step to deeply understand **rendering engines, simulation systems, and supporting technologies**.

The project is designed to be educational: each subsystem (windowing, input, rendering, physics, orchestration) is implemented from scratch with minimal reliance on prebuilt frameworks.  
By the final phase, this will be a fully interactive, physically accurate solar system simulator.

---

## 🚀 Quick Start

1. **Open** `Solar System.sln` in Visual Studio
2. **Build** the solution (Ctrl+Shift+B)
3. **Run** the application (F5)
4. **Controls:**
   - WASD/QE to move camera
   - Mouse to look around
   - ESC to exit

You should see three colored spheres (Sun, Earth, Moon) with basic lighting.

---

## 🚀 Current Status

**Last Updated:** November 3, 2025

- **Phase 1 (Foundation)** – Complete ✅  
- **Phase 2 (3D Rendering)** – Complete ✅  
- **Phase 3 (Scene Graph)** – In Progress 🔄  
- **Phase 4+** – Planned (see Roadmap)

### Recent Achievements

✅ **Core Systems Operational:**
- Window management with GLFW wrapper
- Input system (keyboard & mouse tracking)
- OpenGL 4.6 renderer with depth testing
- Shader compilation and management
- Mesh system with VAO/VBO (move semantics implemented)
- Camera system with view/projection matrices
- Camera controller (WASD movement + mouse look)
- Transform system (position, rotation, scale)

✅ **3D Rendering Working:**
- Sphere mesh generation (parametric UV sphere)
- Basic Phong lighting model
- Multiple celestial bodies rendering (Sun, Earth, Moon)
- Camera orbit controls are functional

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

### ✅ Phase 2: 3D Rendering
- [x] Camera class (orbit & free-fly)  
- [x] Camera controller (WASD + mouse look)
- [x] Camera manager (multi-camera support)
- [x] Mesh generator (UV sphere for planets)  
- [x] Transformation system (model/view/projection)  
- [x] Basic planet rendering with colors
- [x] Phong lighting implementation
- [x] Multiple objects rendering

### 🟡 Phase 3: Scene Graph & Orbital Mechanics
- [ ] SceneNode hierarchy system
- [ ] GameObject with component architecture
- [ ] CelestialBody base class
- [ ] Orbital mechanics (Kepler's laws)
- [ ] Planet and Sun classes
- [ ] Realistic orbital paths  

### 🔜 Phase 4: Advanced Rendering
- [ ] Texture loading (stb_image integration)
- [ ] Material system (PBR properties)
- [ ] Textured planets (Earth, Mars, etc.)  
- [ ] Normal maps for surface detail
- [ ] Specular and roughness maps  

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

## ⚙️ Build Instructions

### Prerequisites
- **Visual Studio 2019+** (or compatible C++17 compiler)
- **Windows 10/11** (primary development platform)
- **OpenGL 4.6** capable graphics card

### Dependencies (Already Integrated)
- ✅ [GLFW 3.x](https://www.glfw.org/) – window & input management
- ✅ [GLAD](https://glad.dav1d.de/) – OpenGL 4.6 function loader  
- ✅ [GLM](https://github.com/g-truc/glm) – mathematics library for graphics
- 📋 [stb_image](https://github.com/nothings/stb) – texture loading (Phase 4)
- 📋 [ImGui](https://github.com/ocornut/imgui) – debug UI (Phase 6)

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

### Current Directory Structure

```
Solar System/
│
├── Include/                    # Header files
│   ├── Core/
│   │   ├── Window.h           ✅ Complete
│   │   └── Input.h            ✅ Complete
│   ├── Renderer/
│   │   ├── Renderer.h         ✅ Complete
│   │   ├── Shader.h           ✅ Complete
│   │   ├── Mesh.h             ✅ Complete (with move semantics)
│   │   └── Entity.h           📋 Placeholder
│   └── Scene/
│       ├── Camera.h           ✅ Complete
│       ├── CameraController.h ✅ Complete
│       ├── CameraManager.h    ✅ Complete
│       └── Transform.h        ✅ Complete
│
├── src/                        # Implementation files
│   ├── Core/
│   │   ├── Window.cpp         ✅ GLFW wrapper
│   │   └── Input.cpp          ✅ Keyboard/mouse handling
│   ├── Renderer/
│   │   ├── Renderer.cpp       ✅ OpenGL state management
│   │   ├── Shader.cpp         ✅ GLSL compilation
│   │   └── Mesh.cpp           ✅ VAO/VBO management + sphere generation
│   └── Scene/
│       ├── Camera.cpp         ✅ View/projection matrices
│       ├── CameraController.cpp ✅ WASD + mouse controls
│       ├── CameraManager.cpp  ✅ Multi-camera support
│       └── Transform.cpp      ✅ Position/rotation/scale
│
├── Shader/                     # GLSL shaders
│   ├── basic.vert             ✅ Vertex shader with MVP
│   └── basic.frag             ✅ Fragment shader with Phong lighting
│
├── Application.h/.cpp          ✅ Main application class
├── Main.cpp                    ✅ Entry point
├── Solar System.sln            ✅ Visual Studio solution
├── Solar System.vcxproj        ✅ Project file
│
└── x64/                        # Build output
    ├── Debug/
    └── Release/
```

### Implemented Components (Phase 1-2)

#### Core Layer ✅
- **Application**: Main game loop with delta time calculation
- **Window**: GLFW wrapper with OpenGL 4.6 context creation
- **Input**: Static input manager with keyboard/mouse state tracking

#### Renderer Layer ✅
- **Renderer**: OpenGL state management and draw call orchestration
- **Shader**: GLSL compilation, linking, and uniform management
- **Mesh**: VAO/VBO management with RAII and move semantics
  - Parametric UV sphere generation
  - Indexed drawing with element buffer objects

#### Scene Layer ✅
- **Transform**: Position, rotation (quaternion), scale with model matrix calculation
- **Camera**: View/projection matrices with configurable FOV and aspect ratio
- **CameraController**: WASD movement + mouse look with delta time integration
- **CameraManager**: Multi-camera support with viewport management

#### Planned Components (Phase 3+)

**Scene Graph:**
- SceneNode hierarchy with parent-child transforms
- GameObject with component system
- Scene management and traversal

**Celestial Objects:**
- CelestialBody base class with orbital mechanics
- Planet class with rotation and axial tilt
- Sun class with emissive properties
- Moon class for satellite objects

**Advanced Rendering:**
- Texture loading and management
- Material system with PBR properties
- Lighting system (point, directional, spot lights)
- Shadow mapping

**Simulation:**
- Orbital mechanics (Kepler's laws)
- Time scaling controls
- Physics integration
- Particle systems for asteroid belts

---

## 🧑‍💻 Usage

### Current Controls

**Camera Movement:**
- `W` / `S` → Move forward / backward
- `A` / `D` → Move left / right  
- `Q` / `E` → Move down / up
- `Mouse Movement` → Look around (first-person view)
- `Mouse Scroll` → Adjust movement speed

**Application:**
- `ESC` → Exit application

### Current Features

The application currently displays:
- **Sun** (yellow sphere at origin)
- **Earth** (blue-green sphere, 6 units from sun)
- **Moon** (grey sphere, 8 units from sun)
- **Basic Phong lighting** from sun position
- **Interactive camera** with smooth WASD controls

### Upcoming Features (Phase 3+)
- Time scaling controls (pause, fast-forward, slow-motion)
- Click planets to inspect details
- Realistic orbital motion
- Multiple camera modes (orbit, follow, free-fly)  

---

## 🔧 Technical Details

### Current Implementation

**Graphics Pipeline:**
- OpenGL 4.6 Core Profile
- Custom shader system with GLSL compilation
- VAO/VBO mesh management with move semantics
- Depth testing and face culling enabled
- Phong lighting model (ambient + diffuse + specular)

**Architecture:**
- Component-based design with clear separation of concerns
- RAII pattern for OpenGL resource management
- Input system with delta time for frame-independent movement
- Camera system with view/projection matrix calculations
- Transform system using GLM for matrix operations

**Performance:**
- Currently rendering 3 objects at 60+ FPS
- Efficient mesh generation with indexed drawing
- Proper OpenGL state management

### Known Issues & Limitations

- Static scene (no orbital motion yet - Phase 3)
- No textures (Phase 4)
- Hardcoded object positions
- No UI overlay (Phase 6)
- Single-threaded rendering

## 🤝 Contributing

This project is primarily for **learning and exploration**, but contributions are welcome.  
Please open an issue or PR for improvements, optimizations, or new features.

### Development Guidelines
- Follow existing code style and architecture patterns
- Test changes thoroughly before committing

---

## 📜 License

GNU V3.0 License © 2025. See [LICENSE](LICENSE) for details.

---

**Last Updated:** November 3, 2025  

