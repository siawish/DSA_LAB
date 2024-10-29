#include<iostream>
#include<iomanip>


using namespace std;

class Person{
public:
	int priority;
	int id;  
	string role; 
	Person* next;

	Person( int id, string role) : id(id), role(role) {
		this->next = NULL;

		if (role == "Admin") {
			priority = 3;
		}
		else if (role == "Teacher") {
			priority = 2;
		}
		else {
			priority = 1;  
		}
	}
public:
	string getTypeOfPerson() { return this->role; }

	Person* getNext() { return this->next; }
};


class LinkedList {
	Person* head;
	Person* current;
public:
	LinkedList() : head(NULL), current(NULL) {}

	/*~LinkedList() {
		Person* current = head;
		while (current != NULL) {
			Person* nextNode = current->getNext();
			delete current;
			current = nextNode;
		}
	}*/
	void insert(Person* person) {
		if (head==NULL) {
			head =current = person;
			
		}
		else {
			Person* temp = head;

			while (temp->next) {
				temp = temp->next;
			}
			temp->next = person;
		}
	}

	void traverseAndDisplay() {
		Person* temp = head;

		
		while (temp) {
			cout << "[" << temp->getTypeOfPerson() << "] ID: " << temp->id << " ";
			temp = temp->next;
		}
		cout << endl;
	}
	Person* getCurrent() {
		return current;
	}

	void moveToNext() {
		if (current && current->next) {
			current = current->next;
		}
		else {
			cout << "\n No next Node!";
		}
	}

	void moveToPrevious() {
		if (head == NULL || head == current) {
			cout << "\n No Previous Node!";
			return;
		}
		Person* temp = head;
		while (temp && temp->next != current) {
			temp = temp->next;
		}
		if (temp) {
			current = temp;
		}
	}


};

class PrintQueue {
public:
	

	void displayQueue(Person* adminFront, Person* adminRear, Person* teacherFront, Person* teacherRear, Person* studentFront, Person* studentRear) {
		if (!adminFront && !teacherFront && !studentFront) {
			cout << "Queue is empty." << endl;
			return;  
		}

		printFrontMarkers(adminFront, teacherFront, studentFront);

		Person* current = adminFront ? adminFront : (teacherFront ? teacherFront : studentFront);
		while (current) {
			printNode(current);
			current = current->next;
		}
		cout << "NULL\n";

		printRearMarkers(adminRear, teacherRear, studentRear);
	}
	
	void printFrontMarkers(Person* adminFront, Person* teacherFront, Person* studentFront) {
		if (adminFront) {
			cout << "  (aF)  ";
		}
		else {
			cout << "        "; 
		}

		if (teacherFront) {
			cout << "  (tF)  ";
		}
		else {
			cout << "        ";  
		}

		if (studentFront) {
			cout << "  (sF)  ";
		}
		else {
			cout << "        ";  
		}

		cout << "\n";  
	}

	
	void printNode(Person* current) {
		if (current) {
			cout << "| " << current->priority << " | --> "; 
		}
		
	}

	
	void printRearMarkers(Person* adminRear, Person* teacherRear, Person* studentRear) {
		if (adminRear) {
			cout << "  (aR)  ";
		}
		else {
			cout << "        ";  
		}

		if (teacherRear) {
			cout << "  (tR)  ";
		}
		else {
			cout << "        ";  
		}

		if (studentRear) {
			cout << "  (sR)  ";
		}
		else {
			cout << "        ";  
		}

		cout << "\n";  
	}
};

class PriorityQueue {
	Person* adminFront;
	Person* adminRear;
	Person* teacherFront;
	Person* teacherRear;
	Person* studentFront;
	Person* studentRear;
	LinkedList List;
	PrintQueue printer;

public:
	PriorityQueue() {
		adminFront = adminRear = NULL;
		teacherFront = teacherRear = NULL;
		studentFront = studentRear = NULL;
		
	}




	void enqueue(Person* person) {
		
		if (idExists(person->id)) {
			cout << "\nID " << person->id << " already exists. Cannot enqueue duplicate ID." << endl;
			delete person;  
			return;
		}

		
		if (person->priority == 3) {
			enqueueAdmin(person);
		}
		else if (person->priority == 2) {
			enqueueTeacher(person);
		}
		else if (person->priority == 1) {
			enqueueStudent(person);
		}

		
		List.insert(person);
		printer.displayQueue(adminFront, adminRear, teacherFront, teacherRear, studentFront, studentRear);
	}

	bool idExists(int id) {
		Person* current = adminFront ? adminFront : (teacherFront ? teacherFront : studentFront);
		while (current) {
			if (current->id == id) {
				return true;
			}
			current = current->next;
		}
		return false;
	}

	void enqueueAdmin(Person* person) {
		if (adminFront == NULL) {
			adminFront = adminRear = person;

		}
		else {
			adminRear->next = person;
			adminRear = person;
			
		}
		adminRear->next = NULL;
	} 

	void enqueueTeacher(Person* person) {
		if (teacherFront == NULL) {
			teacherFront = teacherRear = person;
			
			
		}
		else {
			teacherRear->next = person;
			teacherRear = person;
		
		}
		teacherRear->next = NULL;
	}
	void enqueueStudent(Person* person) {
		if (studentFront == NULL) {
			studentFront = studentRear = person;
		
		}
		else {
			studentRear->next = person;
			studentRear = person;
		}
		studentRear->next = NULL;
	}

	void dequeue() {
		if (adminFront != NULL) {
			dequeuePerson(adminFront, adminRear, "Admin");
		}
		else if (teacherFront != NULL) {
			dequeuePerson(teacherFront, teacherRear, "Teacher");
		}
		else if (studentFront != NULL) {
			dequeuePerson(studentFront, studentRear, "Student");
		}
		else {
			cout << "\n Queue is empty.";
		}
		printer.displayQueue(adminFront, adminRear, teacherFront, teacherRear, studentFront, studentRear);
	}

	

	void dequeuePerson(Person*& front, Person*& rear, string pType) {
		if (front == NULL) {  
			cout << "\n Queue is empty, nothing to dequeue.\n";
			return;
		}

		Person* temp = front;
		front = front->next;
		cout << "\n Dequeued " << pType << " with ID: " << temp->id<<endl;
		delete temp;

		if (front == NULL) {
			rear = NULL;  
		}
	}
	void displayQueue() {
		cout << "\nQueue status: \n";
		printer.displayQueue(adminFront, adminRear, teacherFront, teacherRear, studentFront, studentRear);
	}

	Person* peek() {
		if (adminFront != NULL) { return adminFront; }

		else if (teacherFront != NULL) {
			return teacherFront;
		}
		else if (studentFront != NULL) {
			return studentFront;
		}
		else {
			return NULL;
		}
	}

	bool isEmpty() {
		return (adminFront == NULL && teacherFront == NULL && studentFront == NULL);
	}

	Person* movePrevious(Person* current) {
		if (adminFront == current) {
			cout << "No previous node, you are at the front of the queue.\n";
			return current;
		}

		Person* temp = adminFront ? adminFront : (teacherFront ? teacherFront : studentFront);
		while (temp && temp->next != current) {
			temp = temp->next;
		}
		return temp;
	}

	void traverseData() {
		Person* current = adminFront ? adminFront : (teacherFront ? teacherFront : studentFront);
		if (!current) {
			cout << "Queue is empty.\n";
			return;
		}

		char key;
		cout << "\n Press 'A' to move left <- ,\n 'D' to move right -> , \n 'Q' to quit.";
		cout << "\n *:";

		while (true) {
			if (current == NULL) break;

			cout << "\n Current Person Priority: " << current->priority << endl;
			cout << "To see ID, press 'S', or traverse with 'A' and 'D'." << endl;

			cin >> key;

			if (key == 'A' || key == 'a') {
				current = movePrevious(current);
			}
			else if (key == 'D' || key == 'd') {
				current = current->next;
				if (current == NULL) {
					cout << "\n End of Queue.";
					break;
				}
			}
			else if (key == 'S' || key == 's') {
				cout << "\n Current Person ID: " << current->id << endl;
			}
			else if (key == 'Q' || key == 'q') {
				cout << "\n Exiting traversal.";
				break;
			}
		}
	}
};


void menu() { 
	cout << "\n Select the type of Person to insert:";
	cout << "\n 1. Admin."
		<< "\n 2. Teacher."
		<< "\n 3. Student."
		<< "\n Enter your choice: ";
}

void displayMenu() {
	
	cout << "\n+====== Priority Queue Menu ======+\n";
	cout << "| 1. Enqueue (Insert)" << setw(16) << "| \n";
	cout << "| 2. Dequeue (Remove)" << setw(16) << "| \n";
	cout << "| 3. Peek (View Highest Priority) |\n";
	cout << "| 4. Display Queue" << setw(19) << "| \n";
	cout << "| 5. Check if Queue is Empty      | \n";
	cout << "| 6. Traverse Data                | \n";
	cout << "| 7. Exit" << setw(28) << "| \n";
	cout << "| Enter your choice: ";
}


int main() {
	PriorityQueue pq;
	int mainChoice, personChoice, id;

	do {
		
			
		displayMenu();
		cin >> mainChoice;
		
		cout << "+=================================+\n";


		switch (mainChoice) {
		case 1: 
			do {
				menu();
				cin >> personChoice;

				if (personChoice < 1 || personChoice > 3) {
					cout << "\n Invalid option selected.";
				}
			} while (!(personChoice == 1 || personChoice == 2 || personChoice == 3));

			cout << "\n Enter the ID to enqueue: ";
			cin >> id;
			if (personChoice == 1) {
				pq.enqueue(new Person(id, "Admin"));
			}
			
			else if (personChoice == 2) {
				pq.enqueue(new Person(id, "Teacher"));
			}
			else if (personChoice == 3) {
				pq.enqueue(new Person(id, "Student"));
			}
			break;

		case 2:  
			pq.dequeue();
			break;

		case 3:  
			if (!pq.isEmpty()) {
				Person* p = pq.peek();
				cout << "Highest priority is: [" << p->getTypeOfPerson() << "] ID: " << p->id << endl;
			}
			else {
				cout << "\n Queue is empty.";
			}
			break;

		case 4:  
			pq.displayQueue();
			break;

		case 5:  
			if (pq.isEmpty()) {
				cout << "\n The queue is empty.";
			}
			
			else {
				cout << "\n The queue is not empty.";
			}
			break;

		case 6: 
			pq.traverseData();
			break;

		case 7:  
			cout << "\n ...Exiting program... ";
			break;

		default:
			cout << "\n Invalid choice. Please try again.";
			break;
		}
	} while (mainChoice != 7);

	return 0;
}

