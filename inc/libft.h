/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:02:18 by ctaleb            #+#    #+#             */
/*   Updated: 2021/03/19 16:46:53 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *ptr, int c, size_t size);
void				ft_bzero(void *ptr, size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t size);
void				*ft_memmove(void *dst, const void *src, size_t size);
void				*ft_memchr(const void *ptr, int c, size_t size);
int					ft_memcmp(const void *ptr1, const void *ptr2, size_t size);
size_t				ft_strlen(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
int					ft_strncmp(const char *str1, const char *str2, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t dst_size);
size_t				ft_strlcat(char *dst, const char *src, size_t dst_size);
char				*ft_strnstr(const char *hst, const char *ndl, size_t size);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *str);

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void	*content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

int					ft_isgraph(int c);
int					ft_ispunct(int c);
int					ft_isspace(int c);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_ishex(int c);
char				*ft_chrjoin(char const *s1, char const c);
char				*ft_chrrjoin(char const *s1, char const c);
size_t				ft_numlen(const char *str);
int					ft_abs(int nb);
char				*ft_utoa(unsigned int n);
char				*ft_utoa_base(unsigned long long n, char *base);
char				*ft_ltoa(long long n);
char				*ft_lutoa(unsigned long long n);

int					ft_get_next_line(int fd, int b_size, char **line);

void				ft_vec_rot(float *vec_x, float *vec_y, float angle);

#endif
