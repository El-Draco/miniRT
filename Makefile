# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 11:45:08 by rriyas            #+#    #+#              #
#    Updated: 2023/07/06 14:05:23 by rriyas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minirt
CC		= cc
RM		= rm -f
SRCS	= src/main.c src/parser/camera_lights.c src/parser/parser.c src/parser/shapes.c src/parser/lexer.c\
			src/parser/attribute_parser.c src/parser/validate.c src/parser/float_parser.c\
			src/raytracer/camera.c src/raytracer/cylinder.c src/raytracer/plane.c src/raytracer/sphere.c src/raytracer/ray.c\
			src/raytracer/intersect.c src/raytracer/shade.c src/raytracer/events.c src/raytracer/utils.c
OBJS	= ${SRCS:.c=.o}
LIB		= lib/minilibx_opengl_20191021/libmlx.a
CFLAGS = -Wall -Wextra -Werror 

$(NAME):	${OBJS} ${LIB} libmath.a libft.a
			${CC} ${CFLAGS} libmath.a libft.a -I lib/minilibx_opengl_20191021/ $(OBJS) -L lib/minilibx_opengl_20191021/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

${LIB}:
			make -C lib/minilibx_opengl_20191021/
libmath.a:
			make -C lib/libmath/
			mv lib/libmath/libmath.a ./
libft.a:
			make -C lib/libft/ all
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
