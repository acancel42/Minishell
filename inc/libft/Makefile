NAME = libft.a 

include srcs.mk

CC = cc

CFLAGS = -Wall -Werror -Wextra

OBJS = $(SRCS:%.c=.objects/%.o)

CLEAN = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "Done"
	@echo "\033[0;32mYour libft is built\033[0m"

$(OBJS): .objects/%.o: %.c libft.h
	@echo -n "\r\033[0;31mWait until built-in libft\033[0m"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I./ -c -o $@ $<

clean:
	$(CLEAN) .objects

fclean: clean
	$(CLEAN) $(NAME)

re: fclean all

.PHONY: clean fclean re
