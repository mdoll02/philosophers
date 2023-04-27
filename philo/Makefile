NAME := philo

CC := gcc

CFLAGS := -Wall -Wextra -Werror -g -fsanitize=thread

INCLUDES := -I includes

SRC := main.c \
		input_check.c \
		atolong.c \
		philo_action.c \
		free_utils.c \
		init.c \
		philo_helpers.c \

SRC_DIR = src
OBJ_DIR = obj

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "Compiling $<"


clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re