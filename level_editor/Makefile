# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abechet <abechet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/19 17:31:14 by abechet           #+#    #+#              #
#    Updated: 2019/05/22 18:03:40 by abechet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	editor

SRCS	=	sources/main.c \
			sources/init.c \
			sources/grid.c \
			sources/loop.c \
			sources/sdl_event.c \
			sources/list.c \
			sources/draw_line.c \
			sources/draw_line2.c \
			sources/undo.c \
			sources/delete_mode.c \
			sources/neighbour.c \
			sources/triangulate.c \
			sources/test.c \
			sources/hud.c \
			sources/placing.c \
			sources/delete_asset.c \
			sources/data.c \
			sources/data2.c \
			sources/data3.c \
			sources/free.c \
			sources/texture_mode.c

CC		=	gcc

INCL	=	-I libraries/libft/ -I includes/ \
			-I ./frameworks/SDL2.framework/Headers \
			-I ./frameworks/SDL2_ttf.framework/Headers \
			-I ./frameworks/SDL2_image.framework/Headers \
			-I ./frameworks/SDL2_mixer.framework/Headers

INCL_NORM	=	libraries/libft/ includes/

FLAGS	=	-Wall -Wextra -Werror -O3

OBJS	=	$(SRCS:.c=.o)

FWORK	=	-lpthread -F ./frameworks/ -framework SDL2 -framework SDL2_image -framework SDL2_ttf \
			-framework SDL2_mixer -rpath ./frameworks/

LIB		=	libraries/libft/libft.a

RM		=	rm -rf

.SILENT	:

.PHONY	: 	all clean fclean re

#Colors
_BLACK=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m
_END=\x1b[0m

all		:	$(NAME)

$(NAME)	:	$(OBJS) Makefile includes
			make -C libraries/libft/
			echo "$(_RED)Compiling libft... $(_GREEN)Done$(_END)"
			$(CC) -o $(NAME) $(FLAG2) $(OBJS) $(LIB) $(FWORK)

$(OBJS)	: 	%.o: %.c
			$(CC) $(FLAGS) $(FLAG2) $(INCL) -c $< -o $@

clean	:
			make clean -C libraries/libft/
			$(RM) $(OBJS)
			echo "$(_RED)Cleaning obj... $(_GREEN)Done$(_END)"

fclean	:	clean
			$(RM) $(NAME)
			make fclean -C libraries/libft/
			echo "$(_RED)Cleaning all... $(_GREEN)Done$(_END)"

re		:	fclean all

recl	:	re
			make clean

norm	:	fclean
			echo "$(_RED)Starting norminette...$(_END)"
			norminette $(SRCS) $(INCL_NORM) | grep -B 1 '^Error' 2> /dev/null && echo "$(_RED)Norm KO :(" || echo "$(_GREEN)Norm OK ! :)$(_END)";
