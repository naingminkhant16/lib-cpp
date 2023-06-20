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
    void setCategory(string &category)
    {
        this->category = category;
    }
    void setStatus(string &status)
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
    bool store();
    void displayInfo();
    bool edit(string id);
    bool destroy(string id);
};

void Book::displayInfo()
{
    cout << endl
         << "Book ID: \t" << id << endl
         << "Book Title: \t" << title << endl
         << "Book Author: \t" << author << endl
         << "Book Category: \t" << category << endl
         << "Book Status: \t" << getStatus() << endl
         << "------------------------------" << endl;
}

bool Book::store()
{
    ofstream bookFile("book.txt", ios::app);
    bookFile << id << " " << title
             << " " << author << " " << category << " " << status << endl;
    bookFile.close();
    return true;
}

bool Book::edit(string id)
{
    string line, temp[5], tempStr;
    fstream file("book.txt", ios::in | ios::out);
    bool control = true;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            int i = 0;
            while (getline(ss, tempStr, ' '))
            {
                temp[i] = tempStr;
                i++;
            }

            if (temp[0] == id) // id is found
            {
                this->id = temp[0];
                this->title = temp[1];
                this->author = temp[2];
                this->category = temp[3];
                this->status = temp[4];

                cout << endl
                     << "We found the following data:" << endl;
                displayInfo();

                do
                {
                    cout << "Choose the number to edit : " << endl
                         << endl;
                    int selected_no;
                    bool loop = true; // loop control for status validation

                    cout << "1 for title" << endl;
                    cout << "2 for author" << endl;
                    cout << "3 for category" << endl;
                    cout << "4 for status" << endl;
                    cout << "5 for return to main menu" << endl;
                    cout << "Enter number : ";
                    cin >> selected_no;
                    cout << endl;
                    switch (selected_no)
                    {
                    case 1:
                        cout << "Enter new title : " << endl;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, title);
                        for (int i = 0; i < title.length(); i++)
                        {
                            if (title[i] == ' ')
                                title[i] = '_';
                        }
                        control = false;
                        break;
                    case 2:
                        cout << "Enter new author : " << endl;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, author);
                        for (int i = 0; i < author.length(); i++)
                        {
                            if (author[i] == ' ')
                                author[i] = '_';
                        }
                        control = false;
                        break;
                    case 3:
                        cout << "Enter new category : " << endl;
                        cin >> category;
                        control = false;
                        break;
                    case 4:
                        do
                        {
                            cout << "Enter new status ('a' for available / 'ua' for unavailable) : " << endl;
                            cin >> status;
                            if (status == "a" || status == "ua")
                                loop = false;
                            else
                                cout << "Invalid Input! Choose again." << endl;
                        } while (loop);
                        control = false;
                        break;
                    case 5:
                        return true;
                        break;
                    default:
                        cout << endl
                             << "Invalid number!" << endl
                             << "Choose again." << endl;
                    }
                } while (control);
                file.close();
                // create and open temporary file
                ofstream outfile;
                file.open("book.txt");
                outfile.open("temp.txt", ios::app);

                while (getline(file, line))
                {
                    if (line.find(this->id) == string::npos)
                        outfile << line << endl;
                    else
                    {
                        outfile << this->id << " " << this->title << " " << this->author
                                << " " << this->category << " " << this->status << endl;
                    }
                }
                outfile.close();
                file.close();
                remove("book.txt");
                rename("temp.txt", "book.txt");
                cout << endl
                     << "Successfully updated data!" << endl;
                return true;
            }
        }
        cout << endl
             << "Not found!" << endl;
        return false;
    }
    else
    {
        cout << endl
             << "Could not open file!" << endl;
        return false;
    }
}

bool Book::destroy(string id)
{
    string line, book_id;
    fstream file("book.txt", ios::in | ios::out);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);

            getline(ss, book_id, ' '); // get id from line

            if (book_id == id) // id is found
            {
                file.close();

                // create and open temporary file
                ofstream outfile;
                file.open("book.txt");
                outfile.open("temp.txt", ios::app);

                while (getline(file, line))
                    if (line.find(id) == string::npos)
                        outfile << line << endl;

                outfile.close();
                file.close();
                remove("book.txt");
                rename("temp.txt", "book.txt");

                return true;
            }
        }
        cout << "Not found" << endl;
        return false;
    }
    else
    {
        cout << endl
             << "Could not open file!" << endl;
        return false;
    }
}

class Library
{
public:
    void viewBookList(string type);

    void addNewBook();

    void editBook();

    void deleteBook();
};

void Library::viewBookList(string type)
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
        bookFile.close();
    }
    else
        cout << "Cannot open file!" << endl;
}

void Library::addNewBook()
{
    string id, title, author, category;

    cout << "Adding a new book" << endl;

    // check duplicated id
    do
    {
        bool control = true;
        string line;
        cout << "Enter Book Id : ";
        cin >> id;
        ifstream file("book.txt");
        while (getline(file, line))
        {
            if (line.find(id) != string::npos) // id found
            {
                cout << "Duplicated ID found!"
                     << " Enter the Id again." << endl;
                control = false;
                break;
            }
        }
        if (control)
            break;
    } while (true);

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

    Book book;
    book.setId(id);
    book.setTitle(title);
    book.setAuthor(author);
    book.setCategory(category);

    if (book.store())
        cout << endl
             << "Successfully added." << endl;
    else
        cout << endl
             << "Failed to store new book!" << endl;
}

void Library::deleteBook()
{
    string id;
    cout << "Enter Book ID to delete book : " << endl;
    cin >> id;
    Book book;
    if (book.destroy(id))
        cout << endl
             << "Successfully deleted!" << endl;
    else
        cout << endl
             << "Data not found for id " << id << endl;
}
void Library::editBook()
{
    string id;
    cout << "Enter Book ID to edit book : " << endl;
    cin >> id;
    Book book;
    if (!book.edit(id))
        cout << endl
             << "Data not found for id " << id << endl;
}

class Menu
{
protected:
    int selected_menu_no;
    void displayMenuList(const string menus[], int size);
};

void Menu::displayMenuList(const string menus[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "\t" << menus[i]
             << endl;
    }
}

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

public:
    void displayMainMenu();

    void displaySubMenu();
};

void LibraryMenu::displayMainMenu()
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
        library.addNewBook();
        displayMainMenu();
        break;
    case 3:
        library.editBook();
        displayMainMenu();
        break;
    case 4:
        library.deleteBook();
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

void LibraryMenu::displaySubMenu()
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

int main()
{
    string guest_name;
    cout << "Please Enter your name :";
    getline(cin, guest_name);
    cout << endl
         << "----------------------------------------------" << endl
         << "Hello " << guest_name << ". Welcome to our library." << endl
         << "----------------------------------------------" << endl;

    LibraryMenu library_menu;
    library_menu.displayMainMenu();
    return 0;
}