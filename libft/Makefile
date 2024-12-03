# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 14:20:27 by fjalowie          #+#    #+#              #
#    Updated: 2024/10/23 15:51:58 by fjalowie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	=	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strcpy.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_isspace.c \

OBJS	= ${SRCS:.c=.o}

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			@ar -rcs ${NAME} ${OBJS}
			@echo "Created archive ${NAME}."

all:		${NAME}
			@echo "Build of ${NAME} completed."

clean:
	@rm -f ${OBJS}
	@echo "Clean of ${NAME} completed."

fclean: clean
	@rm -f ${NAME}
	@echo "Full clean of ${NAME} completed."

re: fclean all
	@echo "Rebuild of ${NAME} completed."

.PHONY: all clean fclean re
.PHONY: all clean fclean re
