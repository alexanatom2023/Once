#include <iostream>
#include <windows.h>

#include "User.h"

using namespace std;

// Меню пользователя
void userMenu(User& user);
// Вход в систему
void login();
// Регистрация
bool registration();

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choise = 1;
    while (choise != 0)
    {
        cout << "0. Выход из программы" << endl;
        cout << "1. Регистрация" << endl;
        cout << "2. Вход" << endl;

        cin >> choise;
        cin.ignore();

        switch (choise) 
        {
        case 0:
            return 0;
        case 1:
            system("cls");

            if (registration())
                cout << "Поздравляем с успешной регистрацией!" << endl;
            else
                cout << "Данный пользователь уже есть." << endl;

            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");

            login();

            system("pause");
            system("cls");
            break;
        default:
            cout << "Введите число от 0 до 2 включительно!" << endl;
        }
    }

    User::clear();

    return 0;
}

void login()
{
    string login;
    string password;

    cout << "Введите логин: ";
    getline(cin, login);

    cout << "Введите пароль: ";
    getline(cin, password);

    // Если текущий пользователь уже существует, то входим в систему
    if (User::isExist(login, password))
    {
        system("cls");
        userMenu(*User::getUser(login));
    }
    else
    {
        cout << "Неверный логин и/или пароль" << endl;
        system("pause");
        system("cls");
    }
}

bool registration()
{
    string name;
    string login;
    string password;

    cout << "Введите имя пользователя: ";
    getline(cin, name);

    cout << "Введите логин: ";
    getline(cin, login);

    cout << "Введите пароль: ";
    getline(cin, password);

    // Если пользователь есть в системе, то регистрация провалена
    if (User::isExist(login, password))
        return false;
    else
    {
        // Объект создается динамический, но указатель на него сохраняется в статическом списке пользователей
        new User(login, password, name);
        return true;
    }
}

void userMenu(User& user)
{
    int choise = 1;

    cout << "Добро пожаловать в меню пользователя, " << user.getName() << "! Выберите дальнейшие действия: " << endl;
    while (choise != 0)
    {
        cout << "0. Выйти из системы" << endl;
        cout << "1. Посмотреть свои данные" << endl;
        cout << "2. Посмотреть список зарегистрированных пользователей" << endl;
        cout << "3. Написать сообщение пользователю" << endl;
        cout << "4. Написать сообщение в общий чат" << endl;

        cin >> choise;
        cin.ignore();

        switch (choise)
        {
        case 0:
            return;
        case 1:
            system("cls");
            cout << "Логин: " << user.getLogin() << endl;
            cout << "Имя: " << user.getName() << endl;
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            for (auto obj : User::getUsers())
                cout << *obj << endl;
            system("pause");
            system("cls");
            break;
        case 3:
        {
            system("cls");
            string login;

            cout << "Введите логин пользователя, которому хотите отправить сообщение: ";
            getline(cin, login);

            User* send = User::getUser(login);

            if (send)
            {
                system("cls");
                auto obj = user.getMessages(*send);

                if(obj)
                    for (auto i : *obj)
                        cout << i << endl;

                Message message;

                cin >> message;

                user.sendMessage(*send, message);
                system("pause");
                system("cls");
            }
            else
            {
                system("cls");
                cout << "Пользователь не найден в системе." << endl;
                system("pause");
                system("cls");
            }
        }
            break;
        case 4:
            system("cls");
            auto obj = User::getMessages();

            for (auto i : obj)
                cout << i << endl;

            Message message;

            cin >> message;

            user.sendMessage(message);
            system("pause");
            system("cls");
            break;
        }
    }
}
