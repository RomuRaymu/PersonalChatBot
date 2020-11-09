#include "Calculator.h"

int main(void) {
	//string formula = "3 +4 -(3*5)^2a-2";
	//string formula = "2*3^2";
	//string formula = "3(-(3+2)!)^2";
	//string formula = "3-(-(3+2)!)^2";
	//string formula = "-(3+2)";
	//string formula = "(1-(3+2))";
	//string formula = "3-(-4)";
	//string formula = "3*-(2+5)";
	//string formula = "3+-(2+5)";
	//string formula = "3-(-4)";
	//string formula = "3*-3";

	//string formula = "3+(-(2+5*3)*5)";
	//string formula = "3+(-(2+5*3)*-5)";

	//string formula = "3+5!";
	//string formula = "3 5!";
	//string formula = "3 5*!";
	
	//string formula = "ln(10*10)";
	string formula = "log(10*100)";
	//string formula = "log(10^100)";

	//string formula = "r(100)";
	//string formula = "root(100)";
	//string formula = "r(100*4)";
	//string formula = "log(10^10)*r(100*4)";

	//string formula = "pi";
	//string formula = "3pi";
	//string formula = "3*pi-3";

	//string formula = "e";
	//string formula = "ln(e*3)";
	//string formula = "ln(e^3)";

	//string formula = "sin(2/r(pi))";
	//string formula = "sin(pi/2)";
	//string formula = "cos(pi)";
	//string formula = "atan(0.8)";
	//string formula = "sin(pi/6)";
	//string formula = "sin(pi/atan(r(3)))";
	//string formula = "tan(3pi/4)";
	
	double val;


	switch (Calculator::CalculateFormula(formula, val)) {
	case -1:
		cout << "Err" << endl;
		break;
	case 0:
		cout << "Formula Err" << endl;
		break;
	case 1:
		cout << val << endl;
		break;
	}

}
