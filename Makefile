# **************************************************************************** #
#                                                                              #
#   Makefile — Minishell                                                       #
#                                                                              #
#   Hierarquia:                                                                #
#     src/      — .c organizados por subpastas                                 #
#       general_utils/                                                         #
#       lexer/                                                                 #
#     includes/ — todos os .h                                                  #
#     obj/      — todos os .o (gerados automaticamente)                        #
#     libft/    — biblioteca libft                                             #
#                                                                              #
#   make          →  compila o shell normal                                    #
#   make debug    →  modo DEBUG_LEXER: imprime tokens após cada input          #
#   make val      →  Valgrind completo                                         #
#   make re       →  recompila tudo do zero                                    #
#                                                                              #
# **************************************************************************** #

NAME        := minishell

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g3

# ---------------------------------------------------------------------------- #
#  Pastas                                                                       #
# ---------------------------------------------------------------------------- #

SRC_DIR     := src
INC_DIR     := includes
OBJ_DIR     := obj
LIBFT_DIR   := libft

# ---------------------------------------------------------------------------- #
#  Includes                                                                     #
# ---------------------------------------------------------------------------- #

INCLUDES    := -I$(INC_DIR) -I$(LIBFT_DIR)

# ---------------------------------------------------------------------------- #
#  Fontes — adiciona novos .c aqui                                              #
# ---------------------------------------------------------------------------- #

SRCS        :=  general_utils/free.c              \
                general_utils/inits.c             \
                general_utils/read_input.c        \
                general_utils/run_shell.c         \
                general_utils/sinais.c            \
                lexer/lexer.c                     \
                lexer/lexer_word.c                \
                lexer/lexer_operator.c            \
				lexer/lexer_utils.c               \
				parser/parser.c                   \
				parser/parser_cmds.c              \
				parser/parser_utils.c            \
				main.c

SRC_FILES   := $(addprefix $(SRC_DIR)/, $(SRCS))
OBJ_FILES   := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# ---------------------------------------------------------------------------- #
#  Libft                                                                        #
# ---------------------------------------------------------------------------- #

LIBFT       := $(LIBFT_DIR)/libft.a
LDFLAGS     := -L$(LIBFT_DIR) -lft -lreadline

# ---------------------------------------------------------------------------- #
#  Regra principal                                                              #
# ---------------------------------------------------------------------------- #

all: $(LIBFT) $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LDFLAGS) -o $(NAME)
	@echo ""
	@echo "  [OK]  $(NAME) pronto  ->  ./$(NAME)"
	@echo ""

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# src/ficheiro.c -> obj/ficheiro.o
# Recompila se qualquer .h em includes/ mudar
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minishell.h | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ---------------------------------------------------------------------------- #
#  Libft                                                                        #
# ---------------------------------------------------------------------------- #

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# ---------------------------------------------------------------------------- #
#  Modo debug                                                                   #
# ---------------------------------------------------------------------------- #

debug: CFLAGS += -DDEBUG_LEXER
debug: fclean $(LIBFT) $(OBJ_DIR) $(NAME)
	@echo ""
	@echo "  [DEBUG]  modo lexer activo"
	@echo ""

# ---------------------------------------------------------------------------- #
#  Limpeza                                                                      #
# ---------------------------------------------------------------------------- #

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	@echo "  [OK]  obj/ removido"

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "  [OK]  $(NAME) removido"

re: fclean all

# ---------------------------------------------------------------------------- #
#  Utilitários                                                                  #
# ---------------------------------------------------------------------------- #

run: all
	./$(NAME)

debug_run: debug
	./$(NAME)

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME)

val_debug: debug
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

norminette:
	norminette $(SRC_FILES) $(INC_DIR)/minishell.h

tree:
	@find . -not -path './.git/*' -not -path './obj/*' \
		-not -path './libft/obj/*' -not -name '*.o' \
		| sed 's|[^/]*/|  |g'

.PHONY: all clean fclean re debug run debug_run val val_debug norminette tree
