#include <iostream>
#include <vector>
#include <string>
enum class BookType {
    Fiction,
    Technical
};

class Book {
private:
    std::string author;
    std::string title;
    BookType type;

public:
    Book(const std::string& author, const std::string& title, BookType type)
        : author(author), title(title), type(type) {
        if (author.empty() || title.empty()) {
            throw std::invalid_argument("Книга должна иметь автора и название.");
        }
    }

    BookType getType() const {
        return type;
    }
};

class Library {
private:
    std::vector<Book*> books;

public:
    ~Library() {
        for (Book* book : books) {
            delete book;
        }
    }

    void addBook(const std::string& author, const std::string& title, BookType type) {
        books.push_back(new Book(author, title, type));
    }

    void countBooksByType() const {
        int fictionCount = 0;
        int technicalCount = 0;

        for (const Book* book : books) {
            switch (book->getType()) {
            case BookType::Fiction:
                fictionCount++;
                break;
            case BookType::Technical:
                technicalCount++;
                break;
            }
        }

        std::cout << "Quantity of fiction: " << fictionCount << std::endl;
        std::cout << "Quantity of technical literature: " << technicalCount << std::endl;
    }
};

int main() {
    Library library;

    try {
        library.addBook("Александр Пушкин", "Евгений Онегин", BookType::Fiction);
        library.addBook("Лев Толстой", "Война и мир", BookType::Fiction);
        library.addBook("Брайан Керниган", "Язык программирования C", BookType::Technical);
        library.addBook("Андрей Кнут", "Искусство программирования", BookType::Technical);

        library.countBooksByType();
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
