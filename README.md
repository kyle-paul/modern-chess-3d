# Modern 3D Simulated Chess Game, integrated with AI agents. 

This is a chess game set in a simulated 3D environment, built on a core foundation of OpenGL. While Vulkan is not currently implemented, it is planned for future updates, as the backend renderer is designed to be agnostic. The game supports two-player mode for human opponents as well as gameplay against AI agents, with three difficulty levels: easy, medium, and hard. Players can move pieces using either the keyboard or direct mouse selection within the 3D scene. Additionally, players can customize the board color, adjust environmental lighting, and modify the camera view to analyze the match from different angles.

## Getting Started
### Clone the Repository
First, you need to clone the repository and init all git submodules
```bash
git clone git@github.com:kyle-paul/modern-chess-3d.git
git submodule update --init --recursive
```

### Build Dependencies
Then, to build the dependencies, you can either manually set up by following the [Installation Guide](Installation.md) or run this command to automate the process
```bash
chmod +x build_dependencies.sh
./build_dependencies.sh
```

### Build the Project
Noew, build the project with CMake. My build environment is on Ubuntu 24.04, Linux.
```bash
cmake -B build
cmake --build build --parallel <your-cpu-threads>
./build/chess
```

## Game Controll
|Key|Action|
|:---:|:---:|
|`W`|Move cursor forward 1 step|
|`A`|Move cursor left 1 step|
|`S`|Move cursor backward 1 step|
|`D`|Move cursor right 1 step|
|`Space`|Select piece<br>Move piece<br>Cancel move|
|`Z`|Undo last move|
|`R`|Redo last move|

## Tasks Completed
- [x] Added `spdlog` for debugging the code.  
- [x] Abstracted the window application.  
- [x] Abstracted the camera control.  
- [x] Abstracted the shading program.  
- [x] Abstracted the rendering system (supports multiple backend APIs).  
- [x] Abstracted the `VertexArray`, `VertexBuffer`, and `IndexBuffer`.  
- [x] Abstracted the environment (lighting, background).  
- [x] Abstracted the square on the board, including rotation.  
- [x] Created the game state.  
- [x] Abstracted the mesh loading.  
- [x] Added all chess players to the board and controlled the lighting.  
- [x] Abstracted the game layers (Game → Board → Square → Piece → Grid).  
- [x] Added selection using keyboard events.  
- [x] Abstracted the game rules.  
- [x] Added the feature to select entities by clicking with framebuffer.
- [x] Added an Undo moves feature using a stack.  
- [x] Added a mode to play against the machine (Minimax).
- [x] Added UI elements for users.  
- [x] Created an easy mode (random moves).
- [x] Implemented the Minimax algorithm.  
- [x] Added Alpha-Beta pruning for deeper searches (hard mode).  
- [x] Designed user options (landscape, board color, lighting).  
- [x] Debugged rules for checkmate and stalemate.  
- [x] Added the Redo feature.  
- [x] Added sound effects using OpenAL.  
- [x] Implemented game state serialization and deserialization.  
- [x] Added the File Dialog for file selection.