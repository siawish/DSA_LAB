#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Player {
public:
    string name;
    int odi;
    int matches;
    int t20;
    int test;
    Player* next;
    Player* prev;

    Player(string n, int o, int m, int t20, int tst) : name(n), odi(o), matches(m), t20(t20), test(tst) {
        next = prev = NULL;
    }
};

class Team {
private:
    Player* head;
    Player* tail;
    int size;
    const int maximumPlayers = 20;

public:
    Team() : head(NULL), tail(NULL), size(0) {}


    bool playerExists(string name) {
        Player* current = head;
        while (current) {
            if (current->name == name) return true;
            current = current->next;
        }
        return false;
    }


    void addPlayer(string name, int odi, int matches, int t20, int test) {//add
        if (size >= maximumPlayers) {
            cout << "\n Team is full. Cannot add more players. ";
            return;
        }

        else if (playerExists(name)) {
            cout << "\n Player with the name " << name << " already exists.";
            return;
        }

        else if (odi < 0 || matches < 0 || t20 < 0 || test < 0) {
            cout << "\n Error: Stats cannot be negative.";
            return;
        }
        else

        {
            Player* newPlayer = new Player(name, odi, matches, t20, test);

            if (!head) {
                head = tail = newPlayer;
            }
            else {
                tail->next = newPlayer;
                newPlayer->prev = tail;
                tail = newPlayer;
            }

            size++;
            savePlayerToFile(newPlayer);
            system("CLS");
            cout << "\n Player " << name << " added successfully.";
        }
    }


    void removePlayer(string name) {// Remove
        if (!playerExists(name)) {
            cout << "\n Player " << name << " does not exist.";
            return;
        }

        Player* current = head;
        while (current) {
            if (current->name == name) {
                if (current->prev)
                {
                    current->prev->next = current->next;
                }
                if (current->next)
                {
                    current->next->prev = current->prev;
                }
                if (current == head)
                {
                    head = current->next;
                }
                if (current == tail)
                {
                    tail = current->prev;
                }

                deleteFile(name);
                delete current;
                size--;
                cout << "Player " << name << " removed successfully.\n";
                return;
            }
            current = current->next;
        }
    }


    void updatePlayer(string name, int odi, int matches, int t20, int test) {
        cout << "\n Enter Name of the player to update: ";
        cin >> name;

        if (!playerExists(name)) {
            cout << "\n Player " << name << " does not exist. ";
            return;
        }
        cout << "\n Enter new ODI stats: ";
        cin >> odi;
        cout << "\n Enter new Matches played: ";
        cin >> matches;
        cout << "\n Enter new T20 stats: ";
        cin >> t20;
        cout << "\n Enter new Test stats: ";
        cin >> test;



        if (odi < 0 || matches < 0 || t20 < 0 || test < 0) {
            cout << "\n Error: Stats cannot be negative. ";
            return;
        }

        Player* current = head;
        while (current) {
            if (current->name == name) {
                current->odi = odi;
                current->matches = matches;
                current->t20 = t20;
                current->test = test;

                savePlayerToFile(current);
                cout << "\n Player " << name << " updated successfully. ";
                return;
            }
            current = current->next;
        }
    }


    void displayPlayers() {
        if (!head) {
            cout << "\n Team is empty. ";
            return;
        }

        Player* current = head;
        while (current) {
            cout << "\n Name: " << current->name
                << ", ODI: " << current->odi
                << ", Matches: " << current->matches
                << ", T20: " << current->t20
                << ", Test: " << current->test;
            current = current->next;
        }
    }


    void savePlayerToFile(Player* player) {
        ofstream file(player->name + ".txt");
        if (file.is_open()) {
            file << "Name: " << player->name << "\n";
            file << "ODI: " << player->odi << "\n";
            file << "Matches: " << player->matches << "\n";
            file << "T20: " << player->t20 << "\n";
            file << "Test: " << player->test << "\n";
            file.close();
            cout << "\n Player " << player->name << "'s data saved to file. ";
        }
        else {
            cout << "\n Error opening file for player " << player->name << ".";
        }
    }


    void deleteFile(string name) {
        string filename = name + ".txt";
        if (remove(filename.c_str()) == 0) {
            cout << "\n File " << filename << " deleted successfully.";
        }
        else {
            cout << "\n Error deleting file " << filename << ". ";
        }
    }


    ~Team() {
        Player* current = head;
        while (current) {
            Player* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
};

int main() {
    Team team;
    int choice;

    do {

        cout << "\n+--- Team Management Menu ---\n";
        cout << "| 1. Add Player";
        cout << "\n| 2. Remove Player";
        cout << "\n| 3. Update Player";
        cout << "\n| 4. Display Players";
        cout << "\n| 5. Exit";
        cout << "\n| Enter your choice: ";
        cin >> choice;

        if (choice == 5)
        {
            break;
        }

        string name;
        int odi, matches, t20, test;

        odi = matches = t20 = test = 0;
        switch (choice) {
        case 1:
            cout << "\n Enter Name: ";
            cin >> name;
            cout << "\n Enter ODI stats: ";
            cin >> odi;
            cout << "\n Enter Matches played: ";
            cin >> matches;
            cout << "\n Enter T20 stats: ";
            cin >> t20;
            cout << "\n Enter Test stats: ";
            cin >> test;
            team.addPlayer(name, odi, matches, t20, test);
            break;

        case 2:
            cout << "\n Enter Name of the player to remove: ";
            cin >> name;
            team.removePlayer(name);
            break;

        case 3:

            team.updatePlayer(name, odi, matches, t20, test);
            break;

        case 4:
            team.displayPlayers();
            break;
        case 5:
            cout << "\n Exiting Program....";
            break;

        default:
            cout << "\n Invalid choice. Please try again.";
        }
    } while (choice != 5);

    return 0;
}