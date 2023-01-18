#include <iostream>
#include <windows.h>

#include "User.h"

using namespace std;

// ���� ������������
void userMenu(User& user);
// ���� � �������
void login();
// �����������
bool registration();

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choise = 1;
    while (choise != 0)
    {
        cout << "0. ����� �� ���������" << endl;
        cout << "1. �����������" << endl;
        cout << "2. ����" << endl;

        cin >> choise;
        cin.ignore();

        switch (choise) 
        {
        case 0:
            return 0;
        case 1:
            system("cls");

            if (registration())
                cout << "����������� � �������� ������������!" << endl;
            else
                cout << "������ ������������ ��� ����." << endl;

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
            cout << "������� ����� �� 0 �� 2 ������������!" << endl;
        }
    }

    User::clear();

    return 0;
}

void login()
{
    string login;
    string password;

    cout << "������� �����: ";
    getline(cin, login);

    cout << "������� ������: ";
    getline(cin, password);

    // ���� ������� ������������ ��� ����������, �� ������ � �������
    if (User::isExist(login, password))
    {
        system("cls");
        userMenu(*User::getUser(login));
    }
    else
    {
        cout << "�������� ����� �/��� ������" << endl;
        system("pause");
        system("cls");
    }
}

bool registration()
{
    string name;
    string login;
    string password;

    cout << "������� ��� ������������: ";
    getline(cin, name);

    cout << "������� �����: ";
    getline(cin, login);

    cout << "������� ������: ";
    getline(cin, password);

    // ���� ������������ ���� � �������, �� ����������� ���������
    if (User::isExist(login, password))
        return false;
    else
    {
        // ������ ��������� ������������, �� ��������� �� ���� ����������� � ����������� ������ �������������
        new User(login, password, name);
        return true;
    }
}

void userMenu(User& user)
{
    int choise = 1;

    cout << "����� ���������� � ���� ������������, " << user.getName() << "! �������� ���������� ��������: " << endl;
    while (choise != 0)
    {
        cout << "0. ����� �� �������" << endl;
        cout << "1. ���������� ���� ������" << endl;
        cout << "2. ���������� ������ ������������������ �������������" << endl;
        cout << "3. �������� ��������� ������������" << endl;
        cout << "4. �������� ��������� � ����� ���" << endl;

        cin >> choise;
        cin.ignore();

        switch (choise)
        {
        case 0:
            return;
        case 1:
            system("cls");
            cout << "�����: " << user.getLogin() << endl;
            cout << "���: " << user.getName() << endl;
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

            cout << "������� ����� ������������, �������� ������ ��������� ���������: ";
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
                cout << "������������ �� ������ � �������." << endl;
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
