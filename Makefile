NAME	= minirt

SRCS = $(wildcard src/*.c)

OBJS_DIR = obj
OBJS	= $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRCS))

CC		= cc

CFLAGS	= -I include/ -I libft/ -Wall -Wextra -Werror
LDFLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm -Llibft -lft

$(OBJS_DIR)/%.o: src/%.c
	@echo "Compiling $<..."
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) libft/libft.a
	@$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(NAME)
	@echo "Build of $(NAME) completed."

all:	mlx libft $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)
	@$(MAKE) --no-print-directory -C libft clean
	@echo "Clean of ${NAME} completed."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C libft fclean
	@echo "Full clean of ${NAME} completed."

re: fclean all
	@echo "Rebuild of ${NAME} completed."

mlx:
	@if [ ! -d "mlx" ] || [ -z "`ls -A mlx 2>/dev/null`" ]; then \
		echo "Cloning MinilibX repository..."; \
		rm -rf mlx; \
		git clone https://github.com/42Paris/minilibx-linux.git mlx; \
		cd mlx && ./configure > /dev/null 2>&1; \
		echo "MinilibX cloned and configured."; \
	fi

libft:
	@$(MAKE) --no-print-directory -C libft

.PHONY: all clean fclean re mlx libft