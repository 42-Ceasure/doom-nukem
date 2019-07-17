# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/22 15:00:20 by nvienot           #+#    #+#              #
#    Updated: 2019/07/17 02:09:50 by nvienot          ###   ########.fr        #
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
SRCFIL				=	main.c \
						exit.c \
						error.c \
						process_hint.c \
						screen.c \
						screen_resized.c \
						init.c set_basics.c	\
						textures.c \
						sprite.c \
						parse_core_file.c \
						mytext.c \
						cmd_parse.c \
						cmd_exec.c \
						modif_file.c \
						parse_map_file.c \
						parse_map_in_core.c \
						parse_map_section.c \
						parse_player_section.c \
						parse_sprite_section.c \
						list_main.c \
						list_dep.c \
						list_do.c \
						run_oc.c \
						moving_functions.c \
						game_functions.c \
						key_events.c \
						keyup_events.c \
						keydown_events.c \
						mouse_events.c \
						5_doom_short_functions.c \
						5_line.c \
						draw.c \
						draw_minimap.c \
						draw_txtr.c \
						draw_sprite.c \
						multithreading.c \
						menu.c moving_ennemy.c \
						fill_tab.c \
						ennemy.c \
						ft_free.c \
						manage_sdl_window.c \
						main2.c \
						init2.c \
						grid.c \
						loop.c \
						sdl_event.c \
						list.c \
						draw_line2.c \
						undo.c \
						delete_mode.c \
						neighbour.c \
						triangulate.c \
						test.c \
						hud.c \
						placing.c \
						placing2.c \
						delete_asset.c \
						data.c \
						data2.c \
						data3.c \
						data4.c \
						data5.c \
						data6.c \
						data7.c \
						data8.c \
						data9.c \
						data10.c \
						data11.c \
						data12.c \
						data13.c \
						data14.c \
						data15.c \
						data16.c \
						data17.c \
						free.c \
						texture_mode.c \
						texture_mode2.c \
						params.c \
						set_and_reset.c \
						fall_and_stair.c \
						handed.c \
						visibility.c

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
