#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Book {
    int bookID;
    char title[50];
    char author[50];
    bool issued;

public:
    void addBook() {
        cout << "\nEnter Book ID: ";
        cin >> bookID;

        cin.ignore();

        cout << "Enter Book Title: ";
        cin.getline(title, 50);

        cout << "Enter Author Name: ";
        cin.getline(author, 50);

        issued = false;
    }

    void displayBook() {
        cout << "\nBook ID: " << bookID;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nStatus: ";

        if (issued)
            cout << "Issued";
        else
            cout << "Available";

        cout << endl;
    }

    int getBookID() {
        return bookID;
    }

    char* getTitle() {
        return title;
    }

    char* getAuthor() {
        return author;
    }

    void issueBook() {
        if (!issued) {
            issued = true;
            cout << "\nBook Issued Successfully!";
        } else {
            cout << "\nBook Already Issued!";
        }
    }

    void returnBook() {
        if (issued) {
            issued = false;
            cout << "\nBook Returned Successfully!";
        } else {
            cout << "\nBook Was Not Issued!";
        }
    }
};

void addBookRecord() {
    Book b;

    ofstream file("library.dat", ios::binary | ios::app);

    b.addBook();
    file.write((char*)&b, sizeof(b));

    file.close();

    cout << "\nBook Added Successfully!\n";
}

void displayBooks() {
    Book b;

    ifstream file("library.dat", ios::binary);

    while (file.read((char*)&b, sizeof(b))) {
        b.displayBook();
        cout << "\n----------------------";
    }

    file.close();
}

void searchBook() {
    Book b;
    char searchTitle[50];
    bool found = false;

    ifstream file("library.dat", ios::binary);

    cin.ignore();

    cout << "\nEnter Book Title to Search: ";
    cin.getline(searchTitle, 50);

    while (file.read((char*)&b, sizeof(b))) {
        if (strcmp(b.getTitle(), searchTitle) == 0) {
            b.displayBook();
            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "\nBook Not Found!";
}

int main() {
    int choice;

    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Search Book";
        cout << "\n4. Exit";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice) {
        case 1:
            addBookRecord();
            break;

        case 2:
            displayBooks();
            break;

        case 3:
            searchBook();
            break;

        case 4:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!";
        }

    } while(choice != 4);

    return 0;
}