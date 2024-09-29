#include<iostream>
#include<string>
using namespace std;

template<typename T> 
class Stack {
private:
	int top;
	T* arr;
	int size;
public:

	Stack(T size): size(size) {
		arr = new T[size];
		this->top = -1;
	}

	int itop() {
		if (isEmpty()) {
			cout << "stack is empty";
		}
		return arr[top];
	}
	bool isEmpty() {
		return top == -1 ? true : false;
	}
	void push(T element)
	{
		if (isFull()) {
			cout << " Stack Overflow. ";
			return;
		}
		else
			top++;
		arr[top] = element;
	}
	void pop() {
		if (isEmpty()) {
			cout << "Stack Underflow";
		}
		top--;
	}
	bool isFull() {
		return top == size - 1 ? true : false;
	}

	};
bool isPalindrome(string str)
{
	int size = str.length();
	Stack <char> s(size);
	


	//pushing string to stack
	for (int i = 0; i < size; i++) {
		s.push(str[i]);
	}
	for (int i = 0; i < size; i++) {
		
		if (s.itop() == str[i]) {
			s.pop();
			
		}
		else
			return false;
	}
	if (s.isEmpty()) {
		return true;
	}
	else {
		return false;
	}
}
int main() {
	string str;

	cout << "\nEnter a string :";
	getline(cin, str);


	if (isPalindrome(str)) {
		cout << str << " is a palindrome.";
	}
	else
		cout << str << " is not a palindrome. ";
	
	return 0;
	
}