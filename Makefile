LIBFT_DIR = inc/libft
LIBFT = $(LIBFT_DIR)/libft.a
IFLAG = -I inc -I$(LIBFT_DIR)

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g3

CLEAN = rm -rf

#OBJS = $(SRCS:%.c=.objects/%.o)
#SRCS =

#SRCS = $(wildcard src/*.c)

SRCS =								\
		src/built-in_echo.c			\
		src/built-in_pwd_cd.c		\
		src/built-in_utils.c		\
		src/data_init.c				\
		src/exit_utils.c			\
		src/export_utils.c			\
		src/export.c				\
		src/free_close_utils.c		\
		src/get_env.c				\
		src/heredoc.c				\
		src/lexer_utils.c			\
		src/lexer.c					\
		src/main.c					\
		src/monitoring.c			\
		src/monitoring_utils.c		\
		src/pathfinder_utils.c		\
		src/pathfinder.c			\
		src/pipex.c					\
		src/redirection.c			\
		src/routine.c				\
		src/signal.c				\
		src/syntax_check_utils.c	\
		src/syntax_check.c			\
		src/t_commands_utils.c		\
		src/t_token_utils.c			\
		src/tab_utils.c				\
		src/token_init_utils.c		\
		src/token_init.c			\
		src/unset.c					\

OBJS = $(patsubst src/%.c, .objects/%.o, $(SRCS))

all : $(NAME)

$(LIBFT) : FORCE
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) 
	@$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@echo "\033[0;32m./minishell is built\033[0m" 

.objects/%.o: src/%.c inc/minishell.h inc/lexer.h $(LIBFT)
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(IFLAG) -c -o $@ $<

FORCE :

clean:
	@rm -rf .objects
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: clean fclean re FORCE
