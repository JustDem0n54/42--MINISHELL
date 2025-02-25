# LIBFT_DIR = libft
# LIBFT = $(LIBFT_DIR)/libft.a

CC = cc -g
CFLAGS = -Wall -Wextra -Werror -I ./
LDFLAGS = -lreadline -lhistory -lncurses
NAME = minishell
SRC = builtins.c main.c
OBJ = $(SRC:.c=.o)

all : $(NAME)
	@echo "\033[32mCompilation successful !\033[0m"

# $(LIBFT):
# 	@$(MAKE) -s -C $(LIBFT_DIR)
# 	@echo "Compilating $@"

# $(NAME) : $(OBJ) $(LIBFT)
# 	@$(CC) $(OBJ) -o $(NAME) $(LIBFT)

$(NAME) : $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c
	@echo "Compilating $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# clean :
# 	@$(MAKE) -s clean -C $(LIBFT_DIR)
# 	@rm -f $(OBJ)
# 	@echo "\033[32mClean ok\033[0m"

clean :
	@rm -f $(OBJ)
	@echo "\033[32mClean ok\033[0m"

# fclean : clean
# 	@$(MAKE) -s fclean -C $(LIBFT_DIR)
# 	@rm -f $(NAME)

fclean : clean
	@$(MAKE) -s fclean -C
	@rm -f $(NAME)

re : fclean all