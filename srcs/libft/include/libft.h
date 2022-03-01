/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 20:02:11 by llescure          #+#    #+#             */
/*   Updated: 2022/03/01 15:32:11 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_double_list
{
	void					*content;
	struct s_double_list	*next;
	struct s_double_list	*previous;
}				t_double_list;

/*
 ** Strings
*/

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			**ft_split_multiple_cara(char const *s, char c1, char c2);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strchr(const char *str, int c);
char			*ft_strdup(const char *s1);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dest, const char *src, size_t destsize);
int				ft_strlcpy_without_cara(char *dest, char *src, char cara);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char			*ft_strrchr(const char *str, int c);
int				find_cara_in_word(char *str, char c);
int				number_occurence_cara_in_str(char *str, char c);
char			*ft_join_tab(char **tab);
unsigned long	ft_count_words(char const *str, char sep);
unsigned long	ft_count_words_multiple(char const *str, char sep1, char sep2);
void			ft_free(char **s, unsigned long pos);

/*
 ** Display
*/

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/*
 ** Memory
*/

void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
const void		*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);

/*
 ** Types
*/

int				ft_isprint(int c);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isspace(int c);
int				ft_iscara(char c, char target);
int				ft_isredirections(char c);
int				is_number(char *str);
int				ft_is_only_space(char *str);

/*
 ** Convert
*/

int				ft_atoi(const char *str);
char			*ft_itoa(int n);
int				ft_tolower(int c);
int				ft_toupper(int c);

/*
 ** Linked_lists
*/

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
void			ft_print_list(t_list *lst);
void			ft_free_list(t_list **lst);

/*
 ** Double_linked_lists
*/

t_double_list	*ft_double_lstnew(void *content);
void			ft_double_lstadd_front(t_double_list **alst,
					t_double_list *new);
void			ft_double_lstadd_back(t_double_list **alst, t_double_list *new);
void			ft_double_lstdelone(t_double_list **lst, int pos);
void			delete_node(t_double_list **lst, int free_content);
void			case_middle_node(t_double_list **lst);
void			case_first_node(t_double_list **lst);
void			case_last_node(t_double_list **lst);
void			ft_double_lstclear(t_double_list **lst, t_double_list *del);
t_double_list	*ft_double_lstfirst(t_double_list *lst);
t_double_list	*ft_double_lstlast(t_double_list *lst);
int				ft_double_lstsize(t_double_list *lst);
void			ft_double_print_list(t_double_list *lst);
void			ft_double_free_list(t_double_list **lst, int free_content);

/*
 ** Get_next_line
*/

int				get_next_line(int fd, char **line);
int				return_value(int char_read, char **temp);
int				error_case(int fd, char **line, char **temp, char **buf);
char			*copy_to_join(char *temp, char *buf);
char			*copy_to_get_temp(char *temp);
char			*ft_trim(char *str, int c);
char			*get_temp(char *str, int c);

#endif
