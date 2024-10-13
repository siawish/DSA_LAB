#include<iostream>
using namespace std;

template<typename T>
class Queue {
protected:
	int front;
	int rear;
	int size;
	T* arr;

public:
	Queue(int size): size(size) {
		
		front = rear = -1;
		
		arr = new T[size];
	}
	~Queue() {
		delete[] arr;
	}

	bool isFull() {
		return (front == 0 && rear == size-1) || (rear == (front-1)%(size)); 
	}

	bool isEmpty() {
		return front == -1 ;
	}

	void insert(T element) {
		if (isFull()) {
			cout << "\n Queue Overflow.";
			return;
		}
		if (isEmpty()) {
			front = rear = 0;
		}
		else if (rear == size - 1 && front != 0) {
			rear = 0;  
		}
		else {
			rear++;
		}
		arr[rear] = element;
	}

	void remove() {
		if (isEmpty()) {
			cout << "\nQueue Underflow.";
			return;
		}

		if (front == rear) { 
			front = rear = -1; 
		}
		else if (front == size - 1) {
			
			front = 0;
		}
		else {
			front++;
		}
	
		
	}

	T peek() {
		if (isEmpty()) {
			cout << "\n Queue is empty.";
			return T();
		}
		return arr[front];
	}

	
};

class pintQueue : public Queue<int> {
public:
	pintQueue(int size) : Queue (size) {}

	
	void printQueue() {
		cout << "\n Queue status: \n";

		
		for (int i = 0; i < size; i++) {
			if (i == front && i == rear) {
				cout << "  F R  "; 
			}
			else if (i == front) {
				cout << "   F    "; 
			}
			else if (i == rear) {
				cout << "   R   ";  
			}
			else {
				cout << "       "; 
			}
		}
		cout << "\n";

		// Step 2:
		for (int i = 0; i < size; i++) {
			if ((front <= rear && i >= front && i <= rear) || (front > rear && (i >= front || i <= rear))) { 
				cout << "|  " << arr[i] << "  | "; 
			}
			else {
				cout << "|     | ";  //Empty 
			}
		}
		cout << "\n";
	}

	
	void insert(int element) {
		Queue::insert(element);
		printQueue();
	}

	void remove() {
		Queue::remove();
		printQueue();
	}
};
void menu(double size) {
	
	pintQueue q(size);

	q.printQueue();
	int choice;
	do {
		
		cout << "\n\n Queue Operations Menu:";
		cout << "\n 1. Insert Element";
		cout << "\n 2. Remove Element";
		cout << "\n 3. Peek Front Element";
		cout << "\n 4. Exit";
		cout << "\n Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			if (q.isFull()) {
				cout << "\n Queue is full. Cannot insert new element.";
			}
			else {
				int element;
				cout << "\n Enter element to insert: ";
				cin >> element;
				q.insert(element);
				cout << "\n Inserted " << element << " into the queue.";
			}
			break;
		}
		case 2:
			if (q.isEmpty()) {
				cout << "\n\n Queue is empty. Cannot remove element.";
			}
			else {
				q.remove();
				cout << "\n Removed front element from the queue.";
			}
			break;
		case 3:
			if (q.isEmpty()) {
				cout << "\n Queue is empty. No element to peek.";
			}
			else {
				cout << "\n Front element: " << q.peek();
			}
			break;
		case 4:
			cout << "\n Exiting program.";
			break;
		default:
			cout << "\n Invalid choice! Please select a valid option.";
			break;
		}
		
	} while (choice != 4);
}

int main() {
	int queueSize;
	do
	{
		cin.ignore();
		cout << "\n Enter the size of the queue (positive Integer): ";
		cin >> queueSize;
		if (queueSize <= 0) cout << "\n Invalid Size! "; cin.ignore();

	} while (queueSize <= 0);

	

	menu(queueSize);

	return 0;
}
