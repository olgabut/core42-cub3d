NAME = cub3d
CC = cc
MODE ?= debug
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -g -O0 -fsanitize=address,undefined
ifeq ($(MODE),debug)
	CFLAGS += $(DFLAGS)
endif

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
INC_DIR = inc
BUILD = build

	LINKER_FLAGS = -L$(LIBFT_DIR) -L$(INC_DIR) -lft -lreadline
PREPROC_FLAGS = -I. -I$(LIBFT_DIR) -I$(INC_DIR)

SRC_FILES = cub3d.c



OBJS_FILES = $(SRC_FILES:%.c=$(BUILD)/%.o)

all: $(NAME)

$(BUILD)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(PREPROC_FLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) MODE=$(MODE)

$(NAME): $(OBJS_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_FILES) $(LINKER_FLAGS) -o $(NAME)

clean:
	rm -rf $(BUILD)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
