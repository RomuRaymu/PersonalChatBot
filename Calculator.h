#include <fstream>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cstring>
#include <math.h>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#define OPERATOR_PLUS '+'
#define OPERATOR_MINUS '-'
#define OPERATOR_MULTIPLY '*'
#define OPERATOR_DIVISION '/'
#define OPERATOR_SQUARE '^'
#define OPERATOR_FACTORIAL '!'

#define OPERATOR_LOGSTART 'l'
#define OPERATOR_ROOTSTART 'r'

#define OPERATOR_SINSTART 's'
#define OPERATOR_COSSTART 'c'
#define OPERATOR_TANSTART 't'
#define OPERATOR_ARCSTART 'a'

#define OPERATOR_NONE ' '

#define PARENTHESIS_1_LEFT '('
#define PARENTHESIS_1_RIGHT ')'
#define PARENTHESIS_2_LEFT '{'
#define PARENTHESIS_2_RIGHT '}'
#define PARENTHESIS_3_LEFT '['
#define PARENTHESIS_3_RIGHT ']'

#define OPERAND_PI1 'p'
#define OPERAND_PI2 'i'
#define OPERAND_E 'e'

class Calculator {
private:
    static bool CalculateStack(stack<double> &calStack, stack<char> &operStack,
                               char operators);
    static bool Cal(stack<double> &calStack, stack<char> &operStack);
    static bool Operate(char operators, double operand1, double operand2, double &result);

    static bool IsDigit(char c);
    static bool IsParenthesisLeft(char c);
    static bool IsParenthesisRight(char c);
    static int IsOperatorPrecedenceHigher(char c);

    static char GetMatchParenthesis(char c);
    static double GetNumber(string formula, int &index);

    static bool CalculateFactorial(stack<double> &calStack);
    static bool CalculateLog(string formula, int &index, double &result);
    static bool CalculateRoot(string formula, int &index, double &result);
    static bool CalculateTrigonometric(string formula, int &index,
                                       double &result);
    static bool CalculateParenthesisFormula(string formula, int &index,
                                            double &result);

public:
    static int CalculateFormula(string formula, double &result);
};
