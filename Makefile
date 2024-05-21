LIBFT = libft/libft.a

NAME = minishell 

CFLAGS = -Wall -Wextra -Werror -g3

CLEAN = rm -rf 

OBJS = $(SRCS:%.c=.objects/%.o)

SRCS = 					\
	main_tok.c

all : $(NAME) 

$(LIBFT) : FORCE
	$(MAKE) -C libft/

$(NAME): $(OBJS) 
	$(CC) $(OBJS) -Llibft -lft -o $(NAME) 

.objects/%.o: %.c minishell.h $(LIBFT)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I./ -Ilibft/ -c -o $@ $<

FORCE :

clean:
	rm -rf .objects
	$(MAKE) clean -C libft/

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft/

re: fclean all

.PHONY: clean fclean re FORCE