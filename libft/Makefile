# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/19 18:35:47 by cglavieu          #+#    #+#              #
#    Updated: 2019/06/21 16:18:08 by nvienot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
# NV : Test sans fsanitize -> crash dans loadcore
CFLAG		=	-Wall -Wextra -Werror -O3
# CFLAG		=	-Wall -Wextra -Werror -g -O0 -fsanitize=address
DBGFLAG		=	-g -O0 -fsanitize=address

NAME = libft.a

SRC = ft_atoi.c\
	ft_bzero.c\
	ft_epur_str.c\
	ft_epur_tabul.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_itoa.c\
	ft_memalloc.c\
	ft_memccpy.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memdel.c\
	ft_memmove.c\
	ft_memset.c\
	ft_putchar.c\
	ft_putchar_fd.c\
	ft_putendl.c\
	ft_putendl_fd.c\
	ft_putnbr.c\
	ft_putnbrendl.c\
	ft_putnbr_fd.c\
	ft_putstr.c\
	ft_putstr_fd.c\
	ft_strcat.c\
	ft_strchr.c\
	ft_strclr.c\
	ft_strcmp.c\
	ft_strcpy.c\
	ft_strdel.c\
	ft_strdup.c\
	ft_strequ.c\
	ft_striter.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlen.c\
	ft_strmap.c\
	ft_strmapi.c\
	ft_strncat.c\
	ft_strncmp.c\
	ft_strncpy.c\
	ft_strnequ.c\
	ft_strnew.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strsplit.c\
	ft_strstr.c\
	ft_strsub.c\
	ft_strtrim.c\
	ft_strctrim.c\
	ft_tolower.c\
	ft_toupper.c\
	precise_get_next_line.c\
	get_next_line.c\
	ft_atof.c\
	ft_memreg.c\
	ft_uitoa_base.c\
	ft_atoui_base.c

SRCDIR = ./src/
SRCFILL = $(addprefix $(SRCDIR),$(SRC))

OBJ = $(SRC:.c=.o)
OBJDIR = ./obj/
OBJFILL = $(addprefix $(OBJDIR),$(OBJ))

INC = ./inc/

all: 		$(NAME)

$(NAME): 	$(OBJFILL)
			@ar rc $@ $^
			@echo "compile of libft done."

$(OBJDIR)%.o:	$(SRCDIR)%.c
			@mkdir -p $(OBJDIR)
			@$(CC) $(CFLAG) -I $(INC) -c $< -o $@

clean:
			@rm -rf $(OBJDIR)

fclean:		clean
			@rm -f $(NAME)

re: 		fclean all
