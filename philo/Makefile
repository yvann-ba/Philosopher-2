NAME = ./philo
CC = /bin/cc
CFLAGS = -Wall -Wextra -Werror -g -pthread 

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

SRC = check_args.c main.c philo.c utils.c init_philo.c print_utils.c

OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo
	@echo "$(YELLOW)Compiling source files...$(NC)"
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation is complete. Generated executable: $(NAME).$(NC)"
	@echo

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling file $<...$(NC)"
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo

$(OBJ_DIR):
	@/bin/mkdir -p $(OBJ_DIR)

clean:
	@echo
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	@/bin/rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Cleaning complete.$(NC)"
	@echo

fclean: clean
	@echo
	@echo "$(YELLOW)Removing executable $(NAME)...$(NC)"
	@/bin/rm -f $(NAME)
	@echo "$(GREEN)Removal complete.$(NC)"
	@echo

re: fclean all

.PHONY: all clean fclean re
