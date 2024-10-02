/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:42:02 by kytan             #+#    #+#             */
/*   Updated: 2024/10/01 11:54:48 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t   count_words(char const *s, char c)
{
	size_t  words;

	words = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == 0))
			words++;
		s++;
	}
	return (words);
}

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

char	*add_unquoted_string(char *p, char **word_element)
{
	char	*start;

	start = p;
	while (*p != '\'' && *p)
		p++;
	*word_element = ft_strldup(start, (p - start) + 1);
	return (p);
}

char	*add_quoted_string(char *p, char **word_element)
{
	char	*start;

	start = p;
	if (*p == '\'')
		p++;
	while (*p != '\'' && *p)
		p++;
	if (*p == '\'')
		p++;
	*word_element = ft_strldup(start, (p - start) + 1);
	return (p);
}


void	print_string_array(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		printf("split[%i] = [%s]\n", i, split[i]);
}

char	**ft_splitq(char const *s, char c)
{
	char		**word_list;
	size_t	words;
	char		*p;
	int			i;

	if (!s)
		return (0);
	i = 0;
	p = (char *)s;
	words = count_words(s, c);
	word_list = ft_calloc((words + 1), sizeof(char *));
	if (!word_list)
		return (0);
	while (*p)
	{
		if (*p == '\'')
			p = add_quoted_string(p, word_list + i++);
		else
			p = add_unquoted_string(p, word_list + i++);
	}
	word_list[words] = 0;
	return (word_list);
}
