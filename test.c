#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "unistd.h"
// #include "minishell.h"

bool execute_pwd()
{
	char *path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		printf("WOI CB");
		return (false);
	}
	printf("%s\n", path);
	free(path);
	return (true);
}

int main (int argc, char **argv, char **envp) {
//    printf("PATH : %s\n", getenv("PATH"));
//    printf("HOME : %s\n", getenv("HOME"));
    // char **value;

    // value = getenv("ROOT");
    // envp[0] = "ROOT=/home/runner";
    // printf("ROOT : %s\n", getenv("ROOT"));
	execute_pwd();

   return(0);
}
