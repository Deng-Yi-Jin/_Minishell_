/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:09:07 by kytan             #+#    #+#             */
/*   Updated: 2024/09/26 23:23:15 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sstrlen(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		len++;
		i++;
	}
	return (len);
}

bool	is_flag(char *str)
{
	if (str[0] == '-' && str[1] != '\0')
		return (true);
	return (false);
}

int	set_type(char *cmd, char **envp)
{
	char	*path;

	path = find_command_path(cmd, g_main->envp);
	if (ft_strcmp(cmd, "<<") == 0)
		return (HERE_DOC);
	else if (ft_strcmp(cmd, ">>") == 0)
		return (REDIR_OUT_APPEND);
	else if (ft_strcmp(cmd, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(cmd, "<") == 0)
		return (REDIR_IN);
	else if (path)
	{
		free(path);
		return (CMD);
	}
	else if (is_flag(cmd))
		return (FLAGS);
	return (WORD);
}

void	set_exec_type(t_exec *exec, char **envp)
{
	t_exec	*temp;
	int		i;

	temp = exec;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i])
		{
			temp->type[i] = set_type(temp->cmd[i], envp);
			i++;
		}
		temp = temp->next;
	}
}

void	handle_not_heredoc(char *tmp1, t_exec *temp, int *i)
{
	tmp1 = ft_strdup(temp->cmd[*i]);
	free(temp->cmd[*i]);
	temp->cmd[*i] = ft_strdup(tmp1);
	free(tmp1);
	(*i)++;
}
