// Class: Token
// Description: Class representing basic components of source code
// Author: Philip Jones
// Date: 15/10/2017
#pragma once

#include <string>

#include "../PrisonerStrategyLanguage.h" // Contains possible token types available in PSL
struct Token {
	Token(TokenType type, int value, std::string error = "");
	friend std::ostream& operator<<(std::ostream&, const Token&);


	// Returns true if the token is a binary operation
	bool IsBinOp() const;
	// Returns true if the token is a relational operation
	bool IsRelOp() const;
	// returns true if the token is a a binary arithmetic operator
	bool IsArithmeticOp() const;
	// Returns true if the token is a non-character variable or (integer) value.
	bool IsRValue() const;
	// Returns true if the token is an outcome (BETRAY, RANDOM, SILENCE)
	bool IsOutcome() const;
	// Returns true if the token is an action (GOTO or BETRAY, RANDOM, SILENCE)
	bool IsAction() const;
	// Returns true if the token is a character variable (LASTOUTCOME, W, X, Y, Z)
	bool IsCharVariable() const;
	// Returns true is possible value for last action (W, X, Y, Z)
	bool IsCharResult() const;
	// Returns true if is a variable
	bool IsVariable() const;


	inline TokenType   GetType()  const { return m_type; }
	inline int         GetValue() const { return m_value; }
	inline std::string GetError() const { return m_error; }
private:
	TokenType   m_type;			// Type of Token e.g. LESS_THAN, VARIABLE
	int			m_value;
	std::string m_error;		// Used to hold error messages for invalid tokens	
};


//TODO:Make private
//TODO: Inline(?)