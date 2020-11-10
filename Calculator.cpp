#include "Calculator.h"


// 계산
double Calculator::Operate(char operators, double operand1, double operand2) {
	switch (operators) {
	case OPERATOR_PLUS:
		return operand1 + operand2;
	case OPERATOR_MINUS:
		return operand1 - operand2;
	case OPERATOR_MULTIPLY:
		return operand1 * operand2;
	case OPERATOR_DIVISION:
		return operand1 / operand2;
	case OPERATOR_SQUARE:
		return pow(operand1, operand2);
	}

	return 0;
}


// 오른쪽 괄호와 연산자를 계산
bool Calculator::CalculateStack(stack<double> &calStack, stack<char> &operStack, char operators) {
	switch (operators) {
	case PARENTHESIS_1_RIGHT:
	case PARENTHESIS_2_RIGHT:
	case PARENTHESIS_3_RIGHT:

		while (!operStack.empty() && operStack.top() != GetMatchParenthesis(operators)) {
			if (!Cal(calStack, operStack))
				return false;
		}
		if (operStack.empty())
			return false;
		operStack.pop();
		return true;

	case OPERATOR_SQUARE:
		if (!operStack.empty()) {
			if (!IsParenthesisLeft(operStack.top())) {
				if (IsOperatorPrecedencHigher(operStack.top()) == 2) {
					if (!Cal(calStack, operStack))
						return false;
				}
			}
		}
		break;
	case OPERATOR_MULTIPLY:
	case OPERATOR_DIVISION:
		if (!operStack.empty()) {
			if (!IsParenthesisLeft(operStack.top())) {
				if (IsOperatorPrecedencHigher(operStack.top()) >= 1) {
					if (!Cal(calStack, operStack))
						return false;
				}
			}
		}
		break;
	case OPERATOR_PLUS:
	case OPERATOR_MINUS:
		if (!operStack.empty()) {
			if (!IsParenthesisLeft(operStack.top())) {
				while (!operStack.empty() &&
					!IsParenthesisLeft(operStack.top())) {
					if (!Cal(calStack, operStack))
						return false;
				}
			}
		}
		break;
	}

	operStack.push(operators);
	return true;
}

bool Calculator::CalculateFactorial(stack<double> &calStack) {
	double val = calStack.top();
	calStack.pop();

	if (val < 1) {
		return false;
	}

	double result = 1;
	for (int i = 2; i <= val; i++) {
		result *= i;
	}
	calStack.push(result);

	return true;
}

// Operand Stack의 Operand 2개와, Operator Stack의 Operator 1개를 계산
bool Calculator::Cal(stack<double> &calStack, stack<char> &operStack) {
	double val1, val2;
	if (calStack.size() < 2 || operStack.empty())
		return false;

	val2 = calStack.top();
	calStack.pop();
	val1 = calStack.top();
	calStack.pop();
	calStack.push(Operate(operStack.top(), val1, val2));

	operStack.pop();
	return true;
}

// 왼쪽 괄호인지 확인
bool Calculator::IsParenthesisLeft(char c) {
	switch (c) {
	case PARENTHESIS_1_LEFT:
	case PARENTHESIS_2_LEFT:
	case PARENTHESIS_3_LEFT:
		return true;
	}
	return false;
}

// 오른쪽 괄호인지 확인
bool Calculator::IsParenthesisRight(char c) {
	switch (c) {
	case PARENTHESIS_1_RIGHT:
	case PARENTHESIS_2_RIGHT:
	case PARENTHESIS_3_RIGHT:
		return true;
	}
	return false;
}

int Calculator::IsOperatorPrecedencHigher(char c) {
	int i = 0;
	if (c == OPERATOR_MULTIPLY || c == OPERATOR_DIVISION)
		i = 1;
	else if (c == OPERATOR_SQUARE)
		i = 2;
	return i;
}

// 인자로 받은 괄호와 맞는 짝을 반환
char Calculator::GetMatchParenthesis(char c) {
	switch (c) {
	case PARENTHESIS_1_LEFT:
		return PARENTHESIS_1_RIGHT;
	case PARENTHESIS_1_RIGHT:
		return PARENTHESIS_1_LEFT;
	case PARENTHESIS_2_LEFT:
		return PARENTHESIS_2_RIGHT;
	case PARENTHESIS_2_RIGHT:
		return PARENTHESIS_2_LEFT;
	case PARENTHESIS_3_LEFT:
		return PARENTHESIS_3_RIGHT;
	case PARENTHESIS_3_RIGHT:
		return PARENTHESIS_3_LEFT;
	}
	return 0;
}


double Calculator::GetNumber(string formula, int &index) {
	size_t sz;
	double num = stod(formula.substr(index).c_str(), &sz);
	index += sz - 1;
	return num;
}


bool Calculator::CalculateLog(string formula, int &index, double& result) {
	if (index + 2 < formula.size() && tolower(formula[index + 1]) == 'n') { // ln
		index += 2;
		double val = 0;
		if (CalculateParenthesisFormula(formula, index, val)) {
			if (val <= 0) // Log 음수
				return false;
			result = log(val);
			return true;
		}
	}
	else if (index + 3 < formula.size() && tolower(formula[index + 1]) == 'o' && tolower(formula[index + 2]) == 'g') { // log
		index += 3;
		double val = 0;
		if (CalculateParenthesisFormula(formula, index, val)) {
			if (val <= 0) // Log 음수
				return false;
			result = log10(val);
			return true;
		}
	}
	return false;
}

bool Calculator::CalculateRoot(string formula, int &index, double& result) {
	if (index + 4 < formula.size() && strcasecmp(formula.substr(index, 4).c_str(), "root") == 0) { // root
		index += 4;
		double val = 0;
		if (CalculateParenthesisFormula(formula, index, val)) {
			if (val <= 0) // root 음수
				return false;
			result = sqrt(val);
			return true;
		}
	}
	else { // r
		index += 1;
		double val = 0;
		if (CalculateParenthesisFormula(formula, index, val)) {
			if (val <= 0) // root 음수
				return false;
			result = sqrt(val);
			return true;
		}
	}
	return false;
}

bool Calculator::CalculateParenthesisFormula(string formula, int &index, double& result) {
	if (!IsParenthesisLeft(formula[index]))
		return false;

	int parenthesisCount = 0;
	for (int i = index; i < formula.size(); i++) {
		if (IsParenthesisLeft(formula[i])) {
			parenthesisCount++;
		}
		else if (IsParenthesisRight(formula[i])) {
			if (--parenthesisCount == 0) {
				if (CalculateFormula(formula.substr(index + 1, i - index - 1), result) == 1) {
					index = i;
					return true;
				}
			}
		}
	}

	return false;
}

bool Calculator::CalculateTrigonometric(string formula, int &index, double& result) {
	bool isArc = (tolower(formula[index]) == OPERATOR_ARCSTART);
	if (isArc)
		index++;

	if (index + 5 >= formula.size())
		return false;

	switch (tolower(formula[index])) {
	case OPERATOR_SINSTART:
		if (strcasecmp(formula.substr(index, 3).c_str(), "sin") == 0) {
			index += 3;
			double val = 0;
			if (CalculateParenthesisFormula(formula, index, val)) {
				if (isArc)
					result = asin(val);
				else
					result = sin(val);
				return true;
			}
		}
		break;
	case OPERATOR_COSSTART:
		if (strcasecmp(formula.substr(index, 3).c_str(), "cos") == 0) {
			index += 3;
			double val = 0;
			if (CalculateParenthesisFormula(formula, index, val)) {
				if (isArc)
					result = acos(val);
				else
					result = cos(val);
				return true;
			}
		}
		break;
	case OPERATOR_TANSTART:
		if (strcasecmp(formula.substr(index, 3).c_str(), "tan") == 0) {
			index += 3;
			double val = 0;
			if (CalculateParenthesisFormula(formula, index, val)) {
				if (isArc)
					result = atan(val);
				else
					result = tan(val);
				return true;
			}
		}
		break;
	}

	return false;
}

bool Calculator::IsDigit(char c) {
	return ('0' <= c && c <= '9');
}



/*
	* -1 : Not Formula
	*  0 : Formula Error
	*  1 : Correct
	*/
int Calculator::CalculateFormula(string formula, double &result) {
	stack<double> calculateStack;
	stack<char> operatorStack;
	bool isOperatorStacked = true;

	int index;
	double calValue = 0;
	for (index = 0; index < formula.size(); ++index) {
		char val = tolower(formula[index]);
		switch (val) {
		case PARENTHESIS_1_LEFT:
		case PARENTHESIS_2_LEFT:
		case PARENTHESIS_3_LEFT:
			operatorStack.push(val);
			isOperatorStacked = true;
			continue;
		case OPERATOR_PLUS:
		case OPERATOR_MINUS:
			if (isOperatorStacked) {
				if (index + 1 < formula.size()) {
					if (IsDigit(formula[index + 1])) {
						double val = GetNumber(formula, index);
						calculateStack.push(((val) == OPERATOR_MINUS) ? -val : val);
						isOperatorStacked = false;
						continue;
					}
					else if (IsParenthesisLeft(formula[index + 1])) {
						calculateStack.push(-1);
						operatorStack.push(OPERATOR_MULTIPLY);
						continue;
					}
				}
			}

		case PARENTHESIS_1_RIGHT:
		case PARENTHESIS_2_RIGHT:
		case PARENTHESIS_3_RIGHT:

		case OPERATOR_MULTIPLY:
		case OPERATOR_DIVISION:
		case OPERATOR_SQUARE:
			if (!CalculateStack(calculateStack, operatorStack, val))
				return 0;
			isOperatorStacked = true;
			continue;

		case OPERATOR_FACTORIAL:
			if (isOperatorStacked || !CalculateFactorial(calculateStack))
				return 0;
			continue;

		case OPERATOR_LOGSTART:
			if (!isOperatorStacked || !CalculateLog(formula, index, calValue))
				return 0;
			calculateStack.push(calValue);
			isOperatorStacked = false;
			continue;

		case OPERATOR_ROOTSTART:
			if (!isOperatorStacked || !CalculateRoot(formula, index, calValue))
				return 0;
			calculateStack.push(calValue);
			isOperatorStacked = false;
			continue;

		case OPERATOR_SINSTART:
		case OPERATOR_COSSTART:
		case OPERATOR_TANSTART:
		case OPERATOR_ARCSTART:
			if (!isOperatorStacked || !CalculateTrigonometric(formula, index, calValue))
				return 0;
			calculateStack.push(calValue);
			isOperatorStacked = false;
			continue;


		case OPERAND_PI1:
			if (index + 1 < formula.size()) {
				if (tolower(formula[++index]) == OPERAND_PI2) {
					if (isOperatorStacked)
						calculateStack.push(M_PI);
					else {
						calValue = calculateStack.top()*M_PI;
						calculateStack.pop();
						calculateStack.push(calValue);
					}
					isOperatorStacked = false;
					continue;
				}
			}

			return 0;

		case OPERAND_E:
			calculateStack.push(M_E);
			isOperatorStacked = false;
			continue;
		}

		if (IsDigit(formula[index])) {
			calculateStack.push(GetNumber(formula, index));
			isOperatorStacked = false;
			continue;
		}

		if (val != OPERATOR_NONE) {
			break;
		}
	}

	// 남은 식 계산
	while (!(calculateStack.size() == 1 && operatorStack.empty())) {
		if (!Cal(calculateStack, operatorStack))
			break;
	}
	//계산이 올바르게 됨
	if (calculateStack.size() == 1 && operatorStack.empty()) {
		result = calculateStack.top();
		return 1;
	}

	return 0;
}
