#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <iomanip>

using namespace std;

class Book
{
    // private properties of book class
    string id, title, author, category, status = "a";

public:
    // Implementation of Encapsulation
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
        return (status == "a") ? "available" : "unavailable"; // used ternary operator for the output of book's status
    }

    // methods declaration
    bool store();            // for adding new book
    void displayInfo();      // display the output of the information of book
    bool edit(string id);    // for editing the book's information base on book's id
    bool destroy(string id); // for deleting the book base on book's id
};

// methods definition outside Book class
void Book::displayInfo()
{
    // output book info
    cout << endl
         << setfill('-')
         << "+" << right << setw(51) << "+" << endl
         << left << setw(20) << "| ID" << right << setw(30) << id << " |" << endl
         << left << setw(20) << "| Title" << right << setw(30) << title << " |" << endl
         << left << setw(20) << "| Author" << right << setw(30) << author << " |" << endl
         << left << setw(20) << "| Category" << right << setw(30) << category << " |" << endl
         << left << setw(20) << "| Status:" << right << setw(30) << getStatus() << " |" << endl
         << "+" << right << setw(51) << "+" << endl;
}

bool Book::store() // return true on success, false on fail
{
    try
    {
        ofstream bookFile("book.txt", ios::app); // open book.txt file using ofstream
        if (!bookFile.is_open())
        {
            string err_message = "Could not open file!";
            throw(err_message); // throw exception if file can't open
        }
        // write new book's info to file
        bookFile << id << " " << title
                 << " " << author << " " << category << " " << status << endl;

        bookFile.close(); // file close
        return true;
    }
    catch (string error_message)
    {
        cerr << endl
             << error_message << endl; // display error message
        return false;
    }
}

bool Book::edit(string id) // find and edit book info //return true on success,otherwise false
{
    string line, temp[5], tempStr;
    fstream file("book.txt", ios::in | ios::out);
    bool control = true;

    if (file.is_open())
    {
        while (getline(file, line)) // get books by each line
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
                     << "We found the following data." << endl;
                displayInfo();

                do
                {
                    int selected_no;
                    bool loop = true; // loop control for status validation

                    cout << endl
                         << "Choose the number below to edit. " << endl
                         << endl;

                    cout << "Choose 1 to edit title." << endl;
                    cout << "Choose 2 to edit author." << endl;
                    cout << "Choose 3 to edit category." << endl;
                    cout << "Choose 4 to edit status." << endl;
                    cout << "Choose 5 to return to main menu." << endl
                         << endl;
                    cout << "Enter number : ";
                    cin >> selected_no;
                    cout << endl;
                    switch (selected_no)
                    {
                    case 1:
                        cout << "Enter new title : ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, title);
                        for (int i = 0; i < title.length(); i++) // rename the title into snake case
                        {
                            if (title[i] == ' ')
                                title[i] = '_';
                        }
                        control = false; // set control to false to get out of loop
                        break;
                    case 2:
                        cout << "Enter new author : ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, author);
                        for (int i = 0; i < author.length(); i++) // rename the author into snake case
                        {
                            if (author[i] == ' ')
                                author[i] = '_';
                        }
                        control = false; // set control to false to get out of loop
                        break;
                    case 3:
                        cout << "Enter new category : ";
                        cin >> category;
                        control = false; // set control to false to get out of loop
                        break;
                    case 4:
                        do
                        {
                            cout << "Enter new status ('a' for available / 'ua' for unavailable) : ";
                            cin >> status;
                            if (status == "a" || status == "ua") // check if status is valid input
                                loop = false;                    // break loop
                            else
                                cout << "Invalid Input! Choose again." << endl;
                        } while (loop);
                        control = false; // set control to false to get out of loop
                        break;
                    case 5: // do nothing and return to main menu
                        return true;
                        break;
                    default:
                        cout
                            << "Invalid number!" << endl
                            << "Choose again." << endl;
                    }
                } while (control);
                file.close();

                ofstream outfile;
                file.open("book.txt");
                outfile.open("temp.txt", ios::app); // create and open temporary file

                while (getline(file, line))
                {
                    // rewrite the existing data into temp file until it finds an id that wants to get updated
                    if (line.find(this->id) == string::npos)
                        outfile << line << endl;
                    else
                    { // write the new data if it is found
                        outfile << this->id << " " << this->title << " " << this->author
                                << " " << this->category << " " << this->status << endl;
                    }
                }
                outfile.close(); // temp file close
                file.close();
                remove("book.txt");             // delete book file
                rename("temp.txt", "book.txt"); // and rename temp.txt to book.txt
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

bool Book::destroy(string id) // find and delete book with id // return true on success,otherwise false
{
    string line, book_id;
    fstream file("book.txt", ios::in | ios::out);

    if (!file.is_open())
    {
        cerr << endl
             << "Could not open file!" << endl;
        return false;
    }

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
                if (line.find(id) == string::npos) // rewriting existing data expect the given id
                    outfile << line << endl;

            outfile.close();
            file.close();
            remove("book.txt");             // delete book file
            rename("temp.txt", "book.txt"); // rename temp.txt to book.txt

            return true;
        }
    }
    // if the search id is not found, the code will reach here, and print 'Not found' and return false
    cout << endl
         << "Not found" << endl;
    return false;
}

class Library
{
public:
    // methods declaration for Library class
    void viewBookList(string type);

    void addNewBook();

    void editBook();

    void deleteBook();
};

// methods definition outsie Library class
void Library::viewBookList(string type) // display books' info according to type
{
    string header, temp[5], tmpStr, line;

    if (type == "all")
        header = "all";
    else if (type == "a")
        header = "available";
    else if (type == "ua")
        header = "unavailable";

    cout << endl
         << "----------------------------------------------------" << endl
         << "View " << header << " books" << endl
         << "----------------------------------------------------" << endl;

    ifstream bookFile("book.txt"); // open book file

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

            if (type == temp[4] || type == "all") // display book's info base on type
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
        bookFile.close(); // close book file
    }
    else
        cout << "Cannot open file!" << endl;
}

void Library::addNewBook() // for storing new book
{
    string id, title, author, category;

    cout << endl
         << "----------------------------------------------------" << endl
         << "Adding a new book" << endl
         << "----------------------------------------------------" << endl;

    // check duplicated id
    do
    {
        bool control = true;
        string line;
        cout << endl;
        cout << "Enter Book Id : ";
        cin >> id;
        ifstream file("book.txt"); // open book file to check duplicated id
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
        if (control) // control will still be true if duplicated id is not found
            break;   // break the loop
    } while (true);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Book's Title : ";
    getline(cin, title);
    for (int i = 0; i < title.length(); i++) // rename title to snake case
    {
        if (title[i] == ' ')
            title[i] = '_';
    }

    cout << "Enter Book's Author : ";
    getline(cin, author);
    for (int i = 0; i < author.length(); i++) // rename author to snake case
    {
        if (author[i] == ' ')
            author[i] = '_';
    }
    cout << "Enter Book's Category : ";
    cin >> category;

    // set book infos using setter methods
    Book book;
    book.setId(id);
    book.setTitle(title);
    book.setAuthor(author);
    book.setCategory(category);

    if (book.store()) // book.store() will return true on success,otherwise false
        cout << endl
             << "Successfully added." << endl;
    else
        cout << endl
             << "Failed to store new book!" << endl;
}

void Library::deleteBook() // for deleting book
{
    string id;
    Book book;
    char confirm;
    cout << endl
         << "----------------------------------------------------" << endl
         << "Deleting Book" << endl
         << "----------------------------------------------------" << endl;

    cout << endl
         << "Enter Book ID to delete book : ";
    cin >> id;

    cout << "Are you sure you want to delete?(y/n)? : ";
    cin >> confirm;
    confirm = tolower(confirm);
    if (confirm == 'y')
    {
        if (book.destroy(id)) // book.destroy(id) will return true on success,otherwise false
            cout << endl
                 << "Successfully deleted!" << endl;
        else
            cout << endl
                 << "Data not found for id " << id << "!" << endl;
    }
    else
        cout << "Cancelled Delete!" << endl;
}

void Library::editBook()
{
    string id;
    Book book;
    cout << endl
         << "----------------------------------------------------" << endl
         << "Editing Book" << endl
         << "----------------------------------------------------" << endl;
    cout << endl
         << "Enter Book ID to edit book : ";
    cin >> id;
    if (!book.edit(id)) // book.edit(id) will return true on success,otherwise false
        cout << endl
             << "Data not found for id " << id << endl;
}

class Menu
{
public:
    Menu(); // constructor declaration

protected:
    string guest_name;
    int selected_menu_no;
    void displayMenuList(const string menus[], int size);
};

Menu::Menu() // constructor definition outside class
{
    cout << "Please Enter your name : ";
    getline(cin, guest_name);
    cout << endl
         << "----------------------------------------------------" << endl
         << "Hello, " << guest_name << ". Welcome to our library." << endl
         << "----------------------------------------------------" << endl;
}

// method for displaying menu list
void Menu::displayMenuList(const string menus[], int size)
{
    for (int i = 0; i < size; i++)
        cout << "\t" << menus[i] << endl;
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

void LibraryMenu::displayMainMenu() // for main menu
{
    cout << endl
         << "➡ Main Menu (Choose one number)." << endl
         << endl;

    displayMenuList(MAIN_MENUS, sizeof(MAIN_MENUS) / sizeof(string)); // displaying main menus
    cout << endl
         << "Choose a number : ";
    cin >> selected_menu_no;

    switch (selected_menu_no)
    {
    case 1:
        displaySubMenu();
        break;
    case 2:
        library.addNewBook();
        cout << "_____________________________________________________" << endl;
        displayMainMenu();
        break;
    case 3:
        library.editBook();
        cout << "_____________________________________________________" << endl;
        displayMainMenu();
        break;
    case 4:
        library.deleteBook();
        cout << "_____________________________________________________" << endl;
        displayMainMenu();
        break;
    case 5:
        cout << endl
             << "Good Bye, " << guest_name << ". See you again." << endl;
        break;
    default:
        cout << "Invalid number!" << endl;
        cout << "Choose again!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        displayMainMenu();
        break;
    }
}

void LibraryMenu::displaySubMenu() // for sub menu
{
    cout << endl
         << "➡ Display book list sub menu (Choose one number)." << endl
         << endl;

    displayMenuList(SUB_MENUS, sizeof(SUB_MENUS) / sizeof(string)); // displaying sub menus
    cout << endl
         << "Choose a number : ";
    cin >> selected_menu_no;

    switch (selected_menu_no)
    {
    case 1:
        library.viewBookList("all"); // viewing all books' info
        cout << "_____________________________________________________" << endl;
        displaySubMenu();
        break;
    case 2:
        library.viewBookList("a"); // viewing available books' info
        cout << "_____________________________________________________" << endl;
        displaySubMenu();
        break;
    case 3:
        library.viewBookList("ua"); // viewing unavailable books' info
        cout << "_____________________________________________________" << endl;
        displaySubMenu();
        break;
    case 4:
        cout << "_____________________________________________________" << endl;
        displayMainMenu();
        break;
    default:
        cout << "Invalid number! " << endl
             << "Choose again." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        displaySubMenu();
        break;
    }
}

int main()
{
    LibraryMenu library_menu;
    library_menu.displayMainMenu();
    return 0;
}