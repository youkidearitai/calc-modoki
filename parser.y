%{
#include <stdio.h>

// #define YYDEBUG          1
// #define YYERROR_VERBOSE      1
// int yydebug = 1;
%}

%token TNUM /* YACC宣言部 */
%token BRACKET /* YACC宣言部 */
%token BRACKET_END /* YACC宣言部 */
%token TEND

%left PLUS MINUS
%left MULTI PROD

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
 | exp PLUS exp { $$ = $1 + $3; }
 | exp MINUS exp { $$ = $1 - $3; }
 | exp MULTI exp { $$ = $1 * $3; }
 | exp PROD exp { $$ = $1 / $3; }
 | MINUS exp { $$ = -$2; }
 | BRACKET exp BRACKET_END { $$ = $2; }
;

%%
