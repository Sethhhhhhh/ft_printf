# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yviavant <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 10:40:21 by yviavant          #+#    #+#              #
#    Updated: 2020/01/28 21:10:35 by yviavant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a

LIBFT		=	libft

CFLAGS		=	-Wall -Wextra -Werror

CC			=	gcc

HEADER		=	includes/ft_printf.h

SRCS		=	srcs/ft_printf.c \
				srcs/ft_parse.c \
				srcs/ft_write.c \

OBJ			=	${SRCS:.c=.o}

.c.o		:	@${CC} ${CFLAGS} -c -I ${HEADER} $< -o ${<:.c=.o}

all			:	${NAME}

${NAME}		:	${OBJ} ${HEADER}
				make -C ${LIBFT}
				cp libft/libft.a ./${NAME}
				ar rc ${NAME} ${OBJ}
				ranlib ${NAME}

clean		:
				rm -f ${OBJ}
				make clean -C ${LIBFT}

fclean		:	clean
				rm -rf ${NAME}
				make fclean -C ${LIBFT}

re			:	fclean all
