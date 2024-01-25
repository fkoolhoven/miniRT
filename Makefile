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
SUBDIR		= . parser errors vector_math setup render hit_objects lighting
SRC_SUBDIR	:= $(foreach dir, $(SUBDIR),$(addprefix $(SRC_DIR)/,$(dir)))
SRC			= main.c \
				parser/parse.c \
				parser/utils/addlst.c \
				parser/utils/newlst.c \
				parser/utils/utils.c \
				errors/error.c \
				vector_math/vector_math.c \
				vector_math/double_arithmetic.c \
				vector_math/vectors_arithmetic.c \
				render/get_objects.c \
				render/render.c \
				render/utils.c \
				hit_objects/plane.c \
				hit_objects/sphere.c \
				hit_objects/cylinder.c \
				hit_objects/record_hit.c \
				hit_objects/trace_ray.c \
				shading/shading.c


VPATH = $(SRCDIRS)

all: $(NAME)

$(NAME): $(OBJ) $(LIBMLXBUILD) $(LIBFT)
	$(COMP) $(OBJ) $(LIBS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(LIBMLXBUILD):
	@cmake $(LIBMLX) -B $(LIBMLXBUILD) && make -C $(LIBMLXBUILD) -j4

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(COMP) $(INC) $(FLAGS) -c $< -o $@

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