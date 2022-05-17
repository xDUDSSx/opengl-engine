# Floating islands
## A OpenGL C++ engine

*Semestral project for the BI-PGR class at Czech Technical University in Prague*

A game engine hosting a fictional floating island scene written from scratch using OpenGL and FreeGlut.
This project was written for learning purposes and perhaps hosting it publicly will help someone trying to tackle similar topics.

| **Note** that the project doesn't have a license yet, consider everything "all rights reserved", especially the resources (models / textures), do not redistribute them. |
| --- |

![](img/sc1.png)

# Controls
## UI
There are many settings in the UI of the program realized using Dear ImGui. There are 4 windows:
* Settings - General scene parameters and settings.
* Inspector - Information and parameters of the currently selected object
* Scene Graph - A tree showing the scene graph structure with an option to select specific objects.
* Active camera - Information and parameters about the currently active camera

## General
<dl>
  <dt>RMB</dt>
  <dd>Select object</dd>
  <dt>F1</dt>
  <dd>Camera 1</dd>
  <dt>F2</dt>
  <dd>Camera 2</dd>
  <dt>F3</dt>
  <dd>Camera 3 (Airship)</dd>
  <dt>ESC</dt>
  <dd>Exit</dd>
</dl>

## Camera controls
<dl>
  <dt>F</dt>
  <dd>Switch between pivot and FPS camera modes</dd>
</dl>
### Pivot mode
<dl>
  <dt>LMB Drag</dt>
  <dd>Rotate camera around the pivot point</dd>
  <dt>MMB Drag</dt>
  <dd>Move the pivot perpendicular to the camera's direction</dd>
</dl>
### First person mode
<dl>
  <dt>W, S, A, D</dt>
  <dd>Move camera</dd>
  <dt>LMB Drag</dt>
  <dd>Look around (mouse has to be pressed)</dd>
  <dt>Scroll up</dt>
  <dd>Increase speed</dd>
  <dt>Scroll down</dt>
  <dd>Decrease speed</dd>
  <dt>Shift Hold</dt>
  <dd>Speed boost</dd>
</dl>

![](img/s5.png)