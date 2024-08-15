/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:06:00 by geibo             #+#    #+#             */
/*   Updated: 2024/05/09 14:31:00 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
