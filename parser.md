
Program receives a *.cub file as an input parameter.
This file is parsed, and if the data is valid, a structure is filled, which will be used for visualizing the game space.

# Expected data in the file
## Wall texture information depending on cardinal direction in format
```
<texture_id> <path_to_the_texture>
```

```bash
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
```

**Rules applied to texture information:**

- <texture_id> can be one of the values "NO", "SO", "WE", "EA"
- Leading spaces before texture_id are allowed (none, one or more spaces)
- One or more spaces are allowed between identifier and path_to_the_texture
- Trailing spaces after path_to_the_texture are allowed (none, one or more spaces)
- No space between identifier and path_to_the_texture is allowed
A warning will be shown:
```
Warning
Line <line_number>. No space after identifier
```

- Each texture_id may appear only once in the file
Error for duplicate identifiers:
```
Error
Line <line_number>. Multiple <texture_id> texture definition.
```

Missing identifier error:
```
Error
No texture specified for <cardinal_direction>.
```

- The value path_to_the_texture must be present
Error for missing path_to_the_texture:
```
Error
Line <line_number>. No path for texture <texture_id>
```
!Error for non-existent file path_to_the_texture or invalid texture file.



## Floor and ceiling color information
```
<surface_id> <color_value>
```

```bash
F 220,100,0
C 225,30,0
```
**Rules applied to color information:**

- <surface_id> can be one of the values "C", "F"
Leading spaces before surface_id are allowed (none, one or more spaces)
- One or more spaces are allowed between surface_id and color_value
- Trailing spaces after color_value are allowed (none, one or more spaces)
- No space between surface_id and color_value is allowed

A warning will be shown:
```
Warning
Line <line_number>. No space after identifier
```

- Each surface_id may appear only once in the file
Error for duplicate identifiers:
```
Error
Line <line_number>. Multiple color definition.
```

Warning for missing identifier:
```
Warning
No color information for the <surface>. The <surface> will be <default_color> (default value).");
// where default_color:
// for <surface> = ceiling is 255,255,255 (white)
// for <surface> = floor is 0,0,0 (black)
```

- color_value must consist of 3 numbers separated by commas
- Each number must be in range 0 to 255 inclusive
- Spaces between numbers are allowed (none, one or more)

Error for invalid color_value:
```
Error
Line <line_number>. Color value must be 3 numbers (0-255) separated by commas
```


## Map information
```
        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

- The map must be composed of only **6 possible characters**:
        * 0 for empty space
        * 1 for wall
        * N, S, E or W for the player’s start position and orientation

Error if other characters are used:
```
Error
Line <line_number>. The line contains unsupported characters
```

Error if map is missing:
```
Error
No map in the file
```

- The map may contain only one N or S or E or W character (player start position)
- Error if multiple starting positions are found:
```
Error
Line <line_number>. Multiple starting player positions on the map. Only one character is allowed: N or S or E or Wor E or W.
```
Error
No player start position on the map (N, S, W, E)

```
