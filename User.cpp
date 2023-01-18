#include <chrono>

#include "User.h"

// ������� ������� ���� � �����
const std::string currentDateTime()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

	return buf;
}

// USER

std::list<Message> User::_mainChat;

std::list<User*> User::_users;

User::User(const std::string& login, const std::string& password, const std::string& name)
{
	_name = name;
	_login = login;
	_password = password;

	_messages = new Table;

	_users.push_back(this);
}

User::~User() 
{
	_users.remove(this);

	delete _messages;
}

bool User::sendMessage(User& wher, Message& message)
{
	// ���� ������������ �� ����������
	if (!User::isExist(wher))
		return false;

	// ��������� ��������� ������������
	message._from = this;
	wher._messages->push(*this, message);

	// ��������� ��������� � ������� �������
	message._from = &wher;
	this->_messages->push(wher, message);

	return true;
}

void User::sendMessage(Message& message) 
{
	message._from = this;
	User::_mainChat.push_back(message);
}

const std::list<Message>* User::getMessages(const User& from) const
{
	return _messages->getMessages(from);
}

const std::list<Message>& User::getMessages() 
{
	return _mainChat;
}

bool User::operator == (const User& user) const
{
	return (this->_login == user._login) && (this->_password == user._password);
}

std::ostream& operator << (std::ostream& stream, const User& user) 
{
	stream << "�����: " << user.getLogin() << std::endl;
	stream << "���: " << user.getName() << std::endl;

	return stream;
}

bool User::isExist(const User& user) 
{
	for(auto i = User::_users.begin(); i != User::_users.end(); ++i)
		if (*i._Ptr->_Myval == user)
			return true;

	return false;
}

bool User::isExist(const std::string& login, const std::string& password)
{
	// ���� ������ ����������� �� ���������, ������ ����� ���� �� ������
	if(password == "")
		for (auto i = User::_users.begin(); i != User::_users.end(); ++i)
		{
			if (i._Ptr->_Myval->_login == login)
				return true;
		}
	// ����� ����� ���� �� ������ � ������
	else
		for (auto i = User::_users.begin(); i != User::_users.end(); ++i)
			if (i._Ptr->_Myval->_login == login && i._Ptr->_Myval->_password == password)
				return true;

	return false;
}

void User::clear() 
{
	for (auto i : _users)
	{
		delete i->_messages;
		delete i;
	}

	_mainChat.clear();

	_users.clear();
}

User* User::getUser(const std::string& login)
{
	for (auto obj : User::_users)
		if (obj->_login == login)
			return obj;
	
	return 0;
}

const std::list<User*>& User::getUsers()
{
	return User::_users;
}

std::string User::getLogin() const 
{
	return _login;
}

std::string User::getName() const
{
	return _name;
}

// MESSAGE

Message::Message(const User& from, const std::string& message, const std::string& dateTime)
{
	_from = &from;
	_message = message;
	_dateTime = dateTime;
}
Message::Message(const Message& message) 
{
	_from = message._from;

	_message = message._message;
	_dateTime = message._dateTime;
}

Message& Message::operator = (const Message& message) 
{
	_from = message._from;

	_message = message._message;
	_dateTime = message._dateTime;

	return *this;
}

std::istream& operator >> (std::istream& stream, Message& message) 
{
	std::getline(stream, message._message);
	message._dateTime = currentDateTime();

	return stream;
}
std::ostream& operator << (std::ostream& stream, const Message& message)
{
	stream << "�����������: " << message._from->getLogin() << std::endl;
	stream << "���� � ����� ��������: " << message._dateTime << std::endl;
	stream << "���������: " << message._message << std::endl;

	return stream;
}

// TABLE

Table::~Table()
{
	_keys.clear();

	for (auto i : _values)
		i.clear();
	_values.clear();
}

const std::list<Message>* Table::getMessages(const User& key) const
{
	if (_keys.size() == 0)
		return 0;

	// ��������� �� ������ �������������
	auto i = _keys.begin();
	// ����������� �� ������ ������� ���������
	auto j = _values.begin();

	for (; i != _keys.end(); ++i, ++j)
		if (i._Ptr->_Myval == key)
			return &j._Ptr->_Myval;

	return 0;
}

void Table::push(const User& key, const Message& value)
{
	// ���� ������ ����
	if (_keys.size() == 0)
	{
		// ��������� ������������ � ���������
		_keys.push_back(key);
		_values.push_back(std::list<Message>());
		_values.begin()->push_back(value);

		return;
	}

	// ���������� �� ������������ � ������
	bool isExist = false;
	// ��������� �� ������ �������������
	auto i = _keys.begin();
	// ����������� �� ������ ������� ���������
	auto j = _values.begin();

	// ��������� ��������� � ������ ��������� � ������������ ������������, ���� �� ����������
	for (; i != _keys.end(); ++i, ++j)
		if (i._Ptr->_Myval == key)
		{
			j->push_back(value);
			isExist = true;
			break;
		}

	// ���� ������������ ��� � ������
	if (!isExist)
	{
		// ������� ��� � ������ ���������
		_keys.push_back(key);
		_values.push_back(std::list<Message>());

		auto obj = _values.begin();
		obj->push_back(value);
	}
}