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
SDLHEADER_PATH = ./lib/SDL/include/SDL2/
SDL_PATH = $(shell pwd)/lib/SDL
MIX_PATH = $(shell pwd)/lib/MIX
TTF_PATH = $(shell pwd)/lib/TTF

INCFIL		=	doom.h
OBJFIL		=	$(SRCFIL:.c=.o)
LIBFTFIL	=	libft.a
SRCFIL		=	main.c exit.c error.c	\
				init.c	\
				textures.c sprite.c	\
				cmd_parse.c cmd_exec.c cmd_list.c	\
				parse_map_file.c parse_map_section.c parse_player_section.c	parse_weapon_section.c parse_sprite_section.c \
				list_main.c list_dep.c list_do.c	\
				4_run.c	moving_functions.c \
				key_events.c keyup_events.c keydown_events.c	\
				mouse_events.c	\
				5_doom_short_functions.c 5_line.c	\
				draw_main.c draw_utility.c draw_dep.c draw_minimap.c \
				multi_thread.c ttf_init.c

SRC			=	$(addprefix $(SRCDIR),$(SRCFIL))
OBJ			=	$(addprefix $(OBJDIR),$(OBJFIL))
LIBFT		=	$(addprefix $(LIBFTDIR),$(LIBFTFIL))
INC			=	$(addprefix $(INCDIR),$(INCFIL))
INCSDL		=	$(INCDIR)SDL2/
LIBSDL_FLAG = -I $(SDLHEADER_PATH) -L $(SDL_PATH)/lib -lSDL2 -L $(MIX_PATH)/lib -lSDL2_mixer -L $(TTF_PATH)/lib -lSDL2_ttf

INCLIBFT	=	$(LIBFTDIR)inc	

LIBFT_FLAG	=	-L$(LIBFTDIR) -lft

all				:	libft sdl_if $(NAME)

$(NAME)			:	$(OBJ) $(LIBFT)
	@make sdl_if
	@$(CC) $(CFLAG) -lm $(LIBFT_FLAG) $(LIBSDL_FLAG) -o $@ $^
	@echo "compile done"

$(OBJDIR)%.o	:	$(SRCDIR)%.c $(INC)
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAG) -I $(INCDIR) -I $(INCLIBFT) -I $(INCSDL) -o $@ -c $<

libft			:	$(LIBFT)

$(LIBFT)		:	$(LIBFTDIR)
	@make -C $(LIBFTDIR)

sdl_if:
	@make -C ./lib

clean			:	
	@make -C $(LIBFTDIR) clean
	@rm -Rf  $(OBJDIR)

fclean			:
	@make -C $(LIBFTDIR) fclean
	@rm -Rf  $(OBJDIR)
	@rm -f $(NAME)

sdlclean		:
	@make -C ./lib clean
	@make -C ./lib freetype_clean
	@make -C ./lib ttf_clean
	@make -C ./lib mix_clean
	@make -C ./lib sdl_clean

re				:	fclean all
