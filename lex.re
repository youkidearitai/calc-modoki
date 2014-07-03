#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "parser.tab.h"

#define YYSTYPE char*
#define YYMARKER yymarker

char *yyin;
char *yymarker;
char *yyold;

void yyinputinit(char *p) {
    yyin = p;
}

void yyfilltext() {
    char *p = yyold;
    char yytext[128] = {'\0'};

    int size = yyin - yyold;
    int i;

    if (size + 1 >= 128) {
        return;
    }

    for (i = 0;i < size; i++) {
        yytext[i] = *p++;
    }

    yylval = atoi(yytext);
}

int yylex() {
start:
    yyold = yyin;

/*!re2c

    re2c:define:YYCTYPE = "char";
    re2c:define:YYCURSOR = yyin;
    re2c:yyfill:enable = 0;
    re2c:indent:top = 0;

    [0-9]+ { yyfilltext(); return TNUM; }
    "+"    { return PLUS; }
    "-"    { return MINUS; }
    "*"    { return MULTI; }
    "/"    { return PROD; }
    "("    { return BRACKET; }
    ")"    { return BRACKET_END; }
    [\n\r]   { return TEND; }

    "\000" { return 0; } /* end of line */
    [ \t]+ { goto start; }

*/
}

int yyerror(const char *s) {
    printf("ERROR %s\n", s);
    return 0;
}
