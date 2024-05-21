LIBFT_DIR = inc/libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = minishell 

CFLAGS = -Wall -Wextra -Werror

CLEAN = rm -rf 

#OBJS = $(SRCS:%.c=.objects/%.o)
#SRCS = 					

SRCS = $(wildcard src/*.c)

OBJS = $(patsubst src/%.c, .objects/%.o, $(SRCS))

all : $(NAME) 

$(LIBFT) : FORCE
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) 
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME) 

.objects/%.o: src/%.c inc/minishell.h $(LIBFT)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I./ -I$(LIBFT_DIR) -c -o $@ $<

FORCE :

clean:
	rm -rf .objects
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: clean fclean re FORCE