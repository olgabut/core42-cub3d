# Docker
* Установить Docker desktop

# сборка
```bash
docker build -t cub3d-dev .
docker build --no-cache -t cub3d-dev . #без кэша

```

# графика
* Установить XQuartz
* Настроить XQuartz
```
open -a XQuartz
```
Около яблока -> XQuartz -> Settings (or Preferences) -> Security -> отметить Allow connections from network clients

* Настраиваем чтобы XQuartz слушал TCP порт
```bash
sudo mkdir -p /opt/X11/etc/X11/xinit
sudo nano /opt/X11/etc/X11/xinit/xserverrc
```
* Добавляем строку
```
exec /opt/X11/bin/Xquartz "$@"
```
Ctrl + O -> enter -> Ctrl + X

* Перезапустить XQuartz
```
killall Xquartz
open -a XQuartz
```

* Проверяем что доступ есть
```bash
lsof -i :6000
```

* Разрешить Docker доступ к X11
```bash
xhost +
xhost +localhost
xhost #проверка
```
* Устанавливаем x11 v контейнере
```bash
docker run \
-it \
--rm \
--entrypoint bash \
-e DISPLAY=host.docker.internal:0 \
cub3d-dev

>apt update
>apt install -y x11-apps
>xeyes
>exit
```


# запуск
Обычная сцена
```bash
docker run cub3d-dev scenes/minimal_scene.cub #не будет визуала

docker run \
-it \
--rm \
-e DISPLAY=host.docker.internal:0 \
cub3d-dev \
scenes/minimal_scene.cub
```

Бонус сцена
```
docker run \
-it \
--rm \
-e DISPLAY=host.docker.internal:0 \
cub3d-dev \
scenes/bonus_fire.cub
```


# разработка
```bash
docker run -it --rm \
-v $(pwd):/app \
-e DISPLAY=host.docker.internal:0 \
--entrypoint bash \
cub3d-dev
```
внутри нормально делаем пересборку и запуск проекта
```
make
make bonus
./cub3d [map-cub-file]
```