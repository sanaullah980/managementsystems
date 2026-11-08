#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Book { int id{}; std::string title, author; int copies{}, available{}; };
struct Member { int id{}; std::string name; std::vector<int> borrowed; };

class Library {
    std::map<int, Book> books;
    std::map<int, Member> members;
public:
    bool addBook(Book b) {
        if (b.id <= 0 || b.copies < 1) return false;
        b.available = b.copies;
        return books.emplace(b.id, b).second;
    }
    bool addMember(Member m) { return m.id > 0 && members.emplace(m.id, m).second; }
    bool issue(int memberId, int bookId) {
        auto m = members.find(memberId); auto b = books.find(bookId);
        if (m == members.end() || b == books.end() || b->second.available == 0) return false;
        for (int id : m->second.borrowed) if (id == bookId) return false;
        --b->second.available; m->second.borrowed.push_back(bookId); return true;
    }
    bool giveBack(int memberId, int bookId) {
        auto m = members.find(memberId); auto b = books.find(bookId);
        if (m == members.end() || b == books.end()) return false;
        auto& list = m->second.borrowed;
        for (auto it = list.begin(); it != list.end(); ++it) if (*it == bookId) {
            list.erase(it); ++b->second.available; return true;
        }
        return false;
    }
    void search(const std::string& text) const {
        bool found = false;
        for (const auto& [id, b] : books)
            if (b.title.find(text) != std::string::npos || b.author.find(text) != std::string::npos) {
                std::cout << id << " | " << b.title << " by " << b.author << " | available " << b.available << '/' << b.copies << '\n'; found = true;
            }
        if (!found) std::cout << "No matching books.\n";
    }
    void listBooks() const {
        for (const auto& [id, b] : books) std::cout << id << " | " << b.title << " | " << b.author << " | " << b.available << '/' << b.copies << '\n';
        if (books.empty()) std::cout << "No books registered.\n";
    }
    void listMembers() const {
        for (const auto& [id, m] : members) std::cout << id << " | " << m.name << " | borrowed: " << m.borrowed.size() << '\n';
        if (members.empty()) std::cout << "No members registered.\n";
    }
};

int main() {
    Library library; int choice;
    while (true) {
        std::cout << "\nLibrary Management\n1 Add book\n2 Register member\n3 Issue book\n4 Return book\n5 Search\n6 List books\n7 List members\n0 Exit\nChoice: ";
        if (!(std::cin >> choice)) return 0;
        if (!choice) break;
        if (choice == 1) {
            Book b; std::cout << "ID copies title author(no spaces): "; std::cin >> b.id >> b.copies >> b.title >> b.author;
            std::cout << (library.addBook(b) ? "Book added.\n" : "Invalid/duplicate book.\n");
        } else if (choice == 2) {
            Member m; std::cout << "Member ID name(no spaces): "; std::cin >> m.id >> m.name;
            std::cout << (library.addMember(m) ? "Member registered.\n" : "Invalid/duplicate member.\n");
        } else if (choice == 3 || choice == 4) {
            int m, b; std::cout << "Member ID book ID: "; std::cin >> m >> b;
            bool ok = choice == 3 ? library.issue(m, b) : library.giveBack(m, b);
            std::cout << (ok ? "Operation completed.\n" : "Check IDs, availability, or loan status.\n");
        } else if (choice == 5) { std::string s; std::cout << "Title/author substring: "; std::cin >> s; library.search(s); }
        else if (choice == 6) library.listBooks();
        else if (choice == 7) library.listMembers();
        else std::cout << "Unknown option.\n";
    }
}
