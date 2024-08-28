#ifndef MINISHELL_FT_H
# define MINISHELL_FT_H


# define UNCLOSED NULL

//# define UNCLOSED_Q 1
# define CLOSED_Q 0
# define NO_QUOTES 0

#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>

typedef struct env_var_s
{
	char	*key;
	char	*value;
}	t_env_var;

void	error_exit(char *str, bool is_perror);
int		ft_isalpha(char c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
void	*ft_calloc(size_t n, size_t size);
size_t	ft_strlen(char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(char *s, int c);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
char	*ft_strfjoin(char *s1, char *s2);
int		ft_isunclosed_q(char *s);
char	*ft_strldup(char *src, ptrdiff_t size);
char	**ft_split(char const *s, char c);
void	free_split(char **str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
int	ft_isquote(char c);
char    *ft_strtok(char *input, char delim);

#endif
