🌌 3D Curved Spacetime & Gravitational Lensing Simulation

<p align="center">
  <img src="images/Screenshot 2025-12-11 125014.png" width="650">
</p>

This project is an interactive OpenGL-based visualization that simulates gravitational lensing and spacetime curvature caused by massive objects, inspired by Einstein’s General Theory of Relativity.
It demonstrates how light bends when passing near a massive body and how gravitational potential deforms a 2D spacetime grid.

🔭 Key Features
• Real-time gravitational lensing

Light rays are traced step-by-step as they move through a gravitational field. Their direction updates every frame based on computed gravitational acceleration.

• Curved spacetime grid

A dynamic blue grid is displaced according to gravitational potential, forming a 3D “gravity well.”

• Massive object rendering

Spherical objects (stars or black holes) are placed in the scene. Their mass affects:

curvature depth

light bending strength

visual radius

• Interactive camera controls
Input	Action
W/A/S/D	Rotate camera
Left Mouse Drag	Rotate view
Right Mouse Drag	Zoom
Q / S / E	Zoom controls
R	Retrace light rays
• Physics-inspired calculations

calculategravity() computes gravitational potential.

claculategravityaccelaretion() computes acceleration vectors.

tracelight() performs numerical integration to simulate photon motion.

## 📸 Simulation Views

**Side View (Light bending + deep curvature)**  
<p align="center">
  <img src="images/Screenshot 2025-12-11 125014.png" width="600">
</p>

**Front View of Gravity Well**  
<p align="center">
  <img src="images/Screenshot 2025-12-11 125003.png" width="600">
</p>


📐 Technical Implementation

Built using OpenGL + FreeGLUT for real-time rendering.

Custom spacetime and physics engine implemented in C++.

Light rays follow a discretized integration path.

Adjustable grid resolution and step size.

Clean modular structure:

spacetime.h — physics + rendering class

main.cpp — program entry and GLUT setup

📦 **Build Instructions:**  
See **[BUILD.md](./BUILD.md)** for Windows compilation steps.


🎯 Purpose

This project serves as an educational demonstration of:

Spacetime curvature visualization

Gravitational lensing physics

Numerical integration of motion

Real-time computer graphics using OpenGL

Applying university concepts (transformations, line algorithms, 3D rendering) to scientific simulation

🔧 Build Instructions

See BUILD.md for Windows & Linux compilation steps.
