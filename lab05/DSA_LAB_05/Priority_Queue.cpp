#include<iostream>
#include<iomanip>
using namespace std;
class Node {
private:
	int data;
	Node* next;
public:
	Node(int data = 0) : data(data), next(NULL) {}

	~Node() {
		cout << "Deleting node with data: " << data << endl;
	}

	Node* getNext() {
		return next;
	}

	void setNext(Node* nextNode) {
		next = nextNode;
	}

	int getData() {
		return data;
	}

	void setData(int newData) {
		data = newData;
	}
};

class LinkedList {
	Node* head;
	Node* tail;
public:
	LinkedList() : head(NULL), tail(NULL) {}

	~LinkedList() {
		Node* current = head;
		while (current != NULL) {
			Node* nextNode = current->getNext();
			delete current;
			current = nextNode;
		}
	}
	void addAtHead(Node* NewNode) {
		if (head == NULL) {
			head = tail = NewNode;
		}
		else
		{
			NewNode->setNext(head);
			head = NewNode;
		}
		return;
	}

	void addATail(Node* NewNode) {
		if (head == NULL) {
			head = tail = NewNode;
			return;
		}
		else
		{
			tail->setNext(NewNode);
			tail = NewNode;
		}
	}

	void removeFromHead() {
		if (head == NULL) {
			cout << "\n Linked List is empty. ";
			return;
		}
		else
		{
			Node* current = head;
			head = head->getNext();
			delete current; 
		}
		if (head == NULL) {
			tail = NULL;
			return;
		}
	}
	void removeFromTail() {
		if (head == NULL) {//empty
			cout << "\n Linked List is empty.";
		}
		else if (head == tail) {//one node
			delete head;
			head = tail = NULL;
		}
		else
		{// normal case
			Node* current = head;
			while (current->getNext() != tail) {
				current = current->getNext();

			}
			delete tail;
			tail = current;
			tail->setNext(NULL);
		}
		return;
	}
	Node* getHead() {
		if (head == NULL) {
			cout << "\n Linked List Empty. ";
			return NULL;
		}
		return (this->head);
	}
	Node* getTail() {
		if (head == NULL) {
			cout << "\n Linked List Empty. ";
			return NULL;
		}
		return (this->tail);
	}
	void display() {
		if (head == NULL) {
			cout << "\n Priority Queue is empty.\n";
			return;
		}

		Node* current = head;
		cout << "\n Priority Queue Elements (Highest to Lowest):\n";
		while (current != NULL) {
			cout << current->getData() << " ";
			current = current->getNext();
		}
		cout << endl;
	}

};

class PriorityQueue {
	Node* front;
	Node* rear;
	LinkedList list;
public:
	PriorityQueue() {
		front = rear = NULL;
		
	}
	void enqueue(int data) {
		Node* newNode = new Node(data);

		if (front == NULL) {
			front = rear = newNode;
			list.addAtHead(rear);
		}
		
		else
		{
			Node* current = front;
		Node* previous = NULL;

		
		while (current != NULL && current->getData() >= data) {
			previous = current;
			current = current->getNext();
		}

		if (previous == NULL) {
			list.addAtHead(newNode);
			front = newNode;
		}
		else if (current == NULL) {
			list.addATail(newNode);
			rear = newNode;
		}
		else {
			previous->setNext(newNode);
			newNode->setNext(current);
		}
		}
	}

	void dequeue() {
		if (front == NULL) {
			cout << "\n Queue is empty.";
			return;
		}

		list.removeFromHead();
		front = list.getHead();

		if (front == NULL) {
			rear = NULL;
		}
	}
	

	Node* peek() {
		return list.getHead();
	}

	bool isEmpty() {
		return list.getHead() == NULL;
	}

	void displayQueue() {
		list.display();
	}
	
};

void displayMenu() {
	cout << "\n+====== Priority Queue Menu ======+\n";
	cout << "| 1. Enqueue (Insert)"<<setw(16)<<"| \n";
	cout << "| 2. Dequeue (Remove)" << setw(16) << "| \n";
	cout << "| 3. Peek (View Highest Priority) |\n";
	cout << "| 4. Display Queue" << setw(19) << "| \n";
	cout << "| 5. Check if Queue is Empty      | \n";
	cout << "| 6. Exit" << setw(28) << "| \n";
	cout << "| Enter your choice: ";
}

int main() {
	PriorityQueue pq;
	int choice;
	int value;

	do {
		
		displayMenu();
		cin >> choice;

		cout << "+=================================+\n";

		switch (choice) {
		case 1:
			
			cout << "\n Enter the value to enqueue: ";
			cin >> value;
			pq.enqueue(value);
			cout << value << " has been enqueued.\n";
			break;

		case 2:
			
			if (!pq.isEmpty()) {
				cout << "Dequeued: " << pq.peek()->getData() << endl;
				pq.dequeue();
			}
			else {
				cout << "Queue is empty. Nothing to dequeue.\n";
				
			}
			cin.ignore();
			break;

		case 3:
			
			if (!pq.isEmpty()) {
				cout << "Highest Priority Element: " << pq.peek()->getData() << endl;
			}
			else {
				cout << "Queue is empty.\n";
			}
			cin.ignore();
			break;

		case 4:
			
			pq.displayQueue();
			cin.ignore();
			break;

		case 5:
			
			if (pq.isEmpty()) {
				cout << "Queue is empty.\n";
			}
			else {
				cout << "Queue is not empty.\n";
			}
			cin.ignore();
			break;

		case 6:
			
			cout << "Exiting the program. Goodbye!\n";
			break;

		default:
			cout << "Invalid choice. Please try again.\n";
		}

	} while (choice != 6);

	return 0;
}