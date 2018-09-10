%{
#include <iostream>
// English to l337
%}

%%
[eE] 	{ std::cout << "3"; }
[aA] 	{ std::cout << "4"; }
[tT]	{ std::cout << "7"; }
[sS]	{ std::cout << "5"; }
[oO]	{ std::cout << "0"; }
[wW]	{ std::cout << "\|/";}
[bB]	{ std::cout << "8"; }
[cC]	{ std::cout << "["; }
[dD]	{ std::cout << "[)";}
[fF]	{ std::cout << "|="; }
[gG]	{ std::cout << "6"; }
[hH]	{ std::cout << "]-["; }
[iI]	{ std::cout << "|"; }
[jJ]	{ std::cout << "_|"; }
[kK]	{ std::cout << "|c"; }
[lL]	{ std::cout << "|_"; }
[mM]	{ std::cout << "|\/|"; }
[nN]	{ std::cout << "|\|"; }
[pP]	{ std::cout << "|o"; }
[qQ]	{ std::cout << "&"; }
[rR]	{ std::cout << "\2"; }
[uU]	{ std::cout << "|_|"; }
[vV]	{ std::cout << "\/"; }
[wW]	{ std::cout << "VV"; }
[xX]	{ std::cout << "ecks"; }
[yY]	{ std::cout << "`/"; }
[zZ]	{ std::cout << "-/_"; }

%%
int yywrap() { return 1; }
