#ifndef VACCINES_H // Inclusion guard to prevent multiple inclusions
#define VACCINES_H

#include <iostream>
#include <fstream>
#include "Medicine.h" // Include the base class header

class Vaccines : public Medicine { // Inherit from Medicine
private:
    string immunization;
    string immunity_type;
    string virus_attacked;


public:
    // Default constructor
    Vaccines() : Medicine() {
        immunization = "default";
        immunity_type = "default";
        virus_attacked = "default";
        countVaccines++;
    }
    static int countVaccines; // Static variable to keep track of vaccine count

    // Parameterized constructor
    Vaccines(int NDC, const string name, const string ChemicalName,
        const string mdate, const string edate, float pprice, float sprice,
        const string formulation,
        const string immunization, const string immunity_type,
        const string virus_attacked)
        : Medicine(NDC, name, ChemicalName, mdate, edate, pprice, sprice, formulation) {
        this->immunization = immunization;
        this->immunity_type = immunity_type;
        this->virus_attacked = virus_attacked;
        countVaccines++;
    }

    // Setters
    void setimmunization(const string newImmunization) {
        immunization = newImmunization;
    }

    void setimmunity_type(const string nnewImmunityType) {
        immunity_type = nnewImmunityType;
    }

    void setvirus(const string newVirus) {
        virus_attacked = newVirus;
    }

    // Getters
    string getimmunization() const {
        return immunization;
    }

    string getimmunity_type() const {
        return immunity_type;
    }

    string getvirus() const {
        return virus_attacked;
    }

    // String representation of Vaccines
    string to_String() {
        return Medicine::to_String() + "\t" + immunization + "\t" + immunity_type + "\t" + virus_attacked + "\n";
    }

    // Add vaccine data
    void adddata() {
        ofstream fout("vaccine_data.txt", ios::app); // Open file in append mode
        Vaccines v;
        cin >> v; // Input vaccine data from user

        if (!Medicine::isValidNDC(v.getNDC())) { // Ensure unique NDC
            cout << "Invalid or duplicate NDC. Data not added." << endl;
            return;
        }

        fout << v.to_String(); // Write the vaccine data to file
        fout.close();
    }

    static void printdata(Vaccines vaccines[], int count, int count1) {
        // Populate the vaccine array before printing data
        Vaccines::populatearray(vaccines, count, count1);

        if (count == 0) {
            cout << "No vaccine data found." << endl;
            return;
        }
        // Display all vaccine data
        for (int i = 0; i < count; i++) {
            cout << vaccines[i].to_String() << endl;
        }
    }

    // Search vaccine data
    static  void searchdata(Vaccines vaccines[], int count, int count1) {
        // Populate the vaccine array before searching data
        Vaccines::populatearray(vaccines, count, count1);

        if (count == 0) {
            cout << "No vaccine data found." << endl;
            return;
        }
        int searchNDC;
        cout << "Enter NDC to search: ";
        cin >> searchNDC;
        bool found = false;
        // Search through the vaccines array
        for (int i = 0; i < count; i++) {
            if (vaccines[i].getNDC() == searchNDC) {
                cout << "Vaccine found:" << endl;
                cout << vaccines[i].to_String(); // Display the found vaccine
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Vaccine with NDC " << searchNDC << " not found." << endl;
        }
    }

    // Update vaccine data
    static  void updatedata(Vaccines* vaccines, int count, int count1) {
        // Populate the vaccine array before updating data
        Vaccines::populatearray(vaccines, count, count1);

        if (count == 0) {
            cout << "No vaccine data to update." << endl;
            return;
        }
        int updateNDC;
        cout << "Enter NDC of the vaccine to update: ";
        cin >> updateNDC;
        bool found = false;
        // Search for the vaccine to update
        for (int i = 0; i < count; i++) {
            if (vaccines[i].getNDC() == updateNDC) {
                cout << "Enter new data for the vaccine:" << endl;
                cin >> vaccines[i]; // Update the vaccine object
                // Rewrite the updated data to the file
                ofstream fout("vaccine_data.txt", ios::trunc); // Clear the file
                for (int j = 0; j < count; j++) {
                    fout << vaccines[j].to_String(); // Write all data
                }
                fout.close();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Vaccine with NDC " << updateNDC << " not found." << endl;
        }
    }
    // Populate vaccine array
    static void populatearray(Vaccines* vaccines, int maxSize, int& count) {
        ifstream fin;
        fin.open("vaccine_data.txt");
        int tempNDC;
        string tempname, tempcname, tempmdate, tempedate, tempformulation;
        float tempPrice[2];
        string tempDate[2];
        int index = 0;
        // Read data from file and populate the vaccine array
        while (index < maxSize) {
            fin >> tempNDC;
            vaccines[index].setNDC(tempNDC);
            fin >> tempname;
            vaccines[index].setname(tempname);
            fin >> tempcname;
            vaccines[index].setchemicalname(tempcname);
            fin >> tempDate[0] >> tempDate[1];
            vaccines[index].setdates(tempDate[0], tempDate[1]);
            fin >> tempPrice[0] >> tempPrice[1];
            vaccines[index].setprice(tempPrice[0], tempPrice[1]);
            fin >> tempformulation;
            vaccines[index].setformulation(tempformulation);
            fin >> vaccines[index].immunization
                >> vaccines[index].immunity_type
                >> vaccines[index].virus_attacked;
            index++;
        }
        count = index; // Update the count of vaccines
        fin.close();
    }

    // Operator overloading for output
    friend ostream& operator<<(ostream& output, const Vaccines& v) {
        output << static_cast<const Medicine&>(v); // Print parent class data
        output << "\tImmunization: " << v.getimmunization()
            << "\tImmunity Type: " << v.getimmunity_type()
            << "\tVirus Attacked: " << v.getvirus() << "\n";
        return output;
    }

    // Operator overloading for input
    friend istream& operator>>(istream& input, Vaccines& v) {
        input >> static_cast<Medicine&>(v); // Input parent class data
        cout << "Enter Immunization: ";
        input >> v.immunization;
        cout << "Enter Immunity Type: ";
        input >> v.immunity_type;
        cout << "Enter Virus Attacked: ";
        input >> v.virus_attacked;
        return input;
    }
    static  int  checkrecords() {
        int count = 0;
        string line;
        ifstream fin;
        fin.open("vaccine_data.txt");
        while (getline(fin,line)) {
            count++;
        }
        fin.close();
        return count;
    }
};
int Vaccines::countVaccines = 0;

#endif // End of inclusion guard
