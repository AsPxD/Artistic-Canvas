

# Artistic Canvas Application

This project implements an interactive canvas application where users can draw, move, resize, and color shapes like circles, rectangles, and triangles using the SFML (Simple and Fast Multimedia Library) framework.

## Table of Contents
1. [Project Description](#project-description)
2. [Prerequisites](#prerequisites)
3. [Setting Up SFML](#setting-up-sfml)
4. [Compilation Instructions](#compilation-instructions)
5. [How to Run the Program](#how-to-run-the-program)
6. [Key Features](#key-features)
7. [Keyboard Shortcuts](#keyboard-shortcuts)
8. [Mouse Controls](#mouse-controls)

## Project Description

The `ArtisticCanvas` application allows users to create, manipulate, and interact with various shapes (circle, rectangle, triangle). Users can:
- Select a shape tool (Circle, Rectangle, Triangle).
- Draw shapes by clicking on the canvas.
- Resize, move, and change the color of the shapes using keyboard shortcuts.
- Delete selected shapes.

## Prerequisites

Before compiling the project, ensure the following:
- **SFML** (Simple and Fast Multimedia Library) is installed on your system.
- A C++ compiler like **g++** is set up.

## Setting Up SFML

To run this project, you need to install SFML.

### For Linux:

1. Install SFML using your package manager:
    ```bash
    sudo apt-get install libsfml-dev
    ```

2. Confirm installation:
    ```bash
    dpkg -s libsfml-dev
    ```

### For Windows:

1. Download the SFML package from the official website:
    - [SFML Download Page](https://www.sfml-dev.org/download.php)
2. Extract the package and configure it with your preferred IDE (e.g., Visual Studio, Code::Blocks).

### For macOS:

1. You can install SFML using Homebrew:
    ```bash
    brew install sfml
    ```

2. Verify installation:
    ```bash
    brew list sfml
    ```

## Compilation Instructions

After installing SFML, you can compile the project using a terminal or IDE.

### Compiling with g++ (Linux/macOS):
Ensure you are in the project directory where the source code is located.

```bash
g++ main.cpp -o ArtisticCanvas -lsfml-graphics -lsfml-window -lsfml-system
```

### Compiling with MinGW (Windows):
For Windows users with MinGW, ensure SFML binaries and libraries are properly linked.

```bash
g++ main.cpp -o ArtisticCanvas -lsfml-graphics -lsfml-window -lsfml-system
```

## How to Run the Program

After compiling the project, execute the binary:

```bash
./ArtisticCanvas
```

This will open a graphical window where you can interact with the canvas.

## Key Features

- **Shape Tools**: Draw circles, rectangles, and triangles on the canvas.
- **Color Customization**: Change the color of shapes using keyboard shortcuts.
- **Move Shapes**: Move the selected shape with arrow keys.
- **Resize Shapes**: Enlarge or shrink shapes using the `+` and `-` keys.
- **Delete Shapes**: Press the `D` key to delete the selected shape.

## Keyboard Shortcuts

- `1`: Select **Circle** tool.
- `2`: Select **Rectangle** tool.
- `3`: Select **Triangle** tool.
- `R`: Change shape color to **Red**.
- `G`: Change shape color to **Green**.
- `B`: Change shape color to **Blue**.
- `+`: Increase the size of the selected shape.
- `-`: Decrease the size of the selected shape.
- `Left Arrow`: Move shape left.
- `Right Arrow`: Move shape right.
- `Up Arrow`: Move shape up.
- `Down Arrow`: Move shape down.
- `D`: Delete the selected shape.

## Mouse Controls

- **Left-click on the canvas** to draw a shape at the clicked position.
- **Left-click on tool buttons** to change the current shape tool.
