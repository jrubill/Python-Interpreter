// Generated by transforming |cwd:///work-in-progress/2.7.2-bisonified.y| on 2016-11-23 at 15:46:56 +0000
%{
    #include "includes/ast.h"
    #include <map> 
    #include "parse.tab.h" 
    #include "includes/tableManager.h"
    #include <cstring>
    #include <vector>
    int yylex (void);
	extern char *yytext;
	void yyerror (const char *);
   
    PoolOfNodes& pool = PoolOfNodes::getInstance();
	TableManager& m = TableManager::getInstance();
    
%}

%union {
    Node *node;
    int intNumber;
    float fltNumber;
    char *id;
    std::vector<Node*> *suite;
}


// 83 tokens, in alphabetical order:
%token AMPEREQUAL AMPERSAND AND AS ASSERT AT BACKQUOTE BAR BREAK CIRCUMFLEX
%token CIRCUMFLEXEQUAL CLASS COLON COMMA CONTINUE DEDENT DEF DEL DOT DOUBLESLASH
%token DOUBLESLASHEQUAL DOUBLESTAR DOUBLESTAREQUAL ELIF ELSE ENDMARKER EQEQUAL
%token EQUAL EXCEPT EXEC FINALLY FOR FROM GLOBAL GREATER GREATEREQUAL GRLT
%token IF IMPORT IN INDENT IS LAMBDA LBRACE LEFTSHIFT LEFTSHIFTEQUAL LESS
%token LESSEQUAL LPAR LSQB MINEQUAL MINUS NAME NEWLINE NOT NOTEQUAL FLOAT_NUM INT_NUM 
%token OR PASS PERCENT PERCENTEQUAL PLUS PLUSEQUAL PRINT RAISE RBRACE RETURN
%token RIGHTSHIFT RIGHTSHIFTEQUAL RPAR RSQB SEMI SLASH SLASHEQUAL STAR STAREQUAL
%token STRING TILDE TRY VBAREQUAL WHILE WITH YIELD


%type<intNumber> PLUSEQUAL MINEQUAL STAREQUAL SLASHEQUAL PERCENTEQUAL AMPEREQUAL
%type<intNumber> VBAREQUAL CIRCUMFLEXEQUAL LEFTSHIFTEQUAL RIGHTSHIFTEQUAL 
%type<intNumber> DOUBLESTAREQUAL DOUBLESLASHEQUAL
%type<intNumber> MINUS PLUS TILDE pick_unop
%type<intNumber> pick_PLUS_MINUS
%type<intNumber> pick_multop  
%type<intNumber> INT_NUM
%type<fltNumber> FLOAT_NUM
%type<node> atom arith_expr test factor and_test stmt
%type<node> opt_test term lambdef not_test and_expr
%type<node> power or_test comparison expr xor_expr
%type<node> shift_expr star_EQUAL expr_stmt testlist star_trailer trailer
%type<node> pick_yield_expr_testlist subscript opt_yield_test subscriptlist
%type<node> return_stmt funcdef suite decorator simple_stmt decorated print_stmt compound_stmt
%type<suite> plus_stmt 
%type<id> plus_STRING STRING
%type<intNumber> augassign
%type<id> NAME



%start start

%locations

%%

start
	: file_input
	;
file_input // Used in: start
	: star_NEWLINE_stmt ENDMARKER
	;
pick_NEWLINE_stmt // Used in: star_NEWLINE_stmt
	: NEWLINE 
	| stmt  { if ($1) $1->eval(); 
        }
	;
star_NEWLINE_stmt // Used in: file_input, star_NEWLINE_stmt
	: star_NEWLINE_stmt pick_NEWLINE_stmt
	| %empty
	;
decorator // Used in: decorators
	: AT dotted_name LPAR opt_arglist RPAR NEWLINE { ; }
	| AT dotted_name NEWLINE
	;
opt_arglist // Used in: decorator, trailer
	: arglist
	| %empty
	;
decorators // Used in: decorators, decorated
	: decorators decorator { ;  }
	| decorator { ; }
	;
decorated // Used in: compound_stmt
	: decorators classdef {   }
	| decorators funcdef {$$ = $2;}
	;
funcdef // Used in: decorated, compound_stmt
    : DEF NAME parameters COLON suite {
            $$ = new FuncNode($2, $5);
            pool.add($$);
            delete [] $2;
    }
	;
parameters // Used in: funcdef
	: LPAR varargslist RPAR
	| LPAR RPAR
	;
varargslist // Used in: parameters, old_lambdef, lambdef
	: star_fpdef_COMMA pick_STAR_DOUBLESTAR
	| star_fpdef_COMMA fpdef opt_EQUAL_test opt_COMMA
	;
opt_EQUAL_test // Used in: varargslist, star_fpdef_COMMA
	: EQUAL test
	| %empty
	;
star_fpdef_COMMA // Used in: varargslist, star_fpdef_COMMA
	: star_fpdef_COMMA fpdef opt_EQUAL_test COMMA
	| %empty
	;
opt_DOUBLESTAR_NAME // Used in: pick_STAR_DOUBLESTAR
	: COMMA DOUBLESTAR NAME
	| %empty
	;
pick_STAR_DOUBLESTAR // Used in: varargslist
	: STAR NAME opt_DOUBLESTAR_NAME
	| DOUBLESTAR NAME
	;
opt_COMMA // Used in: varargslist, opt_test, opt_test_2, testlist_safe, listmaker, testlist_comp, pick_for_test_test, pick_for_test, pick_argument
	: COMMA
	| %empty
	;
fpdef // Used in: varargslist, star_fpdef_COMMA, fplist, star_fpdef_notest
	: NAME
	| LPAR fplist RPAR
	;
fplist // Used in: fpdef
	: fpdef star_fpdef_notest COMMA
	| fpdef star_fpdef_notest
	;
star_fpdef_notest // Used in: fplist, star_fpdef_notest
	: star_fpdef_notest COMMA fpdef
	| %empty
	;
stmt // Used in: pick_NEWLINE_stmt, plus_stmt
	: simple_stmt { $$ = $1; }
	| compound_stmt {; }
	;
simple_stmt // Used in: stmt, suite
	: small_stmt star_SEMI_small_stmt SEMI NEWLINE { ;  }
	| small_stmt star_SEMI_small_stmt NEWLINE { ;  }
	;
star_SEMI_small_stmt // Used in: simple_stmt, star_SEMI_small_stmt
	: star_SEMI_small_stmt SEMI small_stmt
	| %empty
	;
small_stmt // Used in: simple_stmt, star_SEMI_small_stmt
	: expr_stmt 
	| print_stmt
	| del_stmt
	| pass_stmt
	| flow_stmt
	| import_stmt
	| global_stmt
	| exec_stmt
	| assert_stmt
	;
expr_stmt // Used in: small_stmt
	: testlist augassign pick_yield_expr_testlist {
		const Literal *lhs = $1->eval();	
		const Literal *rhs = static_cast<Literal*>($3);
		std::string name = static_cast<IdentNode*>($1)->getIdent();
		
		switch($2) {
			case PLUSEQUAL: TableManager::getInstance().updateSymb(name, *lhs + *rhs);
				break;
			case MINEQUAL: TableManager::getInstance().updateSymb(name, *lhs - *rhs);
				break;
			case STAREQUAL: TableManager::getInstance().updateSymb(name, *lhs * *rhs);
				break;
			case SLASHEQUAL: TableManager::getInstance().updateSymb(name, *lhs / *rhs);
				break;
			case PERCENTEQUAL: TableManager::getInstance().updateSymb(name, *lhs % *rhs); 
				break;
		}

	}
	| testlist star_EQUAL {
		if ($2 != 0) {
			$$ = new AsgBinaryNode($1, $2);
			pool.add($$);
		}
	}
	;
pick_yield_expr_testlist // Used in: expr_stmt, star_EQUAL
	: yield_expr { ; } // potentially fix this
	| testlist  { $$ = $1; }
	;
star_EQUAL // Used in: expr_stmt, star_EQUAL
	: star_EQUAL EQUAL pick_yield_expr_testlist {
		if ($1 == 0) $$ = $3;
		if ($1 != 0 && $3 != 0) {
			$$ = new AsgBinaryNode($1, $3);
			pool.add($$);
			}
		}
	| %empty {$$ = 0; }
	;
augassign // Used in: expr_stmt
	: PLUSEQUAL			{ $$ = PLUSEQUAL;    }
	| MINEQUAL			{ $$ = MINEQUAL;     }
	| STAREQUAL			{ $$ = STAREQUAL;    }
	| SLASHEQUAL		{ $$ = SLASHEQUAL;   }
	| PERCENTEQUAL		{ $$ = PERCENTEQUAL; }
	| AMPEREQUAL
	| VBAREQUAL
	| CIRCUMFLEXEQUAL
	| LEFTSHIFTEQUAL
	| RIGHTSHIFTEQUAL 
	| DOUBLESTAREQUAL
	| DOUBLESLASHEQUAL
	;
print_stmt // Used in: small_stmt
	: PRINT opt_test { 
		try {	
			$$ = new PrintNode($2);
            pool.add($$);	
        }
		catch (const std::string &str) {
			std::cout << "Error " << str << std::endl;
		}
		catch ( ... ) {
			std::cout << "oopsies" << std::endl;
		}
	}
	| PRINT RIGHTSHIFT test opt_test_2 { ;  }
	;
star_COMMA_test // Used in: star_COMMA_test, opt_test, listmaker, testlist_comp, testlist, pick_for_test
	: star_COMMA_test COMMA test
	| %empty
	;
opt_test // Used in: print_stmt
	: test star_COMMA_test opt_COMMA
	| %empty
      { $$ = nullptr; }	
    ;
plus_COMMA_test // Used in: plus_COMMA_test, opt_test_2
	: plus_COMMA_test COMMA test
	| COMMA test
    ;
opt_test_2 // Used in: print_stmt
	: plus_COMMA_test opt_COMMA
	| %empty
    ;
del_stmt // Used in: small_stmt
	: DEL exprlist
	;
pass_stmt // Used in: small_stmt
	: PASS
	;
flow_stmt // Used in: small_stmt
	: break_stmt
	| continue_stmt
	| return_stmt
	| raise_stmt
	| yield_stmt
	;
break_stmt // Used in: flow_stmt
	: BREAK
	;
continue_stmt // Used in: flow_stmt
	: CONTINUE
	;
return_stmt // Used in: flow_stmt
    : RETURN testlist {
        $$ = new ReturnNode($2);
        pool.add($$);
    }
    | RETURN {
        const Node *node = new IntLiteral(0);
        $$ = new ReturnNode(node);
        pool.add($$);
        pool.add(node);
    }
	;
yield_stmt // Used in: flow_stmt
	: yield_expr
	;
raise_stmt // Used in: flow_stmt
	: RAISE test opt_test_3
	| RAISE
	;
opt_COMMA_test // Used in: opt_test_3, exec_stmt
	: COMMA test
	| %empty
	;
opt_test_3 // Used in: raise_stmt
	: COMMA test opt_COMMA_test
	| %empty
	;
import_stmt // Used in: small_stmt
	: import_name
	| import_from
	;
import_name // Used in: import_stmt
	: IMPORT dotted_as_names
	;
import_from // Used in: import_stmt
	: FROM pick_dotted_name IMPORT pick_STAR_import
	;
pick_dotted_name // Used in: import_from
	: star_DOT dotted_name
	| star_DOT DOT
	;
pick_STAR_import // Used in: import_from
	: STAR
	| LPAR import_as_names RPAR
	| import_as_names
	;
import_as_name // Used in: import_as_names, star_COMMA_import_as_name
	: NAME AS NAME
	| NAME
	;
dotted_as_name // Used in: dotted_as_names
	: dotted_name AS NAME
	| dotted_name
	;
import_as_names // Used in: pick_STAR_import
	: import_as_name star_COMMA_import_as_name COMMA
	| import_as_name star_COMMA_import_as_name
	;
star_COMMA_import_as_name // Used in: import_as_names, star_COMMA_import_as_name
	: star_COMMA_import_as_name COMMA import_as_name
	| %empty
	;
dotted_as_names // Used in: import_name, dotted_as_names
	: dotted_as_name
	| dotted_as_names COMMA dotted_as_name
	;
dotted_name // Used in: decorator, pick_dotted_name, dotted_as_name, dotted_name
	: NAME
	| dotted_name DOT NAME
	;
global_stmt // Used in: small_stmt
	: GLOBAL NAME star_COMMA_NAME
	;
star_COMMA_NAME // Used in: global_stmt, star_COMMA_NAME
	: star_COMMA_NAME COMMA NAME
	| %empty
	;
exec_stmt // Used in: small_stmt
	: EXEC expr IN test opt_COMMA_test
	| EXEC expr
	;
assert_stmt // Used in: small_stmt
	: ASSERT test COMMA test
	| ASSERT test
	;
compound_stmt // Used in: stmt
	: if_stmt { $$ = nullptr;} 
	| while_stmt { $$ = nullptr;}
	| for_stmt { $$ = nullptr;} 
	| try_stmt { $$ = nullptr;} 
	| with_stmt { $$ = nullptr;} 
	| funcdef { $$ = $1; }
	| classdef { $$ = nullptr;} 
	| decorated { $$ = nullptr;} 
	;
if_stmt // Used in: compound_stmt
	: IF test COLON suite star_ELIF ELSE COLON suite
	| IF test COLON suite star_ELIF
	;
star_ELIF // Used in: if_stmt, star_ELIF
	: star_ELIF ELIF test COLON suite
	| %empty
	;
while_stmt // Used in: compound_stmt
	: WHILE test COLON suite ELSE COLON suite
	| WHILE test COLON suite
	;
for_stmt // Used in: compound_stmt
	: FOR exprlist IN testlist COLON suite ELSE COLON suite
	| FOR exprlist IN testlist COLON suite
	;
try_stmt // Used in: compound_stmt
	: TRY COLON suite plus_except opt_ELSE opt_FINALLY
	| TRY COLON suite FINALLY COLON suite
	;
plus_except // Used in: try_stmt, plus_except
	: plus_except except_clause COLON suite
	| except_clause COLON suite
	;
opt_ELSE // Used in: try_stmt
	: ELSE COLON suite
	| %empty
	;
opt_FINALLY // Used in: try_stmt
	: FINALLY COLON suite
	| %empty
	;
with_stmt // Used in: compound_stmt
	: WITH with_item star_COMMA_with_item COLON suite
	;
star_COMMA_with_item // Used in: with_stmt, star_COMMA_with_item
	: star_COMMA_with_item COMMA with_item
	| %empty
	;
with_item // Used in: with_stmt, star_COMMA_with_item
	: test AS expr
	| test
	;
except_clause // Used in: plus_except
	: EXCEPT test opt_AS_COMMA
	| EXCEPT
	;
pick_AS_COMMA // Used in: opt_AS_COMMA
	: AS
	| COMMA
	;
opt_AS_COMMA // Used in: except_clause
	: pick_AS_COMMA test
	| %empty
	;
suite // Used in: funcdef, if_stmt, star_ELIF, while_stmt, for_stmt, try_stmt, plus_except, opt_ELSE, opt_FINALLY, with_stmt, classdef
	: simple_stmt {$$ = $1;}
    | NEWLINE INDENT plus_stmt DEDENT {
        $$ = new SuiteNode(*$3);
        delete $3;
        pool.add($$);
    }
	;
plus_stmt // Used in: suite, plus_stmt
    : plus_stmt stmt {
        $$ = $1;
        $$->push_back($2);
    }
    | stmt {
        $$ = new std::vector<Node*>();
        $$->reserve(4);
        $$->push_back($1);
    }
	;
testlist_safe // Used in: list_for
	: old_test plus_COMMA_old_test opt_COMMA
	| old_test
	;
plus_COMMA_old_test // Used in: testlist_safe, plus_COMMA_old_test
	: plus_COMMA_old_test COMMA old_test
	| COMMA old_test
	;
old_test // Used in: testlist_safe, plus_COMMA_old_test, old_lambdef, list_if, comp_if
	: or_test
	| old_lambdef
	;
old_lambdef // Used in: old_test
	: LAMBDA varargslist COLON old_test
	| LAMBDA COLON old_test
	;
test // Used in: opt_EQUAL_test, print_stmt, star_COMMA_test, opt_test, plus_COMMA_test, raise_stmt, opt_COMMA_test, opt_test_3, exec_stmt, assert_stmt, if_stmt, star_ELIF, while_stmt, with_item, except_clause, opt_AS_COMMA, opt_IF_ELSE, listmaker, testlist_comp, lambdef, subscript, opt_test_only, sliceop, testlist, dictorsetmaker, star_test_COLON_test, opt_DOUBLESTAR_test, pick_argument, argument, testlist1
	: or_test opt_IF_ELSE
	| lambdef
	;
opt_IF_ELSE // Used in: test
	: IF or_test ELSE test
	| %empty
	;
or_test // Used in: old_test, test, opt_IF_ELSE, or_test, comp_for
	: and_test
	| or_test OR and_test
	;
and_test // Used in: or_test, and_test
	: not_test
	| and_test AND not_test
	;
not_test // Used in: and_test, not_test
	: NOT not_test {$$ = $$;}
	| comparison
	;
comparison // Used in: not_test, comparison
	: expr
	| comparison comp_op expr
	;
comp_op // Used in: comparison
	: LESS
	| GREATER
	| EQEQUAL
	| GREATEREQUAL
	| LESSEQUAL
	| GRLT
	| NOTEQUAL
	| IN
	| NOT IN
	| IS
	| IS NOT
	;
expr // Used in: exec_stmt, with_item, comparison, expr, exprlist, star_COMMA_expr
	: xor_expr
	| expr BAR xor_expr
	;
xor_expr // Used in: expr, xor_expr
	: and_expr
	| xor_expr CIRCUMFLEX and_expr
	;
and_expr // Used in: xor_expr, and_expr
	: shift_expr
	| and_expr AMPERSAND shift_expr
	;
shift_expr // Used in: and_expr, shift_expr
	: arith_expr
	| shift_expr pick_LEFTSHIFT_RIGHTSHIFT arith_expr
	;
pick_LEFTSHIFT_RIGHTSHIFT // Used in: shift_expr
	: LEFTSHIFT
	| RIGHTSHIFT
	;
arith_expr // Used in: shift_expr, arith_expr
	: term
    | arith_expr pick_PLUS_MINUS term {
        if ($2 == PLUS) {
            $$ = new AddBinaryNode($1, $3);
            pool.add($$);
        }
        else { 
            $$ = new SubBinaryNode($1, $3);
            pool.add($$);
        }
    
    }
	;
pick_PLUS_MINUS // Used in: arith_expr
	: PLUS  { $$ = PLUS; }
	| MINUS { $$ = MINUS; }
	;
term // Used in: arith_expr, term
	: factor
	| term pick_multop factor {
		if ($2 == STAR) {
			$$ = new MulBinaryNode($1, $3);
			pool.add($$);
		}
		else if ($2 == SLASH) {
			$$ = new DivBinaryNode($1, $3);
			pool.add($$);
		}
		else if ($2 == PERCENT) {
			// mod operator	
			$$ = new ModBinaryNode($1, $3);
			pool.add($$);
		}
		else {
			// integer division
			$$ = new IntDivBinaryNode($1, $3);
			pool.add($$);
		}
	}
	;
pick_multop // Used in: term
	: STAR 			{ $$ = STAR;        }
	| SLASH			{ $$ = SLASH;       }
	| PERCENT		{ $$ = PERCENT;     }
	| DOUBLESLASH   { $$ = DOUBLESLASH; }
	;
factor // Used in: term, factor, power
	: pick_unop factor {
		if ($1 == MINUS) {
			$$ = new UnaryNode($2);	
	        pool.add($$);	
        }
	}
	| power
	;
pick_unop // Used in: factor
	: PLUS
	| MINUS { $$ = MINUS; }
	| TILDE
	;
power // Used in: factor
	: atom star_trailer DOUBLESTAR factor {
		$$ = new PowBinaryNode($1, $4);
		pool.add($$);
	}
    | atom star_trailer {
        if ($2) {
        std::string n = reinterpret_cast<IdentNode*>($1)->getIdent();
        $$ = new CallNode(n);
        pool.add($$);
        }
        else $$ = $1;

        /* Need to fix this
        if ($2 != nullptr) {
            $$ = new SubscriptNode($1, $2); 
            pool.add($$);
        } */

            }	
    ;
star_trailer // Used in: power, star_trailer
	: star_trailer trailer { $$ = $2; }
	| %empty { $$ = nullptr; }
	;
atom // Used in: power
	: LPAR opt_yield_test RPAR { $$ = $2; }
	| LSQB opt_listmaker RSQB { ; }
	| LBRACE opt_dictorsetmaker RBRACE { ; }
	| BACKQUOTE testlist1 BACKQUOTE { ;  }
	| NAME			{ $$ = new IdentNode($1);     pool.add($$);  delete [] $1; }
	| INT_NUM   	{ $$ = new IntLiteral($1);    pool.add($$);  }
	| FLOAT_NUM 	{ $$ = new FloatLiteral($1);  pool.add($$);  }
	| plus_STRING	{ $$ = new StringLiteral($1); pool.add($$);  delete [] $1; }
	;
pick_yield_expr_testlist_comp // Used in: opt_yield_test
	: yield_expr
	| testlist_comp
	;
opt_yield_test // Used in: atom
	: pick_yield_expr_testlist_comp { ; }
	| %empty { ; }
	;
opt_listmaker // Used in: atom
	: listmaker
	| %empty
	;
opt_dictorsetmaker // Used in: atom
	: dictorsetmaker
	| %empty
	;
plus_STRING // Used in: atom, plus_STRING
	: plus_STRING STRING { 
      char *temp = new char[(strlen($1) + strlen($2)) * sizeof(char)];
      strcpy(temp, $1);
      strcat(temp, $2);
      delete [] $1; delete [] $2;
      $$ = temp;
    }
	| STRING { $$ = $1; }
	;
listmaker // Used in: opt_listmaker
	: test list_for
	| test star_COMMA_test opt_COMMA
	;
testlist_comp // Used in: pick_yield_expr_testlist_comp
	: test comp_for
	| test star_COMMA_test opt_COMMA
	;
lambdef // Used in: test
	: LAMBDA varargslist COLON test { ; }
	| LAMBDA COLON test { ; }
	;
trailer // Used in: star_trailer
	: LPAR opt_arglist RPAR { ;  }
	| LSQB subscriptlist RSQB { 
		$$ = $2;
	}
	| DOT NAME { ; }
	;
subscriptlist // Used in: trailer
	: subscript star_COMMA_subscript COMMA { $$ = nullptr; }
	| subscript star_COMMA_subscript { $$ = $1; }
	;
star_COMMA_subscript // Used in: subscriptlist, star_COMMA_subscript
	: star_COMMA_subscript COMMA subscript 
	| %empty
	;
subscript // Used in: subscriptlist, star_COMMA_subscript
	: DOT DOT DOT { ; }
	| test { $$ = $1; }
	| opt_test_only COLON opt_test_only opt_sliceop {  }
	;
opt_test_only // Used in: subscript
	: test
	| %empty
	;
opt_sliceop // Used in: subscript
	: sliceop
	| %empty
	;
sliceop // Used in: opt_sliceop
	: COLON test
	| COLON
	;
exprlist // Used in: del_stmt, for_stmt, list_for, comp_for
	: expr star_COMMA_expr COMMA
	| expr star_COMMA_expr
	;
star_COMMA_expr // Used in: exprlist, star_COMMA_expr
	: star_COMMA_expr COMMA expr
	| %empty
	;
testlist // Used in: expr_stmt, pick_yield_expr_testlist, return_stmt, for_stmt, opt_testlist, yield_expr
	: test star_COMMA_test COMMA
	| test star_COMMA_test
	;
dictorsetmaker // Used in: opt_dictorsetmaker
	: test COLON test pick_for_test_test
	| test pick_for_test
	;
star_test_COLON_test // Used in: star_test_COLON_test, pick_for_test_test
	: star_test_COLON_test COMMA test COLON test
	| %empty
	;
pick_for_test_test // Used in: dictorsetmaker
	: comp_for
	| star_test_COLON_test opt_COMMA
	;
pick_for_test // Used in: dictorsetmaker
	: comp_for
	| star_COMMA_test opt_COMMA
	;
classdef // Used in: decorated, compound_stmt
	: CLASS NAME LPAR opt_testlist RPAR COLON suite
	| CLASS NAME COLON suite
	;
opt_testlist // Used in: classdef
	: testlist
	| %empty
	;
arglist // Used in: opt_arglist
	: star_argument_COMMA pick_argument
	;
star_argument_COMMA // Used in: arglist, star_argument_COMMA
	: star_argument_COMMA argument COMMA
	| %empty
	;
star_COMMA_argument // Used in: star_COMMA_argument, pick_argument
	: star_COMMA_argument COMMA argument
	| %empty
	;
opt_DOUBLESTAR_test // Used in: pick_argument
	: COMMA DOUBLESTAR test
	| %empty
	;
pick_argument // Used in: arglist
	: argument opt_COMMA
	| STAR test star_COMMA_argument opt_DOUBLESTAR_test
	| DOUBLESTAR test
	;
argument // Used in: star_argument_COMMA, star_COMMA_argument, pick_argument
	: test opt_comp_for
	| test EQUAL test
	;
opt_comp_for // Used in: argument
	: comp_for
	| %empty
	;
list_iter // Used in: list_for, list_if
	: list_for
	| list_if
	;
list_for // Used in: listmaker, list_iter
	: FOR exprlist IN testlist_safe list_iter
	| FOR exprlist IN testlist_safe
	;
list_if // Used in: list_iter
	: IF old_test list_iter
	| IF old_test
	;
comp_iter // Used in: comp_for, comp_if
	: comp_for
	| comp_if
	;
comp_for // Used in: testlist_comp, pick_for_test_test, pick_for_test, opt_comp_for, comp_iter
	: FOR exprlist IN or_test comp_iter
	| FOR exprlist IN or_test
	;
comp_if // Used in: comp_iter
	: IF old_test comp_iter
	| IF old_test
	;
testlist1 // Used in: atom, testlist1
	: test
	| testlist1 COMMA test
	;
yield_expr // Used in: pick_yield_expr_testlist, yield_stmt, pick_yield_expr_testlist_comp
	: YIELD testlist
	| YIELD
	;
star_DOT // Used in: pick_dotted_name, star_DOT
	: star_DOT DOT
	| %empty
	;

%%

#include <stdio.h>
void yyerror (const char *s)
{
    if(yylloc.first_line > 0)	{
        fprintf (stderr, "%d.%d-%d.%d:", yylloc.first_line, yylloc.first_column,
	                                     yylloc.last_line,  yylloc.last_column);
    }
    fprintf(stderr, " %s with [%s]\n", s, yytext);
}

