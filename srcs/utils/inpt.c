/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inpt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinlee <sinlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:51 by codespace         #+#    #+#             */
/*   Updated: 2023/08/16 18:58:18 by sinlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void parse_input(char *input, char **envp) // input -> "ls -l | wc -l"
{
    if (input[0] != '\0')
    {
        // Tokenize input to get command and arguments
        char *args[N_ARGS]; // Adjust the array size as needed
        int argc = 0;
        char *token = strtok(input, " ");
        while (token != NULL)
        {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        // Find the full path of the command
        char *command_path = find_command_path(args[0], envp);
        if (command_path == NULL)
        {
            if (match_cmd(args[0], args, envp) == false)
                printf("Command not found: %s\n", args[0]);
        }
        else
        {
            pid_t child_pid = fork();
            if (child_pid == -1)
            {
                perror("fork");
            }
            else if (child_pid == 0)
            {
                // Child process: Execute the command using execve
                execve(command_path, args, envp);
                perror("execve"); // execve only returns if an error occurs
                exit(EXIT_FAILURE);
            }
            else
            {
                // Parent process: Wait for the child to complete
                int status;
                waitpid(child_pid, &status, 0);
            }
            free(command_path);
        }
    }
}