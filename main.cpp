#include <iostream>
#include <string> 
#include <vector>

#include "libs/mysql-connector/include/mysqlx/xdevapi.h"


class Book {
private:
	std::string name, author, isbn;
	float bookPrice = 0;
	int publicYear = 0, numberOfPages = 0;
	static std::vector<Book*> objList;
public:
	void setBook(
		std::string name,
		std::string author,
		std::string isbn,
		float bookPrice,
		int publicYear,
		int numberOfPages)
	{
		this->setName(name);
		this->setAuthor(author);
		this->setIsbn(isbn);
		this->setBookPrice(bookPrice);
		this->setPublicYear(publicYear);
		this->setNumberOfPages(numberOfPages);
		objList.push_back(this);
	}

	void setName(std::string name) {
		this->name = name;
	}
	std::string getName() {
		return this->name;
	}

	void setAuthor(std::string author) {
		this->author = author;
	}
	std::string getAuthor() {
		return this->author;
	}

	void setIsbn(std::string isbn) {
		this->isbn = isbn;
	}
	std::string getIsbn() {
		return this->isbn;
	}

	void setBookPrice(float bookPrice = 0) {
		this->bookPrice = bookPrice;
	}
	float getBookPrice() {
		return this->bookPrice;
	}

	void setPublicYear(int publicYear = 1990) {
		this->publicYear = publicYear;
	}
	int getPublicYear() {
		return this->publicYear;
	}

	void setNumberOfPages(int numberOfPages = 0) {
		this->numberOfPages = numberOfPages;
	}
	int getNumberOfPages() {
		return this->numberOfPages;
	}

	float getPagePrice() {
		return this->bookPrice / this->numberOfPages;
	}

	int getBookAge() {
		return 2023 - this->publicYear;
	}
	//Метод возвращает строку сведений из объекта Book
	std::string getBook()
	{
		std::string result = {
			"Book: " + this->getName() + "\n"
			+ "Author:" + this->getAuthor() + "\n"
			+ "Book age:" + std::to_string(this->getBookAge()) +
			"\n" };
		return result;
	}

	//Метод возвращает вектор указателей на все объекты Book

	static std::vector<Book*> getAllObjects() {
		return objList;
	}

	//Метод возвращает вектор указателей на объекты Book с заданным условием поиска
	static std::vector<Book*> findInName(std::string find = { " " })
	{
		std::vector<Book*> BookList = Book::getAllObjects();
		std::vector<Book*> FindObjects;

		for (int i = 0; i < BookList.size(); i++) {

			if (BookList[i]->getName().find(find) != std::string::npos and BookList[i]->getName() != "")
			{
				FindObjects.push_back(BookList[i]);
			};
		}
		return FindObjects;
	}
};



//Класс для работы с БД MYSQL
class DataBase
{
private:
	std::string Host;
	int Port;
	std::string Username;
	std::string Password;
	std::string DatabaseName;

public:

	DataBase(
		std::string Host = "127.0.0.1",
		int Port = 33060,
		std::string Username = "root",
		std::string Password = "toor",
		std::string DataBaseName = "world")
	{
		this->setHost(Host);
		this->setPort(Port);
		this->setUserName(Username);
		this->setPassword(Password);
		this->setDataBaseName(DataBaseName);
	}

	void setHost(std::string Host)
	{
		this->Host = Host;
	}
	void setPort(int Port)
	{
		this->Port = Port;
	}
	void setUserName(std::string UserName)
	{
		this->Username = UserName;
	}
	void setPassword(std::string Password)
	{
		this->Password = Password;
	}
	void setDataBaseName(std::string DataBaseName)
	{
		this->DatabaseName = DataBaseName;
	}
	std::string getServer()
	{
		return this->Host + ":" + std::to_string(Port);
	}
	std::string getUserName()
	{
		return this->Username;
	}
	std::string getPassword()
	{
		return this->Password;
	}
	int getPort()
	{
		return this->Port;
	}
	std::string getDataBaseName()
	{
		return this->DatabaseName;
	}
	void openConnection()
	{
		try {
			// Изменение вашей информации
			mysqlx::Session sess(
				mysqlx::SessionOption::USER, this->getUserName(),
				mysqlx::SessionOption::PWD, this->getPassword(),
				mysqlx::SessionOption::HOST, this->getServer(),
				mysqlx::SessionOption::PORT, this->getPort(),
				mysqlx::SessionOption::DB, this->getDataBaseName());

			std::cout << "ttt";
			auto result = sess.sql("select * from city").execute();

		}
		catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
		}



	}
};


std::vector<Book*> Book::objList;


int main()
{
	std::system("chcp 65001");

	std::string name{}, author{}, isbn{};
	float bookPrice = 0.00;
	int publicYear = 0, numberOfPages = 0, counter = 1;

	DataBase db;
	db.openConnection();
	std::cout << "Enter the number of books (max 50): "; std::cin >> counter;

	// Цикл ввода книг
	for (int i = 0; i < counter; i++) {
		std::cout << "Enter " << i + 1 << " book\n";
		std::cout << "name: ";
		std::getline(std::cin >> std::ws, name);
		std::cout << "author: ";
		std::getline(std::cin >> std::ws, author);
		std::cout << "isbn: "; std::cin >> isbn;
		std::cout << "bookPrice: "; std::cin >> bookPrice;
		std::cout << "publicYear: "; std::cin >> publicYear;
		std::cout << "numberOfPages: "; std::cin >> numberOfPages;
		std::cout << std::endl;

		//Создание нового объекта Книга

		Book* current = new Book();
		//Установка значения для созданного объекта
		current->setBook(name, author, isbn, bookPrice, publicYear, numberOfPages);
	}

	// Вектор всех введённых книг
	std::vector<Book*> BookList = Book::getAllObjects();


	// Вектор книг начинающихся с Programm 

	std::vector<Book*> FindList = Book::findInName("Programm");

	//Цикл вывода книг с Programm
	for (int i = 0; i < FindList.size(); i++)
	{
		std::cout << FindList[i]->getBook();
		std::cout << std::endl;
	}


	std::cout << "";
}

/*void printMenu()
{
	std::cout << "Welcome to library\n\n";
	std::cout << "1)\tAdd\n";
	std::cout << "2)\tList\n";
	std::cout << "3)\tSearch\n";
	std::cout << "4)\tExit\n";
	std::cout << "Enter your choice: ";
}*/