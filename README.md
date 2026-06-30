# 🏫 Interactive 3D Classroom Simulation

> **An interactive 3D classroom visualization built from the ground up using OpenGL to explore computer graphics concepts and investigate future applications in scientific visualization.**

![OpenGL](https://img.shields.io/badge/OpenGL-Computer%20Graphics-blue)
![Language](https://img.shields.io/badge/Language-C-success)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
 
<img width="834" alt="Screenshot 2024-09-16 at 3 38 08 PM" src="https://github.com/user-attachments/assets/5c94fdd0-c84a-49e1-89e6-37b3dd87b06e">
---

# Overview

Originally developed as part of a computer graphics course, this project evolved into an exploration of scientific visualization and real-time rendering.
While developing the simulation, I proposed using it as an interactive visualization platform for my environmental health research. My goal was to create a virtual classroom capable of demonstrating how portable HEPA filtration systems influence airflow and carbon dioxide (CO₂) distribution inside occupied learning spaces.

Although the research ultimately followed a different direction, the project became an opportunity to deepen my understanding of computer graphics while exploring how interactive visualization can improve scientific communication.

---

# Motivation

I wanted to better understand how modern graphics engines work by building a 3D environment directly with OpenGL rather than relying on a game engine such as Unity.

Developing the rendering pipeline myself provided a much deeper understanding of the mathematics, rendering techniques, and engineering principles behind real-time graphics.

<img width="839" alt="Screenshot 2024-09-16 at 3 38 21 PM" src="https://github.com/user-attachments/assets/8a208a75-0440-4a7c-8ba3-84bfca1e2e12">

---

# Features

- 🏫 Interactive 3D classroom environment
- 🎮 First-person and perspective camera modes
- 💡 Configurable lighting system
- 🎨 Textured objects and classroom assets
- 🖥️ Real-time rendering
- ⌨️ Interactive keyboard controls
- 📷 Adjustable field of view
- 🌎 Camera movement throughout the environment
- ⚙️ Runtime graphics controls

---

# Technologies

- C
- OpenGL
- GLUT
- Computer Graphics
- Linear Algebra
- Real-Time Rendering

---

# Engineering Challenges

The most challenging aspect of this project was implementing realistic lighting.

Unlike Unity or other game engines, OpenGL requires developers to manually configure almost every part of the graphics pipeline. Developing believable lighting required understanding how:

- Ambient lighting
- Diffuse lighting
- Specular lighting
- Material properties
- Surface normals
- Camera positioning

all interact to produce realistic rendering.

Building these systems manually significantly improved my understanding of modern graphics programming.

<img width="835" alt="Screenshot 2024-09-16 at 3 38 39 PM" src="https://github.com/user-attachments/assets/67fa6984-f584-4e2a-99ef-22946caa63fa">


---

# What I Learned

This project fundamentally changed how I think about graphics programming.

Working directly with OpenGL gave me a much deeper appreciation for how modern game engines such as Unity operate behind the scenes.

Instead of relying on engine abstractions, I learned how to implement many graphics concepts manually, including:

- Graphics pipelines
- Camera systems
- Object transformations
- Lighting models
- Texture mapping
- Real-time rendering
- Graphics optimization

These lessons made learning Unity significantly easier when I later developed my Virtual Reality projects.

---

# Research Inspiration

One of my original goals was to use this project as an interactive visualization tool for my environmental health research.

The vision was to simulate:

- Indoor airflow
- Carbon dioxide (CO₂) concentration
- HEPA air purifier placement
- Classroom ventilation
- Air mixing behavior

allowing researchers to better communicate the effects of portable air filtration systems in classroom environments.

Although the research ultimately moved in another direction, this project demonstrated how computer graphics can support scientific visualization and public health research.

---

# Future Improvements

If I continue this project, I would like to implement:

- 🌬️ Real-time airflow visualization
- 📈 CO₂ concentration heatmaps
- 🫧 Particle system simulation
- 🏫 Interactive classroom layouts
- 🧪 Scientific data overlays
- 🥽 Virtual Reality (VR) support
- 📱 User interface controls
- ⚡ Modern OpenGL rendering techniques (Shaders)

---

# Repository Structure

```text
Assets/
Textures/
Source/
Models/
README.md
```

---

# Installation

Clone the repository:

```bash
git clone https://github.com/NathanielR87/3D-Classroom-OpenGL.git
```

Open the project in your preferred C/OpenGL development environment and build according to your platform.

---

---

# Control
arrow keys  will change view angles
  v:Toggle axes
  u:disable lighting
  x:change perspective (perspective, first person)
  1:Decrease ambient light
  2:increase ambient light
  3:Decrease diffuse light
  4:increase diffuse light
  5:Decrease specular light
  6:increase specular light
  e/E:Decrease/increase emitted light
  n/N:Decrease/increase shininess
  k/k:Switch light sources from ceiling fan to lamp
  a/w/s/d:will let you move if in first person view
  F1:Toggle smooth/flat shading
  F2:Toggle local viewer mode
  +/-:Change field of view of perspective
  arrows:Change view angle
  0:Reset view angle
  ESC:Exit

---

# Why This Project Matters

This project represents an important step in my growth as a software engineer.

It taught me that understanding lower-level graphics programming provides a much stronger foundation for higher-level game engines such as Unity. More importantly, it showed me how computer graphics can extend beyond games into areas like scientific visualization, education, and engineering communication.

---

# Author

**Nathaniel Ramirez**

Systems Software Engineer

Building intelligent, interactive, and data-driven systems.

- 💼 LinkedIn: https://www.linkedin.com/in/nathaniel-ramirez-/
- 💻 GitHub: https://github.com/NathanielR87

---

## Project Status

✅ Completed

This project is no longer under active development but remains an important milestone in my exploration of computer graphics and scientific visualization.
