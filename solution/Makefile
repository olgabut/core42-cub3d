NAME = cub3d
CC = cc
MODE ?= debug
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -g -O0 -fsanitize=address,undefined
ifeq ($(MODE),debug)
	CFLAGS += $(DFLAGS)
endif

OS := $(shell uname)
ifeq ($(UNAME), Linux)
# Linux
CFLAGS += -D__linux__
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -I$(MLX_DIR)
MLX_LINKS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
else
# macOS
MLX_DIR = minilibx_opengl_20191021
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -I$(MLX_DIR) -DGL_SILENCE_DEPRECATION
MLX_LINKS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm -lz
endif



LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
INC_DIR = inc
BUILD = build

LINKER_FLAGS = -L$(LIBFT_DIR) -L$(INC_DIR) -lft -lreadline
PREPROC_FLAGS = -I. -I$(LIBFT_DIR) -I$(INC_DIR)

SRC_FILES = cub3d.c \
	src/parser/parser.c \
	src/parser/checker.c \
	src/parser/print_message.c \
	src/parser/read_file.c \
	src/parser/analyzer_texture.c \
	src/parser/analyzer_color.c \
	src/parser/analyzer_map.c \
	src/parser/map_list_manager.c \
	src/parser/map_arr_manager.c \
	src/parser/check_map_array.c \
	src/visual/renderer.c \
	src/visual/get_pixel.c \
	src/visual/ray_cast.c \
	src/visual/ray2.c \
	src/visual/texture.c \
	src/visual/draw_utils.c \
	src/visual/graphics_init.c \
	src/visual/events.c

BONUS_SRC_FILES = src/visual/minimap.c
BONUS_OBJS_FILES = $(BONUS_SRC_FILES:%.c=$(BUILD)/%.o)

OBJS_FILES = $(SRC_FILES:%.c=$(BUILD)/%.o)

all: $(NAME)

$(BUILD)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(PREPROC_FLAGS) $(MLX_FLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) MODE=$(MODE)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS_FILES) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS_FILES) $(LINKER_FLAGS) $(MLX_LINKS) -o $(NAME)

bonus: CFLAGS += -DBONUS
bonus: fclean $(OBJS_FILES) $(BONUS_OBJS_FILES) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS_FILES) $(BONUS_OBJS_FILES) $(LINKER_FLAGS) $(MLX_LINKS) -o $(NAME)

clean:
	rm -rf $(BUILD)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
