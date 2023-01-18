#pragma once

#include <string>
#include <ostream>
#include <istream>
#include <list>

class Table;
struct Message;
class User;

// ����� ������������
class User 
{
public:
	User(const std::string& login, const std::string& password, const std::string& name = "");
	User() = default;
	~User();

	// ������� �������� ��������� message �� ������������ from ������������ wher 
	// ���������� true, ���� ��������� �����������. ����� false
	bool sendMessage(User& wher, Message& message);

	// ��������� ��������� � ������� ���
	void sendMessage(Message& message);

	// ���������� ������ ��������� �� ����������� ������������
	const std::list<Message>* getMessages(const User& key) const;

	// ���������� ������ ��������� ������ ����
	static const std::list<Message>& getMessages();

	// �������� ��������� ���������� true, ���� ������ �����. ����� false
	bool operator == (const User& user) const;

	// ������������� �������� ������ � �����
	friend std::ostream& operator << (std::ostream& stream, const User& user);

	// ��������, ���������� �� ������������ � �������
	static bool isExist(const User& user);

	// ��������, ���������� �� ������������ � �������
	static bool isExist(const std::string& login, const std::string& password = "");

	// ����� ������� ��
	static void clear();

	// ���������� ��������� �� ������������ �� ������
	static User* getUser(const std::string& login);

	// ���������� ������ ������������������ �������������
	static const std::list<User*>& getUsers();

	// ���������� ����� ������
	std::string getLogin() const;

	// ���������� ����� ����� ������������
	std::string getName() const;
private:
	// �����, ������, ��� ������������
	std::string _login;
	std::string _password;
	std::string _name;

	// ������� ������������� � ������� ���������
	Table* _messages;

	// ��������� ����� ����� �������������� � ������� ����
	static std::list<Message> _mainChat;

	// ������ ���������� �� ���� �������������
	static std::list<User*> _users;
};

// ��������� ���������, �������� ��������� �� �����������, ����� ��������� � ���� ��������
struct Message 
{
	const User* _from;
	std::string _message;
	std::string _dateTime;

	Message(const User& from, const std::string& message, const std::string& dateTime);
	Message(const Message& message);
	Message() = default;
	~Message() = default;

	// ������������� �������� ������������
	Message& operator = (const Message& message);

	// ���� ��������� ����� ����� �����
	friend std::istream& operator >> (std::istream& stream, Message& message);
	// ����� ��������� ����� ����� ������
	friend std::ostream& operator << (std::ostream& stream, const Message& message);
};

// ����� ��� �������� ������ ��������� ����� ����� ��������������
class Table
{
public:
	Table() = default;
	~Table();

	// �������� ��� ��������� � ������������
	const std::list<Message>* getMessages(const User& key) const;

	// ������� ��� � �������������
	void push(const User& key, const Message& value);
private:
	// ���� - ������������-����������
	std::list<User> _keys;
	// �������� - ������ ���������
	std::list<std::list<Message>> _values;
};