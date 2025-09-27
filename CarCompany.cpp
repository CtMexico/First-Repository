#include <iostream>
#include <string>
#include <iomanip> // Include for formatting output with std::fixed and std::setprecision

using namespace std;

// Define a struct for car sales records
struct Record {
    string customer;
    string model;
    int year;
    double mileage;
    double price;
};

// === Function Prototypes (Declarations) ===
// These lines tell the compiler about the functions that exist in our program.
// You do not need to change these lines.
// Your task is to write the actual code for these functions in the section below main().
double calculateTotalSales(const Record arr[], int size);
void searchByCustomer(const Record arr[], int size, const string &name);


int main() {
    const int SIZE = 6;

    // Given array of sales records (teacher provides this data)
    Record sales[SIZE] = {
        {"Alice Johnson", "Toyota Corolla", 2020, 15000, 18000},
        {"Bob Smith", "Honda Civic", 2019, 20000, 17000},
        {"Charlie Lee", "Tesla Model 3", 2021, 5000, 35000},
        {"Diana Perez", "Ford Focus", 2018, 30000, 14000},
        {"Ethan Brown", "Chevrolet Malibu", 2022, 2000, 22000},
        {"Fiona White", "BMW X5", 2020, 10000, 45000}
    };

    // TODO: Goal 1 - Declare a new array named 'list' with the same size
    // and write a loop to copy all records from the 'sales' array into it.
    Record list[SIZE];
    for(int i = 0; i < SIZE; ++i) {
        list[i] = sales[i];
    }


    // Goal 2 - Call function to calculate total sales and print it.
    // We use std::fixed and std::setprecision to format the output as currency (two decimal places).
    cout << fixed << setprecision(2);
    cout << "Total Sales: $" << calculateTotalSales(list, SIZE) << endl;
    cout << "(Press Enter, then type customer name to search)" << endl;

    // Goal 3 - Ask user for customer name and search
    // We use cin.ignore() to clear the input buffer. After the previous output,
    // a newline character ('\n') is left in the input stream. If not ignored,
    // getline() would immediately read this newline and stop, preventing you from entering a name.
    // This line consumes that leftover newline character.
    cin.ignore();
    string name;
    cout << "Enter customer name to search: ";
    getline(cin, name);

    searchByCustomer(list, SIZE, name);

    return 0;
}


// === Function Implementations (Definitions) ===
// This is where you will write the actual code for the functions.


// TODO: Goal 2  Implement the calculateTotalSales function.
// This function should loop through the array and return the sum of all 'price' fields.
double calculateTotalSales(const Record arr[], int size) {
    double total = 0.0;
    for(int i = 0; i < size; ++i) {
        total += arr[i].price;
    }
    return total;
}


// TODO: Goal 3 Implement the searchByCustomer function.
// This function should search for a customer by name. If found, print all record details.
// If not found, print a "No record found" message.
// Remember to format the price output to two decimal places.
void searchByCustomer(const Record arr[], int size, const string &name) {
    string searchName = name;
    transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);

    for(int i = 0; i < size; ++i) {
        string recordName = arr[i].customer;
        transform(recordName.begin(), recordName.end(), recordName.begin(), ::tolower);

        if(recordName == searchName) {
            cout << "Customer: " << arr[i].customer << endl;
            cout << "Model: " << arr[i].model << endl;
            cout << "Year: " << arr[i].year << endl;
            cout << "Mileage: " << arr[i].mileage << endl;
            cout << "Price: " << arr[i].price << endl;
            return;
        }
    }

    cout << "No record found for customer: " << name << endl;
}
