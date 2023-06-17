#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Book
{
private:
    int book_id;
    string title;
    string author;
    string category;
    string status;

public:
    Book(string &book);
    void displayInfo();
};

Book::Book(string &book)
{
    string split_str;
    string splited_arr[5] = {};
    stringstream book_string_stream(book);
    int i = 0;

    while (getline(book_string_stream, split_str, ' '))
    {
        splited_arr[i] = split_str;
        i++;
    }

    stringstream(splited_arr[0]) >> this->book_id;
    this->title = splited_arr[1];
    this->author = splited_arr[2];
    this->category = splited_arr[3];
    this->status = (splited_arr[4] == "a") ? "Available" : "Borrowed";
}
void Book::displayInfo()
{
    cout << "===============================" << endl;
    cout << "Book ID : " << book_id << endl;
    cout << "Title : " << title << endl;
    cout << "Author : " << author << endl;
    cout << "Category : " << category << endl;
    cout << "Availability Status : " << status << endl;
    cout << "===============================" << endl;
}

void viewBookList();
void ViewAllBooksInLibrary();
void displayMenu(const string menus[], int size);

int main()
{
    int selected_menu;

    const string MAIN_MENUS[] = {"1. View book List",
                                 "2. Add new book",
                                 "3. Edit book information",
                                 "4. Delete book",
                                 "5. Exit the program"};

    cout << "Main Menu" << endl
         << endl;
    displayMenu(MAIN_MENUS, sizeof(MAIN_MENUS) / sizeof(string));
    cin >> selected_menu;

    switch (selected_menu)
    {
    case 1:
        viewBookList();
        break;

    default:
        cout << "Invalid number!" << endl;
        break;
    }
    return 0;
}

void viewBookList()
{
    int selected_menu;
    const string SUB_MENUS[] = {"1. View all books in library",
                                "2. View all available books in library",
                                "3. View all unavailable books in library",
                                "4. Return to main menu"};

    cout << "Display book list sub menu" << endl
         << endl;

    displayMenu(SUB_MENUS, sizeof(SUB_MENUS) / sizeof(string));

    cin >> selected_menu;

    switch (selected_menu)
    {
    case 1:
        ViewAllBooksInLibrary();
        break;

    default:
        break;
    }
};

void ViewAllBooksInLibrary()
{
    string book_str; // variable to store book string line by line
    ifstream readBookFile;

    readBookFile.open("book.txt");          // open book file stream
    while (getline(readBookFile, book_str)) // get line by line using getline function
    {
        Book book(book_str);
        book.displayInfo();
    }
    readBookFile.close(); // close book file stream
}

void displayMenu(const string menus[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "\t" << menus[i]
             << endl;
    }
}