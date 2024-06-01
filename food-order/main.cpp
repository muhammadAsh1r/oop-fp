#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;

class Product
{
    string name;
    int quantity;
    float price;
public:
    void add_product() {
        string name;
        cout << "Enter product name: ";
        cin >> name;
        cout << "Enter product price: ";
        cin >> price;

        ofstream product_file("products.txt", ios::app);
        product_file << name << " " <<  price << endl;
        product_file.close();

        cout << "Product added successfully!" << endl;
    }

    vector<string> splitString(const string& input, char delimiter) {
        vector<string> result;
        stringstream ss(input);
        string item;

        while (getline(ss, item, delimiter)) {
            result.push_back(item);
        }

        return result;
    }

    void delete_product() {
        string name;
        cout << "Enter product name to delete: ";
        cin >> name;

        ifstream product_file("products.txt");
        ofstream temp_file("temp.txt");

        string line;
        bool found = false;
        while (getline(product_file, line)) {
            vector<string> result = splitString(line, ' ');
            if (result[0] != name) {
                temp_file << line << endl;
            } else {
                found = true;
            }
        }

        product_file.close();
        temp_file.close();

        remove("products.txt");
        rename("temp.txt", "products.txt");

        if (found) {
            cout << "Product deleted successfully!" << endl;
        } else {
            cout << "Product not found!" << endl;
        }
    }
};

void clearConsole() {
    system("cls");
}

void disableEcho() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & ~ENABLE_ECHO_INPUT);
}

void enableEcho() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode | ENABLE_ECHO_INPUT);
}

void user_login()
{
    string user, password;
    bool user_is_valid = false, pass_is_valid = false;
    int x = 0, i = 0;

    while(1)
    {
        cout << "Enter username: " ;
        cin >> user;
        cout << "Enter password: " ;
        disableEcho();
        cin >> password;
        enableEcho();

        string text;
        ifstream users_file("users.txt");

        while(getline(users_file, text))
        {
            i++;
            if(text == user)
            {
                user_is_valid = true;
                break;
            }
        }

        string p_text;
        ifstream user_password_file("users_password.txt");

        while(getline(user_password_file, p_text))
        {
            x++;
            if(p_text == password)
            {
                pass_is_valid = true;
                break;
            }
        }


        if(i == x)
        {
            clearConsole();
            cout << "\nYou are logged in as " << user << endl;
            break;
        }
        else
        {
            cout << "\nInvalid username or password. " << endl;
            continue;
        }
    }
}



void admin_menu(Product product) {
    while (true) {
        int choice;
        cout << "\n1. Add Product" << endl;
        cout << "\n2. Delete Product" << endl;
        cout << "\n3. Logout" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                product.add_product();
                break;
            case 2:
                product.delete_product();
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }
}

void admin_login(Product product)
{
    string user, password;
    bool user_is_valid = false, pass_is_valid = false;

    while(1)
    {
        int x = 0, i = 0;
        cout << "Enter username: " ;
        cin >> user;
        cout << "Enter password: " ;
        disableEcho();
        cin >> password;
        enableEcho();

        string text;
        ifstream users_file("admins.txt");

        while(getline(users_file, text))
        {
            i++;
            if(text == user)
            {
                user_is_valid = true;
                break;
            }
        }

        string p_text;
        ifstream user_password_file("admins_password.txt");

        while(getline(user_password_file, p_text))
        {
            x++;
            if(p_text == password)
            {
                pass_is_valid = true;
                break;
            }
        }


        if(i == x)
        {
            clearConsole();
            cout << "\nYou are logged in as " << user << endl;
            admin_menu(product);
            break;
        }
        else
        {
            cout << "\nInvalid username or password. " << endl;
            continue;
        }
    }
}

void authentication(Product product)
{
    while(1)
    {
        int choice;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "Login as: ";
        cin >> choice;
        if(choice == 2)
        {
            user_login();
        }
        else if(choice == 1)
        {
            admin_login(product);
        }
        else
        {
            cout << "Invalid choice." << endl;
            continue;
        }
    }
}

int main()
{
    Product product;
    authentication(product);
}


