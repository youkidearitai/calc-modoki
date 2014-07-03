#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "parser.tab.h"

#define YYSTYPE char*
#define YYMARKER yymarker

char* yyin;
char* yymarker;
char yytext[128];
int yytextcnt;
char *yyold;

void yyinputinit(char *p) {
    yyin = p;
    yytextcnt = 0;
}

void yyfilltext() {
    char *p = yyold;
    int size = yyin - yyold;
    int i;

    yytextcnt = 0;

    if (yytextcnt + size + 1 >= 128) {
        return;
    }

    for (i = 0;i < size; i++) {
        yytext[yytextcnt++] = *p++;
    }
    yytext[yytextcnt++] = '\0';

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

    "\000" { return 0; }
    [ \t]+ { goto start; }

*/
}

int yyerror(const char *s) {
    printf("ERROR %s\n", s);
    return 0;
}
