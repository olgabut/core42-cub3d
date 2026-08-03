### Генерация suppression файла с помощью valgrind
```bash
valgrind \
--leak-check=full \
--show-leak-kinds=all \
--gen-suppressions=all \
--error-limit=no \
--log-file=valgrind.log \
./cub3D scenes/minimal_scene.cub
```
### Создать supp файл
Содержимое на основе логов примерно
```
{
   mlx_x11
   Memcheck:Leak
   match-leak-kinds: reachable
   obj:/usr/lib/aarch64-linux-gnu/libX11.so.6.4.0
   fun:*
}

{
   mlx_xext
   Memcheck:Leak
   match-leak-kinds: reachable
   obj:/usr/lib/aarch64-linux-gnu/libXext.so.6.4.0
   fun:*
}

{
   mlx_xcb
   Memcheck:Leak
   match-leak-kinds: reachable
   obj:/usr/lib/aarch64-linux-gnu/libxcb.so.1.1.0
   fun:*
}
```

### Вызов программы с supp файлом
```bash
valgrind \
--leak-check=full \
--show-leak-kinds=all \
--suppressions=valgrind_mlx.supp \
./cub3D scenes/minimal_scene.cub
```