#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv, char **envp) {
//    printf("PATH : %s\n", getenv("PATH"));
//    printf("HOME : %s\n", getenv("HOME"));
    // char **value;

    // value = getenv("ROOT");
    envp[0] = "ROOT=/home/runner";
    printf("ROOT : %s\n", getenv("ROOT"));

   return(0);
}
