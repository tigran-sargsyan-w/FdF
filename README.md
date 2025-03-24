# FdF

![42 Logo](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTXfAZMOWHDQ3DKE63A9jWhIqQaKcKqUIXvzg&s)

**FdF** is a project from 42 School that challenges you to create a 3D wireframe visualization of a landscape based on elevation data. This project will help you delve into graphics programming, matrix transformations, and interactive user input handling.

![Program Screenshot](https://i.ibb.co/S4RJxYsx/Screenshot-2025-03-24-130214.png)

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [Testing](#testing)
- [Troubleshooting](#troubleshooting)

## Description

The **fdf** project involves reading a map file containing elevation data and displaying its 3D wireframe model. Using a simple graphics library, you will render the landscape and provide interactive controls for navigation such as zoom, rotation, and translation.

## Features

- **3D Rendering:** Visualize a wireframe model of a 3D landscape.
- **Interactive Navigation:** Rotate, zoom, and pan the view using keyboard and/or mouse inputs.
- **Data Parsing:** Efficiently read and process elevation data from map files.
- **Optimized Performance:** Designed to render scenes in real time with minimal delay.

## Requirements

- **C Compiler** (e.g., `gcc`)
- **Make** (for building the project)
- **MiniLibX:** A lightweight graphics library used at 42.
- **Unix-based Operating System:** Linux or macOS.

## Installation

1. **Clone the repository:**
    ```bash
    git clone https://github.com/tigran-sargsyan-w/FdF.git
    ```
2. **Navigate to the project directory:**
    ```bash
    cd FdF
    ```
3. **Compile the project using Make:**
    ```bash
    make
    ```
    This will compile the `fdf` executable.

## Usage

Run the program by providing a map file as an argument:
```bash
./fdf maps/42.fdf
```
The program will open a window displaying the 3D wireframe of the provided map. Use the keyboard and mouse to navigate through the landscape.

## How It Works

1. **Input Parsing:**  
   The program reads the input map file and parses the elevation data.

2. **Matrix Transformation:**  
   The elevation data is transformed into a 3D model using matrix operations.

3. **Rendering:**  
   The 3D wireframe is rendered using the MiniLibX graphics library.

4. **User Interaction:**  
   Interactive controls allow you to rotate, zoom, and pan the view.

5. **Output:**  
   The final output is a dynamically rendered 3D visualization of the landscape.

## Testing

The repository includes several test maps and a testing script to verify the functionality of **fdf**.

### Running the Tests

Execute the testing script to run all test cases:
```bash
./tester.sh
```
The script will validate:
- Proper parsing of map files.
- Accurate 3D rendering.
- Responsiveness of interactive controls.
- Memory management and performance.

## Troubleshooting

- **MiniLibX Installation:** Ensure that MiniLibX is correctly installed and configured on your system.
- **Map File Format:** Verify that your map files follow the expected format.
- **Memory Leaks:** Use tools such as Valgrind to detect any memory leaks or errors.

```

Feel free to modify and expand this README as needed for your implementation details or additional features.
