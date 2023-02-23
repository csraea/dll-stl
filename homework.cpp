#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


// class that represents a STL doubly linked list
template <typename T>
class DoublyLinkedList {
    // Node structure to store data and pointers to next and previous nodes
    struct Node {
        T data;                              // data stored in the node
        Node *prev, *next;                   // pointers to previous and next nodes
        Node(const T &d, Node *p = nullptr, Node *n = nullptr) :    // constructor
            data(d), prev(p), next(n) {}                            // initializes data and pointers
    };
    Node *head, *tail;                      // pointers to the first and last nodes
    int length;                             // number of nodes in the list

public:
    // iterator class to iterate through the list
    class Iterator {
        friend class DoublyLinkedList;    // DoublyLinkedList can access private members of Iterator
        Node *p;                          // pointer to a node
        Iterator(Node *p = nullptr) : p(p) {}   // constructor
    public:
        T &operator*() const { return p->data; }   // dereference operator
        Iterator &operator++() { p = p->next; return *this; }  // prefix increment
        Iterator &operator--() { p = p->prev; return *this; }  // prefix decrement
        bool operator!=(const Iterator &rhs) const { return p != rhs.p; } // not equal
    };

    // Begin and end functions
    Iterator begin() const { return Iterator(head); }  // return iterator to the first node
    Iterator end() const { return Iterator(nullptr); } // return iterator to the imaginary node after the last node

    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {} // initialize head, tail and length

    // Copy constructor
    DoublyLinkedList(const DoublyLinkedList &rhs) : head(nullptr), tail(nullptr), length(0) {
        Node *p = rhs.head;
        while (p) {                 // copy all nodes from rhs
            push_back(p->data);
            p = p->next;
        }
    }

    // Destructor
    ~DoublyLinkedList() {
        clear();                   // delete all nodes
    }

    // Initializer list constructor
    DoublyLinkedList(const std::initializer_list<T> &il) : head(nullptr), tail(nullptr), length(0) {
        for (const T &d : il) {   // copy all elements from il
            push_back(d);
        }
    }

    // Sort a list using the comparator template function
    template<typename F>
    void sort(F comparator) {  
        for (Node *i = head; i != tail; i = i->next) { // bubble sort
            for (Node *j = i->next; j; j = j->next) {  // compare i and j
                if (comparator(j->data, i->data)) {    // if j is less than i
                    std::swap(i->data, j->data);       // swap i and j
                }
            }
        }
    }

    // Reverse function
    void reverse() {
        if (!head) return;       // empty list
        Node *p = head;          // p points to the first node
        head = tail;             // head points to the last node
        tail = p;                // tail points to the first node
        while (p) {              // reverse the next and prev pointers
            Node *q = p->next;
            p->next = p->prev;
            p->prev = q;
            p = q;
        }
    }

    // Insertion functions
    void push_front(const T &d) 
    {
        head = new Node(d, nullptr, head);  // create a new node and make it the first node
        if (head->next) head->next->prev = head;        
        if (!tail) tail = head;
        ++length;
    }

    void push_back(const T &d)  
    {   
        tail = new Node(d, tail, nullptr);  // create a new node and make it the last node
        if (tail->prev) tail->prev->next = tail;
        if (!head) head = tail;
        ++length;                           
    }

    // Deletion functions
    void pop_front() 
    {
        if (!head) return;     // empty list
        Node *p = head;
        head = head->next;     // make the second node the first node
        if (head) head->prev = nullptr;     
        else tail = nullptr;
        delete p;              // delete the first node
        --length;
    }

    void pop_back() 
    {
        if (!tail) return;      // empty list
        Node *p = tail;
        tail = tail->prev;      // make the second last node the last node
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete p;               // delete the last node
        --length;
    }

    // Clear function
    void clear() 
    {
        while (head) {          // delete all nodes
            Node *p = head;
            head = head->next;
            delete p;
        }
        tail = nullptr;         // head and tail are set to nullptr
        length = 0;
    }

    // Print function
    void print() const 
    {
        Node *p = head;         // p points to the first node
        while (p) {             // print all nodes
            std::cout << p->data << ' ';
            p = p->next;
        }
        std::cout << std::endl;
    }

    // Length function
    int size() const            
    {                           
        return length;
    }
};

// A book class to store book information
class Book {
public:
    // Data members
    std::string name;
    std::string author;
    std::string isbn;
    int pages;
    std::string publication_date;

    // Constructor
    Book(const std::string &n, const std::string &a, const std::string &i, int p, const std::string &d) :
        name(n), author(a), isbn(i), pages(p), publication_date(d) {}
};

// a function to read books from a file    
void read_books(DoublyLinkedList<Book> &books, const std::string &filename) {
    std::ifstream file(filename);  // open the file
    std::string line;

    // skip a line with column names
    std::getline(file, line);

    // read all lines
    while (std::getline(file, line)) {
        std::istringstream iss(line);   // create a string stream from the line
        std::string name, author, isbn, pages, publication_date;    // variables to store book information
        std::getline(iss, name, ',');  // read a string until a comma
        std::getline(iss, author, ',');
        std::getline(iss, isbn, ',');
        std::getline(iss, pages, ',');
        std::getline(iss, publication_date, ',');
        books.push_back(Book(name, author, isbn, std::stoi(pages), publication_date));
    }
}

// a function to print books
void print_books(const DoublyLinkedList<Book> &books) {
    for (const Book &b : books) {   // print all books using a range-based for loop 
        std::cout << b.name << ' ' << b.author << ' ' << b.isbn << ' ' << b.pages << ' ' << b.publication_date << std::endl;
    }
}

// a function to sort the books by the given field, template comparator function is passed as a parameter
void sort_books(DoublyLinkedList<Book> &books, const std::string &field, bool ascending=true) {
    if(ascending)
    {
        if (field == "name") {
            books.sort([](const Book &a, const Book &b) { return a.name < b.name; });
        } else if (field == "author") {
            books.sort([](const Book &a, const Book &b) { return a.author < b.author; });
        } else if (field == "isbn") {
            books.sort([](const Book &a, const Book &b) { return a.isbn < b.isbn; });
        } else if (field == "pages") {
            books.sort([](const Book &a, const Book &b) { return a.pages < b.pages; });
        } else if (field == "publication_date") {
            books.sort([](const Book &a, const Book &b) { return a.publication_date < b.publication_date; });
        }
    } else {    // descending order
        if (field == "name") {
            books.sort([](const Book &a, const Book &b) { return a.name > b.name; });
        } else if (field == "author") {
            books.sort([](const Book &a, const Book &b) { return a.author > b.author; });
        } else if (field == "isbn") {
            books.sort([](const Book &a, const Book &b) { return a.isbn > b.isbn; });
        } else if (field == "pages") {
            books.sort([](const Book &a, const Book &b) { return a.pages > b.pages; });
        } else if (field == "publication_date") {
            books.sort([](const Book &a, const Book &b) { return a.publication_date > b.publication_date; });
        }
    }
}

// a function to print all the books from the container to the specified file
void print_books_to_file(const DoublyLinkedList<Book> &books, const std::string &filename) {
    std::ofstream file(filename);  // open the file
    file << "name,author,isbn,pages,publication_date" << std::endl; // write the column names
    for (const Book &b : books) {
        file << b.name << ',' << b.author << ',' << b.isbn << ',' << b.pages << ',' << b.publication_date << std::endl;
    }
}

// usage example
int main() {

    DoublyLinkedList<Book> books;
    read_books(books, "knihy.csv");

    std::cout << "Books before sorting:" << std::endl;
    print_books(books);

    std::cout << "Books after sorting by name:" << std::endl;

    sort_books(books, "name");

    print_books(books);

    sort_books(books, "pages", false);

    std::cout << "Books after sorting by pages:" << std::endl;
    
    print_books(books);

    print_books_to_file(books, "knihy_sorted.csv");

    return 0;
}