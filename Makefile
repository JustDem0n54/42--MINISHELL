NAME = minishell

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

LIBFT = libft/libft.a
CFLAGS	= -Wall -Werror -Wextra -ggdb
LDFLAGS = -lreadline -lhistory -lncurses

SOURCES = ./builtins/cd.c ./builtins/echo.c ./builtins/env.c ./builtins/exit.c ./builtins/export_add.c ./builtins/export.c ./builtins/pwd.c ./builtins/unset.c \
		./execution/exec_pipe.c ./execution/execve.c ./execution/init_exec.c ./execution/init.c ./execution/input_output.c ./execution/main.c \
		./execution/make_command.c ./execution/setup_exec.c ./execution/signaux.c ./execution/utils.c \
		./parsing/check_export.c ./parsing/check_dollar.c ./parsing/check_dollar2.c ./parsing/heredoc.c ./parsing/convert_list.c ./parsing/error_parsed.c ./parsing/parse_list.c \

SRCDIR = src
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

all:	${NAME}

${LIBFT}:
	@make -s -C libft all

${NAME}:	${LIBFT} ${OBJS}
	@echo "${YELLOW}---------------------------------------------------------------------------------------------------------"
	@echo "      :::::::::  :::::::::  ::::::::::: ::::::::   ::::::::  :::    ::: :::::::::: :::        :::"
	@echo "     :+:    :+: :+:    :+:     :+:    :+:    :+: :+:    :+: :+:    :+: :+:        :+:        :+:"
	@echo "    +:+    +:+ +:+    +:+     +:+    +:+    +:+ +:+        +:+    +:+ +:+        +:+        +:+"
	@echo "   +#++:++#+  +#++:++#:      +#+    +#+    +:+ +#++:++#++ +#++:++#++ +#++:++#   +#+        +#+"
	@echo "  +#+    +#+ +#+    +#+     +#+    +#+    +#+        +#+ +#+    +#+ +#+        +#+        +#+"
	@echo " #+#    #+# #+#    #+#     #+#    #+#    #+# #+#    #+# #+#    #+# #+#        #+#        #+#"
	@echo "#########  ###    ### ########### ########   ########  ###    ### ########## ########## ##########"
	@echo "---------------------------------------------------------------------------------------------------------${RESET}"
	@cc ${CFLAGS} ${OBJS} -o ${NAME} ${LDFLAGS} ${LIBFT}

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -c $< -o $@

clean:
	@echo "${RED}Cleaning...${RESET}"
	@${RM} -rf ${OBJDIR}

fclean: clean
	@echo "$(RED)Cleaning all...$(RESET)"
	@rm -f $(NAME) obj
	@make -s -C libft fclean

re: fclean all
