// separator tokens
# define PIPE 1
# define OR 2
# define REDIR_IN 3
# define HERE_DOC 4
# define REDIR_OUT 5
# define REDIR_OUT_APPEND 6
# define DOLLAR 7
# define BOO_NO_EXPANSION 8
# define DOMESTIC_EXPANSION 9
# define WORD 10
# define DIGIT 11
# define CMD 12

// enum Flags {
// 	PIPE,
// 	OR,
// 	..
// }

// Structure to hold tokens
typedef struct s_token
{
	int				type;
	char			*cmd;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;