#include "Token.h"

Token::Token(TokenType type, int value, std::string error) :
m_type(type), m_value(value), m_error(error)
{}



bool Token::IsBinOp() const{
	return (IsRelOp() || IsArithmeticOp());
}

bool Token::IsRelOp() const{
	return (m_value == TokenValue::LESS_THAN ||
		    m_value == TokenValue::GREATER_THAN ||
		    TokenValue::EQUAL_TO);
}
bool Token::IsArithmeticOp() const{
	return (m_value == TokenValue::PLUS ||
		m_value == TokenValue::MINUS);
}

// Note: In PSL character variables e.g. LASTOUTCOME should not be used as RValues.
bool Token::IsRValue() const{
	return (m_type == TokenType::INTEGER ||
		(m_type == TokenType::VARIABLE &&
		!IsCharVariable()));
}

bool Token::IsOutcome() const{
	return (m_type == TokenType::OUTCOME);
}

bool Token::IsAction() const{
	return (m_value == TokenValue::GOTO ||
		IsOutcome());
}

bool Token::IsCharVariable() const{
	return (m_value == TokenValue::LASTOUTCOME ||
		    m_value == TokenValue::W ||
		    m_value == TokenValue::X ||
		    m_value == TokenValue::Y ||
		    m_value == TokenValue::Z);
}