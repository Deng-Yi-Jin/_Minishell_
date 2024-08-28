#include "minishell.h"

void	error_exit(char *str, bool is_perror)
{
	if (is_perror)
		printf("%s", str);
	else
		printf("%s", str);
	exit(errno);
}

int	ft_isalpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;
	void	*ptr_cpy;
	int		haha;

	if (!n || !size)
		return (malloc(0));
	if (n > UINT_MAX / size)
		return (0);
	ptr = malloc(n * size);
	haha = n * size;
	ptr_cpy = ptr;
	if (ptr)
	{
		while (haha--)
			*((unsigned char *)ptr_cpy++) = 0;
	}
	return (ptr);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}

char	*ft_strrchr(char *s, int c)
{
	char	*ptr;

	ptr = 0;
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (*s)
	{
		if (*s == (char)c)
			ptr = (char *)s;
		s++;
	}
	return (ptr);
}

char	*ft_strfjoin(char *s1, char *s2)
{
	size_t	s1_len = ft_strlen(s1);
	size_t	s2_len = ft_strlen(s2);
	size_t	join_size = s1_len + s2_len + 1;
	char	*join = malloc(join_size);

	ft_strlcpy(join, s1, s1_len + 1);
	ft_strlcpy(join + s1_len, s2, join_size - s1_len);
	free(s1);
	return (join);
}

int	ft_isunclosed_q(char *s)
{
	int	 q;

	q = 0;
	while (*s)
	{
		if (*s == '\"' || *s == '\'')
			q = *s;
		else if (*s == q)
			q ^= 1;
		s++;
	}
	return (NO_QUOTES);
}
/*
int	ft_isunclosed_q(char *s)
{
	int	q;

	q = 0;
	while (*s)
	{
		if (*s == '\"' || *s == '\'')
			q = *s;
		else if (*s == q)
			q ^= 1;
		s++;
	}
	return (NO_QUOTES);
}
*/
char	*ft_strldup(char *src, ptrdiff_t size)
{
	char	*dup;
	int		i;

	i = 0;
	if (size <= 0 || !src)
		return (0);
	dup = malloc(size * sizeof(char));
	if (!dup)
		return (0);
	while (*src && i + 1 < size)
		dup[i++] = *src++;
	if (i < size)
		dup[i] = '\0';
	return (dup);
}

static size_t	count_words(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == 0))
			words++;
		s++;
	}
	return (words);
}

static char	*new_word(char *s, char c)
{
	char	*word;
	int		chrs;
	int		i;

	i = -1;
	chrs = 0;
	while (s[chrs] != c && s[chrs])
		chrs++;
	word = malloc(chrs + 1);
	if (!word)
		return (0);
	while (++i < chrs)
		word[i] = s[i];
	word[chrs] = 0;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char		**word_list;
	size_t		words;
	char		*p;
	int			i;

	if (!s)
		return (0);
	i = 0;
	p = (char *)s;
	words = count_words(s, c);
	word_list = malloc((words + 1) * sizeof(char *));
	if (!word_list)
		return (0);
	while (p)
	{
		while (*p == c && c)
			p++;
		if (!*p)
			break ;
		word_list[i++] = new_word(p, c);
		p = ft_strchr(p, c);
	}
	word_list[words] = 0;
	return (word_list);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;

	if (start > ft_strlen(s))
	{
		substr = malloc(sizeof(char) * 1);
		substr[0] = '\0';
	}
	else
	{
		if (len > ft_strlen(s + start))
			len = ft_strlen(s + start);
		substr = malloc(sizeof(char) * (len + 1));
		if (substr == 0)
			return (NULL);
		else
			ft_strlcpy(substr, s + start, len + 1);
	}
	return (substr);
}

int	ft_isquote(char c)
{
	return (c == '\"' || c == '\'');
}

char	*ft_strtok(char *input, char delim)
{
	int			i;
	static char	*last;
	char		*token;

	i = 0;
	if (input != NULL)
		last = input;
	while (*last == delim)
		last++;
	if (*last == '\0')
		return (0);
	while (last[i] != delim && last[i])
		i++;
	token = malloc(i + 1);
	i = 0;
	while (*last != delim && *last)
		token[i++] = *last++;
	token[i] = '\0';
	return (token);
}
