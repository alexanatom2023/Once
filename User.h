#pragma once

#include <string>
#include <ostream>
#include <istream>
#include <list>

class Table;
struct Message;
class User;

// Класс пользователя
class User 
{
public:
	User(const std::string& login, const std::string& password, const std::string& name = "");
	User() = default;
	~User();

	// Функция отправки сообщения message от пользователя from пользователю wher 
	// Возвращает true, если сообщение отправилось. Иначе false
	bool sendMessage(User& wher, Message& message);

	// Отправить сообщение в главный чат
	void sendMessage(Message& message);

	// Возвращает список сообщений от конкретного пользователя
	const std::list<Message>* getMessages(const User& key) const;

	// Возвращает список сообщений общего чата
	static const std::list<Message>& getMessages();

	// Оператор равенства возвращает true, если логины равны. Иначе false
	bool operator == (const User& user) const;

	// Перегруженный оператор вывода в поток
	friend std::ostream& operator << (std::ostream& stream, const User& user);

	// Проверка, существует ли пользователь в системе
	static bool isExist(const User& user);

	// Проверка, существует ли пользователь в системе
	static bool isExist(const std::string& login, const std::string& password = "");

	// Метод удаляет всё
	static void clear();

	// Возвращает указатель на пользователя по логину
	static User* getUser(const std::string& login);

	// Возвращает список зарегистрированных пользователей
	static const std::list<User*>& getUsers();

	// Возвращает копию логина
	std::string getLogin() const;

	// Возвращает копию имени пользователя
	std::string getName() const;
private:
	// Логин, пароль, имя пользователя
	std::string _login;
	std::string _password;
	std::string _name;

	// Таблица пользователей и списков сообщений
	Table* _messages;

	// Сообщения между всеми пользователями в главном чате
	static std::list<Message> _mainChat;

	// Список указателей на всех пользователей
	static std::list<User*> _users;
};

// Структура сообщения, хранящая указатель на отправителя, текст сообщения и дату отправки
struct Message 
{
	const User* _from;
	std::string _message;
	std::string _dateTime;

	Message(const User& from, const std::string& message, const std::string& dateTime);
	Message(const Message& message);
	Message() = default;
	~Message() = default;

	// Перегруженный оператор присваивания
	Message& operator = (const Message& message);

	// Ввод сообщения через поток ввода
	friend std::istream& operator >> (std::istream& stream, Message& message);
	// Вывод сообщения через поток вывода
	friend std::ostream& operator << (std::ostream& stream, const Message& message);
};

// Класс для хранения личных переписок между двумя пользователями
class Table
{
public:
	Table() = default;
	~Table();

	// Получить все сообщения с собеседником
	const std::list<Message>* getMessages(const User& key) const;

	// Создать чат с пользователем
	void push(const User& key, const Message& value);
private:
	// Ключ - пользователь-собеседник
	std::list<User> _keys;
	// Значение - список сообщений
	std::list<std::list<Message>> _values;
};