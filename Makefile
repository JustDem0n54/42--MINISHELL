NAME = minishell

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

FILE = main.c \
		builtins.c \
		parsing.c \
	
LIBFT = libft/libft.a
RM = rm -f
CC = cc
CFLAGS	= -Wall -Werror -Wextra -ggdb
LDFLAGS = -lreadline -lhistory -lncurses
AR	= ar rc
OBJDIR = obj

SRCS = ${FILE}
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all:	${NAME} 
	@echo "${GREEN}Compilation OK !${RESET}"

${LIBFT}:
	@make -s -C libft all

${NAME}:	${OBJS} ${LIBFT}
	@echo "${GREEN}<-------MINISHELL------->${RESET}"
	@echo "${GREEN}Compilation MINISHELL...${RESET}"
	@${CC} ${CFLAGS} ${LDFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@cc $(CFLAGS) -c $< -o $@

clean:
	@echo "${RED}Cleaning...${RESET}"
	@${RM} -rf ${OBJDIR}

fclean: clean
	@echo "$(RED)Cleaning all...$(RESET)"
	@rm -f $(NAME) outfile
	@make -s -C libft fclean

re: fclean all
