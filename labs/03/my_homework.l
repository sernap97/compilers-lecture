%{
#include <stdio.h>
%}

%%
[ \t] ;
[\/]{2}.* ;
i                           printf("intdcl ");
f                           printf("floatdcl ");
p                           printf("print ");
[a-e]|[gh]|[j-o]|[q-z]      printf("id ");
=                           printf("assign ");
\+                          printf("plus ");
\-                          printf("minus ");
\*                          printf("times ");
\/                          printf("divided by ");
[0-9]+                      printf("inum ");
[0-9]+\.[0-9]+              printf("fnum ");

%%

int main(int argc, char *argv[])
{
    yyin = fopen(argv[1], "r");
    yylex();
    fclose(yyin);
    return 0;
}