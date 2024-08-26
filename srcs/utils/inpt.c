/* ************************************************************************** */
/*							*/
/*						:::	  ::::::::   */
/*   inpt.c							 :+:	  :+:	:+:   */
/*					+:+ +:+		 +:+	 */
/*   By: codespace <codespace@student.42.fr>		+#+  +:+	   +#+		*/
/*				+#+#+#+#+#+   +#+		   */
/*   Created: 2023/08/14 13:55:51 by codespace		 #+#	#+#			 */
/*   Updated: 2024/01/25 08:39:25 by codespace		###   ########.fr	   */
/*							*/
/* ************************************************************************** */

#include "minishell.h"

// input -> "ls -l | wc -l"
// Tokenize input to get command and arguments
// Adjust the array size as needed
		// Find the full path of the command
void	parse_input(char *input, char **envp)
{
	char	*args[N_ARGS];
	int		argc;
	char	*token;
	char	*command_path;
	pid_t	child_pid;
	int		status;

	if (input != NULL)
	{
		// char *args[N_ARGS];
		// int argc = 0;
		argc = 0;
		token = strtok(input, " ");
		while (token != NULL)
		{
			args[argc++] = token;
			token = strtok(NULL, " ");
		}
		args[argc] = NULL;
		command_path = find_command_path(args[0], envp);
		if (command_path == NULL)
		{
			if (exeute_builtin(args[0], args, envp) == false)
				printf("Command not found: %s\n", args[0]);
		}
		else
		{
			child_pid = fork();
			if (child_pid == -1)
				perror("fork");
			else if (child_pid == 0)
			{
				execve(command_path, args, envp);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else
				waitpid(child_pid, &status, 0);
			free(command_path);
		}
	}
}
// 49 // Child process: Execute the command using execve
// 50 / execve only returns if an error occurs
// 55 // Parent process: Wait for the child to complete