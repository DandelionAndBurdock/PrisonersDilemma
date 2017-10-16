//Description Unit Tests for Interpreter
#include <gtest\gtest.h>

#include <vector>

// Break encapsulation so can test private member functions
#define private public
#include "PrisonerStrategyLanguage.h"
#include "Lexer.h"

//TODO: Split up tests
TEST(Lexer, CanRecogniseOperations)
{
	Lexer lex;
	// Can recognise  keywords
	EXPECT_TRUE(lex.IsKeyword("IF"));
	EXPECT_TRUE(lex.IsKeyword("GOTO"));

	// Can recognise outcomes
	EXPECT_TRUE(lex.IsOutcome("RANDOM"));
	EXPECT_TRUE(lex.IsOutcome("SILENCE"));

	// Can recognise binary ops
	EXPECT_TRUE(lex.IsBinaryOperation("<"));
	EXPECT_TRUE(lex.IsBinaryOperation("="));
	EXPECT_TRUE(lex.IsBinaryOperation("+"));

	// Can distinguish from variable keywords
	EXPECT_FALSE(lex.IsBinaryOperation("ALLOUTCOMES_Y"));
	EXPECT_FALSE(lex.IsBinaryOperation("X"));
	EXPECT_FALSE(lex.IsBinaryOperation("MYSCORE"));
	EXPECT_FALSE(lex.IsBinaryOperation("LASTOUTCOME"));

	// Can distinguish keywords and outcomes
	EXPECT_FALSE(lex.IsBinaryOperation("IF"));

	// Can distinguish variables and outcomes

	// Can distinguish outcomes and binary ops

	// Can distinguish invalid words and characters
	EXPECT_FALSE(lex.IsBinaryOperation("RANDOM;"));
	EXPECT_FALSE(lex.IsBinaryOperation("IFT"));
	EXPECT_FALSE(lex.IsBinaryOperation("SIL ENCE"));
	EXPECT_FALSE(lex.IsBinaryOperation(","));
	EXPECT_FALSE(lex.IsBinaryOperation("DFS"));


	// Can distinguish case
	EXPECT_FALSE(lex.IsBinaryOperation("if"));
	EXPECT_FALSE(lex.IsBinaryOperation("random"));
	EXPECT_FALSE(lex.IsBinaryOperation("silence"));
	

}

TEST(Lexer, CanRecogniseVariables)
{
	Lexer lex;
	// Can distuinguish from operation keywords
	EXPECT_FALSE(lex.IsVariable("IF"));
	EXPECT_FALSE(lex.IsVariable("RANDOM"));
	EXPECT_FALSE(lex.IsVariable("<"));
	EXPECT_FALSE(lex.IsVariable("SILENCE"));
	EXPECT_FALSE(lex.IsVariable("="));
	EXPECT_FALSE(lex.IsVariable("+"));

	// Can recognise variable keywords
	EXPECT_TRUE(lex.IsVariable("ALLOUTCOMES_Y"));
	EXPECT_TRUE(lex.IsVariable("X"));
	EXPECT_TRUE(lex.IsVariable("MYSCORE"));
	EXPECT_TRUE(lex.IsVariable("LASTOUTCOME"));




	// Can distinguish invalid words and characters
	EXPECT_FALSE(lex.IsVariable("MYSCORE;"));
	EXPECT_FALSE(lex.IsVariable("LASTOUTCOMES"));
	EXPECT_FALSE(lex.IsVariable("XY"));
	EXPECT_FALSE(lex.IsVariable(","));
	EXPECT_FALSE(lex.IsVariable("DFS"));


	// Can distinguish case
	EXPECT_FALSE(lex.IsVariable("alloutcomes_y"));
	EXPECT_FALSE(lex.IsVariable("x"));
	EXPECT_FALSE(lex.IsVariable("myscore"));
	EXPECT_FALSE(lex.IsVariable("lastoutcome"));
}

TEST(Lexer, CanRecogniseValues)
{
	Lexer lex;
	// Can recognise integers
	EXPECT_TRUE(lex.IsInteger("30"));
	EXPECT_TRUE(lex.IsInteger("22"));
	EXPECT_TRUE(lex.IsInteger("0"));

	// Can recognise negative integers
	EXPECT_TRUE(lex.IsInteger("-30"));
	EXPECT_TRUE(lex.IsInteger("-22"));
	EXPECT_TRUE(lex.IsInteger("-0"));

	// Can distuinguish from operation keywords
	EXPECT_FALSE(lex.IsInteger("IF"));
	EXPECT_FALSE(lex.IsInteger("RANDOM"));
	EXPECT_FALSE(lex.IsInteger("<"));
	EXPECT_FALSE(lex.IsInteger("silence"));
	EXPECT_FALSE(lex.IsInteger("="));
	EXPECT_FALSE(lex.IsInteger("+"));

	// Can distinguish Integer keywords
	EXPECT_FALSE(lex.IsInteger("ALLOUTCOMES_Y"));
	EXPECT_FALSE(lex.IsInteger("X"));
	EXPECT_FALSE(lex.IsInteger("MYSCORE"));
	EXPECT_FALSE(lex.IsInteger("LASTOUTCOME"));


	// Can distinguish invalid words and characters
	EXPECT_FALSE(lex.IsInteger("myscore;"));
	EXPECT_FALSE(lex.IsInteger("lastoutcomes"));
	EXPECT_FALSE(lex.IsInteger("XY"));
	EXPECT_FALSE(lex.IsInteger(","));
	EXPECT_FALSE(lex.IsInteger("DFS"));


	// Can distinguish case
	EXPECT_FALSE(lex.IsInteger("alloutcomes_y"));
	EXPECT_FALSE(lex.IsInteger("x"));
	EXPECT_FALSE(lex.IsInteger("myscore"));
	EXPECT_FALSE(lex.IsInteger("lastoutcome"));
}


TEST(Lexer, LexerDecomposeValidTokens)
{
	const std::string testLines[2] = { "IF ALLOUTCOMES_W < ALLOUTCOMES_Z GOTO 30",
									   "IF LASTOUTCOME + 5 = X GOTO 50" };


	const TokenType testOneTypes[] = { TokenType::KEYWORD, TokenType::VARIABLE, TokenType::BINARY_OP, TokenType::VARIABLE, TokenType::KEYWORD, TokenType::INTEGER };
	const TokenType testTwoTypes[] = { TokenType::KEYWORD, TokenType::VARIABLE, TokenType::BINARY_OP, TokenType::INTEGER, TokenType::BINARY_OP, TokenType::VARIABLE, TokenType::KEYWORD, TokenType::INTEGER };
	const TokenValue testOneValues[] = { TokenValue::IF, TokenValue::ALLOUTCOMES_W, TokenValue::LESS_THAN, TokenValue::ALLOUTCOMES_Z, TokenValue::GOTO};
	const TokenValue testTwoValues[] = { TokenValue::IF, TokenValue::LASTOUTCOME, TokenValue::PLUS, static_cast<TokenValue>(5), TokenValue::EQUAL_TO, TokenValue::X, TokenValue::GOTO };


	Lexer lex;
	std::vector<Token> tokens = lex.Tokenise(testLines[0]);
	EXPECT_EQ(tokens.size(), 6); // Should find 6 tokens
	for (int i = 0; i < tokens.size(); ++i){
		EXPECT_EQ(tokens[i].m_type, testOneTypes[i]);
	}
	for (int i = 0; i < tokens.size() - 1; ++i){
		EXPECT_EQ(tokens[i].m_value, testOneValues[i]);
	}
	EXPECT_EQ(tokens[5].m_value, 30);

	tokens.clear();
	tokens = lex.Tokenise(testLines[1]);
	EXPECT_EQ(tokens.size(), 8); 
	for (int i = 0; i < tokens.size(); ++i){
		EXPECT_EQ(tokens[i].m_type, testTwoTypes[i]);
	}
	for (int i = 0; i < tokens.size() -1; ++i){
		EXPECT_EQ(tokens[i].m_value, testTwoValues[i]);
	}
	EXPECT_EQ(tokens[7].m_value, 50);



}