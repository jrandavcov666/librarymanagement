#include <iostream>
#include <string>
#include <vector>
#include <memory>     
#include <Windows.h>
#pragma execution_character_set("utf-8")

class Book {
private:
    std::string title;
    std::string author;
    int year;
    bool isIssued;

public:
    Book(std::string t, std::string a, int y) {
        title = t;
        author = a;
        year = y;
        isIssued = false;
    }

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsIssued() const { return isIssued; }

    void setTitle(std::string t) { title = t; }
    void setAuthor(std::string a) { author = a; }
    void setYear(int y) { year = y; }
    void setIsIssued(bool issued) { isIssued = issued; }

    void print() const {
        std::cout << title << " " << author << " " << year << " год";
        if (isIssued) {
            std::cout << " выдана";
        }
        else {
            std::cout << " доступна к выдаче";
        }
    }
};

class Reader {
private:
    std::string fio;
    int age;
    std::vector<std::shared_ptr<Book>> issuedBooks;

public:
    Reader(std::string f, int a) {
        fio = f;
        age = a;
    }

    std::string getFio() const { return fio; }
    int getAge() const { return age; }
    const std::vector<std::shared_ptr<Book>>& getIssuedBooks() const {
        return issuedBooks;
    }

    void setFio(std::string f) { fio = f; }
    void setAge(int a) { age = a; }

    void takeBook(std::shared_ptr<Book> book) {
        (*book).setIsIssued(true);
        issuedBooks.push_back(book);
    }

    void print() const {
        std::cout << fio << " " << age << " лет книг на руках: " << issuedBooks.size();
    }
};

std::vector<std::shared_ptr<Book>> libraryBooks;
std::vector<std::shared_ptr<Reader>> readers;

int findBook(std::string title) {
    for (int i = 0; i < libraryBooks.size(); i = i + 1) {
        if ((*libraryBooks[i]).getTitle() == title) return i;
    }
    return -1;
}

int findReader(std::string fio) {
    for (int i = 0; i < readers.size(); i = i + 1) {
        if ((*readers[i]).getFio() == fio) return i;
    }
    return -1;
}

void addBook() {
    std::unique_ptr<std::string> title = std::make_unique<std::string>();
    std::unique_ptr<std::string> author = std::make_unique<std::string>();
    int year;

    std::cout << "Название: ";
    std::cin.ignore();
    std::getline(std::cin, *title);

    if (findBook(*title) != -1) {
        std::cout << "Книга с таким названием уже есть!\n";
        return;
    }

    std::cout << "Автор: ";
    std::getline(std::cin, *author);

    std::cout << "Год издания: ";
    std::cin >> year;

    Book* tempBook = new Book(*title, *author, year);
    auto newBook = std::make_shared<Book>(*tempBook);
    delete tempBook;

    libraryBooks.push_back(newBook);
    std::cout << "Книга добавлена\n";
}

void showAllBooks() {
    if (libraryBooks.empty()) {
        std::cout << "Библиотека пуста\n";
        return;
    }
    std::cout << "Все книги\n";
    for (int i = 0; i < libraryBooks.size(); i = i + 1) {
        std::cout << i + 1 << ". ";
        (*libraryBooks[i]).print();
        std::cout << "\n";
    }
}

void editBook() {
    std::string title;
    std::cout << "Название книги для изменения: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    int idx = findBook(title);
    if (idx == -1) {
        std::cout << "Книга не найдена\n";
        return;
    }

    std::string newTitle, newAuthor;
    int newYear;

    std::cout << "Новое название: ";
    std::getline(std::cin, newTitle);
    std::cout << "Новый автор: ";
    std::getline(std::cin, newAuthor);
    std::cout << "Новый год: ";
    std::cin >> newYear;

    (*libraryBooks[idx]).setTitle(newTitle);
    (*libraryBooks[idx]).setAuthor(newAuthor);
    (*libraryBooks[idx]).setYear(newYear);

    std::cout << "Книга обновлена\n";
}

void deleteBook() {
    std::string title;
    std::cout << "Название книги для удаления: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    int idx = findBook(title);
    if (idx == -1) {
        std::cout << "Книга не найдена\n";
        return;
    }

    if ((*libraryBooks[idx]).getIsIssued()) {
        std::cout << "Нельзя удалить книгу, она выдана читателю\n";
        return;
    }

    libraryBooks.erase(libraryBooks.begin() + idx);
    std::cout << "Книга удалена\n";
}

void addReader() {
    std::unique_ptr<std::string> fio = std::make_unique<std::string>();
    int age;

    std::cout << "ФИО: ";
    std::cin.ignore();
    std::getline(std::cin, *fio);

    if (findReader(*fio) != -1) {
        std::cout << "Читатель с таким ФИО уже есть\n";
        return;
    }

    std::cout << "Возраст: ";
    std::cin >> age;

    auto newReader = std::make_shared<Reader>(*fio, age);
    readers.push_back(newReader);
    std::cout << "Читатель добавлен\n";
}

void showAllReaders() {
    if (readers.empty()) {
        std::cout << "Читателей нет\n";
        return;
    }
    std::cout << "Все читатели\n";
    for (int i = 0; i < readers.size(); i = i + 1) {
        std::cout << i + 1 << ". ";
        (*readers[i]).print();
        std::cout << "\n";
    }
}

void editReader() {
    std::string fio;
    std::cout << "ФИО читателя для изменения: ";
    std::cin.ignore();
    std::getline(std::cin, fio);

    int idx = findReader(fio);
    if (idx == -1) {
        std::cout << "Читатель не найден\n";
        return;
    }

    std::string newFio;
    int newAge;

    std::cout << "Новое ФИО: ";
    std::getline(std::cin, newFio);
    std::cout << "Новый возраст: ";
    std::cin >> newAge;

    (*readers[idx]).setFio(newFio);
    (*readers[idx]).setAge(newAge);

    std::cout << "Данные обновлены\n";
}

void deleteReader() {
    std::string fio;
    std::cout << "ФИО читателя для удаления: ";
    std::cin.ignore();
    std::getline(std::cin, fio);

    int idx = findReader(fio);
    if (idx == -1) {
        std::cout << "Читатель не найден\n";
        return;
    }

    if ((*readers[idx]).getIssuedBooks().size() > 0) {
        std::cout << "Нельзя удалить, у читателя есть книги\n";
        return;
    }

    readers.erase(readers.begin() + idx);
    std::cout << "Читатель удален\n";
}

void giveBook() {
    std::string fio, title;

    std::cout << "ФИО читателя: ";
    std::cin.ignore();
    std::getline(std::cin, fio);

    int rIdx = findReader(fio);
    if (rIdx == -1) {
        std::cout << "Читатель не найден\n";
        return;
    }

    std::cout << "Название книги: ";
    std::getline(std::cin, title);

    int bIdx = findBook(title);
    if (bIdx == -1) {
        std::cout << "Книга не найдена\n";
        return;
    }

    if ((*libraryBooks[bIdx]).getIsIssued()) {
        std::cout << "Книга уже выдана другому читателю\n";
        return;
    }

    (*readers[rIdx]).takeBook(libraryBooks[bIdx]);
    std::cout << "Книга выдана\n";
}

void showReaderBooks() {
    std::string fio;
    std::cout << "ФИО читателя: ";
    std::cin.ignore();
    std::getline(std::cin, fio);

    int idx = findReader(fio);
    if (idx == -1) {
        std::cout << "Читатель не найден\n";
        return;
    }

    const auto& books = (*readers[idx]).getIssuedBooks();
    if (books.empty()) {
        std::cout << "У читателя нет книг\n";
        return;
    }

    std::cout << "\nКниги читателя " << fio << ":\n";
    for (int i = 0; i < books.size(); i = i + 1) {
        (*books[i]).print();
        std::cout << "\n";
    }
}

void showStatistics() {
    int totalBooks = libraryBooks.size();
    int issuedBooks = 0;
    int freeBooks = 0;

    for (int i = 0; i < libraryBooks.size(); i = i + 1) {
        if ((*libraryBooks[i]).getIsIssued()) issuedBooks = issuedBooks + 1;
        else freeBooks = freeBooks + 1;
    }

    int totalReaders = readers.size();
    int readersWithBooks = 0;

    for (int i = 0; i < readers.size(); i = i + 1) {
        if ((*readers[i]).getIssuedBooks().size() > 0) readersWithBooks = readersWithBooks + 1;
    }

    std::cout << "Всего книг: " << totalBooks << "\n";
    std::cout << "Доступно: " << freeBooks << "\n";
    std::cout << "Выдано: " << issuedBooks << "\n";
    std::cout << "Всего читателей: " << totalReaders << "\n";
    std::cout << "С книгами: " << readersWithBooks << "\n";
}


void firstdata() {
    libraryBooks.push_back(std::make_shared<Book>("Война и мир", "Л.Н. Толстой", 1869));
    libraryBooks.push_back(std::make_shared<Book>("Преступление и наказание", "Ф.М. Достоевский", 1866));
    libraryBooks.push_back(std::make_shared<Book>("Мастер и Маргарита", "М.А. Булгаков", 1967));

    readers.push_back(std::make_shared<Reader>("Иванов Иван Иванович", 20));
    readers.push_back(std::make_shared<Reader>("Петров Пётр Петрович", 22));

    (*readers[0]).takeBook(libraryBooks[0]);
    (*libraryBooks[0]).setIsIssued(true);
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    firstdata();

    int choice = -1;

    while (choice != 0) {
        std::cout << "1. Добавить книгу\n";
        std::cout << "2. Показать все книги\n";
        std::cout << "3. Изменить книгу\n";
        std::cout << "4. Удалить книгу\n";
        std::cout << "5. Добавить читателя\n";
        std::cout << "6. Показать всех читателей\n";
        std::cout << "7. Изменить читателя\n";
        std::cout << "8. Удалить читателя\n";
        std::cout << "9. Выдать книгу\n";
        std::cout << "10. Книги читателя\n";
        std::cout << "11. Статистика\n";
        std::cout << "0. Выход\n";
        std::cout << "Выбор: ";
        std::cin >> choice;

        if (choice == 1) addBook();
        else if (choice == 2) showAllBooks();
        else if (choice == 3) editBook();
        else if (choice == 4) deleteBook();
        else if (choice == 5) addReader();
        else if (choice == 6) showAllReaders();
        else if (choice == 7) editReader();
        else if (choice == 8) deleteReader();
        else if (choice == 9) giveBook();
        else if (choice == 10) showReaderBooks();
        else if (choice == 11) showStatistics();
        else if (choice == 0) std::cout << "Завершение работы\n";
    }
}