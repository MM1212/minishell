PROJECT_NAME = Minishell

SRC_PATH = srcs

## MODULES ##

CTX_SRC_FILES =			context/context.c
EVENTS_SRC_FILES =		events/events.c
LOGGER_SRC_FILES =		logger/functions.c logger/logger.c logger/ctx.c
PROMPTER_SRC_FILES =	prompter/prompter.c
ENVP_SRC_FILES =		env/fns.c env/fns2.c \
						env/var.c env/registry.c

SRC_FILES =	$(CTX_SRC_FILES) $(EVENTS_SRC_FILES) \
			$(LOGGER_SRC_FILES) $(PROMPTER_SRC_FILES) \
			$(ENVP_SRC_FILES) minishell.c

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

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

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
	@make -C $(LIBFT_PATH) --no-print-directory

### END OF LIBS ###

$(NAME): $(LIBFT_ARCH) $(OBJS)
	@echo "$(TAG) compiling $(YELLOW)$(NAME)$(RESET).."
	@$(CC) $(OBJS) $(CFLAGS) $(PROGRAM_FLAGS) -o $(NAME)
	@echo "$(CYAN)Done!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@echo "$(TAG) compiling $(YELLOW)$<$(RESET).."
	@mkdir -p $(OBJ_DIR)/$(dir $<)
	@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS) $(OBJ_DIR)
	@make -C $(LIBFT_PATH) clean --no-print-directory

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_PATH) fclean --no-print-directory

watch:
	@echo "$(TAG) watching for changes.."
	@while true; do ($(MAKE) -q --no-print-directory || $(MAKE) --no-print-directory); sleep 1; done;

re: fclean all
