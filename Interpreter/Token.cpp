#include "Token.h"
#include <iostream>

Token::Token(TokenType type, int value, std::string error) :
m_type(type), m_value(value), m_error(error)
{}

std::ostream& operator<<(std::ostream& os, const Token& t){
	os << t.GetValue() << std::endl;
	return os;
}

bool Token::IsBinOp() const{
	return (m_type == TokenType::BINARY_OP);
}

bool Token::IsRelOp() const{
	return (m_value == TokenValue::LESS_THAN ||
		    m_value == TokenValue::GREATER_THAN ||
		    m_value == TokenValue::EQUAL_TO);
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

bool Token::IsCharResult() const{

	return (m_value == TokenValue::A ||
			m_value == TokenValue::B ||
			m_value == TokenValue::C ||
			m_value == TokenValue::W ||
			m_value == TokenValue::X ||
			m_value == TokenValue::Y ||
			m_value == TokenValue::Z);
}

bool Token::IsCharVariable() const{
	return (m_value == TokenValue::LASTOUTCOME ||
		    IsCharResult());
}

bool Token::IsVariable() const{
	return (m_type == TokenType::VARIABLE);
}

//TODO: CLean this up LASTOUTCOME included in RValue
//TODO: Variable - RValue() still using