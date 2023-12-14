#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

// Function prototypes
void registerUser();
bool loginUser();
void changePassword();

int main() {
    int choice;

    do {
        cout << "\n********* MENU *********\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Change Password\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    cout << "Login successful!\n";
                } else {
                    cout << "Login failed. Invalid full name or password.\n";
                }
                break;
            case 3:
                changePassword();
                break;
            case 4:
                cout << "Thank You !\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

void registerUser() {
    string fullName, password;

    cout << "Enter your full name: ";
    cin.ignore();
    getline(cin, fullName);

  
    ifstream infile("user_list.txt");
    while (infile >> ws, !infile.eof()) {
        string storedFullName;
        getline(infile, storedFullName);
        if (fullName == storedFullName) {
            cout << "User already registered. Please choose a different full name.\n";
            infile.close();
            return;
        }
    }
    infile.close();

    cout << "Enter a password: ";
    cin >> password;

    ofstream userListFile("user_list.txt", ios::app);
    userListFile << fullName << endl;
    userListFile.close();

    ofstream userFile(fullName + ".txt");
    userFile << fullName << " " << password << endl;
    userFile.close();

    cout << "Registration successful!\n";
}
bool loginUser() {
    string fullName, password, storedFullName, storedPassword;

    cout << "Enter your full name: ";
    cin.ignore(); 
    getline(cin, fullName);


    ifstream userFile(fullName + ".txt");
    if (!userFile.good()) {
        cout << "User not found. Please register first.\n";
        return false;
    }

    cout << "Enter your password: ";
    cin >> password;


    userFile >> storedFullName >> storedPassword;
    userFile.close();

    if (password == storedPassword) {
        return true;
    } else {
        return false;
    }
}

void changePassword() {
    string fullName, oldPassword, newPassword, storedFullName, storedPassword;

    cout << "Enter your full name: ";
    cin.ignore(); 
    getline(cin, fullName);

   
    ifstream userFile(fullName + ".txt");
    if (!userFile.good()) {
        cout << "User not found. Please register first.\n";
        return;
    }

    cout << "Enter your current password: ";
    cin >> oldPassword;

    userFile >> storedFullName >> storedPassword;
    userFile.close();

   
    if (oldPassword == storedPassword) {
        cout << "Enter your new password: ";
        cin >> newPassword;

       
        ofstream userFile(fullName + ".txt");
        userFile << fullName << " " << newPassword << endl;
        userFile.close();

        cout << "Password changed successfully!\n";
    } else {
        cout << "Incorrect current password. Password change failed.\n";
    }
}
