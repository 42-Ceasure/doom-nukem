#

.PHONY: clean, fclean, re

CC			=	gcc

CFLAG		=	-Wall -Wextra -Werror -g -O0 -fsanitize=address
DBGFLAG		=	-g -O0 -fsanitize=address

NAME		=	doom-nukem

INCDIR		=	./inc/
OBJDIR		=	./obj/
LIBFTDIR	=	./libft/
SRCDIR		=	./src/

INCFIL		=	doom.h
OBJFIL		=	$(SRCFIL:.c=.o)
	LIBFTFIL	=	libft.a
	SRCFIL		=	0_main.c 0_exit.c 0_error.c	\
					1_init.c	\
					2_00_parse_cmd.c 2_01_exec_cmd.c 2_02_cmd.c	\
					2_10_parse_map_file.c 2_11_map_section.c 2_12_player_section.c	\
					3_recap_parsing.c 3_set_game.c	\
					4_run.c	\
					5_doom_short_functions.c 5_line.c 5_draw.c 5_draw_utility.c 5_main_draw.c 5_minimap.c

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

