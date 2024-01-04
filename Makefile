NAME		= miniRT
COMP		= cc
FLAGS		= -Wall -Wextra -Werror
LEAK_CHECK	= -fsanitize=address -g -fsanitize=leak
RM			= rm -f
INC			= inc
OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
SRC_DIR		= src
SRC			= main.c

LIBMLX		= ./MLX42
LIBMLXBUILD	= ./MLX42/build
LIBS		= $(LIBMLXBUILD)/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

all: libmlx $(NAME)

libmlx: $(LIBMLX) $(LIBMLXBUILD)

$(LIBMLX):
	git clone https://github.com/codam-coding-college/MLX42.git

$(LIBMLXBUILD):
	@cmake $(LIBMLX) -B $(LIBMLXBUILD) && make -C $(LIBMLXBUILD) -j4

$(NAME): $(OBJ)
	$(COMP) $(LEAK_CHECK) $(OBJ) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(COMP) $(LEAK_CHECK) -I $(INC) $(FLAGS) -c $< -o $@

clean:
	$(RM)r $(OBJ_DIR)
	@rm -rf $(LIBMLXBUILD)
	@echo Removed MLX42 build directory

fclean: clean
	$(RM) $(NAME)

libclean: fclean
	@rm -rf $(LIBMLX)
	@echo Removed MLX42 repository/directory

re: fclean all

libre: fclean libclean all