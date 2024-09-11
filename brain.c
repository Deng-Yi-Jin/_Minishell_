#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct s_exec
{
	char			**cmd;
	struct	s_exec	*next;
	struct	s_exec	*prev;
	pid_t			pid;
	int				*type;
	int				fd[2];
	int				infile;
	int				outfile;
}	t_exec;

typedef struct env_var_s
{
	char	*key;
	char	*value;
}	t_env_var;

typedef struct s_main
{
	int			nuclear_status; // exit status
	char		**envp;
	t_env_var	**env_vars;
}	t_main;

typedef struct s_ast
{
	char			*cmd;
	int				type;
	int				fd[2];
	struct s_ast	*child;
	struct s_ast	*prev;
	struct s_ast	*next;
	struct s_ast	*parent;
}	t_ast;

typedef struct s_execute
{
	int		fd[2];
	pid_t	pid;
}	t_execute;

typedef struct s_token
{
	int				type;
	char			*cmd;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

t_exec	*executing(t_ast **ast, t_exec *exec)
{
	t_exec	*head;
	t_ast	*go_to_history;
	t_ast	*go_to_pipe;
	int		n_cmd;
	int		word;
	bool	is_pipe;

	head = 0;
	is_pipe = true;
	exec = 0;
	(*ast) = (*ast)->child;
	while ((*ast))
	{
		n_cmd = 0;
		word = 0;
		go_to_pipe = (*ast);
		while ((*ast) && (*ast)->child != NULL)
			(*ast) = (*ast)->child;
		go_to_history = (*ast);
		while ((*ast))
		{
			n_cmd++;
			if ((*ast)->next == NULL)
				break ;
			(*ast) = (*ast)->next;
		}
		(*ast) = go_to_history;
		exec = join_exec_nodes(exec, ft_calloc(n_cmd + 1, sizeof(char *)), NULL);
		if (!head)
			head = exec;
		while (*ast)
		{
			exec->cmd[word] = ft_strdup((*ast)->cmd);
			if ((*ast)->next == NULL)
				break ;
			(*ast) = (*ast)->next;
			word++;
		}
		(*ast) = go_to_pipe;
		if ((*ast)->next == NULL)
			break ;
		(*ast) = (*ast)->next;
	}
	return (head);
}


void	start_parse(t_ast **ast, t_token **tokens, char **envp)
{
	while ((*tokens)->cmd != NULL)
	{
		form_ast(ast, tokens, envp);
		if ((*tokens)->type == PIPE)
		{
			(*ast) = (*ast)->parent;
			(*tokens) = (*tokens)->next;
		}
	}
}

void	construct_child_after_pipe(t_ast **ast, char *tmp, bool *is_child)
{
	(*ast)->next = create_ast_node(ft_strdup(tmp), PIPE);
	free(tmp);
	(*ast)->next->parent = (*ast)->parent;
	(*ast)->next->prev = (*ast);
	(*ast) = (*ast)->next;
	*is_child = false;
}

void	construct_child_before_pipe(t_ast **ast, char *tmp, bool *is_child)
{
	(*ast)->child = create_ast_node(ft_strdup(tmp), PIPE);
	free(tmp);
	(*ast)->child->parent = (*ast);
	(*ast) = (*ast)->child;
	*is_child = false;
}

void	eldest_child(t_ast **ast, t_token **tokens,
		bool *create_sibling, char **envp)
{
	if ((*tokens)->cmd == NULL)
		return ;
	(*ast)->child = create_ast_node(rm_quote((*tokens)->cmd), 0);
	(*ast)->child->parent = (*ast);
	(*ast) = (*ast)->child;
	if ((*tokens)->type == DOLLAR)
	{
		(*ast)->type = DOLLAR;
		dollar_deal((*ast), create_sibling, envp);
	}
	else
    (*ast)->type = is_command((*tokens)->cmd, envp);
	if ((*tokens)->next != NULL && (*tokens)->next->type != PIPE)
		*create_sibling = true;
}

void	sibling(t_ast **ast, t_token **tokens,
		bool *create_sibling, char **envp)
{
	if ((*tokens)->cmd == NULL)
		return ;
	(*ast)->next = create_ast_node(rm_quote((*tokens)->cmd), 0);
	(*ast)->next->parent = (*ast)->parent;
	(*ast)->next->prev = (*ast);
	(*ast) = (*ast)->next;
	if ((*tokens)->type == DOLLAR)
	{
		(*ast)->type = DOLLAR;
		dollar_deal((*ast), create_sibling, envp);
	}
	else
		(*ast)->type = is_command((*tokens)->cmd, envp);
}

void	construct_sibling(t_ast **ast, t_token **tokens,
		bool *create_sibling, char **envp)
{
	if (*create_sibling == false)
		eldest_child(ast, tokens, create_sibling, envp);
	else if (*create_sibling == true)
		sibling(ast, tokens, create_sibling, envp);
}

void	form_ast(t_ast **ast, t_token **tokens, char **envp)
{
	char	*tmp;
	bool	is_c;
	bool	create_s;

	is_c = true;
	create_s = false;
	tmp = ft_calloc(1, sizeof(char));
	while ((*tokens)->type != PIPE && (*tokens)->cmd != NULL)
	{
		tmp = ft_strjoin(tmp, (*tokens)->cmd);
		(*tokens) = (*tokens)->next;
	}
	*tokens = lst_go_back(*tokens);
	while ((*tokens)->type != PIPE && (*tokens)->cmd != NULL)
	{
		if (is_c && (*tokens)->prev && (*tokens)->prev->type == PIPE)
			construct_child_after_pipe(ast, tmp, &is_c);
		else if (is_c == true)
			construct_child_before_pipe(ast, tmp, &is_c);
		if ((*tokens)->type != PIPE && (*tokens)->cmd != NULL && is_c == false)
		{
			construct_sibling(ast, tokens, &create_s, envp);
			(*tokens) = (*tokens)->next;
		}
	}
}

t_ast	*create_parent_node(char *cmd)
{
	t_ast	*new_node;

	new_node = calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->child = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->parent = NULL;
	return (new_node);
}

t_token	*lst_first_last(t_token *tokens, bool is_last)
{
	if (is_last == true)
	{
		while (tokens -> next != NULL && tokens != NULL)
			tokens = tokens -> next;
		return (tokens);
	}
	while (tokens -> prev != NULL && tokens != NULL)
		tokens = tokens -> prev;
	return (tokens);
}


void	parse(t_token **tokens, char **envp)
{
	t_ast	**ast;
	t_ast	*minishell;
	t_exec	*exec;

	(*tokens) = lst_first_last(*tokens, false);
	ast = (t_ast **)malloc(sizeof(t_ast *));
	*ast = NULL;
	(*ast) = create_parent_node(NULL);
	minishell = (*ast);
	start_parse(ast, tokens, envp);
	while ((*ast)->parent != NULL)
		(*ast) = (*ast)->parent;
	(*ast) = minishell;
	minishell = (*ast);
	exec = executing(ast, exec);
	exec = renamed_here_doc(exec, envp);
	execute(exec, envp);
	free_exec(exec);
	(*ast) = minishell;
	traverse(ast, free, 0, false);
	free(ast);
}
