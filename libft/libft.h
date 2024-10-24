/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:20:14 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/24 13:01:49 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include "ft_printf/libftprintf.h"
# include "ft_fprintf/libftfprintf.h"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define WARLOCK "\033[38;5;19m"
# define MAGENTA "\033[35m"
# define PURPLE "\033[35m"
# define CYAN "\033[36m"
# define GREY "\033[90m"
# define RESET "\033[0m"

# define BUFFER_SIZE 1024
# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

char				*ft_strchr(const char *str, int c);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *src, size_t n);
char				*ft_strnstr(const char *hs, const char *nd, size_t len);
char				*ft_strrchr(const char *str, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_itoa(int n);
char				**ft_split(char const *s, char c);
char				*ft_strtok(char *str, char *delim);

int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

int					ft_atoi(const char *str);
long int			ft_atol(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);

void				ft_bzero(void *str, size_t len);
void				*ft_memchr(const void *str, int c, unsigned int len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_realloc(void *ptr, size_t size, size_t new_size);
void				*ft_memset(void *byte, int c, size_t len);

void				*ft_calloc(size_t count, size_t size);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_bool				ft_str_isdigit(char *str);

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
char				*get_next_line(int fd);
#endif
