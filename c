[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0mLIBFT_DIR = inc/libft
command 'LIBFT_DIR' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0mLIBFT = $(LIBFT_DIR)/libft.a
command 'LIBFT' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0mIFLAG = -I inc -I$(LIBFT_DIR)
command 'IFLAG' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0mNAME = minishell
command 'NAME' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0mCFLAGS = -Wall -Wextra -Werror -g3
command 'CFLAGS' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0mCLEAN = rm -rf
command 'CLEAN' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m#OBJS = $(SRCS:%.c=.objects/%.o)
command '#OBJS' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m#SRCS =
command '#SRCS' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0mSRCS = $(wildcard src/*.c)
command 'SRCS' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0mOBJS = $(patsubst src/%.c, .objects/%.o, $(SRCS))
command 'OBJS' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0mall : $(NAME)
command 'all' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m$(LIBFT) : FORCE
execve failed
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m@$(MAKE) -C $(LIBFT_DIR)
execve failed
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m$(NAME): $(OBJS) 
execve failed
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m@$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
execve failed
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m@echo "\033[0;32m./minishell is built\033[0m" 
command '@echo' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m.objects/%.o: src/%.c inc/minishell.h inc/lexer.h $(LIBFT)
execve failed
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m@mkdir -p $(@D)
command '@mkdir' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m@echo "Compiling $<"
syntax error
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m@$(CC) $(CFLAGS) $(IFLAG) -c -o $@ $<
syntax error
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0mFORCE :
command 'FORCE' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0mclean:
command 'clean:' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m@rm -rf .objects
command '@rm' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m@$(MAKE) clean -C $(LIBFT_DIR)
execve failed
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0mfclean: clean
command 'fclean:' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m$(RM) $(NAME)
execve failed
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m$(MAKE) fclean -C $(LIBFT_DIR)
execve failed
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0mre: fclean all
command 're:' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m.PHONY: clean fclean re FORCE
command '.PHONY:' not found
[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m[1;91m[1mexit
[0m[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m[1;91m[1mexit
[0m[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m[1;91m[1mexit
[0m[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m[1;91m[1mexit
[0m[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m[1;91m[1mexit
[0m[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m[1;91m[1mexit
[0m[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m[1;91m[1mexit
[0m[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m[1;91m[1mexit
[0m[1;96m[1macancel@z2r2p2:~/42_CC/Minishell$ [0m[1;91m[1mexit
[0m