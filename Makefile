# **************************************************************************** #
#                                  Makefile                                    #
# **************************************************************************** #

NAME        = fdf

# -------------------------------
#   Compiler and Flags
# -------------------------------
CC          = cc -g
C_FLAGS     = -Wall -Wextra -Werror
LD_FLAGS    = -Wl,--allow-multiple-definition
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
MATH_FLAGS  = -lm
INC_FLAGS   = -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11

# -------------------------------
#   Directories
# -------------------------------
SRC_DIR     = src
INC_DIR     = includes
OBJ_DIR     = obj
LIBFT_DIR   = libft
MLX_DIR     = minilibx

# -------------------------------
#   Library Dependency
# -------------------------------
LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

# -------------------------------
#   All Source Files (Mandatory + Bonus)
# -------------------------------
SRCS        = $(SRC_DIR)/fdf.c \
			  $(SRC_DIR)/bbox_utils.c \
			  $(SRC_DIR)/draw_grid.c \
			  $(SRC_DIR)/draw_menu.c \
			  $(SRC_DIR)/event_handler_transform.c \
			  $(SRC_DIR)/event_handler_utils.c \
			  $(SRC_DIR)/event_handler.c \
			  $(SRC_DIR)/event_system.c \
			  $(SRC_DIR)/exit_utils.c \
			  $(SRC_DIR)/math_utils.c \
			  $(SRC_DIR)/parsing_utils.c \
			  $(SRC_DIR)/parsing.c \
			  $(SRC_DIR)/rendering.c \
			  $(SRC_DIR)/transform_utils.c

# -------------------------------
#   Header Files
# -------------------------------
HEADERS     = $(INC_DIR)/fdf.h \
			  $(INC_DIR)/fdf_defs.h \
			  $(INC_DIR)/fdf_types.h

# -------------------------------
#   Object Files (Mandatory + Bonus)
# -------------------------------
OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# **************************************************************************** #
#                                 Build Rules                                  #
# **************************************************************************** #

all: $(NAME)
	@echo "🚀 Executable $(NAME) created successfully!"

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) $(MATH_FLAGS) $(LD_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) compiled."

bonus: all

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -s -C $(MLX_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@$(CC) $(C_FLAGS) $(INC_FLAGS) -c $< -o $@

clean:
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@$(MAKE) -s clean -C $(MLX_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "🗑️ $(NAME) object files removed."

fclean:
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@$(MAKE) -s clean -C $(MLX_DIR)
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME) 
	@echo "😒 $(NAME) and $(NAME) object files removed."

re: fclean all

.PHONY: all bonus clean fclean re
