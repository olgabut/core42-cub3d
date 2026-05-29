NAME = cub3d
CC = cc
MODE ?= debug
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -g -O0 -fsanitize=address,undefined
ifeq ($(MODE),debug)
	CFLAGS += $(DFLAGS)
endif

OS := $(shell uname)
# Linux
# MLX_DIR = minilibx-linux
# MLX = $(MLX_DIR)/libmlx.a
# MLX_FLAGS = -I$(MLX_DIR)
# MLX_LINKS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz


LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
INC_DIR = inc
BUILD = build

LINKER_FLAGS = -L$(LIBFT_DIR) -L$(INC_DIR) -lft -lreadline
PREPROC_FLAGS = -I. -I$(LIBFT_DIR) -I$(INC_DIR)

SRC_FILES = cub3d.c \
	src/parser/parser.c \
	src/parser/checker.c \
	src/parser/errors.c \
	src/parser/read_file.c \
	src/parser/analyzer_texture.c \
	src/parser/analyzer_color.c

OBJS_FILES = $(SRC_FILES:%.c=$(BUILD)/%.o)

all: $(NAME)

$(BUILD)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(PREPROC_FLAGS) -c $< -o $@
# 	$(CC) $(CFLAGS) $(PREPROC_FLAGS) $(MLX_FLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) MODE=$(MODE)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS_FILES) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS_FILES) $(LINKER_FLAGS) $(MLX_LINKS) -o $(NAME)

clean:
	rm -rf $(BUILD)
	@$(MAKE) -C $(LIBFT_DIR) clean
# 	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
