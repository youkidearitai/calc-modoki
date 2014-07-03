#include <stdio.h>

void calcinput() {
    char buff[128] = {'\0'};
    int c, i;
    i = 0;

    while ((c = getchar()) != EOF) {
        buff[i++] = c;
        if (c == '\n') {
            break;
        }
    }

    yyinputinit(&buff);
    yyparse();
}

int main() {
    while(1) {
        calcinput();
    }
    return 0;
}

