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
	printf("Line:%d (Key: %s)\n", yylineno, yytext);
}

";" | 
"(" |
")" |
"[" |
"]" |
"{" |
"}" |
"," {
	printf("Line:%d (Sep: %s)\n", yylineno, yytext);
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
	printf("Line:%d (Opa: %s)\n", yylineno, yytext);
}

">" |
"<" |
">=" |
"<=" |
"==" {
	printf("Line:%d (Cmp: %s)\n", yylineno, yytext);
}

"=" {
	printf("Line:%d (Asg: %s)\n", yylineno, yytext);
}

"." |
"#" {
	printf("Line:%d (Spec: %s)\n", yylineno, yytext);
}

{Identifiers} {
	printf("Line:%d (Ide: %s)\n", yylineno, yytext);
}

{Integer} {
	printf("Line:%d (Int: %s)\n", yylineno, yytext);
}

{Float} {
	printf("Line:%d (Flo: %s)\n", yylineno, yytext);
}

"//".* {
	printf("Line:%d (Note: %s)\n", yylineno, yytext);
}

"/*"([^*]|\*+[^*/])*\**"*/" {
	printf("Line:%d (Note: %s)\n", yylineno, yytext);
}

"'"[^'\n]"'" {
	printf("Line:%d (Char: %s)\n", yylineno, yytext);
}

"\""([^"]|\\\"+)*"\"" {
	printf("Line:%d (Str: %s)\n", yylineno, yytext);
}

[\n] {
//	yylineno++;
	printf("Line:%d %s\n", yylineno, yytext);
}

[ \t\v\b\r\f\a] {
	printf("Line:%d (Bnk: %s)\n", yylineno, yytext);
}

[\\\?] {
	printf("Line:%d (Spe: %s)\n", yylineno, yytext);
}

. {
	printf("Line:%d Unexpected Word Was Analysed!", yylineno);
}

%%

int main()
{
	freopen("file.in", "r", stdin);
	freopen("file.c", "w", stdout);
	yylex();
	printf("\n//The analysize of character is finish !\n");
	return 0;
}

int yywrap()
{
	return 1;
}
