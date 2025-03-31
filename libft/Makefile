NAME	= libft.a

LIBC	= \
		ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_memcpy.c ft_memmove.c ft_memset.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
		ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strnjoin.c \
		get_next_line_bonus.c get_next_line_utils_bonus.c free_split.c ft_printf.c \
		ft_len.c ft_utilities.c ft_strcmp.c ft_isspace.c \

BONUS	= \
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

SRCS = ${LIBC}

SRCSALL = ${LIBC} ${BONUS}

OBJS	= ${SRCS:.c=.o}

OBJSALL	= ${SRCSALL:.c=.o}

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

CC	= cc -ggdb
RM	= rm -f
AR	= ar rc

CFLAGS	= -Wall -Werror -Wextra

all:		bonus

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
		
${NAME}:	${OBJS}
	@${AR} ${NAME} ${OBJS} -s

bonus:		${OBJSALL}
	@echo "${GREEN}Compilation FT_PRINTF...${RESET}"
	@echo "${GREEN}Compilation GNL...${RESET}"
	@echo "${GREEN}Compilation LIBFT...${RESET}"
	@${AR} ${NAME} ${OBJSALL}
	@echo "${GREEN}Compilation OK...${RESET}"

clean:
	@${RM} ${OBJSALL}
		
fclean:		clean
	@${RM} ${NAME}
	
re:		fclean all