/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:56:37 by Acancel           #+#    #+#             */
/*   Updated: 2024/07/18 03:38:28 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <string.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

char	**ft_split(char const *s, char c);
int		ft_iswspace(char c);
int		ft_isoperator(char c);
int		ft_isquote(char c);
char	*ft_itoa(int n);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_chardup(const char c);
char	*ft_strjoin(char *s1, char *s2, int flag);
char	*ft_charjoin(char *s1, char const s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *str, int c);
int		ft_strchr_b(char *str, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_lstsize(t_list *lst);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *str, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_putchar_fd(char c, int fd);
int		ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_is_charset(char s1, char const *set);

/*GNL*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
size_t	ft_is_strchr(const char *str, char c);
size_t	ft_strlen_or_len_to_nl(char *s);

/*ft_printf & ft_dprintf */

# define HU "0123456789ABCDEF"
# define HL "0123456789abcdef"
# define D 	"0123456789"

int		ft_print_add(unsigned long nbr, char *base, int maj, int *pl);
int		ft_print_char(char c);
int		ft_print_str(char *s);
int		ft_printf(const char *str, ...);
int		ft_putnbr_base_uns(unsigned int nbr, char *base, int *pl);
int		ft_putnbr_base(long nbr, char *base, int *pl);
size_t	ft_strlen_ft_printf(const char *str);
int		ft_cset(char s1, char const *set);
int		ft_dprint_add(unsigned long nbr, char *base, int maj, int *pl);
int		ft_dprint_char(char c);
int		ft_dprint_str(char *s);
int		ft_dprintf(const char *str, ...);
int		ft_dputnbr_base_uns(unsigned int nbr, char *base, int *pl);
int		ft_dputnbr_base(long nbr, char *base, int *pl);

#endif
