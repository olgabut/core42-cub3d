
Программа получает файл *.cub, как входящий параметр
Данный файл анализируется, если данные корректны то заполняется структура, которая будет использоваться для визуализации пространства игры.

Ожидаемые данные в файле
## Информация о текстурах стен в зависимости от стороны света в формате
```
<texture_id> <path_to_the_texture>
```

```bash
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
```
**Правила, применимые к информации о текстурах:**
- <texture_id> может быть одно из значений "NO", "SO", "WE", "EA"
- Допускается отсутствие, один или больше пробелы перед texture_id.
- Допускаются один или больше пробелов между identifier и path_to_the_texture
- Допускаются отсутствие, один или больше пробелы после path_to_the_texture
- Допускается отсутствие пробела между identifier и path_to_the_texture
Об этом будет информационное сообщение
```
Warning
Line <line_number>. No space after <texture_id>
```

- В файле texture_id может присутствовать только один раз
Ошибка о дублирующихся идентификаторах
```
Error
Line <line_number>. Duplicate <texture_id> texture definition.
```
!Ошибка об отсутствующем идентификаторе
```
Error
No texture specified for <cardinal_direction>.
```

- Значение path_to_the_texture должно присутствовать
Ошибка об отсутствующем значении path_to_the_texture
```
Error
Line <line_number>. No path for texture <texture_id>
```
!Ошбика о несуществующем файле path_to_the_texture или не явзяется файлом текстуры



## Информация о цвете потолка и пола
```
<surface_id> <color_value>
```

```bash
F 220,100,0
C 225,30,0
```
**Правила, применимые к информации о цветах:**
- <surface_id> может быть одно из значений "C", "F"
- Допускается отсутствие, один или больше пробелы перед surface_id.
- Допускаются один или больше пробелов между surface_id и color_value
- Допускаются отсутствие, один или больше пробелы после color_value
- Допускается отсутствие пробела между surface_id и color_value
Об этом будет информационное сообщение
```
Warning
Line <line_number>. No space after <surface_id>
```

- В файле surface_id может присутствовать только один раз
Ошибка о дублирующихся идентификаторах
```
Error
Line <line_number>. Duplicate color definition.
```

Предупреждение об отсутствующем идентификаторе
```
Warning
The file doesn't specify a color for the <surface>. The ceiling will be <default_color> (default value).");
// где default_color
//        для <surface> = ceiling равно 255,255,255 (белый)
//        для <surface> = floor равно 0,0,0 (черный)
```

- color_value должно состоять из 3 чисел разделенные запятой
- Значение каждого числа может быть от 0 до 255 включительно
- Допускается отсуствие, один или больше пробелов между числами
Ошибка при некорректном color_value
```
Error
Line <line_number>. Wrong color value.
```


## Информация о карте
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
	0 for an empty space,
	1 for a wall,
	N,S,E or W for the player’s start position and spawning orientation
Ошбика в случае использования других символов
```
Error
Line <line_number> contains unsupported characters.
```

Ошибка в случа отсутствия карты
```
Error
There is not a map.
```

- На карте может присутствовать только один символ N или S или E или W (первоначальная позиция игрока)
- Ошибка в случае повторения нескольких символов N,S,E,W
```
Error
Line <line_number>. There are multiple starting player positions on the map. Only one character is allowed: N or S or E or W.
```
Error
The player's starting position (N, S, E or W) is not indicated on the map.
```
```
