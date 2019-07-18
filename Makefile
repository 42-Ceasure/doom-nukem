# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/22 15:00:20 by nvienot           #+#    #+#              #
#    Updated: 2019/07/18 21:05:22 by nvienot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = bash
DEBUG = 0
CC = gcc

ifneq ($(wildcard ./core/core.dn3d),)
	ZIP			=	echo -e "\033[38;5;79m[core.dn3d] found, no unzip needed !\033[0m"
else
	ZIP			=	echo -e "\033[38;5;79m[core.dn3d] not found, let's unzip it !" && unzip ./core/core.dn3d.zip && mv ./core.dn3d ./core && echo -e "Unzip done :D\033[0m"
endif

ifeq ($(DEBUG), 0)
    CFLAG       =   -Wall -Wextra -Werror -O2
    MESSAGE     =   "\033[38;5;79m[$(NAME)] compiled on normal rules ! Have fun\033[0m           "

else
    CFLAG       =   -Wall -Wextra -Werror -g -O0 -fsanitize=address
    MESSAGE     =   "\033[38;5;79m[DEBUG] [$(NAME)] compiled on debug rules ! Good job\033[0m       "
endif

NAME                =   doom-nukem

INCDIR              =   ./inc/
OBJDIR              =   ./obj/
LIBFTDIR            =   ./libft/
SRCDIR              =   ./src/

INCFIL              =   doom.h
OBJFIL              =   $(SRCFIL:.c=.o)
LIBFTFIL            =   libft.a
SRCFIL				=	src_game/main.c \
						src_game/exit.c \
						src_game/error.c \
						src_game/process_hint.c \
						src_game/screen.c \
						src_game/screen_resized.c \
						src_game/init.c \
						src_game/set_basics.c \
						src_game/textures.c \
						src_game/sprite.c \
						src_game/parse_core_file.c \
						src_game/mytext.c \
						src_game/cmd_parse.c \
						src_game/cmd_exec.c \
						src_game/modif_file.c \
						src_game/parse_map_file.c \
						src_game/parse_map_in_core.c \
						src_game/parse_map_section.c \
						src_game/parse_player_section.c \
						src_game/parse_sprite_section.c \
						src_game/list_main.c \
						src_game/list_dep.c \
						src_game/list_do.c \
						src_game/run_oc.c \
						src_game/moving_functions.c \
						src_game/game_functions.c \
						src_game/key_events.c \
						src_game/keyup_events.c \
						src_game/keydown_events.c \
						src_game/mouse_events.c \
						src_game/5_doom_short_functions.c \
						src_game/5_line.c \
						src_game/draw.c \
						src_game/draw_minimap.c \
						src_game/draw_txtr.c \
						src_game/draw_sprite.c \
						src_game/multithreading.c \
						src_game/menu.c \
						src_game/moving_ennemy.c \
						src_game/fill_tab.c \
						src_game/ennemy.c \
						src_game/ft_free.c \
						src_game/set_and_reset.c \
						src_game/fall_and_stair.c \
						src_game/handed.c \
						src_game/visibility.c \
						src_game/sdl_event.c \
						src_game/hud.c \
						\
						src_editor/manage_sdl_window.c \
						src_editor/launch_editor.c \
						src_editor/init_editor.c \
						src_editor/grid.c \
						src_editor/loop.c \
						src_editor/list.c \
						src_editor/line_editor.c \
						src_editor/undo.c \
						src_editor/delete_mode.c \
						src_editor/neighbour.c \
						src_editor/triangulate.c \
						src_editor/test.c \
						src_editor/placing.c \
						src_editor/placing2.c \
						src_editor/delete_asset.c \
						src_editor/data.c \
						src_editor/data2.c \
						src_editor/data3.c \
						src_editor/data4.c \
						src_editor/data5.c \
						src_editor/data6.c \
						src_editor/data7.c \
						src_editor/data8.c \
						src_editor/data9.c \
						src_editor/data10.c \
						src_editor/data11.c \
						src_editor/data12.c \
						src_editor/data13.c \
						src_editor/data14.c \
						src_editor/data15.c \
						src_editor/data16.c \
						src_editor/data17.c \
						src_editor/free_editor.c \
						src_editor/texture_mode.c \
						src_editor/texture_mode2.c \
						src_editor/params.c

SRC                 =   $(addprefix $(SRCDIR),$(SRCFIL))
OBJ                 =   $(addprefix $(OBJDIR),$(OBJFIL))
LIBFT               =   $(addprefix $(LIBFTDIR),$(LIBFTFIL))
INC                 =   $(addprefix $(INCDIR),$(INCFIL))
INCLIBFT            =   $(LIBFTDIR)inc
LIBFT_FLAG          =   -L$(LIBFTDIR) -lft

SDL_PATH            =   ./SDL2-2.0.9/
LIBSDL_ROOT         =   ./libSDL2/
LIBSDL_PATH         =   ./libSDL2/lib/
LIBSDL              =   libSDL2.a
INCSDL              =   $(LIBSDL_ROOT)include/
LIBSDL_FLAG         =   -L$(LIBSDL_PATH) -lSDL2 -lSDL2_mixer
SDLBIN              =   $(addprefix $(LIBSDL_PATH),$(LIBSDL))
SDL_CURL            =   `curl https://www.libsdl.org/release/SDL2-2.0.9.zip -o sdl2.zip`

SDLMIX_PATH         =   ./SDL2_mixer-2.0.4/
LIBSDLMIX_ROOT      =   ./libSDL2/
LIBSDLMIX_PATH      =   ./libSDL2/lib/
LIBSDLMIX           =   libSDL2_mixer.a
INCSDLMIX           =   $(LIBSDLMIX_ROOT)include/
SDLMIXBIN           =   $(addprefix $(LIBSDLMIX_PATH),$(LIBSDLMIX))
CURL_MIX            =   `curl https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.zip -o sdl_mix.zip`

T = $(words $(OBJ))
N = 0
C = $(words $N)$(eval N := x $N)
PROGRESS = "[`expr $C  '*' 100 / $T`%]"

all                 :   libft sdl sdlmix $(NAME)

$(NAME)             :   $(OBJ) $(LIBFT)
						@$(CC) $(CFLAG) -lm $(LIBFT_FLAG) $(LIBSDL_FLAG) -o $@ $^ -lpthread
						@echo -e $(MESSAGE)
						@$(ZIP)

$(OBJDIR)%.o        :   $(SRCDIR)%.c $(INC)
						@mkdir -p $(OBJDIR)
						@mkdir -p ./obj/src_game
						@mkdir -p ./obj/src_editor
						@$(CC) $(CFLAG) -I $(INCDIR) -I $(INCLIBFT) -I $(INCSDL) -o $@ -c $<
						@echo -ne "[$(NAME)] progress : $(PROGRESS) | $@                    \r"

libft               :   $(LIBFT)

$(LIBFT)            :   $(LIBFTDIR)
						@make -C $(LIBFTDIR)

sdl                 :   $(SDLBIN)

$(SDLBIN)           :
						$(SDL_CURL)
						unzip sdl2.zip
						rm sdl2.zip
						mkdir -p $(LIBSDL_ROOT)
						cd $(SDL_PATH) && ./configure --prefix=$(PWD)/$(LIBSDL_ROOT)
						make -C $(SDL_PATH)
						make install -C $(SDL_PATH)

sdlmix              :   $(SDLMIXBIN)

$(SDLMIXBIN)        :
						$(CURL_MIX)
						unzip sdl_mix.zip
						rm sdl_mix.zip
						cd $(SDLMIX_PATH) && ./configure --prefix=$(PWD)/$(LIBSDLMIX_ROOT)
						make -C $(SDLMIX_PATH)
						make install -C $(SDLMIX_PATH)

clean               :
						@make -C $(LIBFTDIR) clean
						@rm -Rf  $(OBJDIR)

fclean              :
						@make -C $(LIBFTDIR) fclean
						@echo -ne "Cleaning [$(NAME)]... In progress...\r"
						@rm -Rf  $(OBJDIR)
						@rm -f $(NAME)
						@echo -e "Cleaning [$(NAME)] done !              "

sdlclean            :
						rm -rf $(LIBSDL_ROOT)
						rm -rf $(SDL_PATH)
						rm -rf $(LIBSDLMIX_ROOT)
						rm -rf $(SDLMIX_PATH)

re                  :   fclean all
