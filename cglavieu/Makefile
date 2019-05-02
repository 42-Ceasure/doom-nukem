#

.PHONY: clean, fclean, re

CC					=	gcc

CFLAG				=	-Wall -Wextra -Werror -g -O0 -fsanitize=address
DBGFLAG				=	-g -O0 -fsanitize=address

NAME				=	doom-nukem

INCDIR				=	./inc/
OBJDIR				=	./obj/
LIBFTDIR			=	./libft/
SRCDIR				=	./src/

INCFIL				=	doom.h
OBJFIL				=	$(SRCFIL:.c=.o)
LIBFTFIL			=	libft.a
SRCFIL				=	main.c exit.c error.c process_hint.c	\
						init.c config_file.c set_basics.c	\
						textures.c sprite.c parse_core_file.c	\
						cmd_parse.c cmd_exec.c cmd_list.c	\
						parse_map_file.c parse_map_section.c parse_player_section.c parse_weapon_section.c parse_sprite_section.c	\
						list_main.c list_dep.c list_do.c	\
						4_run.c	moving_functions.c	\
						key_events.c keyup_events.c keydown_events.c	\
						mouse_events.c	\
						5_doom_short_functions.c 5_line.c	\
						draw_main.c draw_utility.c draw_dep.c draw_minimap.c \
						multi_thread.c

SRC					=	$(addprefix $(SRCDIR),$(SRCFIL))
OBJ					=	$(addprefix $(OBJDIR),$(OBJFIL))
LIBFT				=	$(addprefix $(LIBFTDIR),$(LIBFTFIL))
INC					=	$(addprefix $(INCDIR),$(INCFIL))

INCLIBFT			=	$(LIBFTDIR)inc	

LIBFT_FLAG			=	-L$(LIBFTDIR) -lft

SDL_PATH			=	./SDL2-2.0.3/
LIBSDL_ROOT 		=	./libSDL2/
LIBSDL_PATH 		=	./libSDL2/lib/
LIBSDL				=	libSDL2.a
INCSDL				=	$(LIBSDL_ROOT)include/
LIBSDL_FLAG 		=	-L$(LIBSDL_PATH) -lSDL2 -lSDL2_mixer
SDLBIN				=	$(addprefix $(LIBSDL_PATH),$(LIBSDL))
SDL_CURL			=	`curl https://www.libsdl.org/release/SDL2-2.0.3.zip -o sdl2.zip`

SDLMIX_PATH			=	./SDL2_mixer-2.0.1/
LIBSDLMIX_ROOT		=	./libSDL2/
LIBSDLMIX_PATH		=	./libSDL2/lib/
LIBSDLMIX			=	libSDL2_mixer.a
INCSDLMIX			=	$(LIBSDLMIX_ROOT)include/
SDLMIXBIN			=	$(addprefix $(LIBSDLMIX_PATH),$(LIBSDLMIX))
CURL_MIX			=	`curl https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.1.zip -o sdl_mix.zip`

# FTYPES_PATH			=	./freetype-2.4.8/

# CURL_FTYPES			=	`curl https://www.libsdl.org/projects/SDL_ttf/libs/ft248.zip -o ftypes.zip`

SDLTTF_PATH			=	./SDL2_ttf-2.0.14/
LIBSDLTTF_ROOT		=	./libSDL2/
LIBSDLTTF_PATH		=	./libSDL2/lib/
LIBSDLTTF			=	libSDL2_ttf.a
INCSDLTTF			=	$(LIBSDLTTF_ROOT)include/
SDLTTFBIN			= 	$(addprefix $(LIBSDLTTF_PATH),$(LIBSDLTTF))
CURL_TTF			=	`curl https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.zip -o sdl_ttf.zip`

all					:	libft sdl sdlmix sdlttf $(NAME)

$(NAME)				:	$(OBJ) $(LIBFT)
						@$(CC) $(CFLAG) -lm $(LIBFT_FLAG) $(LIBSDL_FLAG) -o $@ $^ -lpthread
						@echo "compile done"

$(OBJDIR)%.o		:	$(SRCDIR)%.c $(INC)
						@mkdir -p $(OBJDIR)
						@$(CC) $(CFLAG) -I $(INCDIR) -I $(INCLIBFT) -I $(INCSDL) -o $@ -c $<

libft				:	$(LIBFT)

$(LIBFT)			:	$(LIBFTDIR)
						@make -C $(LIBFTDIR)

sdl					:	$(SDLBIN)

$(SDLBIN)			: 		
						$(SDL_CURL)
						unzip sdl2.zip
						rm sdl2.zip
						mkdir -p $(LIBSDL_ROOT)
						cd $(SDL_PATH) && ./configure --prefix=$(PWD)/$(LIBSDL_ROOT)
						make -C $(SDL_PATH)
						make install -C $(SDL_PATH)

sdlmix				:	$(SDLMIXBIN)

$(SDLMIXBIN)		: 		
						$(CURL_MIX)
						unzip sdl_mix.zip
						rm sdl_mix.zip
						cd $(SDLMIX_PATH) && ./configure --prefix=$(PWD)/$(LIBSDLMIX_ROOT)
						make -C $(SDLMIX_PATH)
						make install -C $(SDLMIX_PATH)

sdlttf				:	$(SDLTTFBIN)

$(SDLTTFBIN)		:
						$(CURL_TTF)
						unzip sdl_ttf.zip
						rm sdl_ttf.zip
						cd $(SDLTTF_PATH) && ./configure --prefix=$(PWD)/$(LIBSDLTTF_ROOT)
						make -C $(SDLTTF_PATH)
						make install -C $(SDLTTF_PATH)

clean				:	
						@make -C $(LIBFTDIR) clean
						@rm -Rf  $(OBJDIR)

fclean				:
						@make -C $(LIBFTDIR) fclean
						@rm -Rf  $(OBJDIR)
						@rm -f $(NAME)

sdlclean			:
						rm -rf $(LIBSDL_ROOT)
						rm -rf $(SDL_PATH)
						rm -rf $(LIBSDLMIX_ROOT)
						rm -rf $(SDLMIX_PATH)
						rm -rf $(LIBSDLTTF_ROOT)
						rm -rf $(SDLTTF_PATH)

re					:	fclean all

