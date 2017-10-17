//Description Unit Tests for Interpreter
#include <gtest\gtest.h>

#include <vector>

// Break encapsulation so can test private member functions
//#define private public
#include "PrisonerStrategyLanguage.h"
#include "Token.h"
#include "SyntaxAnalyser.h"

TEST(SyntaxAnalyser, ValidateArithmeticSubExpressions)
{
	SyntaxAnalyser analyser;
	// Test Some Valid Expression
	std::vector<Token> expression;
	// Variable + Variable
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	EXPECT_TRUE(analyser.IsArithmeticSubExpression(expression));

	// Variable - Integer
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::MINUS));
	expression.push_back(Token(TokenType::INTEGER, 50));
	EXPECT_TRUE(analyser.IsArithmeticSubExpression(expression));

	// Integer + Variable
	expression.clear();
	expression.push_back(Token(TokenType::INTEGER, -12));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::MINUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	EXPECT_TRUE(analyser.IsArithmeticSubExpression(expression));

}

TEST(SyntaxAnalyser, DetectInvalidSubExpressions)
{
	SyntaxAnalyser analyser;
	std::vector<Token> expression;
	// Test character variables
	// Variable + Variable
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	EXPECT_FALSE(analyser.IsArithmeticSubExpression(expression));

	// Variable - Integer
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::MINUS));
	expression.push_back(Token(TokenType::INTEGER, 50));
	EXPECT_FALSE(analyser.IsArithmeticSubExpression(expression));

	// Integer + Variable
	expression.clear();
	expression.push_back(Token(TokenType::INTEGER, -12));
	expression.push_back(Token(TokenType::BINARY_OP, TokenType::BINARY_OP));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::PLUS));
	EXPECT_FALSE(analyser.IsArithmeticSubExpression(expression));


	
	// Variable Variable Variable
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::LASTOUTCOME));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	EXPECT_FALSE(analyser.IsArithmeticSubExpression(expression));

	// Integer Keyword Integer
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::IF));
	expression.push_back(Token(TokenType::INTEGER, 50));
	EXPECT_FALSE(analyser.IsArithmeticSubExpression(expression));

	// Keyword Keyword Keywod
	expression.clear();
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::IF));
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::GOTO));
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::IF));
	EXPECT_FALSE(analyser.IsArithmeticSubExpression(expression));

	// Variable RelOp Variable
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::W));
	EXPECT_FALSE(analyser.IsArithmeticSubExpression(expression));

	// Incorrect Sized Vector
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	EXPECT_FALSE(analyser.IsArithmeticSubExpression(expression));

	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	EXPECT_FALSE(analyser.IsArithmeticSubExpression(expression));

}
//
//
TEST(SyntaxAnalyser, ValidateExpression)
{
	SyntaxAnalyser analyser;
	// Test Some Valid Expression
	std::vector<Token> expression;

	// None-nested Expressions
	// Variable < Variable
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::LESS_THAN));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	EXPECT_TRUE(analyser.IsExpression(expression));

	// Variable > Integer
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Y));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::GREATER_THAN));
	expression.push_back(Token(TokenType::INTEGER, 50));
	EXPECT_TRUE(analyser.IsExpression(expression));

	// Integer = Variable
	expression.clear();
	expression.push_back(Token(TokenType::INTEGER, -12));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	EXPECT_TRUE(analyser.IsExpression(expression));

	// Nested Expressions
	// Integer + Variable < Variable
	expression.clear();
	expression.push_back(Token(TokenType::INTEGER, -12));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::GREATER_THAN));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	EXPECT_TRUE(analyser.IsExpression(expression));

	// Integer + Variable = Variable - Variable
	expression.clear();
	expression.push_back(Token(TokenType::INTEGER, -12));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Y));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::MINUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	EXPECT_TRUE(analyser.IsExpression(expression));

	// Variable > Variable + Integer
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::GREATER_THAN));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Y));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::INTEGER, 6));
	EXPECT_TRUE(analyser.IsExpression(expression));

	// Longer chains
	//Variable + Variable + Variable + Variable = Variable
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Y));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Z));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ITERATIONS));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	EXPECT_TRUE(analyser.IsExpression(expression));

	//Variable = Variable + Variable + Variable + Variable
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Z));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Y));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Z));
	EXPECT_TRUE(analyser.IsExpression(expression));


	//Variable  Variable + Variable = Variable + Variable + Variable
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Z));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Z));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Y));
	EXPECT_TRUE(analyser.IsExpression(expression));

	// LASTOUTCOME = CHARVARIABLE
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::LASTOUTCOME));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::X));
	EXPECT_TRUE(analyser.IsExpression(expression));

	// X = LASTOUTCOME
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::X)); 
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::LASTOUTCOME));
	EXPECT_TRUE(analyser.IsExpression(expression));
}


TEST(SyntaxAnalyser, DetectInvalidExpression)
{
	SyntaxAnalyser analyser;
	std::vector<Token> expression;

	// None-nested Expressions
	// Character Variable + Variable
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	EXPECT_FALSE(analyser.IsExpression(expression));

	// Charcter Variable - Integer
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::LASTOUTCOME));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::INTEGER, 50));
	EXPECT_FALSE(analyser.IsExpression(expression));

	// Variable Variable Variable
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Y));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	EXPECT_FALSE(analyser.IsExpression(expression));

	// Integer Keyword Integer
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::IF));
	expression.push_back(Token(TokenType::INTEGER, 50));
	EXPECT_FALSE(analyser.IsExpression(expression));

	// Keyword Outcome Keywod
	expression.clear();
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::GOTO));
	expression.push_back(Token(TokenType::OUTCOME, TokenValue::BETRAY));
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::IF));
	EXPECT_FALSE(analyser.IsExpression(expression));


	// Incorrect Sized Vector
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	EXPECT_FALSE(analyser.IsExpression(expression));



	// Nested Expressions
	// Keyword + Variable < Variable
	expression.clear();
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::GOTO));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::GREATER_THAN));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	EXPECT_FALSE(analyser.IsExpression(expression));

	// Integer < Variable = Variable - Variable
	expression.clear();
	expression.push_back(Token(TokenType::INTEGER, -12));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::GREATER_THAN));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::GREATER_THAN));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Y));
	EXPECT_FALSE(analyser.IsExpression(expression));

	// Variable + Variable + Integer
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Y));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::INTEGER, 6));
	EXPECT_FALSE(analyser.IsExpression(expression));

	// Variable = Variable =
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Y));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Z));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	EXPECT_FALSE(analyser.IsExpression(expression));

	// Character variable  + Variable = Variable
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Z));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	EXPECT_FALSE(analyser.IsExpression(expression));

	// Variable + Variable > Variable + Chararacter Variable
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Z));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::LASTOUTCOME));
	EXPECT_FALSE(analyser.IsExpression(expression));


	//Variable  Variable + Variable = Variable + CharacterVariable + Variable
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Z));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Z));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_Y));
	EXPECT_FALSE(analyser.IsExpression(expression));

	//TODO: Character Variable RelOp Variable + Variable
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::X));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_X));
	EXPECT_FALSE(analyser.IsExpression(expression));

	// LASTOUTCOME > CHARVARIABLE
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::LASTOUTCOME));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::GREATER_THAN));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::X));
	EXPECT_FALSE(analyser.IsExpression(expression));

	// X < LASTOUTCOME
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::X));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::LESS_THAN));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::LASTOUTCOME));
	EXPECT_FALSE(analyser.IsExpression(expression));
}

TEST(SyntaxAnalyser, TestValidLine)
{
	SyntaxAnalyser analyser;
	

	// IF EXPRESSION GOTO INTEGER
	std::vector<Token> expression;
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::IF));
	expression.push_back(Token(TokenType::INTEGER, -12));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::GREATER_THAN));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::GOTO));
	expression.push_back(Token(TokenType::INTEGER, 30));
	EXPECT_TRUE(analyser.ValidateLine(expression));

	// ACTION
	std::vector<Token> expression2;
	expression2.push_back(Token(TokenType::OUTCOME, TokenValue::BETRAY));
	EXPECT_TRUE(analyser.ValidateLine(expression2));

	expression2.clear();
	expression2.push_back(Token(TokenType::OUTCOME, TokenValue::RANDOM));
	EXPECT_TRUE(analyser.ValidateLine(expression2));

	// IF EXPRESSION OUTCOME
	std::vector<Token> expression3;
	expression3.push_back(Token(TokenType::KEYWORD, TokenValue::IF));
	expression3.push_back(Token(TokenType::INTEGER, -12));
	expression3.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression3.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression3.push_back(Token(TokenType::OUTCOME, TokenValue::SILENCE));
	EXPECT_TRUE(analyser.ValidateLine(expression3));

	// GOTO INT
	std::vector<Token> expression4;
	expression4.push_back(Token(TokenType::KEYWORD, TokenValue::GOTO));
	expression4.push_back(Token(TokenType::INTEGER, 30));
	EXPECT_TRUE(analyser.ValidateLine(expression4));
}


TEST(SyntaxAnalyser, TestInvalidLine)
{
	SyntaxAnalyser analyser;


	// IF GOTO INTEGER
	std::vector<Token> expression;
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::IF));
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::GOTO));
	expression.push_back(Token(TokenType::INTEGER, 30));
	EXPECT_FALSE(analyser.ValidateLine(expression));

	// EXPRESSION GOTO INTEGER
	expression.clear();
	expression.push_back(Token(TokenType::INTEGER, -12));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::GREATER_THAN));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::GOTO));
	expression.push_back(Token(TokenType::INTEGER, 30));
	EXPECT_FALSE(analyser.ValidateLine(expression));

	// IF EXPRESSION INTEGER
	expression.clear();
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::IF));
	expression.push_back(Token(TokenType::INTEGER, -12));
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	expression.push_back(Token(TokenType::INTEGER, 23));



	// KEYWORD
	expression.clear();
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::IF));
	EXPECT_FALSE(analyser.ValidateLine(expression));

	expression.clear();
	expression.push_back(Token(TokenType::KEYWORD, TokenValue::GOTO));
	EXPECT_FALSE(analyser.ValidateLine(expression));

	// OPERATOR
	expression.clear();
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::EQUAL_TO));
	EXPECT_FALSE(analyser.ValidateLine(expression));

	expression.clear();
	expression.push_back(Token(TokenType::BINARY_OP, TokenValue::PLUS));
	EXPECT_FALSE(analyser.ValidateLine(expression));

	// RVALUE
	expression.clear();
	expression.push_back(Token(TokenType::VARIABLE, TokenValue::ALLOUTCOMES_W));
	EXPECT_FALSE(analyser.ValidateLine(expression));

	expression.clear();
	expression.push_back(Token(TokenType::INTEGER, 25));
	EXPECT_FALSE(analyser.ValidateLine(expression));

	// BINOP BINOP


	// BINOP KEYWORD


	// Expression with two consecutive variable

	// Expression with two relational operators

	// Expression with two consecutive binary operators

	// 

	// NEED TO DISTINGUISH CHARACTER FROM VARIABLE
}