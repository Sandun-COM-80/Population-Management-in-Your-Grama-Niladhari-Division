#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Structure for Individual Records
struct Person {
    string nationalID;
    string name;
    int age;
    string gender;
    string address;
    string familyID;
};

// Function prototypes
void addPerson(vector<Person>&);
void displayPopulation(const vector<Person>&);
void searchPopulation(const vector<Person>&);
void displayStatistics(const vector<Person>&);
void saveToFile(const vector<Person>&);
void loadFromFile(vector<Person>&);

// Convert string to lowercase
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Function to add a new person
void addPerson(vector<Person>& population) {
    Person newPerson;
    cin.ignore();
    cout << "Enter National ID: ";
    getline(cin, newPerson.nationalID);
    cout << "Enter Name: ";
    getline(cin, newPerson.name);
    cout << "Enter Age: ";
    while (!(cin >> newPerson.age) || newPerson.age <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a valid Age: ";
    }
    cin.ignore();
    cout << "Enter Gender (Male/Female): ";
    getline(cin, newPerson.gender);
    cout << "Enter Address: ";
    getline(cin, newPerson.address);
    cout << "Enter Family ID: ";
    getline(cin, newPerson.familyID);

    population.push_back(newPerson);
    cout << "\nPerson added successfully!" << endl;
}

// Function to display all records
void displayPopulation(const vector<Person>& population) {
    if (population.empty()) {
        cout << "No population data available.\n";
        return;
    }

    cout << setw(15) << left << "National ID"
         << setw(20) << left << "Name"
         << setw(5) << left << "Age"
         << setw(10) << left << "Gender"
         << setw(30) << left << "Address"
         << setw(10) << left << "Family ID" << endl;

    cout << string(90, '-') << endl;

    for (const auto& person : population) {
        cout << setw(15) << left << person.nationalID
             << setw(20) << left << person.name
             << setw(5) << left << person.age
             << setw(10) << left << person.gender
             << setw(30) << left << person.address
             << setw(10) << left << person.familyID << endl;
    }
}

// Function to search population
void searchPopulation(const vector<Person>& population) {
    string searchCriteria;
    cout << "Enter search criteria (National ID/Name/Family ID/Address): ";
    cin.ignore();
    getline(cin, searchCriteria);

    bool found = false;
    for (const auto& person : population) {
        if (toLowerCase(person.nationalID) == toLowerCase(searchCriteria) ||
            toLowerCase(person.name) == toLowerCase(searchCriteria) ||
            toLowerCase(person.familyID) == toLowerCase(searchCriteria) ||
            toLowerCase(person.address) == toLowerCase(searchCriteria)) {
            cout << "\nRecord Found:\n";
            cout << "National ID: " << person.nationalID << endl;
            cout << "Name: " << person.name << endl;
            cout << "Age: " << person.age << endl;
            cout << "Gender: " << person.gender << endl;
            cout << "Address: " << person.address << endl;
            cout << "Family ID: " << person.familyID << endl;
            found = true;
            cout << "--------------------------" << endl;
        }
    }
    if (!found) {
        cout << "No matching records found.\n";
    }
}

// Function to display statistics
void displayStatistics(const vector<Person>& population) {
    int maleCount = 0, femaleCount = 0;
    int totalPopulation = population.size();

    for (const auto& person : population) {
        string genderLower = toLowerCase(person.gender);
        if (genderLower == "male" || genderLower == "m") {
            maleCount++;
        } else if (genderLower == "female" || genderLower == "f") {
            femaleCount++;
        }
    }

    cout << "\n--- Population Statistics ---\n";
    cout << "Total Population: " << totalPopulation << endl;
    cout << "Male Population: " << maleCount << endl;
    cout << "Female Population: " << femaleCount << endl;
}

// Function to save population data to a file
void saveToFile(const vector<Person>& population) {
    ofstream outputFile("GramaNiladhariData.csv");
    if (!outputFile) {
        cout << "Error saving data to file.\n";
        return;
    }

    outputFile << "NationalID,Name,Age,Gender,Address,FamilyID\n";
    for (const auto& person : population) {
        outputFile << person.nationalID << ',' << person.name << ','
                   << person.age << ',' << person.gender << ','
                   << person.address << ',' << person.familyID << '\n';
    }

    cout << "Data saved to GramaNiladhariData.csv successfully!\n";
}

// Function to load population data from a file
void loadFromFile(vector<Person>& population) {
    ifstream inputFile("GramaNiladhariData.csv");
    if (!inputFile) {
        cout << "No saved data found.\n";
        return;
    }

    string line, nationalID, name, age, gender, address, familyID;
    getline(inputFile, line); // Skip header
    while (getline(inputFile, line)) {
        stringstream ss(line);
        getline(ss, nationalID, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, gender, ',');
        getline(ss, address, ',');
        getline(ss, familyID, ',');

        Person person = {nationalID, name, stoi(age), gender, address, familyID};
        population.push_back(person);
    }

    cout << "Data loaded successfully!\n";
}

// Main Program
int main() {
    vector<Person> population;
    loadFromFile(population);

    int choice;
    while (true) {
        cout << "\n--- Grama Niladhari Population Management System ---\n";
        cout << "1. Add Person\n";
        cout << "2. Display All Population\n";
        cout << "3. Search Population\n";
        cout << "4. Display Statistics\n";
        cout << "5. Save to File\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addPerson(population);
                break;
            case 2:
                displayPopulation(population);
                break;
            case 3:
                searchPopulation(population);
                break;
            case 4:
                displayStatistics(population);
                break;
            case 5:
                saveToFile(population);
                break;
            case 6:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
