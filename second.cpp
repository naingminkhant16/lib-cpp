#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Book
{
    int book_id;
    string title;
    string author;
    string category;
    string status;
} book;

class Library
{
    Book books_list[5];

public:
    Library();
    Book *getAllBooks();
};
Library::Library()
{
    string book_str;                   // variable to store book string line by line
    ifstream readBookFile("book.txt"); // open book file stream
    int j = 0;
    while (getline(readBookFile, book_str)) // get line by line using getline function
    {
        string split_str;
        string splited_arr[] = {};
        int index = 0;
        stringstream book_str_stream(book_str);

        for (int i = 0; i < book_str.length(); i++)
        {
            // if (book_str[i] == ' ')
            // {
            //     index++;
            // }
            // else
            // {
            splited_arr[index] = book_str[i];
            // }
        }
        cout << splited_arr << endl;

        // stringstream(splited_arr[0]) >> book.book_id;
        // book.title = splited_arr[1];
        // book.author = splited_arr[2];
        // book.category = splited_arr[3];
        // book.status = (splited_arr[4] == "a") ? "Available" : "Borrowed";
        // this->books_list[j] = book;
        // cout << book.title << endl;
        // j++;
    }
    readBookFile.close(); // close book file stream
}
Book *Library::getAllBooks()
{
    return books_list;
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
    Library lib;
    Book *books = lib.getAllBooks();
    for (int i = 0; i < 5; i++)
    {
        cout << books[i].title << endl;
    }
}

void displayMenu(const string menus[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "\t" << menus[i]
             << endl;
    }
}