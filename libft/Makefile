NAME = libft.a 

include srcs.mk

CC = cc

CFLAGS = -Wall -Werror -Wextra

OBJS = $(SRCS:%.c=.objects/%.o)

OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)

CLEAN = rm -rf

all: $(NAME)
	
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

.objects/%.o: %.c libft.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I./ -c -o $@ $<
	
clean:
	$(CLEAN) .objects

fclean: clean
	$(CLEAN) $(NAME)

re: fclean all

.PHONY: clean fclean re
