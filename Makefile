NAME = minishell

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

FILE = main.c \
		parsing.c \
		execve.c \
		init.c \
		utils2.c \
		# cd.c \
		# echo.c \
		# env.c \
		# export.c \
		# export_add.c \
		# pwd.c \
		# unset.c \
		# exit.c \

LIBFT = libft/libft.a
RM = rm -f
CC = cc
CFLAGS	= -Wall -Werror -Wextra -ggdb
LDFLAGS = -lreadline -lhistory -lncurses
AR	= ar rc
OBJDIR = obj

SRC_DIR = src/builtins src/execution

SRC = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)

all:	${NAME} 
	@echo "${GREEN}Compilation OK !${RESET}"

${LIBFT}:
	@make -s -C libft all

${NAME}:	${OBJS} ${LIBFT}
	@echo "${YELLOW}---------------------------------------------------------------------------------------------------------"
	@echo "      :::::::::  :::::::::  ::::::::::: ::::::::   ::::::::  :::    ::: :::::::::: :::        :::"
	@echo "     :+:    :+: :+:    :+:     :+:    :+:    :+: :+:    :+: :+:    :+: :+:        :+:        :+:"
	@echo "    +:+    +:+ +:+    +:+     +:+    +:+    +:+ +:+        +:+    +:+ +:+        +:+        +:+"
	@echo "   +#++:++#+  +#++:++#:      +#+    +#+    +:+ +#++:++#++ +#++:++#++ +#++:++#   +#+        +#+"
	@echo "  +#+    +#+ +#+    +#+     +#+    +#+    +#+        +#+ +#+    +#+ +#+        +#+        +#+"
	@echo " #+#    #+# #+#    #+#     #+#    #+#    #+# #+#    #+# #+#    #+# #+#        #+#        #+#"
	@echo "#########  ###    ### ########### ########   ########  ###    ### ########## ########## ##########"
	@echo "---------------------------------------------------------------------------------------------------------${RESET}"
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
