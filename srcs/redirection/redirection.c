/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:17:49 by geibo             #+#    #+#             */
/*   Updated: 2024/05/23 13:14:43 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir(char *cmd)
{
	return (ft_strcmp(cmd, ">") == 0
		|| ft_strcmp(cmd, "<<") == 0
		|| ft_strcmp(cmd, "<") == 0);
}

bool	open_outfile(t_exec *exec, char *file)
{
	exec->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (exec->outfile < 0)
	{
		printf("bash: %s: No such file or directory\n", file);
		return (false);
	}
	return (true);
}

bool	open_infile(t_exec *exec, char *file)
{
	exec->infile = open(file, O_RDONLY);
	if (exec->infile < 0)
	{
		printf("bash: %s: No such file or directory\n", file);
		return (false);
	}
	dup2(exec->infile, STDIN_FILENO);
	return (true);
}

bool	redirect(char *file, char *cmd, t_exec *exec)
{
	t_exec	*temp;

	temp = exec;
	if (ft_strcmp(cmd, "<") == 0)
	{
		if (!open_infile(exec, file))
			return (false);
	}
	if (ft_strcmp(cmd, ">") == 0)
	{
		if (!open_outfile(exec, file))
			return (false);
	}
	return (true);
}
