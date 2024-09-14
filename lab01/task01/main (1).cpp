#include<iostream>
#include<string>
#include<iomanip>
#include<list>
using namespace std;

class House {
private:
    string Owner;
    string Address;
    int Bedrooms=0;
    float Price=0;

public:
    //Getters
    string getOwner() 
    {
        return this->Owner;
    }
    string getAddress() 
    {
        return this->Address;
    }
    int getBedrooms() 
    {
        return this->Bedrooms;
    }
    float getPrice() 
    {
        return this->Price;
    }
    //Setters
    void setOwner(string oName) 
    {
        this->Owner = oName;
    }
    void setAddress(string Address) 
    {
        this->Address = Address;
    }
    void setBedrooms(int Bedrooms) 
    {
        this->Bedrooms = Bedrooms;
    }
    void setPrice(float price) 
    {
        this->Price = price;
    }
};
void printDataHouse(list<House>& houses) {
     int ownerWidth = 20;
     int addressWidth = 30;
     int bedroomsWidth = 10;
     int priceWidth = 15;

    cout << "\n"
        << left << setw(ownerWidth) << "Owner"
        << left << setw(addressWidth) << "Address"
        << right << setw(bedroomsWidth) << "Bedrooms"
        << right << setw(priceWidth) << "Price" << endl;

    for ( auto house : houses) {
        cout << left << setw(ownerWidth) << house.getOwner()
            << left << setw(addressWidth) << house.getAddress()
            << right << setw(bedroomsWidth) << house.getBedrooms()
            << right << setw(priceWidth) << fixed << setprecision(2) << house.getPrice() << endl;
    }
}

string check(string n) {
    while (n.size() > 20)
    {
        cout << "\n Try Again!\n  must be shorter than 20 charcters: ";
        getline(cin, n);
        cin.ignore();
    }
    return n;
}

int main()
{
    list<House> houses;
    const int maxHouses = 100;
    char choice;
    do
    {
        cin.ignore();

        if (houses.size() >= maxHouses) {
            cout << "You have reached the maximum limit of 100 houses.\n";
            break;
        }
        string name = "";
        string address = "";
        int bedroom = 0;
        float price = 0;

        House house;

        cout << "\nEnter Owner : ";
        getline(cin, name);
        name = check(name);
        house.setOwner(name);
        cin.ignore();


        cout << "\nEnter Address: ";
        getline(cin, address);
        address = check(address);
        house.setAddress(address);
        cin.ignore();


        cout << "\nEnter Number of Bedrooms: ";
        cin >> bedroom;
        house.setBedrooms(bedroom);
        cin.ignore();

        cout << "\nPrice: ";
        cin >> price;
        house.setPrice(price);
        cin.ignore();

        houses.push_back(house);

        cout << "\nEnter another House? ";

        cin >> choice;
    } while (choice == 'Y' || choice == 'y');

    printDataHouse(houses); // printing all houses data

    return 0;
}