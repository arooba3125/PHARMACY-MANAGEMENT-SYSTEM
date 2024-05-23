#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Medicine {
private:
    int NDC;
    string name;
    string Chemicalname;
    string* dates;
    float* price;
    string formulation;

public:
    static int countMedicine;

    // Default constructor
    Medicine() {
        NDC = 0;
        name = "default";
        Chemicalname = "default";
        dates = new string[2];
        dates[0] = "not set";
        dates[1] = "not set";
        price = new float[2];
        price[0] = 0.0;
        price[1] = 0.0;
        formulation = "none";
        countMedicine++;
    }

    // Parameterized constructor
    Medicine(int NDC, string name, string ChemicalName, string mdate, string edate, float pprice, float sprice, string formulation)
        : NDC(NDC), name(name), Chemicalname(ChemicalName), formulation(formulation) {
        dates = new string[2];
        dates[0] = mdate;
        dates[1] = edate;
        price = new float[2];
        price[0] = pprice;
        price[1] = sprice;
        countMedicine++;
    }

    // Destructor
    ~Medicine() {
        delete[] dates;
        delete[] price;
        countMedicine--;
    }

    // Setters
    void setNDC(int newNDC) {
        NDC = newNDC;
    }

    void setname(string newName) {
        name = newName;
    }

    inline void setchemicalname(string newChemicalname) {
        Chemicalname = newChemicalname;
    }

    inline void setdates(string mdate, string edate) {
        dates[0] = mdate;
        dates[1] = edate;
    }

    inline void setprice(float pprice, float sprice) {
        price[0] = pprice;
        price[1] = sprice;
    }

    inline void setformulation(string newFormulation) {
        formulation = newFormulation;
    }

    // Getters
    inline int getNDC() {
        return NDC;
    }

    inline string getname() {
        return name;
    }

    inline string getchemicalname() {
        return Chemicalname;
    }

    inline string getmdates() {
        return dates[0];
    }

    inline string getedates() {
        return dates[1];
    }

    inline float getpprice() {
        return price[0];
    }

    inline float getsprice() {
        return price[1];
    }

    inline string getformulation() {
        return formulation;
    }

    static int getCountMedicine() {
        return countMedicine;
    }

    // Validity check
    static bool isValidNDC(int NDC) {
        ifstream fin("medicine_data.txt");
        int checkNDC;
        bool isUnique = true; // Assume the NDC is unique until proven otherwise
        // Check if the NDC already exists in the file
        while (fin >> checkNDC) {
            if (checkNDC == NDC) {
                isUnique = false; // NDC is found, indicating duplication
                break;
            }
        }
        fin.close();
        return isUnique; // Return true if the NDC is unique, false otherwise
    }

    // to_string method
    string to_String() {
        string result;
        result = to_string(NDC) + "\t" + name + "\t" + Chemicalname + "\t" + dates[0] + "\t" + dates[1] + "\t";
        result += to_string(price[0]) + "\t" +to_string(price[1]) + "\t" + formulation; // Add a newline at the end for file operations
        return result; // Return the string representation
    }

    // adddata method
    virtual void adddata() {
        ofstream fout("medicine_data.txt", ios::app);
        Medicine m;
        cin >> m; // Using operator overloading to read data from user
        if (!isValidNDC(m.getNDC())) {
            cout << "Invalid NDC";
            return;
        }
        fout << m.to_String();
        fout.close();
    }

    // searchdata method
    static string searchdata(Medicine* medicines, int size,int count) {
        medicines = new Medicine[size];
       Medicine::populatearray(medicines,size,count);
        if (count == 0) {
            cout << "No data found." << endl;
            return ""; // Return an empty string if there's no data to search
        }
        int searchNDC;
        cout << "Enter NDC to search: ";
        cin >> searchNDC;
        bool found = false;
        // Search through the populated data
        for (int i = 0; i < count; i++) {
            if (medicines[i].NDC == searchNDC) {
                cout << "Medicine found:" << endl;
                return medicines[i].to_String(); // Display the found medicine
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Medicine not found." << endl;
            return ""; // Return an empty string if the medicine is not found
        }
    }

    // updatedata method
    virtual void updatedata(Medicine* medicines, int& count) {
        if (count == 0) {
            cout << "No data to update." << endl;
            return; // Exit early if there's no data to update
        }
        int updateNDC;
        cout << "Enter NDC of the medicine to update: ";
        cin >> updateNDC;

        bool found = false;

        // Search for the medicine to update
        for (int i = 0; i < count; i++) {
            if (medicines[i].NDC == updateNDC) {
                cout << "Enter new data for the medicine:" << endl;
                cin >> medicines[i]; // Update the specific medicine object
                // Rewrite the updated data to the file
                ofstream fout("medicine_data.txt", ios::trunc); // Clear the file
                for (int j = 0; j < count; j++) {
                    fout << medicines[j].to_String();
                }
                fout.close();
                found = true;
                break; // Exit the loop once the update is done
            }
        }
        if (!found) {
            cout << "Medicine with NDC " << updateNDC << " not found." << endl;
        }
    }

    // printdata method
    virtual void printdata(Medicine medicines[], int count) {
        if (count == 0) {
            cout << "No data found." << endl;
            return;
        }
        // Display all data based on the count of populated elements
        for (int i = 0; i < count; i++) {
            cout << medicines[i].to_String();
        }
    }

    // Operator overloading
    friend ostream& operator<<(ostream& output, const Medicine& m) {
        output << "NDC: " << m.NDC <<
            "\nName: " << m.name <<
            "\nChemical Name: " << m.Chemicalname <<
            "\nManufacturing Date: " << m.dates[0] <<
            "\nExpiration Date: " << m.dates[1] <<
            "\nPurchase Price: " << m.price[0] <<
            "\nSelling Price: " << m.price[1] <<
            "\nFormulation: " << m.formulation << "\n";
        return output;
    }

    friend istream& operator>>(istream& input, Medicine& med) {
        cout << "Enter NDC: ";
        input >> med.NDC;
        cout << "Enter Name: ";
        getline(input >> ws, med.name);
        cout << "Enter Chemical Name: ";
        getline(input, med.Chemicalname);
        cout << "Enter Manufacturing Date: ";
        getline(input, med.dates[0]);
        cout << "Enter Expiry Date: ";
        getline(input, med.dates[1]);
        cout << "Enter Purchase Price: ";
        input >> med.price[0];
        cout << "Enter Selling Price: ";
        input >> med.price[1];
        cout << "Enter Formulation: ";
        getline(input >> ws, med.formulation); // Ensure correct handling of trailing whitespace
        return input;
    }

    // Array population
    static void populatearray(Medicine* medicines, int maxSize, int& count) {
     //   medicines = new Medicine[maxSize];
        ifstream fin;
        fin.open("medicine_data.txt");
        try {
            if (fin.fail()) {
                throw runtime_error("File not found\n");
            }
        }
        catch (runtime_error r) {
            cout << r.what();
        }
        int index = 0;
        // Check format consistency with given file data
        while (index < maxSize && fin >> medicines[index].NDC) {
            fin >> medicines[index].name
                >> medicines[index].Chemicalname
                >> medicines[index].dates[0]
                >> medicines[index].dates[1]
                >> medicines[index].price[0]
                >> medicines[index].price[1]
                >> medicines[index].formulation;
            index++;
            countMedicine++;
        }
        count = index;
        fin.close();
    }
    static int  checkrecords() {
        string line;
        int count = 0;
        ifstream fin;
        fin.open("medicine_data.txt");
        while (getline(fin, line)) {
            count++;
        }
        fin.close();
        return count;
   }
};
int Medicine::countMedicine = 0;
