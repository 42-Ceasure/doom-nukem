# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agay <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/21 09:39:33 by agay              #+#    #+#              #
#    Updated: 2019/02/15 08:06:28 by agay             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

O_FILES = ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o ft_memchr.o ft_memcmp.o \
		  ft_strlen.o ft_strdup.o ft_strcpy.o ft_strncpy.o ft_strcmp.o ft_strncmp.o ft_isalpha.o \
		  ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_toupper.o ft_tolower.o \
		  ft_strcat.o ft_strncat.o ft_strchr.o ft_strrchr.o ft_strstr.o ft_strnstr.o ft_atoi.o \
		  ft_strlcat.o ft_memalloc.o ft_memdel.o ft_strnew.o ft_strdel.o ft_strclr.o \
		  ft_striter.o ft_striteri.o ft_strmap.o ft_strmapi.o ft_strequ.o ft_putchar.o \
		  ft_putstr.o ft_putnbr.o ft_putendl.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o \
		  ft_putnbr_fd.o ft_strnequ.o ft_strsub.o ft_strjoin.o ft_strtrim.o ft_strsplit.o \
		  ft_itoa.o ft_strtrim_char.o ft_lstnew.o ft_lstdelone.o ft_lstdel.o  ft_lstadd.o \
		  ft_lstiter.o ft_lstmap.o ft_catindex.o ft_countword.o ft_isint.o ft_isneg.o \
		  ft_isspace.o ft_spacecleaner.o ft_isblank.o ft_iscntrl.o ft_isgraph.o \
		  ft_islower.o ft_isupper.o ft_str_is_alpha.o ft_str_is_lowercase.o ft_str_is_numeric.o \
		  ft_str_is_printable.o ft_str_is_uppercase.o ft_strcapitalize.o ft_strcasecmp.o \
		  ft_strlowcase.o ft_strupcase.o get_next_line.o

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	  ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcmp.c ft_strncmp.c ft_isalpha.c \
	  ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	  ft_strcat.c ft_strncat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_atoi.c \
	  ft_strlcat.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
	  ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_putchar.c \
	  ft_putstr.c ft_putnbr.c ft_putendl.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	  ft_putnbr_fd.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
	  ft_itoa.c ft_strtrim_char.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
	  ft_lstiter.c ft_lstmap.c ft_catindex.c ft_countword.c ft_isint.c ft_isneg.c \
	  ft_isspace.c ft_spacecleaner.c ft_isblank.c ft_iscntrl.c ft_isgraph.c \
	  ft_islower.c ft_isupper.c ft_str_is_alpha.c ft_str_is_lowercase.c ft_str_is_numeric.c \
	  ft_str_is_printable.c ft_str_is_uppercase.c ft_strcapitalize.c ft_strcasecmp.c \
	  ft_strlowcase.c ft_strupcase.c get_next_line.c

all: $(NAME)

$(NAME):
	gcc -c -Wall -Wextra -Werror $(SRC)
	ar rc $(NAME) $(O_FILES)
	ranlib $(NAME)
clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
