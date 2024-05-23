#include <iostream>
#include <fstream>
#include <iomanip>
#include "Medicine.h"
#include "Customer.h"

using namespace std;

class Purchase {
private:
    int purchaseID;
    string purchaseDate;
    Medicine med;
    Customer cust;
    int quantity;

public:
    // Setter methods
    void setPurchaseID(int ID) {
        purchaseID = ID;
    }

    void setPurchaseDate(string date) {
        purchaseDate = date;
    }

    void setQuantity(int qty) {
        quantity = qty;
    }


    float getMedicinePrice() {
        int selectedNDC;
        cout << "Enter the NDC of the selected medicine: ";
        cin >> selectedNDC;

        // Open the medicine file to search for the selected medicine
        ifstream fin("medicine_data.txt");
        float price = 0.0;
        int NDC;
        while (fin >> NDC) {
            if (NDC == selectedNDC) {
                // Medicine found, retrieve its price
                fin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
                fin.ignore(numeric_limits<streamsize>::max(), '\t'); // Ignore NDC
                fin.ignore(numeric_limits<streamsize>::max(), '\t'); // Ignore Name
                fin.ignore(numeric_limits<streamsize>::max(), '\t'); // Ignore Chemical Name
                fin.ignore(numeric_limits<streamsize>::max(), '\t'); // Ignore Manufacturing Date
                fin.ignore(numeric_limits<streamsize>::max(), '\t'); // Ignore Expiration Date
                fin >> price; // Read the Purchase Price
                break; // Stop searching once the medicine is found
            }
            // Skip to the next line
            fin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        fin.close();
        return price;
    }

    // Method to calculate bill
    float calculateBill() {
        float price = getMedicinePrice(); // Retrieve the price of the selected medicine
        return quantity * price;
    }

    // Method to check customer
    void checkCustomer(Customer* customers, int MAX_CUSTOMERS, int count) {
        Customer::searchdata(customers, MAX_CUSTOMERS, count);
    }

    void checkMedicine(Medicine* med, int size, int count) {
        Medicine m;
       m.searchdata(med, size,count);
    }
    // Method to generate bill
     void generateBill(Customer* customers, int MAX_CUSTOMERS, Medicine* medicine, int count) {
        // Display bill information
        cout << "Enter purchase ID";
        cin >> purchaseID;
        cout << "Enter purchase Date";
        cin >> purchaseDate;
        cout << "Customer Information:\n";
        checkCustomer(customers, MAX_CUSTOMERS, count); // Display customer information
        cout << "Medicine Information:\n";
        checkMedicine(medicine, count, count); // Display medicine information
        cout << "Enter the quantity\n";
        cin >> quantity;
        cout << "Purchase ID: " << purchaseID << endl;
        cout << "Purchase Date: " << purchaseDate << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Total Amount: $" << fixed << setprecision(2) << calculateBill() << endl;
    }

};
