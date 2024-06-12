NAME			:= miniRT
COMP			:= cc
FLAGS			:= -Wall -Wextra -Werror -O3 
LEAK_CHECK		:= #-fsanitize=address -g -fsanitize=leak
REMOVE			:= rm -f
INC				:= -I inc -I libft

LIBFT_DIR		:= libft
LIBFT			:= $(LIBFT_DIR)/libft.a

LIBMLX_DIR		:= ./MLX42
LIBMLX_BUILD 	:= $(LIBMLX_DIR)/build
LIBMLX			:= $(LIBMLX_BUILD)/libmlx42.a
LIBS			:= $(LIBMLX) -Iinclude -ldl -lglfw -pthread -lm $(LIBFT)

SRC_DIR			:= src
OBJ_DIR			:= obj

SRC				:= $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)
OBJ				:= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

DISCARD			:= /dev/null 2>&1


all: init-submodule $(NAME)

init-submodule:
	@git submodule init
	@git submodule update

$(NAME): $(OBJ) $(LIBMLX_BUILD) $(LIBFT)
	@echo "$(GREEN)$(BOLD)COMPILING:  $(RESET)$(GREEN)$(NAME)$(RESET)"
	@$(COMP) $(LEAK_CHECK) $(OBJ) $(LIBS) -o $(NAME)

$(LIBFT):
	@echo "$(CYAN)$(BOLD)COMPILING:  $(RESET)$(CYAN)$(LIBFT)$(RESET)"
	@make -s -C $(LIBFT_DIR)

$(LIBMLX_BUILD):
	@echo "$(YELLOW)$(BOLD)COMPILING:  $(RESET)$(YELLOW)$(LIBMLX_BUILD)$(RESET)"
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_BUILD) > $(DISCARD) && make -C $(LIBMLX_BUILD) -j4 > $(DISCARD)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@echo "$(BLUE)$(BOLD)COMPILING:  $(RESET)$(BLUE)$(notdir $<)$(RESET)"
	@mkdir -p $(@D)
	@$(COMP) $(INC) $(FLAGS) $(LEAK_CHECK) -c $< -o $@

clean:
	@echo "$(RED)$(BOLD)REMOVING:   $(RESET)$(RED)obj$(RESET)"
	@$(REMOVE)r $(OBJ_DIR)
	@echo "$(RED)$(BOLD)REMOVING:   $(RESET)$(RED)libft obj$(RESET)"
	@make clean -s -C $(LIBFT_DIR) 
	@echo "$(RED)$(BOLD)REMOVING:   $(RESET)$(RED)$(LIBMLX_BUILD)$(RESET)"
	@$(REMOVE)r $(LIBMLX_BUILD)

fclean: clean
	@echo "$(RED)$(BOLD)REMOVING:   $(RESET)$(RED)$(NAME)$(RESET)"
	@$(REMOVE) $(NAME)
	@echo "$(RED)$(BOLD)REMOVING:   $(RESET)$(RED)$(LIBFT)$(RESET)"
	@make fclean -s -C $(LIBFT_DIR)

re: fclean all

BOLD      := \033[1m
RESET     := \033[0m
BLUE      := \033[34m
YELLOW    := \033[33m
GREEN     := \033[32m
RED    	  := \033[31m
CYAN      := \033[36m