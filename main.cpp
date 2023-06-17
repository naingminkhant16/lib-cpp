#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>

using namespace std;

class Book
{

    string id, title, author, category, status = "a";

public:
    void setId(string &id)
    {
        this->id = id;
    }
    void setTitle(string &title)
    {
        this->title = title;
    }
    void setAuthor(string &author)
    {
        this->author = author;
    }
    void setCategory(string category)
    {
        this->category = category;
    }
    void setStatus(string status)
    {
        this->status = status;
    }
    string getId() { return id; }
    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getCategory() { return category; }
    string getStatus()
    {
        if (status == "a")
            return "available";
        else if (status == "ua")
            return "unavailable";
    }
    void store()
    {
        ofstream bookFile("book.txt", ios::app);
        bookFile << id << " " << title
                 << " " << author << " " << category << " " << status << endl;
        bookFile.close();
        cout << "Successfully added." << endl;
    }
    void displayInfo()
    {
        cout << "Book ID: \t" << id << endl;
        cout << "Book Title: \t" << title << endl;
        cout << "Book Author: \t" << author << endl;
        cout << "Book Category: \t" << category << endl;
        cout << "Book Status: \t" << getStatus() << endl;
        cout << "------------------------------" << endl;
    }
};

class Library
{
public:
    void viewBookList(string type)
    {
        string header;
        if (type == "all")
            header = "all";
        else if (type == "a")
            header = "available";
        else if (type == "ua")
            header = "unavailable";

        cout << endl
             << "View " << header << " books" << endl
             << endl;

        ifstream bookFile("book.txt");
        string temp[5], tmpStr, line;

        if (bookFile.is_open())
        {
            while (getline(bookFile, line))
            {
                stringstream ss(line);
                int i = 0;

                while (getline(ss, tmpStr, ' '))
                {
                    temp[i] = tmpStr;
                    i++;
                }

                if (type == temp[4] || type == "all")
                {
                    Book book;
                    book.setId(temp[0]);
                    book.setTitle(temp[1]);
                    book.setAuthor(temp[2]);
                    book.setCategory(temp[3]);
                    book.setStatus(temp[4]);
                    book.displayInfo();
                }
            }
        }
        else
            cout << "Cannot open file!" << endl;
    }

    void addNewBook(Book *book)
    {
        string id, title, author, category;

        cout << "Adding a new book" << endl;
        cout << "Enter Book Id : ";
        cin >> id;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Book's Title : ";
        getline(cin, title);
        for (int i = 0; i < title.length(); i++)
        {
            if (title[i] == ' ')
                title[i] = '_';
        }

        cout << "Enter Book's Author : ";
        getline(cin, author);
        for (int i = 0; i < author.length(); i++)
        {
            if (author[i] == ' ')
                author[i] = '_';
        }
        cout << "Enter Book's Category : ";
        cin >> category;

        book->setId(id);
        book->setTitle(title);
        book->setAuthor(author);
        book->setCategory(category);
        book->store();
    }
    void editBook(string id)
    {
    }
};

class Menu
{
protected:
    int selected_menu_no;
    void displayMenuList(const string menus[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            cout << "\t" << menus[i]
                 << endl;
        }
    }
};

class LibraryMenu : public Menu
{
    const string MAIN_MENUS[5] = {"1. View book List",
                                  "2. Add new book",
                                  "3. Edit book information",
                                  "4. Delete book",
                                  "5. Exit the program"};
    const string SUB_MENUS[4] = {"1. View all books in library",
                                 "2. View all available books in library",
                                 "3. View all unavailable books in library",
                                 "4. Return to main menu"};
    Library library;
    Book book;

public:
    void displayMainMenu()
    {
        cout << endl
             << "Main Menu (Choose one number)." << endl
             << endl;

        displayMenuList(MAIN_MENUS, sizeof(MAIN_MENUS) / sizeof(string));
        cin >> selected_menu_no;

        switch (selected_menu_no)
        {
        case 1:
            displaySubMenu();
            break;
        case 2:
            library.addNewBook(&book);
            displayMainMenu();
            break;
        case 5:
            cout << "Bye Bye" << endl;
            break;
        default:
            cout << "Invalid number!" << endl;
            cout << "Choose again!" << endl;
            displayMainMenu();
            break;
        }
    }

    void displaySubMenu()
    {
        cout << endl
             << "Display book list sub menu (Choose one number)." << endl
             << endl;

        displayMenuList(SUB_MENUS, sizeof(SUB_MENUS) / sizeof(string));
        cin >> selected_menu_no;

        switch (selected_menu_no)
        {
        case 1:
            library.viewBookList("all");
            displaySubMenu();
            break;
        case 2:
            library.viewBookList("a");
            displaySubMenu();
            break;
        case 3:
            library.viewBookList("ua");
            displaySubMenu();
            break;
        case 4:
            displayMainMenu();
            break;
        default:
            cout << "Invalid number! " << endl
                 << "Choose again." << endl;
            displaySubMenu();
            break;
        }
    }
};

int main()
{
    LibraryMenu library_menu;
    library_menu.displayMainMenu();
    return 0;
}