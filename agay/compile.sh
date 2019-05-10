gcc -Wall -Wextra -Werror -g -O0 -fsanitize=address -o doom doom2.c event.c parse.c recap_parsing.c libft/libft.a -L ./minilibx_macos -lmlx -framework OpenGL -framework AppKit
