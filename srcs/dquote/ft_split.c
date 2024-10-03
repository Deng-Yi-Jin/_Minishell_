/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:51:39 by sinlee            #+#    #+#             */
/*   Updated: 2024/10/03 18:01:48 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_no_words(const char *str, const char *delim)
{
	int	word_count;
	int	i;

	word_count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(delim, str[i]) != NULL)
			i++;
		if (str[i] != '\0')
			word_count++;
		while (str[i] && ft_strchr(delim, str[i]) == NULL)
			i++;
	}
	return (word_count);
}

static int	count_word_len(const char *str, const char *delim)
{
	int	len;

	len = 0;
	while (str[len] && ft_strchr(delim, str[len]) == NULL)
		len++;
	return (len);
}

static void	insert_chars(char **split_str, const char *str, const char *delim)
{
	int		word_len;
	char	*new_word;
	int		i;

	word_len = count_word_len(str, delim);
	new_word = malloc(sizeof(char) * (word_len + 1));
	i = 0;
	while (i < word_len)
	{
		new_word[i] = str[i];
		i++;
	}
	new_word[i] = '\0';
	split_str[0] = new_word;
}

static void	insert_word(char **split_str, const char *str, const char *delim)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(delim, str[i]) != NULL)
			i++;
		if (str[i] != '\0')
		{
			insert_chars(split_str + j, str + i, delim);
			j++;
		}
		while (str[i] && ft_strchr(delim, str[i]) == NULL)
			i++;
	}
	if (j == 0)
		split_str[j++] = (char *)str;
	split_str[j] = NULL;
}

char	**ft_split(const char *str, const char *delim)
{
	int		word_count;
	char	**split_str;

	if (!str || !delim)
		return (NULL);
	word_count = count_no_words(str, delim);
	split_str = malloc(sizeof(char *) * (word_count + 1));
	if (!split_str)
		return (NULL);
	insert_word(split_str, str, delim);
	return (split_str);
}
