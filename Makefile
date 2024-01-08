NAME		= miniRT
COMP		= cc
FLAGS		= -Wall -Wextra -Werror
LEAK_CHECK	= -fsanitize=address -g -fsanitize=leak
RM			= rm -f
INC			= -I inc -I libft
OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

LIBFT_DIR	= libft
LIBFT		= $(addprefix $(LIBFT_DIR)/,libft.a)
LIBMLX		= ./MLX42
LIBMLXBUILD	= ./MLX42/build
LIBS		= $(LIBMLXBUILD)/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm $(LIBFT)

SRC_DIR		= src
SUBDIR		= . parser errors arithmetic setup test
SRC_SUBDIR	:= $(foreach dir, $(SUBDIR),$(addprefix $(SRC_DIR)/,$(dir)))
SRC			= main.c \
				parser/parse.c \
				parser/utils/addlst.c \
				parser/utils/newlst.c \
				errors/error.c \
				arithmetic/vector_vector.c \
				arithmetic/vector_double.c \
				setup/setup_mlx.c \
				test/test.c


VPATH = $(SRCDIRS)

all: $(NAME)

$(NAME): $(OBJ) $(LIBMLXBUILD) $(LIBFT)
	$(COMP) $(LEAK_CHECK) $(OBJ) $(LIBS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(LIBMLXBUILD):
	@cmake $(LIBMLX) -B $(LIBMLXBUILD) && make -C $(LIBMLXBUILD) -j4

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(COMP) $(LEAK_CHECK) $(INC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir $@

clean:
	$(RM)r $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(LIBMLXBUILD)
	@echo Removed MLX42 build directory

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all