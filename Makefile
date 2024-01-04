NAME		= miniRT
COMP		= cc
FLAGS		= -Wall -Wextra -Werror
LEAK_CHECK	= -fsanitize=address -g -fsanitize=leak
RM			= rm -f
INC			= inc
OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

LIBMLX		= ./MLX42
LIBMLXBUILD	= ./MLX42/build
LIBS		= $(LIBMLXBUILD)/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

SRC_DIR		= src
SUBDIR		:= . \
			   parser \
			   errors
SRC_SUBDIR	:= $(foreach dir, $(SUBDIR),$(addprefix $(SRC_DIR)/,$(dir)))
SRC			= main.c \
				parser/parse.c \
				errors/error.c


VPATH = $(SRCDIRS)

all: $(NAME)

$(NAME): $(OBJ) $(LIBMLXBUILD)
	$(COMP) $(LEAK_CHECK) $(OBJ) $(LIBS) -o $(NAME)

$(LIBMLXBUILD):
	@cmake $(LIBMLX) -B $(LIBMLXBUILD) && make -C $(LIBMLXBUILD) -j4

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(COMP) $(LEAK_CHECK) -I $(INC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir $@

clean:
	$(RM)r $(OBJ_DIR)
	@rm -rf $(LIBMLXBUILD)
	@echo Removed MLX42 build directory

fclean: clean
	$(RM) $(NAME)

re: fclean all