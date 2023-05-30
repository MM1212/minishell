PROJECT_NAME = Minishell

SRC_PATH = srcs

## MODULES ##

CTX_SRC_FILES =			context/context.c
EVENTS_SRC_FILES =		events/events.c
LOGGER_SRC_FILES =		logger/functions.c logger/logger.c logger/ctx.c
PROMPTER_SRC_FILES =	prompter/prompter.c prompter/utils.c
ENVP_SRC_FILES =		env/fns.c env/fns2.c env/fns3.c env/fns4.c \
						env/var.c env/var2.c env/registry.c \
						env/path/ctx.c env/path/path.c
CMDS_SRC_FILES = 		cmd/cmd.c cmd/ctx.c cmd/fns.c \
						cmd/overrides.c \
						cmd/overrides/cd.c \
						cmd/overrides/env.c \
						cmd/overrides/exit.c \
						cmd/overrides/pwd.c \
						cmd/overrides/echo.c \
						cmd/overrides/export.c \
						cmd/overrides/unset.c
RUNNER_SRC_FILES = 		runner/sanitizer.c runner/utils.c \
						runner/unix.c runner/runner.c \
						runner/runtime.c runner/runtime2.c \
						runner/heredoc.c
PARSER_SRC_FILES = 		parser/parsing_errors.c parser/parsing_lexer.c \
						parser/parsing_utils.c parser/parsing_utils2.c parser/parsing.c \
						parser/parsing_lexer2.c
SIGNAL_SRC_FILES =		signals/signals.c
DIR_SRC_FILES =			dir/fns.c dir/fns2.c \
						dir/ctx.c
UTILS_SRC_FILES = 		utils/error.c utils/quit.c
SRC_FILES =	$(CTX_SRC_FILES) $(EVENTS_SRC_FILES) \
			$(LOGGER_SRC_FILES) $(PROMPTER_SRC_FILES) \
			$(ENVP_SRC_FILES) $(DIR_SRC_FILES) \
			$(UTILS_SRC_FILES) $(CMDS_SRC_FILES) \
			$(SIGNAL_SRC_FILES) $(PARSER_SRC_FILES) \
			$(RUNNER_SRC_FILES) minishell.c

SRCS = $(addprefix $(SRC_PATH)/, $(SRC_FILES))

OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

NAME = minishell

CC = cc

LIBFT_PATH = libs/libft
LIBFT_BIN = $(addprefix $(LIBFT_PATH)/,bin)
LIBFT_INCLUDES = $(addprefix $(LIBFT_PATH)/,includes/)
LIBFT_ARCH = $(addprefix $(LIBFT_BIN)/,libft.a)

INCLUDES = -O3 -Iinclude -I$(LIBFT_INCLUDES)

OBJ_FLAGS = $(INCLUDES)
PROGRAM_FLAGS = $(OBJ_FLAGS) -L$(LIBFT_BIN) -lft -lreadline

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

### COLORS ###

RED = \033[0;31m
GREEN = \033[0;92m
YELLOW = \033[93m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[96m
RESET = \033[0m

TAG = [$(CYAN)$(PROJECT_NAME)$(RESET)]

## RULES ##

all: $(NAME)

### LIBS ###

$(LIBFT_ARCH):
	@make -C $(LIBFT_PATH) --no-print-directory --silent

### END OF LIBS ###

$(NAME): $(LIBFT_ARCH) $(OBJS)
	@echo "$(TAG) compiling $(YELLOW)$(NAME)$(RESET).."
	@$(CC) $(OBJS) $(CFLAGS) $(PROGRAM_FLAGS) -o $(NAME)
	@echo "$(CYAN)Done!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@echo "$(TAG) compiling $(YELLOW)$<$(RESET).."
	@mkdir -p $(OBJ_DIR)/$(<D)
	@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS) $(OBJ_DIR) *.o
	@make -C $(LIBFT_PATH) clean --no-print-directory
	@echo "$(TAG) cleaned $(YELLOW)objects!$(RESET)"
fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@echo "$(TAG) cleaned $(YELLOW)archive!$(RESET)"
watch:
	@echo "$(TAG) watching for changes.."
	@while true; do ($(MAKE) -q --no-print-directory || $(MAKE) --no-print-directory); sleep 1; done;

parser_test: $(LIBFT_ARCH)
	@$(CC) -D PARSER_TEST= srcs/parser/*.c $(PROGRAM_FLAGS) $(CFLAGS) -o parser_test
	./parser_test
	rm parser_test

re: fclean all

vg: $(NAME)
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME)

.PHONY: all clean fclean re watch
