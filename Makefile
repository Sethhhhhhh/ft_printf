# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yviavant <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 10:40:21 by yviavant          #+#    #+#              #
#    Updated: 2020/01/21 10:55:13 by yviavant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a

CFLAGS		=	-Wall -Wextra -Werror

CC			=	gcc

HEADER		=	includes/ft_printf.h

SRCS		=	srcs/ft_printf.c \
				srcs/ft_parse.c \
				srcs/ft_write.c \
				srcs/ft_utils.c \

LIBFT_SRCS	=	libft/ft_atoi.c \
				libft/ft_bzero.c \
				libft/ft_calloc.c \
				libft/ft_isalnum.c \
				libft/ft_isalpha.c \
				libft/ft_isascii.c \
				libft/ft_isdigit.c \
				libft/ft_isprint.c \
				libft/ft_itoa.c \
				libft/ft_itoa_base.c \
				libft/ft_memccpy.c \
				libft/ft_memchr.c \
				libft/ft_memcmp.c \
				libft/ft_memcpy.c \
				libft/ft_memmove.c \
				libft/ft_memset.c \
				libft/ft_putchar_fd.c \
				libft/ft_putendl_fd.c \
				libft/ft_putnbr_fd.c \
				libft/ft_putnbr_base_fd.c \
				libft/ft_putstr_fd.c \
				libft/ft_split.c \
				libft/ft_strchr.c \
				libft/ft_strdup.c \
				libft/ft_strjoin.c \
				libft/ft_strlcpy.c \
				libft/ft_strlcat.c \
				libft/ft_strlen.c \
				libft/ft_strmapi.c \
				libft/ft_strncmp.c \
				libft/ft_strnstr.c \
				libft/ft_strrchr.c \
				libft/ft_strtrim.c \
				libft/ft_substr.c \
				libft/ft_tolower.c \
				libft/ft_toupper.c \
				libft/ft_strrev.c \

OBJ			=	${SRCS:.c=.o}

LIBFT_OBJ	=	${LIBFT_SRCS:.c=.o}

.c.o		:	${CC} ${CFLAGS} -c -I ${HEADER} $< -o ${<:.c=.o}

${NAME}		:	${OBJ} ${LIBFT_OBJ} ${HEADER}
				ar rc ${NAME} ${OBJ} ${LIBFT_OBJ}
				ranlib ${NAME}

all			:	${NAME}

clean		:
				rm -f ${OBJ} ${LIBFT_OBJ}

fclean		:	clean
				rm -rf ${NAME}

re			:	fclean all
