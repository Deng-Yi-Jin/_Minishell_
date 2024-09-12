/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:06:00 by geibo             #+#    #+#             */
/*   Updated: 2024/09/11 11:19:58 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_expansion_needed(char *s)
{
	return (!ft_strchr(s, '$') && !ft_strchr(s, '\"') && !ft_strchr(s, '\''));
}

char	ft_quote(char *s)
{
	while (*s)
	{
		if (*s == '\"' || *s == '\'')
			return (*s);
		s++;
	}
	return (0);
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

char	*extract_env(char *s)
{
	char	*env_s;
	char	*extract;

	if (!s || !s[0])
		return (0);
	if (*s == '$')
		s++;
	env_s = s;
	while (*s && ft_isalnum(*s))
		s++;
	extract = ft_strldup(env_s, (s - env_s) + 1);
	return (extract);
}

size_t	expanded_len(char *s, char q)
{
	size_t		env_len;
	char		*env;
	t_env_var	*env_token;

	env_len = 0;
	while (*s)
	{
		if (*s == '$' && q != '\"')
		{
			env = extract_env(++s);
			env_token = find_env_vars(env);
			if (!env_token)
				return (0);
			env_len += ft_strlen(env_token->value);
			s += ft_strlen(env);
			q = ft_quote(s);
			free(env);
		}
		else if (*s != q)
			env_len++;
		s++;
	}
	return (env_len);
}

void	cp_to_output(char *dst, char *src, char q)
{
	size_t		env_len;
	size_t		copied;
	char		*env;
	t_env_var	*env_token;

	env_len = 0;
	while (*src)
	{
		if (*src == '$' && q != '\'')
		{
			env = extract_env(++src);
			env_token = find_env_vars(env);
			env_len = ft_strlen(env_token->value);
			copied = ft_strlcpy(dst, env_token->value, env_len + 1);
			src += ft_strlen(env);
			q = ft_quote(src);
			dst += copied;
			free(env);
		}
		if (*src != q)
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
}

char	*dollar_q_expansion(char *s)
{
	size_t	total_size;
	char	*output;

	total_size = expanded_len(s, ft_quote(s)) + 1;
	//printf("total_size = %zu\n", total_size);
	output = ft_calloc(total_size, sizeof(char));
	//error checking for ft_calloc
	cp_to_output(output, s, ft_quote(s));
	return (output);
}

char	*env_expansion(char **split, char q)
{
	char	*output;
	char	*expanded;
	size_t	i;

	i = -1;
	while (split[++i])
	{
		if (no_expansion_needed(split[i]))
			continue ;
		else
		{
			expanded = dollar_q_expansion(split[i]);
			free(split[i]);
			split[i] = expanded;
		}
	}
	i = -1;
	output = ft_calloc(1, sizeof(char));
	while (split[++i])
	{
		output = ft_strfjoin(output, split[i]);
		if (split[i + 1] != NULL)
			output = ft_strfjoin(output, " ");
	}
	return (output);
}

char	*expand_dollar(char *input)
{
	char	*output;
	char	*env_value;
	char	*tmp;
	int		start;
	int		i;
	int		j;

	i = 0;
	j = 0;
	output = (char *)malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!output)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			if (input[i] == '(')
			{
				while (input[i] && input[i] != ')')
					i++;
				i++;
			}
			else
			{
				start = i;
				while (input[i] && ft_isalnum(input[i]))
					i++;
				tmp = ft_substr(input, start, i - start);
				if (find_env_vars(tmp) != NULL)
					env_value = find_env_vars(tmp)->value;
				else
					env_value = "";
				free(tmp);
				ft_strlcpy(output + j, env_value, ft_strlen(env_value) + 1);
				j += ft_strlen(env_value);
			}
		}
		else
			output[j++] = input[i++];
	}
	output[j] = '\0';
	// free(input);
	return (output);
}

// void    expand_dollar(t_token **tokens)
// {
//     t_token    *current_node;
//     char    *env_value;
//     char    *tmp;

//     current_node = *tokens;
//     while (current_node)
//     {
//         if (current_node->type == DOLLAR)
//         {
//             tmp = ft_strtrim(current_node->cmd, "$");
//             if (tmp[0] == '(')
//             {
//                 free(tmp);
//                 return ;
//             }
//             if (find_env_vars(tmp) != NULL)
//                 env_value = find_env_vars(tmp)->value;
//             else
//                 env_value = "";
//             free(tmp);
//             free(current_node->cmd);
//             current_node->cmd = ft_strdup(env_value);
// 			current_node->type = CMD;
//         }
//         current_node = current_node->next;
//     }
// }
