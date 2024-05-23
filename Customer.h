#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Address class definition
class Address {
private:
    string street;
    string city;
    string state;
    string country;

public:
    // Constructors
    Address() : street("not set"), city("none"), state("none"), country("not set") {}
    Address(string street, string city, string state, string country)
        : street(street), city(city), state(state), country(country) {}

    // Getter methods
    string getStreet() const { return street; }
    string getCity() const { return city; }
    string getState() const { return state; }
    string getCountry() const { return country; }

    // String representation of Address
    string toString() const {
        return "\t" + street + "\t " + city + "\t " + state + "\t " + country;
    }

    // Overloaded input operator for Address
    friend istream& operator>>(istream& input, Address& addr) {
        cout << "Street: ";
        getline(input >> ws, addr.street); // Ensure proper reading of street (handles whitespace)

        cout << "City: ";
        getline(input, addr.city);

        cout << "State: ";
        getline(input, addr.state);

        cout << "Country: ";
        getline(input, addr.country);

        return input;
    }
};

class Customer {
private:
    int id;
    string name;
    int age;
    long int contactno;
    Address Residence;

public:
    static int countCustomer;
    // Constructors
    Customer() : id(0), name(" "), age(0), contactno(0), Residence(Address()) { countCustomer++; }
    Customer(int id, string name, int age, long int contactno, Address residence)
        : id(id), name(name), age(age), contactno(contactno), Residence(residence) {
        countCustomer++;
    }

    // Setters
    void setid(int id) { this->id = id; }
    void setname(string name) { this->name = name; }
    void setage(int age) { this->age = age; }
    void setcontactno(long int contactno) { this->contactno = contactno; }

    // Getters
    int getid() const { return id; }
    string getname() const { return name; }
    int getage() const { return age; }
    long int getcontactno() const { return contactno; }

    // String representation of Customer
    string to_String() {
        return to_string(id) + "\t" + name + "\t" + to_string(age) + "\t" + to_string(contactno) + "\t" + Residence.toString() + "\t" + "\n";
    }

    // Write customer data to file
    void writetofile() {
        ofstream fout;
        fout.open("customer.txt", ios::app);
        fout << to_String();
        fout.close();
    }

    // Add customer data
    void adddata() {
        ofstream fout("customer.txt", ios::app);
        Customer c;
        cin >> c;
        fout << c.to_String();
        fout.close();
    }

    // View all customer data from file
    static  void viewdata() {
        ifstream fin("customer.txt");
        string line;
        while (getline(fin, line)) {
            cout << line << endl;
        }
        fin.close();
    }

    // Search for a specific customer by ID
// Search for a specific customer by ID
    static void searchdata(Customer* customers, int numCustomers, int count) {
        populatearray(customers, numCustomers, count); // Populate the array with fresh data
        int searchID;
        cout << "Enter Customer ID to search: ";
        cin >> searchID;

        bool found = false;
        for (int i = 0; i < numCustomers; ++i) {
            if (customers[i].getid() == searchID) {
                cout << "Customer found: " << customers[i].to_String() << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Customer with ID " << searchID << " not found." << endl;
        }
    }

    // Update a customer's data by ID
    static void updatedata(Customer* customers, int numCustomers, int count) {

        populatearray(customers, numCustomers, count); // Populate the array with fresh data
        int updateID;
        cout << "Enter Customer ID to update: ";
        cin >> updateID;

        bool found = false;
        for (int i = 0; i < numCustomers; ++i) {
            if (customers[i].getid() == updateID) {
                cout << "Enter updated data:" << endl;
                cin >> customers[i];
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Customer with ID " << updateID << " not found." << endl;
        }

        // Rewrite all data to file after update
        ofstream fout("customer.txt");
        for (int i = 0; i < numCustomers; ++i) {
            fout << customers[i].to_String();
        }
        fout.close();
    }

    // Overloaded input operator for Customer
    friend istream& operator>>(istream& n, Customer& c) {
        cout << "Enter Customer ID: ";
        n >> c.id;

        cout << "Enter Customer Name: ";
        getline(n >> ws, c.name);

        cout << "Enter Customer Age: ";
        n >> c.age;

        cout << "Enter Customer Contact No.: ";
        n >> c.contactno;

        cout << "Enter Address details (street, city, state, country): ";
        n >> c.Residence;

        return n;
    }

    // Populate array of customers from file
    static void populatearray(Customer* customers, int MAX_Customers, int count) {
        customers = new Customer[MAX_Customers];
        ifstream fin;
        fin.open("customer.txt",ios::app);
        int id;
        string name;
        int age;
        long int contactno;
        string street, city, state, country;

        int index = 0;
        while (index < MAX_Customers && fin >> id >> name >> age >> contactno >> street >> city >> state >> country) {
            Address addr(street, city, state, country);
            Customer c(id, name, age, contactno, addr);
            customers[index] = c;
            index++;
        }
        count = index;
        fin.close();
    }
   static int  checkrecords() {
        int count = 0;
        ifstream fin;
        string line;
        fin.open("customer.txt");
        while (getline(fin, line)) {
            count++;
        }
        fin.close();
        return count;
    }
};
int Customer::countCustomer = 0;



