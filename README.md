# Artistic Canvas

## Overview

Artistic Canvas is a simple drawing application built using the SFML library. It allows users to create, manipulate, and save shapes on a canvas. The application supports circles, rectangles, triangles, and an eraser tool, providing a straightforward graphical interface for artistic creation.

## Features

- Draw shapes: Circle, Rectangle, Triangle
- Erase shapes
- Change shape colors
- Resize, move, and rotate shapes
- Duplicate and invert shape colors
- Save the canvas as an image

## Setup and Installation

### Prerequisites

- **C++ Compiler**: Ensure you have a C++ compiler installed (e.g., GCC, Clang, MSVC).
- **SFML Library**: Download and install the SFML library from [SFML's official website](https://www.sfml-dev.org/download.php).

### Installation Steps

#### Windows

1. **Download SFML**:
   - Choose the version compatible with your compiler (e.g., MinGW).
   - Extract the downloaded files to a known directory.

2. **Set Up SFML**:
   - Add the SFML `include` and `lib` directories to your compiler's search paths.
   - Copy the SFML DLLs to your project's directory or system path.

3. **Compile and Run**:
   - Use the following g++ command to compile:
     ```bash
     g++ -o ArtisticCanvas main.cpp -I<path_to_SFML_include> -L<path_to_SFML_lib> -lsfml-graphics -lsfml-window -lsfml-system
     ```
   - Replace `<path_to_SFML_include>` and `<path_to_SFML_lib>` with the actual paths.

#### Linux

1. **Install SFML**:
   - Use your package manager to install SFML:
     ```bash
     sudo apt-get install libsfml-dev
     ```

2. **Compile and Run**:
   - Use the following g++ command to compile:
     ```bash
     g++ -o ArtisticCanvas main.cpp -lsfml-graphics -lsfml-window -lsfml-system
     ```

#### macOS

1. **Install SFML**:
   - Use Homebrew to install SFML:
     ```bash
     brew install sfml
     ```

2. **Compile and Run**:
   - Use the following g++ command to compile:
     ```bash
     g++ -o ArtisticCanvas main.cpp -lsfml-graphics -lsfml-window -lsfml-system
     ```

### Troubleshooting

- **Compiler Errors**: Ensure all SFML libraries are correctly linked and paths are set.
- **Missing DLLs (Windows)**: Ensure SFML DLLs are in the executable's directory or system path.
- **Font Issues**: Ensure `arial.ttf` is available in the project directory or modify the code to use a different font.

## User Guide

### Starting the Application

- **Run the Program**: Launch the application by executing the compiled program. A window titled "Artistic Canvas" will appear.

### Interface Components

- **Canvas**: The main area where shapes are drawn.
- **Color Palette**: Located at the top-left, offering five colors (Red, Green, Blue, Yellow, Magenta) for selection.
- **Tool Buttons**: Below the color palette, eight buttons for tool selection:
  - **Circle**: Draw circles.
  - **Rectangle**: Draw rectangles.
  - **Triangle**: Draw triangles.
  - **Eraser**: Remove shapes.
  - **Clear**: Remove all shapes.
  - **Duplicate**: Copy the selected shape.
  - **Invert**: Invert the color of the selected shape.
  - **Download**: Save the canvas as an image.

### Basic Operations

- **Select Color**: Click a color in the palette to set the current drawing color.
- **Choose Tool**: Click a tool button to select the drawing or editing tool.
- **Draw Shape**: Click on the canvas to create a shape using the selected tool and color.
- **Select Shape**: Click on an existing shape to select it for manipulation.

### Shape Manipulation

- **Resize**: Use `+` to increase size, `-` to decrease.
- **Move**: Use arrow keys or `W`, `A`, `S`, `D` to move the shape.
- **Rotate**: Use `Q` to rotate left, `E` to rotate right.
- **Delete**: Press `Delete` to remove the selected shape.
- **Duplicate**: Press `C` to copy the selected shape.
- **Invert Color**: Press `I` to invert the selected shape's color.
- **Save Canvas**: Press `S` or click "Download" to save the canvas as "artwork.png".

### Advanced Features

- **Move to Front/Back**: Press `F` to bring the shape to the front, `B` to send it to the back.

### Tips

- **Eraser Tool**: Click on shapes to remove them.
- **Shape Selection**: Only one shape can be selected at a time for manipulation.
- **Saving**: Ensure the canvas is fully drawn before saving to capture all elements.

## Code Documentation

### Enums and Classes

1. **Tool Enum**: Defines the types of tools available, including Circle, Rectangle, Triangle, and Eraser.

2. **Shape Class**: An abstract base class for drawable shapes, providing virtual methods for drawing, setting color, resizing, moving, rotating, checking if a point is within the shape, getting color, cloning, and destruction.

3. **Circle, Rectangle, Triangle Classes**: Derived from `Shape`, each class implements the virtual methods to handle specific shape operations using SFML's shape classes (`sf::CircleShape`, `sf::RectangleShape`, `sf::ConvexShape`).

### ArtisticCanvas Class

1. **Attributes**:
   - `sf::RenderWindow window`: The main window for rendering the canvas.
   - `std::vector<Shape*> shapes`: A collection of shapes drawn on the canvas.
   - `sf::Color currentColor`: The current color used for drawing new shapes.
   - `Tool currentTool`: The currently selected drawing tool.
   - `Shape* selectedShape`: The currently selected shape for manipulation.
   - `sf::RectangleShape colorPalette[5]`: A palette of colors for selection.
   - `sf::RectangleShape toolButtons[8]`: Buttons for tool selection.
   - `sf::Font font`: Font used for text labels.
   - `sf::Text toolLabels[8]`: Labels for tool buttons.
   - `sf::VertexArray gradient`: A gradient background for the canvas.

2. **Methods**:
   - `setupUI()`: Initializes the UI components, including the color palette, tool buttons, and gradient background.
   - `run()`: Main loop handling events, drawing the UI, and shapes.
   - `drawUI()`: Draws the UI elements on the window.
   - `handleMousePress()`: Handles mouse click events for color and tool selection, and shape creation or manipulation.
   - `createShape()`: Creates a new shape based on the current tool and adds it to the canvas.
   - `eraseShape()`: Removes a shape if the eraser tool is used.
   - `clearShapes()`: Clears all shapes from the canvas.
   - `handleKeyPress()`: Handles keyboard inputs for shape manipulation (resize, move, rotate, delete, etc.).
   - `moveToFront()`, `moveToBack()`: Changes the drawing order of shapes.
   - `duplicateShape()`: Creates a copy of the selected shape.
   - `invertShapeColor()`: Inverts the color of the selected shape.
   - `saveCanvas()`: Saves the current canvas as an image file.

### Main Function

- Instantiates the `ArtisticCanvas` and starts the application by calling `run()`.

## Keyboard Shortcuts

- **Resize Shape**: `+` to increase size, `-` to decrease.
- **Move Shape**: Arrow keys or `W`, `A`, `S`, `D` to move.
- **Rotate Shape**: `Q` to rotate left, `E` to rotate right.
- **Delete Shape**: `Delete` key.
- **Duplicate Shape**: `C` key.
- **Invert Shape Color**: `I` key.
- **Save Canvas**: `S` key or "Download" button.
- **Move Shape to Front/Back**: `F` to front, `B` to back.

## Arial.ttf

The `arial.ttf` font file is included in the repository to ensure consistent text rendering across different systems. Make sure `arial.ttf` is in the project directory to avoid font issues. Modify the code if you prefer using a different font.
