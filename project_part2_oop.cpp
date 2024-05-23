#include <iostream>
#include <cstdlib> // For exit()
#include "Medicine.h"
#include "Antibiotics.h"
#include "Vacccines.h"
#include "Customer.h"
#include "Purchase.h"
using namespace std;

int main() {
    cout << "\n\n*********WELCOME TO PHARMACY MANAGEMENT SYSTEM********\n\n:::MENU:::\n\n";
    Medicine* m = nullptr;

    while (true) {
        cout << "1.MEDICINE \n2.CUSTOMER\n3.PURCHASE \n4.EXIT \n\n";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            Vaccines v;
            Vaccines* vac;
            int size = Vaccines::checkrecords(); // Change size to your desired size
            vac = new Vaccines[size];
            int count = 0;
            cout << "WORKING ON MEDICINE\n";
            cout << "1.VACCINE \n2.ANTIBIOTIC \n3.BACK TO MENU\n\n";
            int medchoice;
            cin >> medchoice;

            switch (medchoice) {
            case 1: {
                m = new Vaccines;
                cout << "WORKING ON VACCINE \n";
                cout << "1.ADD \n2.VIEW\n3.SEARCH\n4.UPDATE \n5.COUNT VACCINES\n\n";
                int choicemenu;
                cin >> choicemenu;

                switch (choicemenu) {
                case 1:
                    m->adddata();
                    break;
                case 2:
                    Vaccines::printdata(vac, size, count);
                    break;
                case 3:
                    Vaccines::searchdata(vac, size, count);
                    break;
                case 4:
                    Vaccines::updatedata(vac, size, count);
                    break;
                case 5:
                    cout << "TOTAL NO OF RECORDS OF VACCINE : " << Vaccines::countVaccines << endl;
                    break;
                default:
                    cout << "Enter valid choice\n";
                    break;
                }
                delete m; // Free allocated memory
                break;
            }
            case 2: {
                m = new Antibiotics;
                Antibiotics* ant;
                int size = Antibiotics::checkrecords(); // Change size to your desired size
                ant = new Antibiotics[size];
                int count = 0;
                m = new Antibiotics;
                cout << "WORKING ON ANTIBIOTICS \n";
                cout << "1.ADD\n2.VIEW\n3.SEARCH\n4.UPDATE \n5.COUNT ANTIBIOTICS\n\n";
                int choicemenu;
                cin >> choicemenu;

                switch (choicemenu) {
                case 1:
                    m->adddata();
                    break;
                case 2:
                    Antibiotics::printdata(ant, size, count);
                    break;
                case 3:
                    Antibiotics::searchdata(ant, size, count);
                    break;
                case 4:
                    Antibiotics::updatedata(ant, size, count);
                    break;
                case 5:
                    cout << "TOTAL NO OF RECORDS OF ANTIBIOTICS : " << Antibiotics::countAntibiotics << endl;
                    break;
                default:
                    cout << "Enter valid choice\n";
                    break;
                }
                delete m; // Free allocated memory            
                break;
            }
            case 3: {
                cout << "Going to Main Menu\n";
              
                break;
            }
            default:
                cout << "Enter valid choice\n";
                break;
            }
            delete[] vac; // Free allocated memory for vac
            break;
        }
        case 2: {
            Customer c;
            int MAX_Customers = Customer::checkrecords();
            int count = 0;
            Customer* customers;
            customers = new Customer[MAX_Customers];
            cout << "WORKING ON CUSTOMERS \n";
            cout << "1.ADD\n2.VIEW\n3.SEARCH\n4.UPDATE\n5.COUNT CUSTOMERS\n\n";
            int choicemenu;
            cin >> choicemenu;
            switch (choicemenu) {
            case 1:
                c.adddata();
                break;
            case 2:
                Customer::viewdata();
                break;
            case 3:
                Customer::searchdata(customers, MAX_Customers,count);
                break;
            case 4:
                Customer::updatedata(customers, MAX_Customers,count);
                break;
            case 5:
                cout << "TOTAL NO OF RECORDS OF CUSTOMERS : " << Customer::countCustomer << endl;
                break;
            default:
                cout << "Enter valid entry\n";
                break;
            }
            delete[] customers; // Free allocated memory for customers
            break;
        }
        case 3: {         
            int customersize = Customer::checkrecords(); // Change size to your desired size
            int medicinesize = Medicine::checkrecords();
            Customer* cust;
            cust = new Customer[customersize];
            Medicine* med;
            med = new Medicine[medicinesize];
            int count = 0;
            cout << "WORKING ON PURCHASE\n";
            Purchase p;
            p.generateBill(cust, customersize, med, medicinesize);
            break;
        }
        case 4: {
            exit(0);
        }
        default:
            cout << "Enter valid choice\n";
            break;
        }
    }
    return 0;
}
