/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 13:56:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/11 23:02:11 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdarg.h>
# define TYPES    "cspPfFdDiIoOuUXxbvr%"
# define LENGTH   "lhLzj"
# define HASH    (1 << 0)
# define ZERO    (1 << 1)
# define SUB     (1 << 2)
# define L_      (1 << 1) + 1
# define LL_     (1 << 1)
# define H_      (1 << 2) + 1
# define HH_     (1 << 2)
# define LU_     (1 << 3) + 1
# define Z_      (1 << 4) + 1
# define J_      (1 << 5) + 1
# define MAX OPEN_MAX
# define BUFF_SIZE 32
# define FD_MAX OPEN_MAX

typedef struct	s_gnl
{
	int			i;
	int			i_read;
	char		buff[BUFF_SIZE + 1];
	char		*ptr_leak;
	char		*s[MAX];
}				t_gnl;
int				get_next_line(int fd, char **line, char separator);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle,
		size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_is_space(int c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(intmax_t n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
int				ft_min(int n, int b);
int				ft_max(int n, int b);
void			ft_putchar_fd(char c, int fd);
void			ft_nputchar(char c, int n);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
char			*ft_itoa_base(intmax_t nb, int base, int uppercase);
char			*ft_ftoa(long double d, int precision);
char			*ft_utoa_base(uintmax_t nb,
				unsigned base, int uppercase);
int				ft_count_char(char c, char *str);
int				ft_count_words(char const *s, char c);
double			interpolate(double start, double end, double interpolat);
int				ft_counti(char *string, char c, int i);
typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstadd(t_list **alst, t_list *new);
int				ft_lstpushback(t_list **begin, t_list *new);
void			ft_lstrev(t_list **alst);
int				ft_lstdestroy(t_list **lst);
int				ft_repeat_char(int fd, char c, int n);
typedef struct	s_fmt
{
	int				prec;
	int				length;
	int				type;
	int				field;
	int				opt;
	int				signe;
	int				prefixe;
}				t_fmt;
typedef struct	s_ype
{
	int				type;
	int				(*function)(int fd, va_list list, t_fmt *fmt);
}				t_ype;
int				handle_char(int fd, va_list list, t_fmt *fmt);
int				handle_string(int fd, va_list list, t_fmt *fmt);
int				handle_array(int fd, va_list list, t_fmt *fmt);
int				print_numbers(int fd, t_fmt *fmt, char *str, int len);
int				handle_number(int fd, va_list ap, t_fmt *fmt);
t_fmt			*get_options(char *s, va_list ap);
char			*get_s(t_fmt *fmt, va_list ap);
int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
intmax_t		ft_abs(intmax_t nb);
int				ft_get_color(int color1, int color2, double percentage);
double			ft_percent(int start, int end, int curr);
int				ft_split_count(char **split);
void			ft_splitdel(char **split);
char			*ft_strcjoin(char const *s1, char const *s2, char c);
char			**ft_strsplitstr(char const *s, char *needle);
int				ft_count_words_str(char const *s, char *needle);
int				ft_lastindexof(char *string, char c);
size_t			ft_levenshtein_n(char *a, size_t length, char *b, size_t blen);
size_t			ft_levenshtein(char *a, char *b);
int				ft_indexof(char *string, char separator);
char			*ft_substr(char *src, int m, int n);
char			*ft_strreplace(char *orig, char *rep, char *with);
char			**ft_strsplitwhitespace(char *orig);
#endif
