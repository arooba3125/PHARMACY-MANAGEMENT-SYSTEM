#ifndef ANTIBIOTIC_H
#define ANTIBIOTIC_H

#include "Medicine.h"
#include <fstream>
using namespace std;

class Antibiotics : public Medicine {
private:
    string antibioticType;
    string spectrum;
    string resistance;

public:
    // Default constructor
    Antibiotics() : Medicine() {
        antibioticType = "default";
        spectrum = "default";
        resistance = "default";
        countAntibiotics++;
    }
    static int countAntibiotics;

    // Parameterized constructor
    Antibiotics(int NDC, const string name, const string ChemicalName,
        const string mdate, const string edate, float pprice, float sprice,
        const string formulation,
        const string antibioticType, const string spectrum,
        const string resistance)
        : Medicine(NDC, name, ChemicalName, mdate, edate, pprice, sprice, formulation) {
        this->antibioticType = antibioticType;
        this->spectrum = spectrum;
        this->resistance = resistance;
        countAntibiotics++;
    }

    // Setters
    void setAntibioticType(const string newAntibioticType) {
        antibioticType = newAntibioticType;
    }

    void setSpectrum(const string newSpectrum) {
        spectrum = newSpectrum;
    }

    void setResistance(const string newResistance) {
        resistance = newResistance;
    }

    // Getters
    string getAntibioticType() const {
        return antibioticType;
    }

    string getSpectrum() const {
        return spectrum;
    }

    string getResistance() const {
        return resistance;
    }

    // String representation of Antibiotics
    string to_String() {
        return Medicine::to_String() + "\t " + antibioticType + "\t " + spectrum + "\t " + resistance;
    }

    // Methods for managing antibiotic data
    void adddata() {
        ofstream fout("Antibiotics.txt", ios::app); // Open file in append mode
        Antibiotics a;
        cin >> a; // Input vaccine data from user

        if (!Medicine::isValidNDC(a.getNDC())) { // Ensure unique NDC
            cout << "Invalid or duplicate NDC. Data not added." << endl;
            return;
        }

        fout << a.to_String(); // Write the vaccine data to file
        fout.close();
    }


    static void searchdata(Antibiotics antibiotics[], int size, int count) {
        // Populate the antibiotic array before searching data
        Antibiotics::populatearray(antibiotics, size, count);

        if (count == 0) {
            cout << "No Antibiotics data found." << endl;
            return;
        }
        int searchNDC;
        cout << "Enter NDC to search: ";
        cin >> searchNDC;
        bool found = false;
        // Search through the antibiotics array
        for (int i = 0; i < count; i++) {
            if (antibiotics[i].getNDC() == searchNDC) {
                cout << "Antibiotic found:" << endl;
                cout << antibiotics[i].to_String(); // Display the found antibiotic
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Antibiotic with NDC " << searchNDC << " not found." << endl;
        }
    }

    static  void updatedata(Antibiotics* antibiotics, int size, int count) {
        // Populate the antibiotic array before updating data
        Antibiotics::populatearray(antibiotics, size, count);

        if (count == 0) {
            cout << "No antibiotic data to update." << endl;
            return;
        }
        int updateNDC;
        cout << "Enter NDC of the antibiotic to update: ";
        cin >> updateNDC;
        bool found = false;
        // Search for the antibiotic to update
        for (int i = 0; i < count; i++) {
            if (antibiotics[i].getNDC() == updateNDC) {
                cout << "Enter new data for the antibiotic:" << endl;
                cin >> antibiotics[i]; // Update the antibiotic object
                // Rewrite the updated data to the file
                ofstream fout("Antibiotics.txt", ios::trunc); // Clear the file
                for (int j = 0; j < count; j++) {
                    fout << antibiotics[j].to_String(); // Write all data
                }
                fout.close();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Antibiotic with NDC " << updateNDC << " not found." << endl;
        }
    }

    static  void printdata(Antibiotics antibiotics[], int size, int count) {
        cout << "Antibiotics:\n";
        Antibiotics::populatearray(antibiotics, size, count);

        if (count == 0) {
            cout << "No antibiotic data found." << endl;
            return;
        }
        for (int i = 0; i < count; i++) {
            cout << antibiotics[i].to_String() << endl;
        }
    }

    // Operator overloading for input and output
    friend ostream& operator<<(ostream& output, const Antibiotics& a) {
        output << static_cast<const Medicine&>(a); // Print parent class data
        output << "\Antibiotic Type: " << a.antibioticType
            << "\tSpectrum: " << a.spectrum
            << "\tResistance: " << a.resistance << "\n";
        return output;
    }

    friend istream& operator>>(istream& input, Antibiotics& a) {
        input >> static_cast<Medicine&>(a); // Input parent class data
        cout << "Enter AntiBiotic Type: ";
        input >> a.antibioticType;
        cout << "Enter Spectrum: ";
        input >> a.spectrum;
        cout << "Enter Resistance: ";
        input >> a.resistance;
        return input;
    }

    static  void populatearray(Antibiotics* antibiotics, int maxSize, int& count) {
        ifstream fin;
        fin.open("Antibiotics.txt");
        int tempNDC;
        string tempname, tempcname, tempmdate, tempedate, tempformulation;
        float tempPrice[2];
        string tempDate[2];
        int index = 0;
        // Read data from file and populate the vaccine array
        while (index < maxSize) {
            fin >> tempNDC;
            antibiotics[index].setNDC(tempNDC);
            fin >> tempname;
            antibiotics[index].setname(tempname);
            fin >> tempcname;
            antibiotics[index].setchemicalname(tempcname);

            fin >> tempDate[0] >> tempDate[1];
            antibiotics[index].setdates(tempDate[0], tempDate[1]);
            fin >> tempPrice[0] >> tempPrice[1];
            antibiotics[index].setprice(tempPrice[0], tempPrice[1]);
            fin >> tempformulation;
            antibiotics[index].setformulation(tempformulation);
            fin >> antibiotics[index].antibioticType
                >> antibiotics[index].spectrum
                >> antibiotics[index].resistance;
            index++;
        }
        count = index; // Update the count of vaccines
        fin.close();
    }
    static int  checkrecords() {
        int count = 0;
        string line;
        ifstream fin;
        fin.open("Antibiotics.txt");
        while (getline(fin, line)) {
            count++;
        }
        fin.close();
        return count;
    }
};
int Antibiotics::countAntibiotics = 0;


#endif // ANTIBIOTIC_H
