
#include<iostream>
#include<limits>

using namespace std;

class Node {
private:
	int data;
	Node* next;
public:
	Node(int data = 0) : data(data), next(NULL) {}


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
	int size;
public:
	LinkedList() : head(NULL), tail(NULL), size(0) {}

	~LinkedList() {
		Node* current = head;
		while (current != NULL) {
			Node* nextNode = current->getNext();
			delete current;
			current = nextNode;
		}
	}


	//insert
	void addAtHead(Node* NewNode) {
		if (head == NULL) {
			head = tail = NewNode;
		}
		else
		{
			NewNode->setNext(head);
			head = NewNode;
		}
		size++;
		return;
	}

	void addATail(Node* NewNode) {
		if (head == NULL) {
			head = tail = NewNode;
			
		}
		else
		{
			tail->setNext(NewNode);
			tail = NewNode;
		}
		size++;
	}

	void insertSorted(Node* NewNode) {
		
		 if ( NewNode->getData() > head->getData() || head == NULL  ) {
			addAtHead(NewNode);
			size++;
		}
		else if (NewNode->getData() <= tail->getData()) {
			
			addATail(NewNode);
			size++;
		}
		else {
				Node* temp = tail;
			
				removeFromTail();
				insertSorted(NewNode);

			
			
				addATail(temp);
		
		}
		
	}

	
	// remove 
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
			size = -1;
			return;
		}
		size--;
	}

	void removeFromHead(Node* NewNode) {
		if (head == NULL) {
			cout << "\n Linked List is empty. ";
			return;
		}
		else
		{
			Node* current = head;
			head = head->getNext();
			NewNode = current;
			delete current;
		}
		if (head == NULL) {
			tail = NULL;
			size = -1;
			return;
		}
		size--;
	}
	void removeFromTail() {
		if (head == NULL) {//empty
			cout << "\n Linked List is empty.";
			return;
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
		size--;

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

	int getSize() {
		return this->size;
	}

};

class Stack {
private:
	
	LinkedList list;
public:
	Stack() { }
	
	void push(Node* NewNode) {
		list.addAtHead(NewNode);
	}

	void pop() {
		list.removeFromHead();
	}

	Node* getTop() {
		return list.getHead();
	}

	int getSize() {
		return list.getSize();
	}
};

class AbstractQueue {
public:

	virtual void insert(Node* NewNode) = 0;

	virtual void remove() = 0;

	virtual Node* getFront() = 0;

	virtual Node* getRear() { 
		return NULL; 
	} 

	virtual int getSize() = 0;
	
	virtual ~AbstractQueue() {}
};

class Queue : public AbstractQueue{
private:
	LinkedList list;
public:
	

	void insert(Node* NewNode) override {
		list.addATail(NewNode);
	}

	void remove() override{ 
		list.removeFromHead(); 
	}

	Node* getFront() override{
		return list.getHead();
	}
	
	Node* getRear() override {
		 return list.getTail();
	}

	int getSize() override {
		return list.getSize();
	}
};

class PriorityQueue : public AbstractQueue {
public:
	LinkedList list;
	void insert(Node* NewNode) override {
		list.insertSorted(NewNode);

	}
	void remove() override {
		list.removeFromHead();
	}
	Node* getFront() override {
		return list.getHead();
	}

	Node* getRear() override {
		return list.getTail();
	}

	int getSize() override {
		return list.getSize();
	}

};

class circularQueue : public AbstractQueue {
	LinkedList list;
public:
	void insert(Node* NewNode) override {
		list.addATail(NewNode);
		list.getTail()->setNext(list.getHead()) ;
	}

	void remove() override {
		if (list.getHead() == NULL) {
			cout << "\n Circular Queue is Empty. ";
			return;
		}
		list.removeFromHead();
		if (list.getHead() != NULL) {
			list.getTail()->setNext(list.getHead());
		}
	}
	Node* getFront() override {
		return list.getHead();
	}

	Node* getRear()  override {
		return list.getTail();
	}

	int getSize() override {
		return list.getSize();
	}
};



class Dequeue {
	LinkedList list;
	string type;
	// input restricted from head or tail
	// output restricted from head or tail

public:
	Dequeue(string type = "") : type(type) {}

	void insertAtHead(Node* NewNode) {
		if (type == "" || type != "input restricted from head") {
			list.addAtHead(NewNode);
		}
		else
			cout << "\n Insertion restricted at Head.";
	}
	void insertAtTail(Node* NewNode) {
		if (type == "" || type != "input restricted from tail") {
			list.addATail(NewNode);
		}
		else
			cout << "\n Insertion restricted at Tail.";
	}

	void removeFromHead() {
		if (type == "" || type != "removal restricted from head") {
			list.removeFromHead();
		}
		else
			cout << "\n Removal restricted at Head.";
		
	}
	void removeFromTail() {
		if (type == "" || type != "removal restricted from tail") {
			list.removeFromTail();
		}
		else
			cout << "\n Removal restricted at Tail.";
		
	}
	 
	Node* getFront() {
		return list.getHead();
	}

	Node* getRear() {
		return list.getTail();
	}

	string getType() {
		return this->type;
	}
};

#include<string.h>
bool isDigitString(string& str, int range = 9, int i = 0) {
	
	while (i < str.size() && (str[i] == ' ' || str[i] == '0')) {
		i++;
	}

	
	if (i >= str.size()) {
		return false;
	}

	
	if (str[i] >= '1' && str[i] <= '0' + range) {
		if (i == str.size() - 1) { 
			return true;
		}
		return isDigitString(str, range, i + 1); 
	}

	return false; 
}
void makeValid(string& str, int range) {
	while (!isDigitString(str,range )) {
		cout << "\n Try Again! \n Enter digit 0 to " << range << " to continue: ";
		str = "";
		cin >> str;
	}

	return;
}

// menus
#include<string>
void queue(string qtype, string& choice) {// circular ,linear , priority
	AbstractQueue* aQ;

	if (qtype == "Linear Queue") aQ = new Queue;
	else if (qtype == "Circular Queue") aQ = new circularQueue ;
	else aQ = new PriorityQueue ;

	do {
		cout << "\n --" << qtype << "-- "
			<< "\n 1. Insert."
			<< "\n 2. Remove."
			<< "\n 3. get front."
			<< "\n 4. get rear."
			<< "\n 5. exit."
			<< "\n Choose an option: ";
		 cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, choice );
		makeValid(choice, 5);


		Node* front = nullptr;
		Node* rear = nullptr;

		switch (choice[0]) {
		case '1':
			int value;

			cout << "\n Enter a value to insert in "<< qtype<<" : ";
			cin >> value;

			aQ->insert(new Node(value));

			break;
		case'2':
			cout << "\n Removing " << aQ->getFront();
			aQ->remove();

			break;
		case '3':
			front = aQ->getFront();

			if (front) {
				cout << "\n Front Element: " << front->getData();
			}
			break;
		case'4':
			rear = aQ->getRear();

			
		if (rear){
			cout << "\n Rear element: " << rear->getData();
		}
		else if (qtype == "Priority Queue")
		{
			cout << "\n Priority Queue does not support retrieval of a rear element.";
		}
		   break;
		case '5':
			cout << "\n Exiting " << qtype << " menu...";
			return;
			break;
		default:
			cout << "\n Invalid choice! Please try again.";
		}
		cout << "\n Do you want to continue with " << qtype << " (press y to continue): ";
		getline(cin, choice );



	} while (choice == "y" || choice == "Y");
	delete aQ;
}

void DoublyEndedQueue(string& choice) {
	cout << "\n =========Dequeue================"
		<< "\n -------------Head----------------"
		<< "\n 1. Input Restricted from Head. "
		<< "\n 2. Output Restricted from Head." << endl
		<< "\n -------------Tail----------------"
		<< "\n 3. Input Restricted from Tail. "
		<< "\n 4. Output Restricted from Tail." << endl
		<< "\n  5. !!!no restriction!!!"
		<< "\n 6. Exit... "
		<< "\n Choose an option: ";
	 cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, choice );
	makeValid(choice, 6);

	Dequeue* dequeue = NULL;

	switch (choice[0]) {
	case '1':
		dequeue = new Dequeue("input restricted from head");
		break;
	case '2':
		dequeue = new Dequeue("removal restricted from head");
		break;
	case '3':
		dequeue = new Dequeue("input restricted from tail");
		break;
	case '4':
		dequeue = new Dequeue("removal restricted from tail");
		break;
	case '5':
		dequeue = new Dequeue();
		break;
	case '6':
		cout << "\n Exiting Dequeue menu...";
		return;
		break;
	default:
		cout << "\n Invalid choice! Please try again.";
		return;
	}

	do {
		cout << "\n -- " << (dequeue ? dequeue->getType() : "No restriction") << " Dequeue --"
			<< "\n 1. Insert at Head."
			<< "\n 2. Insert at Tail."
			<< "\n 3. Remove from Head."
			<< "\n 4. Remove from Tail."
			<< "\n 5. Exit."
			<< "\n Choose an option: ";
		getline(cin, choice );
		makeValid(choice, 5);

		int value;
		switch (choice[0]) {
		case '1':
			cout << "\n Enter a value to insert at Head: ";
			cin >> value;
			dequeue->insertAtHead(new Node(value));
			break;
		case '2':
			cout << "\n Enter a value to insert at Tail: ";
			cin >> value;
			dequeue->insertAtTail(new Node(value));
			break;
		case '3':
			dequeue->removeFromHead();
			break;
		case '4':
			dequeue->removeFromTail();
			break;
		case '5':
			cout << "\n Exiting Dequeue menu...";
			return;
			break;
		default:
			cout << "\n Invalid choice! Please try again.";
		}

		cout << "\n Do you want to continue with Dequeue (press y to continue): ";
		getline(cin, choice );

	} while (choice == "y" || choice == "Y");

	delete dequeue;

}

void QueueMenu(string& choice) {

	do{
		cout << "\n ------Queue Menu-------"
			<<"\n 1. Linear Queue"
			<< "\n 2. Circular Queue."
			<< "\n 3. Priority Queue."
			<< "\n 4. Doubly Ended Queue."
			<< "\n 5. Exit..."
			<< "\n Choose an option: ";

		 cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, choice );
		makeValid(choice, 5);// queue option selcted 

		switch (choice[0]) {
		case '1':
			queue("Linear Queue",choice);
			break;
		case '2': 
			queue("Circular Queue", choice);
			break;
		case '3':
			queue("Priority Queue", choice);
			break;
		case '4':
			DoublyEndedQueue(choice);
		case '5':
			cout << "\n Exiting....";
			return;
			break;
		default:
			cout << "\n Invalid choice! Please try again." << endl;
		}
		cout << "\n Do you want to continue Queues. press 1 to continue: ";
		 cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, choice );
		makeValid(choice, 1);

	} while (choice == "1");
}

void stack(string& choice) {
	Stack s;
	Node* NodeTop;
	do{

		cout << "\n---Stack---"
			<< "\n 1. push."
			<< "\n 2. pop."
			<< "\n 3. get top."
			<< "\n 4. Exit."
			<< "\n Choose an option: ";
		 cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, choice );
		makeValid(choice, 4);

		switch (choice[0]) {

		case'1':
			cout << "\n Enter a int value to push: ";
			int num;
			cin >> num;
			s.push(new Node(num));
			break;

		case'2':
			cout << "\n Successfully poped";
			s.pop();
			break;
		case'3':
			NodeTop = s.getTop();
			if (NodeTop) {
				cout << "Top element: " << s.getTop()->getData();
			}
			break;
		case'4':
			cout << "\n Exiting to main menu ...";
			return;
			break;
		default:
			cout << "\n Invalid choice! Please try again.";
		}
		cout << "\n Do you want to continue with stack (press y to continue):  ";
		 cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, choice );
	} while (choice == "y" || choice == "Y");

}

void mainMenu() {

	cout << "\n ---------Main Menu----------"
		<< "\n 1. Stacks using LinkedList."
		<< "\n 2. Queues using LinkedList."
		<< "\n 3. Exit..";
	cout << "\n Choose an option: ";
}


int main() {
	string choice;
	do {
		mainMenu();
		cin>>choice;

		makeValid(choice, 3);

		switch (choice[0]) {
		case '1':// stack
			stack( choice);
			// stack option select
			
			break;
		case '2':
			QueueMenu(choice);// Queue selected

			break;

		case '3':
			cout << "\n Exiting....";
			return 0;
			break;
		default:
			cout << "\n Invalid choice! Please try again.";
		}
		 cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\n Do you want to continue to Main Menu: ";


		getline(cin, choice );

	} while (choice == "y" || choice == "Y");
	return 0;
}