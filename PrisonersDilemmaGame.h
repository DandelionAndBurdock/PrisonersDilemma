#pragma once
//TODO: Put in namespace
enum ActionType { BETRAY, SILENCE, GOTO };
struct Action{
	Action(ActionType a, int line = -1) :
		m_action(a), m_line(line){}

	ActionType  m_action;
	int		m_line;		// If GOTO holds the line
};
