/*
* Made By Yuanxiang Xie
*/
%{
	#include "stdio.h"
	#include "stdlib.h"
	//int yylexlineno = 1;
%}

Letter [A-Za-z]
Identifiers [a-zA-Z_][a-zA-Z_0-9]*
Integer [-+]?([1-9][0-9]*|0([0-7]+|(x|X)[0-9A-Fa-f]*)?)[uUlL]?
Float [-+]?([0-9]*.[0-9]*[1-9](e|E)?(-)?[0-9]*[1-9](f|lf)?)
WhiteSpace [ \t]+

%option yylineno

%%

"auto" |

"double" |

"int" |

"struct" |

"break" |

"else" |

"long" |

"switch" |

"case" |

"enum" |

"register" |

"typedef" |

"char" |

"extern" |

"return" |

"union" |

"const" |

"float" |

"short" |

"unsigned" |

"continue" |

"for" |

"signed" |

"void" |

"default" |

"goto" |

"sizeof" |

"volatile" |

"do" |

"if" |

"static" |

"while" |
"include" {
	printf("%s", yytext);
}

";" | 
"(" |
")" |
"[" |
"]" |
"{" |
"}" |
"," {
	printf("%s", yytext);
}

"+" |
"-" |
"*" |
"/" |
"%" |
"&" |
"|" |
"^" |
"!" |
"&&" |
"||" |
"++" |
"--" |
"+=" |
"-=" |
"*=" |
"/=" |
"%=" |
"!=" |
"^=" |
"<<" |
">>" {
	printf("%s", yytext);
}

">" |
"<" |
">=" |
"<=" |
"==" {
	printf("%s", yytext);
}

"=" {
	printf("%s", yytext);
}

"." |
"#" {
	printf("%s", yytext);
}

{Identifiers} {
	printf("%s", yytext);
}

{Integer} {
	printf("%s", yytext);
}

{Float} {
	printf("%s", yytext);
}

"//".* {
	//printf("%s", yytext);
}

"/*"([^*]|\*+[^*/])*\**"*/" {
	//printf("%s", yytext);
}

"'"[^'\n]"'" {
	//printf("%s", yytext);
}

"\""([^"]|\\\"+)*"\"" {
	printf("%s", yytext);
}

[\n] {
//	yylineno++;
	printf("%s", yytext);
}

[ \t\v\b\r\f\a] {
	printf("%s", yytext);
}

[\\\?] {
	printf("%s", yytext);
}

. {
	printf("%s", yytext);
}

%%

int main()
{
	freopen("file.in", "r", stdin);
	freopen("route.cpp", "w", stdout);
	yylex();
	printf("%s", yytext);
	return 0;
}

int yywrap()
{
	return 1;
}
