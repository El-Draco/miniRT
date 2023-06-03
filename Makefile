# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 11:45:08 by rriyas            #+#    #+#              #
#    Updated: 2023/06/03 20:11:30 by rriyas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minirt
CC		= gcc
RM		= rm -f
SRCS	= src/events.c src/main.c src/mlx_utils.c src/evaluate_ray.c src/parser.c
OBJS	= ${SRCS:.c=.o}
LIB		= lib/minilibx_opengl_20191021/libmlx.a
CFLAGS = -Wall -Wextra -Werror -g

$(NAME):	${OBJS} ${LIB} libmath.a libft.a
			${CC} ${CFLAGS} libmath.a libft.a -I lib/minilibx_opengl_20191021/ -g $(OBJS) -L lib/minilibx_opengl_20191021/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

${LIB}:
			make -C lib/minilibx_opengl_20191021/
libmath.a:
			make -C lib/libmath/
			mv lib/libmath/libmath.a ./
libft.a:
			make -C lib/libft/
			mv lib/libft/libft.a ./

all:	$(NAME)

clean:
		make fclean -C lib/libmath
		make fclean -C lib/libft
		${RM} ${OBJS}

fclean:	clean
		${RM} minirt
		${RM} libft.a libmath.a

re:		fclean all

.PHONY: all clean fclean re