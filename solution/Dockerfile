FROM ubuntu:24.04

WORKDIR /app

RUN apt update && apt install -y \
    x11-apps \
    build-essential \
    gcc \
    make \
    libx11-dev \
    libxext-dev \
    zlib1g-dev \
    libbsd-dev \
    libreadline-dev \
    git \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

COPY minilibx-linux ./minilibx-linux
RUN cd minilibx-linux && ./configure && make

COPY libft ./libft
RUN make -C libft

COPY . .

RUN make bonus

ENTRYPOINT ["./cub3D"]