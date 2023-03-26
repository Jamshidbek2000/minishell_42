CC				= cc
SRC_DIR			= src/
OBJ_DIR			= obj/
RM				= rm -rf
NAME			= minishell
DN				= > /dev/null
LIBFT			= libft/libft.a
OS				= $(shell uname)
USER			= $(shell whoami)
FLAGS			= -Wall -Werror -Wextra

#DELETE THE PRINT FUNCTIONS FILE
MAIN			= main/prompt \
				  main/minishell \
				  main/shell_loop \
				  main/main_utils \
				  main/print_functions \

BUILTINS		= builtins/cd/cd \
				  builtins/env/env \
				  builtins/pwd/pwd \
				  builtins/exit/exit \
				  builtins/echo/echo \
				  builtins/unset/unset \
				  builtins/cd/cd_utils \
				  builtins/run_builtins \
				  builtins/export/export \
				  builtins/env/env_utils \
				  builtins/echo/echo_trim_n \
				  builtins/export/export_utils \

INIT 			= init/init \

LEXER			= lexer/lexer \
				  lexer/lexer_utils \
				  lexer/syntax_check \
				  lexer/syntax_utils \

PARSER			= parser/parser \
				  parser/token_utils \
				  parser/create_tokens \
				  parser/init_cmd_table \
				  parser/add_token_utils \
				  parser/cmd_table_utils \
				  parser/create_cmd_table \

EXPANDER		= expander/expander \
				  expander/extra_utils \
				  expander/expander_utils \

EXECUTOR		= executor/open/open \
				  executor/execute/execute \
				  executor/path/path_check \
				  executor/heredoc/here_doc \
				  executor/path/extract_path \
				  executor/pipe_handling/pipe \
				  executor/execute/execute_cmd \
				  executor/heredoc/open_heredoc \
				  executor/redirections/wrong_redirs \
				  executor/redirections/handle_redirs \
				  executor/execute/execute_without_pipes \
				  executor/pipe_handling/exec_only_heredoc \

SIGNALS			= signals/signals \

CLEANUP_TOOLS	= cleanup_tools/free/free \
				  cleanup_tools/free_at_error/free_at_error \

GENERAL_UTILS	= general_utils/error \
				  general_utils/general_utils \

SOURCE			= $(MAIN) $(INIT) $(SIGNALS) $(EXPANDER) $(LEXER) $(PARSER) \
				  $(EXECUTOR) $(BUILTINS) $(GENERAL_UTILS) $(CLEANUP_TOOLS) \

SRC				= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SOURCE)))
OBJ				= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SOURCE)))

ifeq ($(OS), Linux)
INCL_RDL_HEADER	= -I /home/linuxbrew/.linuxbrew/opt/readline/include/readline
INCL_RDL_LIB	= -lreadline -L /home/linuxbrew/.linuxbrew/opt/readline/lib
else
INCL_RDL_HEADER	= -I /Users/$(USER)/.brew/opt/readline/include
INCL_RDL_LIB	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
endif

# curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo ""
# @echo "$(YELLOW)  Compiling: $(DEF_COLOR)$(PURPLE)$(NAME) Mandatory Part By:$(DEF_COLOR) $(RED)Mr. Minishell Community$(DEF_COLOR)"
	@echo "$(CYAN2)" $(DN)
	@$(CC) $(FLAGS) $(OBJ) $(INCL_RDL_LIB) $(LIBFT) -lreadline -o minishell $(DN)
	@cd obj/general_utils && touch user.txt && echo $$USER > user.txt
# @echo "$(PURPLE)                       $(NAME) $(DEF_COLOR)$(GREEN)Compiling done.$(DEF_COLOR)"
# @echo ""
# @echo "$(RED) ████▒░▒████▒░██▒░███▒░  █▒░██▒░ ████▒░ ██▒░░▒██▒░██████▒░██▒░    ██▒░"
# @echo " ██▒██▒██▒██▒░██▒░█▒██▒░ █▒░██▒░█▒░ ██▒░██▒░░▒██▒░██▒░    ██▒░    ██▒░"
# @echo " ██▒░███▒░██▒░██▒░█▒░██▒░█▒░██▒░  ██▒░  ████████▒░████▒░  ██▒░    ██▒░"
# @echo " ██▒░░█▒░ ██▒░██▒░█▒░ ██▒█▒░██▒░██▒░ █▒░██▒░░▒██▒░██▒░    ██▒░    ██▒░"
# @echo " ██▒░░░   ██▒░██▒░█▒░  ███▒░██▒░ ████▒░ ██▒░░▒██▒░██████▒░██████▒░██████▒░"
# @echo " ▓▓▒░░     ▓░▒▓▓▒░    ░▒▓▓▒░▓▒░ ░▒▓▓▒░   ▓▒░░▒▓▒░░▒▓▓▒░░░░░░▒▓▓▒░░░▒▓▓▒░"
# @echo " ▓▒░░       ░▒▓▒░     ░▒▓▒░      ░▒▓     ▒░   ▒░  ░▒▓▒░   ░░▒▓▒░  ░░▒▓▒░"
# @echo " ▒░░          ▒░        ▒░        ░░     ░    ░    ░▒░     ░▒▒░    ░▒▒░"
# @echo " ░░           ░         ░          ░                ░       ░░      ░░"
# @echo " ░                                                           ░       ░ $(DEF_COLOR)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(INCL_RDL_HEADER) -c $< -o $@ $(DN)

$(LIBFT):
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(CYAN)LIBFT. $(DEF_COLOR)"
	@echo "$(CYAN2)" $(DN)
	@git submodule update --init --recursive --remote $(DN)
	@make -C ./libft $(DN)
	@echo "$(PURPLE)LIBFT $(DEF_COLOR)$(GREEN)has been compiled.$(DEF_COLOR)"

clean:
	@echo "$(CYAN)CLEAN$(DEF_COLOR)"
	@echo "$(RED)Deleting objects.$(DEF_COLOR)"
	@echo "$(CYAN2)" $(DN)
	@$(RM) $(OBJ_DIR) $(DN)
	@make clean -C ./libft $(DN)
	@echo "$(RED)Object files have been successfully removed!$(DEF_COLOR)"

fclean:
	@make clean $(DN)
	@echo "$(CYAN)FCLEAN$(DEF_COLOR)"
	@echo "$(RED)Deleting objects, executables.$(DEF_COLOR)"
	@echo "$(CYAN2)" $(DN)
	@$(RM) $(NAME) $(DN)
	@make fclean -C ./libft $(DN)
	@$(RM) minishell.dSYM $(DN)
	@echo "$(RED)Executable and object files have been successfully removed.$(DEF_COLOR)"

re: fclean all
	@echo "$(RED)Files have been cleaned and project has been rebuilt!$(DEF_COLOR)"

run: all
	clear
	@./$(NAME)

r:
	@./$(NAME)

v:
	valgrind --read-var-info=yes --leak-check=full --track-origins=yes ./minishell

DEF_COLOR = \033[0;39m
CYAN3 = \033[1;4;96m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
BWhite = \033[1;37m
RED = \033[1;4;91m
GREEN = \033[4;92m
CYAN2 = \x1B[1;36m
CYAN = \033[1;96m

.PHONY: all clean fclean re run r v
