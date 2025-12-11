his project is an interactive OpenGL-based visualization that simulates gravitational lensing and the curvature of spacetime caused by massive objects, inspired by Einstein’s General Theory of Relativity. The program demonstrates how light rays bend when passing near a massive body, and how the gravitational potential affects the curvature of a 2D spacetime grid.

🔭 Key Features

Real-time simulation of gravitational lensing
Light rays are traced step-by-step as they move through a gravitational field. Their direction continuously changes based on the calculated gravitational acceleration.

Visual spacetime curvature grid
A dynamic grid is rendered where each point is displaced based on the gravitational potential, giving a 3D impression of curvature (“gravity well”).

Massive object rendering
Spherical bodies (representing stars/black holes) are placed in space. Their mass determines the depth of curvature and the intensity of light bending.

Interactive camera controls
Users can rotate, zoom, and move around the scene:

W/A/S/D — rotate view

Mouse drag — look around

Right mouse drag — zoom

Q / S / E — zoom in/out

R — retrace light rays

Physics-inspired calculations

Gravitational potential and acceleration are computed per-point.

Light rays follow a numerically integrated path influenced by nearby masses.

Mass determines gravitational strength and effective radius.

📐 Technical Implementation

Built with OpenGL (FreeGLUT) for real-time rendering.

Uses custom physics functions:

calculategravity() – gravitational potential.

claculategravityaccelaretion() – acceleration vector.

tracelight() – stepwise integration of light paths.

Smooth animation and adjustable resolution for the spacetime grid.

Clean modular structure (spacetime.h, main.cpp).

🎯 Purpose

This project serves as a visual and educational demonstration of:

Spacetime curvature

Gravitational lensing

Numerical integration of physics

Real-time graphical simulation using OpenGL
