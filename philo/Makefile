NAME := philo

CC := gcc

CFLAGS := -Wall -Wextra -Werror

INCLUDES := -I includes

SRC := main.c \
		input_processing/input_check.c \
		helper_functions/atolong.c

SRC_DIR = src
OBJ_DIR = obj

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/input_processing
	@mkdir -p $(OBJ_DIR)/helper_functions
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "Compiling $<"


clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re