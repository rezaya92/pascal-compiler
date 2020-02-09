
%{
#include <math.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "Scanner.h"
using namespace std;

string tokens[] = {"$", "function", "begin", "end", "procedure", "boolean", "integer", "char", "string", "read", "write", "strlen", "true", "false", "if", "then", "and", "or", "array", "of", "do", "else", "while", "return", "real", "long", "bad_string", "<=", ">=", "<>", "<", ">", "ch", "rc", "ic", "id", "str", "=", "&", "*", "/", "+", "\\", "-", ",", ";", ":", "(", ")", "[", "]", "|", "%", "^", "~"};

%}

%option yylineno
%option noyywrap
%option c++

white_space		[ \t\n\f\r\v]*
digit			[0-9]
alpha			[A-Za-z_]
alpha_num		({alpha}|{digit})
hex_digit		[0-9A-F]
id			{alpha}{alpha_num}*
integer			{digit}+
hex_integer		0x{hex_digit}+
real			({digit}*\.{digit}+)|({digit}+\.{digit}*)
string			\"([^"\n]|\\\")*\"
character		\'.\'
bad_string		\"([^"\n])*
comment			(((--)|(\/\/)).*)|(<--(.|\n)*?-->)
%%


{comment}		printf("comment");
function		return(1);
begin			return(2);
end			return(3);
procedure		return(4);
boolean			return(5);
integer			return(6);
char			return(7);
string			return(8);
read			return(9);
write			return(10);
strlen			return(11);
true			return(12);
false			return(13);
if			return(14);
then			return(15);
and			return(16);
or			return(17);
array			return(18);
of			return(19);
do			return(20);
else			return(21);
while			return(22);
return			return(23);
real			return(24);
long			return(25);
{bad_string}		return(26);
[<][=]			return(27);
[>][=]			return(28);
[<][>]			return(29);
[<]			return(30);
[>]			return(31);
{character}		return(32);
{real}			return(33);
{hex_integer}		return(34);
{integer}		return(34);
{id}			return(35);
{string}		return(36);
[=]			return(37);
[&]			return(38);
[*]			return(39);
[/]			return(40);
[+]			return(41);
[\\]			return(42);
[-]			return(43);
[,]			return(44);
[;]			return(45);
[:]			return(46);
[(]			return(47);
[)]			return(48);
[\[]			return(49);
[\]]			return(50);
[|]			return(51);
[%]			return(52);
[\^]			return(53);
[~]			return(54);
{white_space}		/* do nothing */
.			printf("error");
<<EOF>>			return(0);

%%

Scanner::Scanner(char* filename)
{
  	inF.open(filename, std::ios_base::in);
	lexer = new yyFlexLexer(&inF);
}

Scanner::~Scanner()
{

}

string Scanner::NextToken()
{
	string tmpStr = tokens[lexer->yylex()];
	return tmpStr;
}

