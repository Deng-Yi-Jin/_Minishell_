#include "minishell.h"

t_env_var       *find_env_vars(char *key)
{
	t_env_var       *env_token;

	env_token = malloc(sizeof(t_env_var));
	env_token->key = "SHELL";
	env_token->value = "/bin/bash";
	if (ft_strcmp(key, env_token->key))
		return (0);
	return (env_token);
}

size_t  ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t i;

	i = 0;
	while (*src && i + 1 < size)
	{
		*dst++ = *src++;
		i++;
	}
	if (i < size)
		*dst = '\0';
	return (i);
}

char    *prompt_unfinished_q(char *input, char q)
{
	char    *buffer;

	if (!q || !input) // not necessary but just checking
		return (input);
	buffer = calloc(1, sizeof(char));
	while (ft_strchr(buffer, q) == UNCLOSED)
	{
		free(buffer);
		buffer = readline(" > ");
		if (!input)
			break ;
		input = ft_strfjoin(input, "\n");
		input = ft_strfjoin(input, buffer);
	}
	free(buffer);
	return (input);
}

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

char    *extract_env(char *env_s)
{
	char    *start;
	char    *extract;

	if (!env_s || !env_s[0])
		return (0);
	if (*env_s == '$')
		env_s++;
	start = env_s;
	while (*env_s && ft_isalnum(*env_s))
		env_s++;
	extract = ft_strldup(start, (env_s - start) + 1);
	return (extract);
}

void    cp_to_expanded(char *dst, char *src, size_t size)
{
	char    *env;
	size_t  env_len;
	size_t  copied;
	t_env_var	*env_token;
	// char	q;

	env_len = size;
	// q = ft_quote(src);
	while (*src)
	{
		if (*src == '$')
		{
			env = extract_env(++src);
			env_token = find_env_vars(env);
			env_len = ft_strlen(env_token->value);
			copied = ft_strlcpy(dst, env_token->value, env_len + 1);
			printf("dst = [%s]\n", dst);
			src += ft_strlen(env);
			dst += copied;
			free(env);
			free(env_token);
		}
		if (*src != '\"' && *src != '\'')
			*dst++ = *src++;
		else
			src++;
	}
	*dst = '\0';
}

/*****************************************************/

/*
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
void    parse_input(char *input, char **envp)
{
	if (ft_isunclosed_q(input))
		input = prompt_unfinished_q(input, ft_isunclosed_q(input));

	input = format_input(ft_split(input, ' '));
	printf("output = [%s]\n", input);

	if (strcmp(input, "exit") == 0)
	{
		free(input);
		exit(0);
	}
	(void)envp;
}

*/
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

	char *print_dst = dst;
	env_len = 0;
	while (*src)
	{
		if (*src == '$' && q != '\'') // if $SHELL or "$SHELL"
		{
			env = extract_env(++src);
			q = ft_quote(src + 1);
			env_token = find_env_vars(env);
			env_len = ft_strlen(env_token->value);
			copied = ft_strlcpy(dst, env_token->value, env_len + 1);
			printf("dst after copied to = [%s]\nprint_dst = [%s]\n", dst, print_dst);
			src += ft_strlen(env);
			printf("src = [%s]\n", src + 1);
			printf("q = ft_quote(%s) = %c\n", src, q);
			dst += copied;
			printf("dst after added copied len = [%s]\nprint_dst = [%s]\n", dst, print_dst);
			free(env);
		}
		if (*src != q)
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
	printf("print_dst = [%s]\n", print_dst);
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

char	*env_expansion(char **split)
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
	free_split(split);
	return (output);
}

/*****************************************************/


int main(int argc, char **argv)
{
	if (argc != 1 && !argv[0])
		return (1);
	while (1)
	{
		char *input = readline("prompt > ");
		if (!input)
			break ;
//		parse_input(input, envp);
				char *output = env_expansion(ft_split(input, ' '));
				printf("output = [%s]\n", output);
			if (strcmp(output, "exit") == 0)
			{
			free(input);
			exit(0);
			}
	}
	return (0);
}

