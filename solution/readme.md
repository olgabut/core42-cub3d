*This project has been created as part of the 42 curriculum by vivantso, obutolin.*

# Description

**Cub3D** is a graphics project from the 42 School curriculum aimed at developing a simple first-person 3D engine. The main objective is to create a realistic visualization of a maze using the raycasting algorithm, which transforms a two-dimensional map into a pseudo-3D environment.

The project is implemented in **C using the MiniLibX graphics library** and is designed to deepen understanding of computer graphics, mathematics, and system-level programming.

## Input data and parsing

The visualization is generated based on an input configuration file, whose path must be provided as an argument when launching the program.
<details>
<summary>Input data...</summary>

### Input file (*.cub) contents

The file must contain the following required elements:
* Texture paths for each wall direction
	* North (NO)
	* South (SO)
	* West (WE)
	* East (EA)
* Floor color (F) defined in RGB format
* Ceiling color (C) defined in RGB format
* Map Layout
	* 1 — wall
	* 0 — empty space
	* N, S, E, W — player starting position and orientation

### Validation Rules

* The configuration file must follow the correct format (***.cub**)
* All required identifiers must appear only once and have a valid value format
* All texture values must be accessible and valid
* Color values must be properly formatted **R,G,B** in range [0,255]
* The map must contain only valid characters (1, 0, N, S, E, W)
* Space characters are allowed in the map **only in areas that are not reachable by the player**, and can be used to shape the structure of the maze.
* The map must contain exactly one player starting position
* The map must be closed on all sides of the player's position by walls
* The map should always be at the end of the file, the sequence of other identifiers is not important.
* Any invalid input should result in an error with a clear message

### Example of a valid file
```
NO ./scenes/texture/north.xpm
SO ./scenes/texture/south.xpm
WE ./scenes/texture/west.xpm
EA ./scenes/texture/east.xpm

C 102,255,255
F 64,64,64

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111111100000010001
11110111111111111101010010001
11000000110101011100000010001
10000000000000001100000000001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111101111
```

### Bonus part
Additionally, the file must contain information
* Texture paths for door (D)
* The map layout may contain additional optional characters
	* 2 - door
	* 3 - fire
* A door (2) must be placed between two wall blocks (1), with a wall block directly opposite the other side of the door. The door must also be connected to two empty spaces (0), forming a valid passageway through the wall.

#### Example of a valid file with bonus part
```
NO ./scenes/texture/north.xpm
SO ./scenes/texture/south.xpm
WE ./scenes/texture/west.xpm
EA ./scenes/texture/east.xpm
D ./scenes/texture/door.xpm
C 102,255,255
F 64,64,64

        1111111111111111111111111
        1000000003110000000000301
        1011000001110000000000001
        1001000000020000000000001
111111111011211111110000000000001
100000000011000001110111121111111
11110111111111101000000010001
11110111111111111101010010001
11000003110101011100000010301
10000000000000000110000020001
10000000000000000201010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111101111
```
</details>

## Rendering and visualization

The visualization represents a 3D view generated from a 2D map. The player does not see the entire map at once. Instead, the engine renders only the part of the environment visible from the current camera angle, similar to classic maze-based FPS games (Wolfenstein 3D).

<details>
<summary>Rendering and visualization...</summary>

### Graphics library

The visualization part of Cub3D is implemented using the **MiniLibX graphics library**. MiniLibX is a lightweight graphical library, designed to work with low-level window management and image rendering.

It is used for:
* Creating and managing the application window
* Generating images and displaying them on the screen
* Handling keyboard and mouse events
* Managing the rendering loop
* Working with pixels and textures directly

### Visualization

The visualization represents a 3D view generated from a 2D map. The map itself only contains a top-down representation of the world, but the **raycasting** engine converts it into a perspective view with:
* Textured walls with different appearances depending on their orientation
* A colored ceiling and floor creating
* Depth perception based on the distance from the player to the walls
* A first-person camera perspective centered on the player's position

### Event Handling

The program uses MiniLibX event handlers to process user input.

Keyboard Events

* W — move forward
* S — move backward
* A — move left (strafe)
* D — move right (strafe)
* Left Arrow — rotate camera left
* Right Arrow — rotate camera right
* ESC — close the program and free allocated resources

### Scene Rendering Process
The scene is rendered using the raycasting technique. The engine does not create a real 3D world but calculates a pseudo-3D representation based on the 2D map.

The rendering process consists of several steps:

1. Ray generation
	* For each vertical column of pixels on the screen, a ray is cast from the player's position.
	* Each ray has its own direction depending on the player's viewing angle and camera plane.
2. Ray intersection calculation
	* The ray travels through the map grid until it hits a wall.
	* The **DDA (Digital Differential Analyzer)** algorithm is used to efficiently determine the first wall intersection point.
3. Wall distance calculation
	* The distance between the player and the wall is calculated.
	* The perpendicular distance is used to avoid the fish-eye distortion effect.
4. Wall projection
	* Based on the calculated distance, the height of the wall slice on the screen is determined.
	* Closer walls appear taller, while distant walls appear smaller.
5. Texture mapping
	* The correct texture is selected depending on the direction of the wall hit:
		* North-facing walls
		* South-facing walls
		* East-facing walls
		* West-facing walls
	* The corresponding pixels from the texture are copied to the rendered image.
6. Floor and ceiling rendering
	* The remaining screen areas are filled with the configured floor and ceiling colors.

After all calculations are completed, the generated image is displayed in the window using MiniLibX.

### Scene updating during movement and rotation

The scene is rendered dynamically every time the player's position or viewing direction changes.

* When the player presses a movement key:
	* The corresponding movement vector is calculated.
	* The new position is checked against the map for collisions.
	* If the position is valid, the player's coordinates are updated.
	* The entire scene is rendered again from the new position.

* When the player rotates:
	* The player's viewing angle is changed.
	* The direction vector and camera plane are recalculated.
	* New rays are generated according to the updated viewing direction.
	* The scene is fully redrawn with the new perspective.

## Bonus part

### Minimap
The minimap provides a real-time top-down view of the maze. The minimap is updated dynamically during movement and rotation.

It displays:
* The player's current position and viewing direction (arrow)
* The structure of the map with walls and open spaces
* Open and close doors
* Places with fire

### Doors
The bonus part includes an interactive door system that allows the player to open doors.

Keyboard Events
* F — open or close door (For interaction you need to stand close enough to the door and the player's camera should be directed towards the door)

A closed door is rendered as a wall element with its own door texture, blocking the player's movement and line of sight. When the player presses F near a door, its state changes and the door opens.

An opened door is displayed as two door textures positioned opposite each other, creating a passage between them. This allows the player to move through the doorway while maintaining the visual appearance of the environment.

### Fire animation

The bonus part includes an animated fire effect implemented using a sequence of 5 fire textures with a transparent background.

The fire textures are not configurable through the input .cub file. They are fixed resources that must be located at a strictly defined path and have specific names:
```
./scenes/texture/fire/fire01.xpm
./scenes/texture/fire/fire02.xpm
./scenes/texture/fire/fire03.xpm
./scenes/texture/fire/fire04.xpm
./scenes/texture/fire/fire05.xpm
```

The fire is rendered as a sprite object placed inside the 3D world. Each frame of the animation contains only the flame itself, while the transparent background allows the environment behind the fire to remain visible.

The animation works by replacing the current fire texture with the next one in the sequence. The update logic checks the current time and changes the animation frame every 200 milliseconds.

### Mouse camera rotation

Mouse movement is tracked to calculate the horizontal camera rotation. The player's viewing direction and camera plane are updated according to the mouse displacement, and the scene is redrawn with the new perspective.

Mouse Events

* Mouse movement changes the player's viewing angle.
* The camera rotates according to the horizontal mouse displacement.
* The scene is redrawn after every camera update.

</details>

# Instructions

## Compilation

To build the project, simply run:
```bash
#Mandatory part:
make

#Mandatory part with bonus part:
make bonus
```
This will compile the minishell executable using the default debug mode, which enables additional debugging flags (-g, AddressSanitizer, and UndefinedBehaviorSanitizer).

You can also explicitly control the build mode:
```bash
#Debug mode (default):
make MODE=debug

#Release mode (without debug flags):
make MODE=release
```

## Execution
After compilation, run the program by providing the path to a valid .cub configuration file:
```bash
./cub3d [file-path]

#Example mandatory part:
./cub3d scenes/minimal_scene.cub

#Example bonus part:
./cub3d scenes/bonus_fire.cub
```

## Cleaning
Remove object files:
```bash
make clean
```

Remove all generated files (including executables):
```bash
make fclean
```

Rebuild everything:
```bash
make re
```

# Resources

* Raycasting tutorials
	* https://lodev.org/cgtutor/raycasting.html
	* https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/

* MiniLibX
	* https://github.com/42paris/minilibx-linux
	* https://harm-smits.github.io/42docs/libs/minilibx

* Images and converter
	* https://minecraft.wiki/w/Template:ItemSprite
	* GNU Image Manipulation Program (GIMP)
	* https://convertio.co/png-xpm/

* Docker documentation
	* https://docker-curriculum.com/

* ChatGPT
	* explaining difficult concepts
	* helping understand errors and debug code
