/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:06:00 by geibo             #+#    #+#             */
/*   Updated: 2024/03/05 15:34:40 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    expand_dollar(t_token **tokens)
{
    t_token    *current_node;
    char    *env_value;
    char    *tmp;

    current_node = *tokens;
    while (current_node)
    {
        if (current_node->type == DOLLAR)
        {
            tmp = ft_strtrim(current_node->cmd, "$");
            if (tmp[0] == '(')
            {
                free(tmp);
                return ;
            }
            if (find_env_vars(tmp) != NULL)
                env_value = find_env_vars(tmp)->value;
            else
                env_value = "";
            free(tmp);
            free(current_node->cmd);
            current_node->cmd = ft_strdup(env_value);    
        }
        current_node = current_node->next;
    }
}
