# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 15:39:02 by ochaar            #+#    #+#              #
#    Updated: 2019/04/26 17:00:32 by ochaar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), clean, fclean, re

#color
CL = \x1b[35m
GREEN = \033[1;32m
RED = \033[1;31m
CL2 = \x1b[36m
NC = \033[0m

NAME = SDL
SDL_PATH = $(shell pwd)/SDL
FREETYPE_PATH = $(shell pwd)/FREETYPE
MIX_PATH = $(shell pwd)/MIX
TTF_PATH = $(shell pwd)/TTF

ifneq ("$(wildcard $(SDL_PATH))","")
SDL = 1
else
SDL = 0
endif

ifneq ("$(wildcard $(MIX_PATH))","")
MIX = 1
else
MIX = 0
endif

ifneq ("$(wildcard $(FREETYPE_PATH))","")
FREETYPE = 1
else
FREETYPE = 0
endif

ifneq ("$(wildcard $(TTF_PATH))","")
TTF = 1
else
TTF = 0
endif


all: $(NAME)

$(NAME):
	@if [ $(SDL) = 0 ]; then \
	make sdl_2 -j8; \
	fi
	@if [ $(MIX) = 0 ]; then \
	make mix -j8; \
	fi
	@if [ $(FREETYPE) = 0 ]; then \
	make freetype -j8; \
	fi
	@if [ $(TTF) = 0 ]; then \
	make ttf -j8; \
	fi

sdl_2:
	@rm -rf $(SDL_PATH)
	@mkdir $(SDL_PATH)
	@cd $(SDL_PATH) && $(SDL_PATH)/../SDL2-2.0.3/configure --prefix=$(SDL_PATH) && make && make install
	@echo "$(GREEN)[✓] SDL 2.0 COMPILED$(NC)"

mix:
	@rm -rf $(MIX_PATH)
	@mkdir $(MIX_PATH)
	@cd $(MIX_PATH) && $(MIX_PATH)/../SDL2_mixer-2.0.1/configure --prefix=$(MIX_PATH) --with-sdl-prefix=$(SDL_PATH) && make && make install
	@echo "$(GREEN)[✓] SDL_MIXER COMPILED$(NC)"

ttf:
	@rm -rf $(TTF_PATH)
	@mkdir $(TTF_PATH)
	@cd $(TTF_PATH) && $(TTF_PATH)/../SDL2_ttf-2.0.14/configure --prefix=$(TTF_PATH) --with-freetype-prefix=$(FREETYPE_PATH) --with-sdl-prefix=$(SDL_PATH) && make && make install
	@echo "$(GREEN)[✓] SDL_TFF COMPILED$(NC)"

freetype:
	@rm -rf $(FREETYPE_PATH)
	@mkdir $(FREETYPE_PATH)
	@cd $(FREETYPE_PATH) && $(FREETYPE_PATH)/../freetype-2.5.5/configure --prefix=$(FREETYPE_PATH) && make && make install
	@echo "$(GREEN)[✓] FREETYPE COMPILED$(NC)"

mix_clean:
	@rm -rf $(MIX_PATH)
	@echo "$(RED)[-] LIB SDL_MIXER CLEANED$(NC)"

ttf_clean:
	@rm -rf $(TTF_PATH)
	@echo "$(RED)[-] LIB SDL_TTF CLEANED$(NC)"

sdl_clean:
	@rm -rf $(SDL_PATH)
	@echo "$(RED)[-] LIB SDL 2.0 CLEANED$(NC)"

freetype_clean:
	@rm -rf $(FREETYPE_PATH)
	@echo "$(RED)[-] LIB FREETYPE CLEANED$(NC)"

clean:
	@echo "$(CL)[...] CLEANING LIB$(NC)"
	@make ttf_clean
	@make sdl_clean
	@make mix_clean
	@make freetype_clean
