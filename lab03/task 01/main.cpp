#include<iostream>
#include<string>
#include<stack>


using namespace std;


bool isOpr(char& c) { return  c == '+' || c == '-' || c == '*' || c == '/' || c == '^'; }

bool isBracketO(char& c) { return  c == '(' || c == '{' || c == '['; }

bool isBracketC(char& c) { return  c == ')' || c == '}' || c == ']'; }

bool balanced(string& expression) {
	stack<char>s;
	for (int i = 0; i < expression.length(); i++) {
		if (isBracketO(expression[i])) {
			s.push(expression[i]);
		}
		else if (expression[i] == ')' && !s.empty() && s.top() == '(') {
			s.pop();
		}
		else if (expression[i] == '}' && !s.empty() && s.top() == '{') {
			s.pop();
		}
		else if (expression[i] == ']' && !s.empty() && s.top() == '[') {
			s.pop();
		}
		else if (isBracketC(expression[i])) {
			return false;
		}

	}
	return s.empty();

}
 
int charToInt(char& c) { return (c - '0'); }

bool isAlpha(char& c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

bool isDigit(char& c) { return (c >= '0' && c <= '9'); }

void removeSpaces(string& expression) {
	string temp;
	for (char i : expression) {
		if (i != ' ') temp += i;
	}
	expression = temp;
}

void input(string& expression) {

	bool check = 1;

	while (check)
	{
		check = 0;

		cout << "\n Enter an Expression: ";
		cin.ignore();
		getline(cin, expression);

		if (balanced(expression)) {
			removeSpaces(expression);
		}
		else
		{
			cout << "\n !!!!!Unbalanced Expression!!!!!!";
			cout << "\n Do you want to enter an expression again (Press Y or y) to continue.";
			char ch;
			cin >> ch;
			if (ch == 'y' || ch == 'Y') {
				check = 1;
			}
		}
	}
}

void power(int& num, int& pwr) {
	if (pwr == 0) {
		num=1;
		return;
	}
	else if (pwr == 1) {
		return;
	}
	int temp = num;
	pwr--;
	power(num, pwr);
		
	num *= temp;
}

int precedence(char& c) {
	if (c == '^') {
		return 5;
	}
	else if (c == '/') {
		return 4;
	}
	else if (c == '*') {
		return 3;
	}
	else if (c == '+') {
		return 2;
	}
	else if (c == '-') {
		return 1;
	}
	return -1;
}

void reverseString(string& str) {
	stack<char>s;

	for (int i = 0; i < str.length(); i++) {
		s.push(str[i]);
	}
	int i = 0;
	while(!s.empty()) {

		str[i] = s.top();
		s.pop();
		i++;
	}
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(') str[i] = ')';
		else if (str[i] == ')') str[i] = '(';

		else if(str[i] == '{') str[i] = '}';
		else if (str[i] == '}') str[i] = '{';

		else if (str[i] == '[') str[i] = ']';
		else if (str[i] == ']') str[i] = '[';
	}
	return;
}

//infix-To-Postfix
void infixToPostfix(string& expression) {
	stack<char>s;
	
	string resultant ;
	
	for (int i = 0; i < expression.length(); i++) {

		if (isBracketO(expression[i])) {
			s.push(expression[i]);
		}
		else if (isAlpha(expression[i])) {
				resultant += expression[i];
		}
		else if (isOpr(expression[i])) {
			while (!s.empty() && precedence(s.top()) >= precedence(expression[i]) && !(isBracketO(s.top()))) {
				resultant += s.top();
				s.pop();
			}
			s.push(expression[i]);
		}
		else if (isBracketC(expression[i])) {
			char openBracket = (expression[i] == ')') ? '(' : (expression[i] == '}') ? '{' : '[';

			
			while (!s.empty() && s.top() != openBracket) {
				resultant += s.top();
				s.pop();
			}
			s.pop();
		}
		else
		{
			cout << "\n Invalid! Input. ";
			return ;
		}
	}
	while (!s.empty()) {
			resultant += s.top();
			s.pop();
	}
	
	expression = resultant;

}
//infix-To-Prefix
void infixToPrefix(string& expression) {
	//Step 1:
	reverseString(expression);
	
	//Step 2:
	infixToPostfix(expression);
	
	//Step 3:
	reverseString(expression);

	cout << "\n Conversion of infix to prefix expression: " << expression;

	cout << "\n Do you want to continue with infix to prefix (Press Y or y) to continue.";
	char ch;
	cin >> ch;
	if (ch == 'y' || ch == 'Y') {
		system("CLS");
		cout << "\n ----infix to prefix----";
		input(expression);
		infixToPrefix(expression);
	}

}

//evaluation
void evaluatePostfix(string& expression)  {
	stack<int>s;

	for (int i = 0; i < expression.length(); i++) {
		if (isDigit(expression[i])) {
			s.push(charToInt(expression[i]));//
		}
		else if (isOpr(expression[i])) {
			if (s.size() < 2) {
				cout << "\n Insufficient operands for operator: ";
				return;
			}
			int num = s.top();
			s.pop();

			if (expression[i] == '+') {
				s.top() += num;
			}
			else if (expression[i] == '-') {
				s.top() -= num;
			}
			else if (expression[i] == '*') {
				s.top() *= num;
			}
			else if (expression[i] == '/') {
				if (s.top() != 0) {
					s.top() /= num;
				}
				else {
					cout << "\n Division by zero error! ";
					return;
				}
			}
			else if (expression[i] == '^') {
				power(num, s.top());
				s.top() = num;
			}
		}
	}
	if (s.size() != 1) {
		cout << "\n Error: Invalid postfix expression.";
		return;
	}
	expression = to_string(s.top());
}

void evaluatePrefix(string& expression) {
	//Step 1:
	reverseString(expression);

	//Step 2:
	evaluatePostfix(expression);

	cout << "\n Evaluation of Prefix expression: " << expression << endl;

	cout << "\n Do you want to continue with evaluation of prefix expression (Press Y or y) to continue.";
	char ch;
	cin >> ch;
	if (ch == 'y' || ch == 'Y') {
		system("CLS");
		cout << "\n --------PREFIX------";
		input(expression);
		evaluatePrefix(expression);
	}
	return;
}

//menu
void menu(int option) {
	cout << "\n     -: MENU :- "
		<< "\n 1. INFIX to POSTFIX. "
		<< "\n 2. INFIX to PREFIX. "
		<< "\n 3. Evaluation of postfix expression. "
		<< "\n 4. Evaluation of prefix expression. " 
		<<"\n 5. Exit. " << endl;
	cout << "\n option: ";
	cin >> option;

	string expression;

	switch (option) {
	case 1:
		//postfix
		input(expression);

		infixToPostfix(expression);
		cout << "\n Conversion of infix to postfix expression: " << expression;

		cout << "\n Do you want to continue with infix to postfix (Press Y or y) to continue.";
		char ch;
		cin >> ch;
		if (ch == 'y' || ch == 'Y') {
			system("CLS");
			cout << "\n ----infix to postfix----";
			input(expression);
			infixToPostfix(expression);
			cout << "\n Conversion of infix to postfix expression: " << expression;
		}
		break;
	case 2:
		//prefix
		input(expression);

		infixToPrefix(expression);

		break;
	case 3:
		input(expression);

		evaluatePostfix(expression);
		
		cout << "\n Evaluation of postfix expression: " << expression<<endl;

		cout << "\n Do you want to continue with Postfix evaluation (Press Y or y) to continue.";
		char a;
		cin >> a;
		if (a == 'y' || a == 'Y') {
			system("CLS");
			cout << "\n ----infix to prefix----" << endl;
			input(expression);
			evaluatePostfix(expression);
			cout << "\n Evaluation of postfix expression: " << expression;
		}

		break;
	case 4:
		input(expression);

		evaluatePrefix(expression);
		
		break;
	case 5:
	system("CLS");
	cout << "\n Exiting the program..." << endl;
		exit(0);
	default:
		cout << " INVALID OPTION !";
	}
}

int main() {

	int option = 0;
	do {
		system("CLS");
		menu(option);

		cout << "\n\n Do you want to continue to Menu (Press ""1""): ";
		cin.ignore();
		cin >> option;

	} while (option == 1);

	return 0;
}

