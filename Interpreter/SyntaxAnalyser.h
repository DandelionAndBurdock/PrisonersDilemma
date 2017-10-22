// Class: Syntax Analyser
// Description: A class handling the checking
// a line of tokens follows the rules of the language
// Author: Philip Jones
// Date: 15/10/2017
#pragma once

// Standard Library Includes
#include <vector>

#include "Token.h"


class SyntaxAnalyser
{
public:
	SyntaxAnalyser();
	~SyntaxAnalyser();

	// Returns true if the given triplet is a valid subexpression
	// A subexpression is V1 BINOP V2 where V1 and V2 are either variables
	// or (integer) values and BINOP is a binary arithmetic operator
	bool static IsArithmeticSubExpression(const std::vector<Token>& provisional);
	// Returns true if the given triplet is a valid conditional expression
	// A conditional expression is V1 RELOP V2 where V1 and V2 are either variables
	// or (integer) values and RELOP is a relational operator
	bool static IsConditionalSubExpression(const std::vector<Token>& provisional);

	// Returns true if the provisional expression has the form S1 RELOP S2 where 
	// S1 and S2 are subexpressions and RELOP is a relational operator
	bool static IsExpression(const std::vector<Token>& provisional);

	// Returns true if provisional line of tokens is valid in the
	// Prisoner Stategy Language
	bool static ValidateLine(const std::vector<Token>& provisional);

private:
	enum class ErrorCode { EMPTY, DANGLING_BINARY, DANGLING_VARIABLE, INVALID_GOTO, INVALID_OUTCOME, INVALID_IF, INVALID_KEYWORD, OTHER };//TODO: Comment
	// Returns true if the provisional expression is of the form 
	// LASTOUTCOME = CharacterVariable or CharacterVariable = LASTOUTCOME
	bool static TestCharExpressionFormat(const std::vector<Token>& provisional) ;

	// Returns true if provsional expression alternates between a variable and a binary operation
	// and has only one relational operator. 
	bool static TestNonCharExpressionFormat(const std::vector<Token>& provisional); //TODO: Rename IsValid

	// Rule testing functions:
	// Rule 1: Returns true if provisional line is empty
		bool static IsEmptyLine(const std::vector<Token>& provisional);
		// Rule 2: Returns true if a binary operator starts or end a line
		bool static IsDanglingBinaryOp(const std::vector<Token>& provisional);
	// Rule 3: Returns true if line starts or ends with a variable or starts with an integer
		bool static IsDanglingVariable(const std::vector<Token>& provisional);
	// Rule 4: Returns true if GOTO is followed by an integer (only)
		bool static IsValidGOTO(const std::vector<Token>& provisional);
	// Rule 5: Returns true if nothing follows an outcome
		bool static IsValidOutcome(const std::vector<Token>& provisional);
	// Rule 6: Returns true if IF keyword is followed by a valid expression and then an action
		bool static IsValidIf(const std::vector<Token>& provisional);

	// Prints syntax errors to the console
		void static PrintError(const ErrorCode& error);
};

