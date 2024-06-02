SRCS = \
	$(addprefix $(CHAR_STR_DIR), $(SRCS_CHAR_STR)) \
	$(addprefix $(MEM_DIR), $(SRCS_MEM)) \
	$(addprefix $(FD_DIR), $(SRCS_FD)) \
	$(addprefix $(INT_DIR), $(SRCS_INT)) \
	$(addprefix $(GNL_DIR), $(SRCS_GNL)) \
	$(addprefix $(FT_PRINTF_DIR), $(SRCS_FT_PRINTF)) \
	$(addprefix $(FT_DPRINTF_DIR), $(SRCS_FT_DPRINTF)) \
	$(addprefix $(LST_DIR), $(SRCS_LST))

CHAR_STR_DIR = char_str/
SRCS_CHAR_STR = \
		ft_iswspace.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_is_charset.c

MEM_DIR = mem/
SRCS_MEM = \
		ft_bzero.c \
		ft_calloc.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c

FD_DIR = fd/
SRCS_FD = \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c

INT_DIR = int/
SRCS_INT = \
		ft_atoi.c \
		ft_itoa.c

GNL_DIR = gnl/
SRCS_GNL = \
		get_next_line.c \
		get_next_line_utils.c

FT_PRINTF_DIR = ft_printf/
SRCS_FT_PRINTF = \
		ft_print_char.c \
		ft_print_nbrs.c \
		ft_printf.c

FT_DPRINTF_DIR = ft_dprintf/
SRCS_FT_DPRINTF = \
		ft_dprint_char.c \
		ft_dprint_nbrs.c \
		ft_dprintf.c


LST_DIR = lst/
SRCS_LST = \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c
