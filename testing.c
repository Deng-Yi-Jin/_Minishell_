#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum {
    TOKEN_IO,
    TOKEN_IO_NUMBER,
    TOKEN_APPEND,
    TOKEN_IOR,
    TOKEN_PIPE,
    TOKEN_AMPERSAND,
    TOKEN_OPTION,
    TOKEN_OPTION2,
    TOKEN_WORD,
    TOKEN_UNKNOWN,
} TokenType;

typedef struct {
    TokenType type;
    char value[100]; // Store the token value
} Token;

bool is_allowed_char(char c) {
    return isalnum(c) || c == '%' || c == '=' || c == '+' || c == '\'' || c == '\"' ||
           c == '(' || c == ')' || c == '$' || c == '/' || c == '_' || c == '-' ||
           c == '.' || c == '?' || c == '*' || c == '~';
}

void tokenize_input(const char *input, Token *tokens, int *num_tokens) {
    int input_length = strlen(input);
    int token_start = 0;
    int token_end = 0;
    *num_tokens = 0;

    while (token_end < input_length) {
        while (token_end < input_length && isspace(input[token_end])) {
            token_end++;
        }
        token_start = token_end;

        if (input[token_start] == '\'' || input[token_start] == '\"') {
            char quote = input[token_start++];
            token_end = token_start;
            while (token_end < input_length && input[token_end] != quote) { // ' or "
                token_end++;
            }
        } else {
            while (token_end < input_length && !isspace(input[token_end])) {
                token_end++;
            }
        }

        if (token_start < token_end) {
            Token token;
            strncpy(token.value, input + token_start, token_end - token_start);
            token.value[token_end - token_start] = '\0';

            if (strcmp(token.value, "#") == 0) {
                token.type = TOKEN_IO;
            } else if (strcmp(token.value, ">") == 0) {
                token.type = TOKEN_IO;
            } else if (strcmp(token.value, ">>") == 0) {
                token.type = TOKEN_APPEND;
            } else if (strcmp(token.value, ">&") == 0) {
                token.type = TOKEN_IOR;
            } else if (strcmp(token.value, "|") == 0) {
                token.type = TOKEN_PIPE;
            } else if (strcmp(token.value, "&") == 0) {
                token.type = TOKEN_AMPERSAND;
            } else if (token.value[0] == '-') {
                token.type = TOKEN_OPTION;
            } else if (strstr(token.value, "--") == token.value) {
                token.type = TOKEN_OPTION2;
            } else if (token.value[0] == '#' || (token.value[0] == '>' && isdigit(token.value[1]))) {
                token.type = TOKEN_IO_NUMBER;
            } else if (is_allowed_char(token.value[0])) {
                bool is_word = true;
                for (int i = 1; token.value[i]; i++) {
                    if (!is_allowed_char(token.value[i])) {
                        is_word = false;
                        break;
                    }
                }
                if (is_word) {
                    token.type = TOKEN_WORD;
                } else {
                    token.type = TOKEN_UNKNOWN;
                }
            } else {
                token.type = TOKEN_UNKNOWN;
            }

            tokens[*num_tokens] = token;
            (*num_tokens)++;
        }
    }
}

void print_tokens(const Token *tokens, int num_tokens) {
    for (int i = 0; i < num_tokens; i++) {
        printf("Token type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
    }
}

int main() {
    char input[100];
    while (1)
    {
        printf("minishell$ ");
        fgets(input, sizeof(input), stdin);

        Token tokens[100];
        int num_tokens = 0;

        tokenize_input(input, tokens, &num_tokens);
        print_tokens(tokens, num_tokens);
    }
    return 0;
}
