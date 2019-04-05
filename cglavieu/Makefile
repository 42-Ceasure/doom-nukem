#

.PHONY: clean, fclean, re

CC			=	gcc

CFLAG		=	-Wall -Wextra -Werror
DBGFLAG		=	-g -O0 -fsanitize=address

NAME		=	doom-nukem

INCDIR		=	./inc/
OBJDIR		=	./obj/
LIBFTDIR	=	./libft/
SRCDIR		=	./src/

INCFIL		=	doom-nukem.h
OBJFIL		=	$(SRCFIL:.c=.o)
LIBFTFIL	=	libft.a
SRCFIL		=	main.c parse.c recap_parsing.c run.c draw.c doom_short_functions.c line.c

SRC			=	$(addprefix $(SRCDIR),$(SRCFIL))
OBJ			=	$(addprefix $(OBJDIR),$(OBJFIL))
LIBFT		=	$(addprefix $(LIBFTDIR),$(LIBFTFIL))
INC			=	$(addprefix $(INCDIR),$(INCFIL))

INCLIBFT	=	$(LIBFTDIR)inc	

LIBFT_FLAG	=	-L$(LIBFTDIR) -lft

SDL_PATH	=	./SDL2-2.0.3/
LIBSDL_ROOT =	./libSDL2/
LIBSDL_PATH =	./libSDL2/lib/
LIBSDL		=	libSDL2.a
INCSDL		= 	$(LIBSDL_ROOT)include/
LIBSDL_FLAG = 	-L$(LIBSDL_PATH) -lSDL2
SDLBIN		= 	$(addprefix $(LIBSDL_PATH),$(LIBSDL))
SDL_CURL	= 	`curl https://www.libsdl.org/release/SDL2-2.0.3.zip -o sdl2.zip`

all				:	libft sdl $(NAME)

$(NAME)			:	$(OBJ) $(LIBFT)
					@$(CC) $(CFLAG) -lm $(LIBFT_FLAG) $(LIBSDL_FLAG) -o $@ $^
					@echo "compile done"

$(OBJDIR)%.o	:	$(SRCDIR)%.c $(INC)
					@mkdir -p $(OBJDIR)
					@$(CC) $(CFLAG) -I $(INCDIR) -I $(INCLIBFT) -I $(INCSDL) -o $@ -c $<

libft			:	$(LIBFT)

$(LIBFT)		:	$(LIBFTDIR)
					@make -C $(LIBFTDIR)

sdl				:	$(SDLBIN)

$(SDLBIN)		: 		
					$(SDL_CURL)
					unzip sdl2.zip
					rm sdl2.zip
					mkdir -p $(LIBSDL_ROOT)
					cd $(SDL_PATH) &&  ./configure --prefix=$(PWD)/$(LIBSDL_ROOT)
					make -C $(SDL_PATH)
					make install -C $(SDL_PATH)

clean			:	
					@make -C $(LIBFTDIR) clean
					@rm -Rf  $(OBJDIR)

fclean			:
					@make -C $(LIBFTDIR) fclean
					@rm -Rf  $(OBJDIR)
					@rm -f $(NAME)

sdlclean		:
					rm -rf $(LIBSDL_ROOT)
					rm -rf $(SDL_PATH)

re				:	fclean all
