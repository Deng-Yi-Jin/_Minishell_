// separator tokens
# define PIPE 1
# define OR 2
# define REDIR_IN 3
# define HERE_DOC 4
# define REDIR_OUT 5
# define REDIR_OUT_APPEND 6
# define OPEN_BRACKET 7
# define CLOSE_BRACKET 8
# define OPEN_BRACE 9
# define CLOSE_BRACE 10
# define ANDPARSEN 11
# define DOUBLE_AND 12
# define DOLLAR 13
# define BOO_NO_EXPANSION 14
# define DOMESTIC_EXPANSION 15
# define EXCLAMATION 16
# define AT 17
# define HASH 18
# define PERCENT 19
# define CIRCUMFLEX 20
# define ASTERISK 21
# define MINUS 22
# define UNDERSCORE 23
# define EQUAL 24
# define PLUS 25
# define COLON 26
# define QUESTION 27
# define DOT 28
# define COMMA 29
# define SLASH 30
# define OPEN_SQUARE_BRACKET 31
# define CLOSE_SQUARE_BRACKET 32
# define WORD 33
# define DIGIT 34

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