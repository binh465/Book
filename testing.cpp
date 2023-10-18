#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;
class Book {
private:
    string id;
    int status;
    string name;
    string location;
    string borrow_date;
    string return_date;
    int borrow_count;
    string reader_id;

public:
    Book() {
        id = "";
        name = "";
        status = 0; // 0 = đã cho mượn, 1 = chưa cho mượn, 2 = đã mất
        location = "";
        borrow_date = "";
        return_date = "";
        borrow_count = 0;
        reader_id = "";
    }
    Book(string id, string name, int status, string location, string borrow_date, string return_date, int borrow_count, string reader_id) {
        this->id = id;
        this->name = name;
        this->status = status;
        this->location = location;
        this->borrow_date = borrow_date;
        this->return_date = return_date;
        this->borrow_count = borrow_count;
        this->reader_id = reader_id;
    }

    void setID(string id) {
        this->id = id;
    }

    string getID() const {
        return id;
    }

    void setStatus(int status) {
        this->status = status;
    }

    int getStatus() const {
        return status;
    }

    void setName(string name) {
        this->name = name;
    }

    string getName() const {
        return name;
    }

    void setLocation(string location) {
        this->location = location;
    }

    string getLocation() const {
        return location;
    }

    void setBorrowedDate(string borrow_date) {
        this->borrow_date = borrow_date;
    }

    string getBorrowDate() const {
        return borrow_date;
    }

    void setReturnDate(string return_date) {
        this->return_date = return_date;
    }

    string getReturnDate() const {
        return return_date;
    }

    void setBorrowCount(int borrow_count) {
        this->borrow_count = borrow_count;
    }

    int getBorrowCount() const {
        return borrow_count;
    }

    void setReaderID(string reader_id) {
        this->reader_id = reader_id;
    }

    string getReaderID() const {
        return reader_id;
    }
};

class BookList {
private:
    vector<Book> books;
public:
    BookList() {
        books = vector<Book>();
    }
    vector<Book> getBooks() {
        return books;
    }
    void addBook(Book book) {
        books.push_back(book);
    }

    //xoá sách khỏi danh mục theo mã sách
    void deleteBook(string id) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getID() == id) {
                books.erase(books.begin() + i);
                return;
            }
        }
        cout << "Không tìm thấy sách có mã " << id << endl;
    }

    //Sửa thông tín sách theo mã sách
    void editBook(string id, string name, string location) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getID() == id) {

                books[i].setName(name);
                books[i].setLocation(location);

                break;
            }
        }
    }

    void borrowBook(string id, string borrow_date, string return_date, string reader_id) {
        for (Book& book : books) {
            if (book.getID() == id) {
                book.setStatus(1);
                book.setBorrowedDate(borrow_date);
                book.setReturnDate(return_date);
                book.setBorrowCount(book.getBorrowCount() + 1);
                book.setReaderID(reader_id);
                return;
            }
        }
    }

    void returnBook(string id) {
        for (Book& book : books) {
            if (book.getID() == id) {
                book.setStatus(0);
                book.setReaderID("");
                book.setBorrowedDate("");
                book.setReturnDate("");
                return;
            }
        }
    }

    void printBooks() {
        for (const Book& book : books) {
            cout << "Book ID: " << book.getID()
                << ", Book Name: " << book.getName()
                << ", Book Status: " << book.getStatus()
                << ", Book Location: " << book.getLocation()
                << ", Borrow Date: " << book.getBorrowDate()
                << ", Return Date: " << book.getReturnDate()
                << ", Borrow Count: " << book.getBorrowCount()
                << ", Reader ID: " << book.getReaderID()
                << endl;
        }
    }

    void addDataToFile(string filename) {
        ofstream outFile(filename, ios::out);
        if (outFile.is_open()) {
            for (const Book& book : books) {
                outFile << "Book ID: " << book.getID()
                    << ", Book Name: " << book.getName()
                    << ", Book Status: " << book.getStatus()
                    << ", Book Location: " << book.getLocation()
                    << ", Borrow Date: " << book.getBorrowDate()
                    << ", Return Date: " << book.getReturnDate()
                    << ", Borrow Count: " << book.getBorrowCount()
                    << ", Reader ID: " << book.getReaderID() << endl;
                outFile << "---------------" << endl;
           
            }
            outFile.close();
        }
        else {
            cout << "Unable to open file" << endl;
        }
    }

    


    void loadDataFromFile(string filename) {
        ifstream inFile(filename);
        string line;
        if (inFile.is_open()) {
            while (getline(inFile, line)) {
                stringstream ss(line);
                string id, name, location, borrow_date, return_date, reader_id;
                int status, borrow_count;

                // Đọc dữ liệu từ file theo định dạng đã lưu
                getline(ss, id, ',');
                id = id.substr(id.find(":") + 2); // Loại bỏ "Book ID: "

                getline(ss, name, ',');
                name = name.substr(name.find(":") + 2); // Loại bỏ "Book Name: "

                ss.ignore(14); // Bỏ qua "Book Status: "
                ss >> status;
                ss.ignore(2, ','); // Bỏ qua dấu phẩy và khoảng trắng sau nó

                getline(ss, location, ',');
                location = location.substr(location.find(":") + 2); // Loại bỏ "Book Location: "

                getline(ss, borrow_date, ',');
                borrow_date = borrow_date.substr(borrow_date.find(":") + 2); // Loại bỏ "Borrow Date: "

                getline(ss, return_date, ',');
                return_date = return_date.substr(return_date.find(":") + 2); // Loại bỏ "Return Date: "

                ss.ignore(14); // Bỏ qua "Borrow Count: "
                ss >> borrow_count;
                ss.ignore(2, ','); // Bỏ qua dấu phẩy và khoảng trắng sau nó

                getline(ss, reader_id);
                reader_id = reader_id.substr(reader_id.find(":") + 2); // Loại bỏ "Reader ID: "

                // Tạo sách mới với dữ liệu đã đọc
                Book book(id, name, status, location, borrow_date, return_date, borrow_count, reader_id);

                // Thêm sách vào danh sách
                books.push_back(book);
 
            }
            inFile.close();
        }
        else {
            cout << "Unable to open file" << endl;
        }
    }

};

// Hàm main để thực hiện các chức năng của bài code
int main() {
   
        BookList bookList;

        /*bookList.loadDataFromFile("DauMucSach.txt");
        bookList.printBooks(); */
        

        
        // Thêm một số sách vào danh mục
        Book book1("123", "Book 1", 1, "Section A", "", "", 0, "");
        Book book2("456", "Book 2", 1, "Section B", "", "", 0, "");
        Book book3("789", "Book 3", 1, "Section C", "", "", 0, "");

        bookList.addBook(book1);
        bookList.addBook(book2);
        bookList.addBook(book3);
        bookList.addDataToFile("DauMucSach.txt");
        bookList.printBooks();
        cout << "-------------------------------" << endl; 
        
        // Xóa sách theo mã
        string bookIdToDelete = "456";
        bookList.deleteBook(bookIdToDelete);

        
        bookList.editBook("123", "Book 4", "Section D");
        bookList.printBooks();
        
        cout << "-------------------------------" << endl;

        bookList.borrowBook("123", "02/01/2013", "02/02/2013", "hj733");
        bookList.printBooks();
        cout << "-------------------------------" << endl;

        bookList.returnBook("123");
        bookList.printBooks();
        cout << "-------------------------------" << endl;

        bookList.borrowBook("123", "04/06/2013", "04/07/2013", "hjy33");
        bookList.printBooks();
        cout << "-------------------------------" << endl; 

        bookList.addDataToFile("DauMucSach.txt");

        Book book4("124", "Book 4", 1, "Section D", "", "", 0, "");
        Book book5("684", "Book 5", 1, "Section E", "", "", 0, "");
        Book book6("347", "Book 6", 1, "Section F", "", "", 0, "");

        bookList.addBook(book4);
        bookList.addBook(book5);
        bookList.addBook(book6);
        bookList.addDataToFile("DauMucSach.txt");
        bookList.printBooks();
        cout << "-------------------------------" << endl;

        bookList.borrowBook("684", "04/06/2013", "04/07/2013", "hjy33");
        bookList.printBooks();
        bookList.addDataToFile("DauMucSach.txt");
        cout << "-------------------------------" << endl;
        return 0;
 

}

