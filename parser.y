%{
#include <stdio.h>

// #define YYDEBUG          1
// #define YYERROR_VERBOSE      1
// int yydebug = 1;
%}

%token TNUM         /* [0-9]+ */
%token BRACKET      /* ( */
%token BRACKET_END  /* ) */
%token TEND         /* \n */

%left PLUS MINUS /* + - */
%left MULTI PROD /* * / */

/* 文法規則部 */
%%

input: /* empty */
     | input line
;

line: TEND
    | exp TEND { 
        printf("%d\n", $1);
      }
;

exp: TNUM { $$ = $1; }
 | exp PLUS exp { $$ = $1 + $3; }        /* 38 + 38 */
 | exp MINUS exp { $$ = $1 - $3; }       /* 38 - 38 */
 | exp MULTI exp { $$ = $1 * $3; }       /* 38 * 38 */
 | exp PROD exp { $$ = $1 / $3; }        /* 38 / 38 */
 | MINUS exp { $$ = -$2; }               /* -38 */
 | BRACKET exp BRACKET_END { $$ = $2; }  /* (38) */
;

%%
