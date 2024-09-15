/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_execute_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 04:03:10 by codespace         #+#    #+#             */
/*   Updated: 2024/09/16 02:55:29 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ast_len(t_ast *ast)
{
	t_count	count;
	t_ast	*current_node;

	count = (t_count){0, 0, 0, 0};
	current_node = ast->child;
	while (current_node)
	{
		count.strlen++;
		current_node = current_node->next;
	}
	return (count.strlen);
}

char	*add_cmd(t_ast *current_node, char **envp)
{
	static int	i;

	i = 0;
	if (current_node->type == DOLLAR)
		return (execute_dollar_expansion(current_node, envp));
	else if (current_node->type == CMD)
		return (ft_strdup(current_node->cmd));
	else if (current_node->type == WORD)
		return (ft_strdup(current_node->cmd));
}

char	*matching_cmd(char **cmd)
{
	char	*result;
	t_count	count;

	count = (t_count){1, 1, 1, 1};
	if (ft_strcmp(cmd[0], "echo"))
	{
		while (cmd[count.i])
		{
			result = ft_strjoin(result, cmd[count.i]);
			count.i++;
		}
	}
	return (result);
}

char	*executing_cmd(char **cmd, char **envp)
{
	t_execute	execute;
	char		*result;
	char		*command_path;

	command_path = find_command_path(cmd[0], envp);
	if (command_path == NULL)
	{
		// exit_status how?
		if (execute_builtin(cmd[0], cmd, envp))
			return (NULL);
	}
	if (pipe(execute.fd) == -1)
	{
		perror("pipe");
		return (NULL);
	}
	result = handle_fork(&execute, command_path, cmd, envp);
	return (result);
}

char	*execute_dollar_expansion(t_ast *ast, char **envp)
{
	char	**cmd;
	char	*result;
	t_ast	*current_node;
	int		i;

	i = 0;
	current_node = ast->child;
	cmd = ft_calloc(ast_len(ast) + 1, sizeof(char *));
	while (current_node)
	{
		cmd[i++] = add_cmd(current_node, envp);
		current_node = current_node->next;
	}
	if (ast && ast->cmd)
	{
		result = executing_cmd(cmd, envp);
		if (result != NULL)
		{
			free(ast->cmd);
			ast->cmd = ft_strdup(result);
			free(result);
		}
	}
	free_split(cmd);
	return (ast->cmd);
}

/* KYLIE TINKERED WITH 10:55AM 8/14/2024

split execute_dollar_expansion(): added ast_len() and add_cmd()
split handle_fork(): added execute_parent_process()
created fork_utils.c: handle_fork(), parent_prcoes()

*/
/*
char	*execute_dollar_expansion(t_ast *ast, char **envp)
{
	char	**cmd;
	char	*result;
	t_ast	*current_node;
	int		i;
	// t_count	count;

	// count = (t_count){0, 0, 0, 0};
	// current_node = ast->child;
	// while (current_node)
	// {
	// 	count.strlen++;
	// 	current_node = current_node->next;
	// }
	current_node = ast->child;
	cmd = ft_calloc(ast_len(ast) + 1, sizeof(char *));
	// cmd = ft_calloc(count.strlen + 1, sizeof(char *));
	while (current_node)
	{
		cmd[i++] = add_cmd(current_node, envp)
		// if (current_node->type == DOLLAR)
		// 	cmd[i++] = execute_dollar_expansion(current_node, envp);
		// else if (current_node->type == CMD)
		// 	cmd[i++] = ft_strdup(current_node->cmd);
		// else if (current_node->type == WORD)
		// 	cmd[i++] = ft_strdup(current_node->cmd);
		current_node = current_node->next;
	}
	if (ast && ast->cmd)
	{
		result = executing_cmd(cmd, envp);
		if (result != NULL)
		{
			free(ast->cmd);
			ast->cmd = ft_strdup(result);
			free(result);
		}
	}
	free_split(cmd);
	// while (cmd[count.j])
	// 	free(cmd[count.j++]);
	// free(cmd);
	return (ast->cmd);
}*/
/*
char	*handle_fork(t_execute *execute, char *command_path,
		char **cmd, char **envp)
{
	// t_count	count;
	char		*result;
	// size_t	bytes_read;

	// count = (t_count){0, 0, 0, 0};
	execute->pid = fork();
	if (execute->pid == -1)
	{
		perror("fork");
		return (NULL);
	}
	if (execute->pid == 0)
	{
		close(execute->fd[0]);
		dup2(execute->fd[1], 1);
		execve(command_path, cmd, envp);
		exit(0);
	}
	else
		result = execute_parent_process(execute, );
	// {
	// 	close(execute->fd[1]);
	// 	result = ft_calloc(BUFFER_SIZE, sizeof(char));
	// 	bytes_read = read(execute->fd[0], result, BUFFER_SIZE - 1);
	// 	result[bytes_read] = '\0';
	// 	while (count.i < bytes_read)
	// 	{
	// 		if (result[count.i] == '\n')
	// 			result[count.i] = '\t';
	// 		count.i++;
	// 	}
	// 	close(execute->fd[0]);
	// 	waitpid(execute->pid, NULL, 0);
	// }
	free(command_path);
	return (result);
}*/