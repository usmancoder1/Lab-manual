#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    string isbn;
    string title;
    string author;
    int year;

    Book* next;
    Book* prev;

    Book(string i, string t, string a, int y) {
        isbn = i;
        title = t;
        author = a;
        year = y;
        next = NULL;
        prev = NULL;
    }
};

class Library {
private:
    Book* head;
    Book* tail;
    int total;

public:
    Library() {
        head = tail = NULL;
        total = 0;
    }

    void insertBook(string isbn, string title, string author, int year) {
        Book* newBook = new Book(isbn, title, author, year);

        if (head == NULL) {
            head = tail = newBook;
        } else {
            tail->next = newBook;
            newBook->prev = tail;
            tail = newBook;
        }

        total++;
        cout << "Book inserted successfully.\n";
    }

    Book* searchBook(string key) {
        Book* temp = head;

        while (temp != NULL) {
            if (temp->isbn == key || temp->title == key) {
                return temp;
            }
            temp = temp->next;
        }

        return NULL;
    }

    void modifyBook(string key) {
        Book* found = searchBook(key);

        if (found == NULL) {
            cout << "Book not found.\n";
            return;
        }

        cout << "Enter new title: ";
        cin.ignore();
        getline(cin, found->title);

        cout << "Enter new author: ";
        getline(cin, found->author);

        cout << "Enter new publication year: ";
        cin >> found->year;

        cout << "Book updated successfully.\n";
    }

    void displayBooks() {
        Book* temp = head;

        if (temp == NULL) {
            cout << "Library is empty.\n";
            return;
        }

        cout << "\nAll Books:\n";
        while (temp != NULL) {
            cout << "ISBN: " << temp->isbn << endl;
            cout << "Title: " << temp->title << endl;
            cout << "Author: " << temp->author << endl;
            cout << "Year: " << temp->year << endl;
            cout << "----------------------\n";
            temp = temp->next;
        }

        cout << "Total books: " << total << endl;
    }
};

int main() {
    Library lib;
    int choice;
    string isbn, title, author;
    int year;
    string key;

    do {
        cout << "\n1. Insert Book";
        cout << "\n2. Search Book";
        cout << "\n3. Modify Book";
        cout << "\n4. Display Books";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter ISBN: ";
            cin >> isbn;
            cin.ignore();
            cout << "Enter title: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            cout << "Enter year: ";
            cin >> year;
            lib.insertBook(isbn, title, author, year);
            break;

        case 2:
            cout << "Enter ISBN or Title to search: ";
            cin.ignore();
            getline(cin, key);
            {
                Book* found = lib.searchBook(key);
                if (found) {
                    cout << "Book Found:\n";
                    cout << found->title << " by " << found->author << endl;
                } else {
                    cout << "Book not found.\n";
                }
            }
            break;

        case 3:
            cout << "Enter ISBN or Title to modify: ";
            cin.ignore();
            getline(cin, key);
            lib.modifyBook(key);
            break;

        case 4:
            lib.displayBooks();
            break;
        }

    } while (choice != 0);

    return 0;
}
