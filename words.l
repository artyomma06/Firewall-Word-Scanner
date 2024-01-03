%top{
#include <stdio.h>
}
%option noinput
%option nounput
%option noyywrap

LET  [(A-Z)a-z_]
DIG  [0-9]
WS   [ \t\r\n]
PUNC [~`!@#$%^&*()_+-={}|\\\[\]:;\"\'<>,/?.]
%%
{LET}+                     { return 0; }
{LET}+"'"({LET}+)          { return 0; }
{LET}+"-"({LET}+)          { return 0; }
{LET}+"`"({LET}+)          { return 0; }
{LET}+{DIG}+               { return 0; }
{PUNC}+                    {}
{WS}+                      {}
<<EOF>>                    { return -1; }
.                                     {}

%%
