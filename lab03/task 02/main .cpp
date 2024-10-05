#include<iostream>
#include<string>
using namespace std;

void input(double& a, double& b) {
	cout << "\n Enter two numbers seperated by space: ";
	cin >> a >> b;

	if (a < 0) {
		a *= -1;
	}
	if (b < 0) b *= -1;
}
double multipl(double& a, double& b) {

	if (a == 0 || b == 0) {
		return 0;
	}
	else if (b == 1) {
		return a;
	}
	else if (a == 1) {
		return b;
	}
	b--;
	return a + multipl(a, b );
}

double powe(double& num, double& exponent) {

	if (exponent == 0) {
		return 1;
	}
	else if (num == 0) {
		return 0;
	}
	else if (exponent == 1) {
		return num;
	}
	return num * (powe(num, --exponent));
}
bool isDigit(const string& str) {
	return (str == "1" || str == "2");
}
void menu() {
	cout << "\n select an option "
		<< "\n 1. multiplication. "
		<< "\n 2. power. " << endl << "option: ";
}
int main()
{
	string option;
	do {
		system("CLS");
		double a, b;
		menu();
		
		cin >> option;
		while (!isDigit(option)) {
			system("CLS");
			cout << "\n Invalid! \n Try Again."<<endl;
				cout<<" \n (select between 1 and 2): "<<endl;
				menu();

			cin.ignore();
			cin >> option;
		}

		input(a, b);
		switch (stoi(option)) {
		case 1:
			cout << "\n " << a << " x " << b << " = " << multipl(a, b);
			break;
		case 2:
			cout << "\n " << a << " ^ " << b << " = " << pow(a, b);
			break;
		}
		cout << "\n Do you want to continue to menu: (Press ""y"" || ""Y"") ";
		cin >> option;
	} while (option=="Y"|| option == "y");
}