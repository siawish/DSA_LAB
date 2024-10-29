
#include<string>
using namespace std;

#include<iostream>
class Node
{
public:
	Node* next, * previous;
	double runs;
	int matchNo;
	Node(int matchNo,double run) : matchNo(matchNo) ,runs(run), next(NULL), previous(NULL) {}
};

class DoublyLinkedList {
public:
	Node* head;
	Node* tail;
	DoublyLinkedList(): head(NULL), tail(NULL) {}

	Node* findMatch(int matchNo) {
		Node* temp = head;
		while (temp) {
			if (temp->matchNo == matchNo) return temp;
			temp = temp->next;
		}
		return NULL;
	}

	void AddRunsAtStart(int matchNo ,int runs) {//1. Add Runs at Start
		Node* existingMatch = findMatch(matchNo);

		if (existingMatch) {

			cout << "\n Match " << matchNo << " already exists. Updating score."
				 << "\n Previous score : ";

			existingMatch->runs = runs;

			cout << "\n Updated score: " << existingMatch->runs;

			return;
		}

		Node* NewNode = new Node(matchNo, runs);
		if (head==NULL) {
			head = tail = NewNode;
			return;
		}
		else {
			NewNode->next = head;
			head->previous = NewNode;
			head = NewNode;
			return;
		}
	}
	void AddRunsAtEnd(int matchNo, int runs) {// 2.	Add Runs at End
		Node* existingMatch = findMatch(matchNo);

		if (existingMatch) {

			cout << "\n Match " << matchNo << " already exists. Updating score."
				<< "\n Previous score : ";

			existingMatch->runs = runs;

			cout << "\n Updated score: " << existingMatch->runs;

			return;
		}
		Node* NewNode = new Node(matchNo, runs);
		if (!head) {
			head = tail = NewNode;
			return;
		}
		else {
			tail->next = NewNode;
			NewNode->previous = tail;
			tail = NewNode;
			return;
		}
	}

	void DeleteAllOccurrencesOfaScore(int runs) {//	3.	Delete All Occurrences of a Score


		if (!head) {
			cout << "\n No matches recorded yet.";
			return;
		}
		Node* temp = head;
		bool flag = false;

		while (temp) {
			if (temp->runs == runs) {
				flag = true;
				Node* toDelete = temp;
				if (temp == head) {
					head = head->next;
					if (head) head->previous = nullptr;
					else tail = nullptr;  
				}
				else if (temp == tail) {
					tail = tail->previous;
					tail->next = nullptr;
				}
				else {
					temp->previous->next = temp->next;
					temp->next->previous = temp->previous;
				}
				temp = temp->next;
				delete toDelete;
			}
			else {
				temp = temp->next;
			}
		}
		if (!flag) {
			cout << "\n Score not found in any match.";
		}
	}
	void DisplayScoresInSequence() {// 4. Display Scores in Sequence
		if (!head) {
			cout << "\n No Nodees recorded yet.";
			return;
		}
		else {
			cout << endl;
			Node* temp = head;
			while (temp)
			{
				cout << " | " <<temp->matchNo<< "," << temp->runs << " |";
				temp = temp->next;
			}
			return;
		}
	}

	void DisplayScoresInReverseSequence() {// 5. Display Scores in  Reverse Sequence
		if (!head) {
			cout << "\n No Nodees recorded yet.";
			return;
		}
		else {
			cout << endl;
			Node* temp = tail;
			while (temp)
			{
				cout << " | " << temp->matchNo << "," << temp->runs << " |";
				temp = temp->previous;
			}
			return;
		}
	}
	void FindHighestAndLowestScores() {//6.	Find Highest and Lowest Scores: 
		if (!head) {
			cout << "\n No Nodees recorded yet.";
			return;
		}
		else {
			Node* biggest, * smallest;
			biggest = smallest = head;

			Node* temp = head;
			while (temp) {
				if (biggest->runs <=  temp->runs) {
					biggest = temp;
				}
				if (smallest->runs >= temp->runs) {
					smallest = temp;
				}
				temp = temp->next;
			}
			cout << "\n Highest score: " << biggest->runs;
			cout << "\n Lowest score: " << smallest->runs;
		}
	}
};



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
	while (!isDigitString(str, range)) {
		
		cout << "\n Try Again! \n Enter digit 0 to " << range << " to continue: ";
		str.clear();
		cin >> str;
	}

	return;
}

void  menu() {
	cout << "\n +================Menu===================+"
		 << "\n | 1. Add Runs at Start.                 |"
		 << "\n | 2. Add Runs at End.                   | "
		 << "\n | 3. Delete All Occurrences of a Score. |" 
		 << "\n | 4. Display Scores in Sequence.        |" 
		 << "\n | 5. Display Scores in Reverse Sequence.| "
		 << "\n | 6. Find Highest and Lowest Scores.    | "
		 << "\n | 7.  Exit.                             | "    
		 << "\n | Enter Your choice: ";
}

int takeInput() {
	
	int run;
	cout << "\n Enter runs: ";
	  cin >> run;
	  return run;
}

int takeMatchNumber() {
	int num;
	do
	{
		cin.clear();
		cout << "\n Enter match number: ";
		cin >> num;
		if (num < 0) 
		{
			cout << "\n Invalid Input. Try Again!. ";
		}
		

	} while (num < 0);
	return num;
}

int main() {
	string choice;
	DoublyLinkedList list;
	bool first = 1;
	do {
		choice.clear();
		if (first)
		{
			cin.ignore();
			first = 0;
		}

		menu();
		getline(cin, choice);
		makeValid(choice, 7);

		switch (choice[0]) {

		case '1':
			;
			
			list.AddRunsAtStart(takeMatchNumber(), takeInput());
			break;
		case '2':
			
			list.AddRunsAtEnd(takeMatchNumber(), takeInput());
			break;
		case '3':
			
			list.DeleteAllOccurrencesOfaScore(takeInput());
			break;
		case '4':
			list.DisplayScoresInSequence();
			break;
		case '5':
			list.DisplayScoresInReverseSequence();
			break;
		case '6':
			list.FindHighestAndLowestScores();
			break;
		}
	} while (choice[0] != '7');
	return 0;
}
