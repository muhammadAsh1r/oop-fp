#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;

vector<string> splitString(const string& input, char delimiter) {
        vector<string> result;
        stringstream ss(input);
        string item;

        while (getline(ss, item, delimiter)) {
            result.push_back(item);
        }

        return result;
    }

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

    void display_products()
    {
        string line;
        ifstream products("products.txt");

        while(getline(products, line))
        {
            vector<string> result = splitString(line, ' ');
            cout << "\n***********************" << endl;
            cout << "Name: " << result[0] << endl;
            cout << "Price: " << result[1] << endl;
        }
    }
};

void clearConsole() {
    system("cls");
}

void user_menu()
{
    cout << "Happy Shopping!" << endl;
    while(1)
    {
        string item_name;
        cout << "\nEnter item you want to buy: ";
        cin >> item_name;

        ifstream product_file("products.txt");
        string line;
        bool found = false;
        while (getline(product_file, line)) {
            vector<string> result = splitString(line, ' ');
            if (result[0] == item_name) {
                found = true;
            }
        }

        ofstream sold_history("sold_history.txt", ios::app);
        if(found){
            clearConsole();
            string cu;
            ifstream product_file("products.txt");
            ifstream current_user("current_user.txt");
            current_user >> cu;
            while (getline(product_file, line)) {
                vector<string> result = splitString(line, ' ');
                if(result[0] == item_name) {
                    sold_history << result[0] << " " << result[1] << " " << cu << endl;
                    sold_history.close();
                }
            }
            cout << item_name << " purchased successfully!" << endl;
            break;
        }
        else{
            cout << "Invalid Input" << endl;
            continue;
        }
    }
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

void user_login(Product product)
{
    string user, password;

    while(1)
    {
        bool user_is_valid = false, pass_is_valid = false;
        int x = 0, i = 0;
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


        if(i == x && user_is_valid && pass_is_valid)
        {
            clearConsole();
            ofstream current_user("current_user.txt");
            current_user << user;
            current_user.close();
            cout << "\nYou are logged in as " << user << endl;
            product.display_products();
            user_menu();
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


        if(i == x && user_is_valid && pass_is_valid)
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
            user_login(product);
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
