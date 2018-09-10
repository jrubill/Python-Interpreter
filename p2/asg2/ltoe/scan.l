%{
#include <iostream>
// l337 to English
%}

%%
4		{ std::cout << "a"; }
8		{ std::cout << "b"; }
"["		{ std::cout << "c"; }
"[)"	{ std::cout << "d"; }
3		{ std::cout << "e"; }
"|="	{ std::cout << "f"; }
6		{ std::cout << "g"; }
"]-["	{ std::cout << "h"; }
1		{ std::cout << "i"; }
"_|"	{ std::cout << "j"; }
"|c"	{ std::cout << "k"; }
"|_"	{ std::cout << "l"; }
"|\/|"	{ std::cout << "m"; }
"|\|"	{ std::cout << "n"; }
0		{ std::cout << "o"; }
"|o"	{ std::cout << "p"; }
&		{ std::cout << "q"; }
"/2"	{ std::cout << "r"; }
5		{ std::cout << "s"; }
7		{ std::cout << "t"; }
"|_|"	{ std::cout << "u"; }
"\/"	{ std::cout << "v"; }
"VV"	{ std::cout << "w"; }
"ecks"	{ std::cout << "x"; }
"`/"	{ std::cout << "y"; }
"-\_"	{ std::cout << "z"; }


%%
int yywrap() { return 1; }
