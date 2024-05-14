#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a book
struct Book {
    string title;
    string author;
    int quantity;

    Book(string t, string a, int q) : title(t), author(a), quantity(q) {}
};

// Vector to store library books
vector<Book> library;

// Function to read books from a file
void ReadBooksFromFile(const string& LMSBooks) {
    ifstream file("LMSBooks.txt");
    if (!file.is_open()) {
        cerr << "Error opening file: " << LMSBooks << endl;
        return;
    }

    library.clear(); // Clear the library vector before reading new books

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string title, author;
        int quantity;

        getline(ss, title, ';');
        getline(ss, author, ';');
        ss >> quantity;

        library.emplace_back(title, author, quantity);
    }

    file.close();
}

// Function to check user credentials against a file
bool UserCheckCredentials(const string& username, const string& password) {
    ifstream file("LMSUserlogin.csv");

    if (!file.is_open()) {
        cerr << "Error opening the file!" << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string storedUsername, storedPassword;
		
		// Extract username and password from each line in the file
        if (getline(iss, storedUsername, ',') && getline(iss, storedPassword)) {
            if (storedUsername == username && storedPassword == password) {
                return true;  
            }
        }
    }

    return false;  
}

// Function to check admin credentials against a file
bool AdminCheckCredentials(const string& username, const string& password){
    ifstream file("LMSAdminlogin.csv");

    if (!file.is_open()) {
        cerr << "Error opening the file!" << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string storedUsername, storedPassword;
		
		// Extract username and password from each line in the file
        if (getline(iss, storedUsername, ',') && getline(iss, storedPassword)) {
            if (storedUsername == username && storedPassword == password) {
                return true;  
            }
        }
    }

    return false;  
}

// Function to borrow a book
void BorrowBook() {
    string bookTitle;
    cout << "Enter the title of the book you want to borrow: ";
    getline(cin, bookTitle);

    auto it = find_if(library.begin(), library.end(), [&](const Book& book) {
        return book.title == bookTitle && book.quantity > 0;
    });

    if (it != library.end()) {
        it->quantity--;
        cout << "You have successfully borrowed \"" << bookTitle << "\"." << endl;
    } else {
        cout << "Sorry, \"" << bookTitle << "\" is either not available or not found in the library." << endl;
    }
}

// Function to return a book
void ReturnBook() {
    string bookTitle;
    cout << "Enter the title of the book you want to return: ";
    getline(cin, bookTitle);

    auto it = find_if(library.begin(), library.end(), [&](const Book& book) {
        return book.title == bookTitle;
    });

    if (it != library.end()) {
        it->quantity++;
        cout << "Thank you for returning \"" << bookTitle << "\"." << endl;
    } else {
        cout << "Sorry, \"" << bookTitle << "\" was not found in the library." << endl;
    }
}

// Function to add a new book to the library
void AddNewBook() {
    string title, author;
    int quantity;

    cout << "Enter the title of the book: ";
    getline(cin, title);

    cout << "Enter the author of the book: ";
    getline(cin, author);

    cout << "Enter the quantity of the book: ";
    cin >> quantity;

    library.push_back(Book(title, author, quantity));
    cout << "\"" << title << "\" by " << author << " (Quantity: " << quantity << ") has been added to the library." << endl;
}

// Function to remove a book from the library
void RemoveBook() {
    string bookTitle;
    cout << "Enter the title of the book you want to remove: ";
    getline(cin, bookTitle);

    auto it = find_if(library.begin(), library.end(), [&](const Book& book) {
        return book.title == bookTitle;
    });

    if (it != library.end()) {
        library.erase(it);
        cout << "\"" << bookTitle << "\" has been removed from the library." << endl;
    } else {
        cout << "Sorry, \"" << bookTitle << "\" was not found in the library." << endl;
    }
}

int main(){
    string username;
    string password;

    cout << "\t Welcome to Library Management System" << endl;
    
    bool successfulLogin = false;

    while (!successfulLogin) {
        cout << "Enter User Name: ";
        getline(cin, username);

        cout << "Enter Password: ";
        getline(cin, password);
        
        if (UserCheckCredentials(username, password)) {
            // User logged in
            cout << "Successful login!" << endl;
            int choice;
            cout << "Choose preferred action\n1. Borrow book\n2. Return Book" << endl;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            
            switch (choice) {
                case 1:
                    BorrowBook();
                    break;
                case 2:
                    ReturnBook();
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
            successfulLogin = true;
        }
        else if(AdminCheckCredentials(username, password)) {
            // Admin logged in
            cout << "Successful login!" << endl;
            int choice;
            cout << "Choose preferred action\n1. Add new book\n2. Remove book" << endl;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            
            switch (choice) {
                case 1:
                    AddNewBook();
                    break;
                case 2:
                    RemoveBook();
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
            successfulLogin = true;
        }
        else {
            // Invalid credentials
            int Relogin;
            cout << "Invalid username or password.\nWould you like to try again?\n1. Yes\n2. No\n";
            cin >> Relogin;

            if (Relogin != 1) {
                break;
            }
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    ReadBooksFromFile("LMSBooks.txt");

    return 0;
}
