#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    int isbn;
    string title;
    string author;

    Book(int i, const string& t, const string& a) : isbn(i), title(t), author(a) {}
};

class TreeNode {
public:
    Book book;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Book b) : book(b), left(NULL), right(NULL) {}
};

void insertBook(TreeNode*& root, const Book& book) {
    if (root == NULL) {
        root = new TreeNode(book);
        return;
    }

    if (book.isbn < root->book.isbn) {
        insertBook(root->left, book);
    } else if (book.isbn > root->book.isbn) {
        insertBook(root->right, book);
    } else {
        // Duplicate ISBN, handle as needed
        cout << "Book with ISBN " << book.isbn << " already exists." << endl;
    }
}

TreeNode* findMin(TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

TreeNode* deleteNode(TreeNode* root, int isbn) {
    if (root == NULL) {
        return root;
    }

    if (isbn < root->book.isbn) {
        root->left = deleteNode(root->left, isbn);
    } else if (isbn > root->book.isbn) {
        root->right = deleteNode(root->right, isbn);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        TreeNode* temp = findMin(root->right);
        root->book = temp->book;
        root->right = deleteNode(root->right, temp->book.isbn);
    }

    return root;
}

void listBooks(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    listBooks(root->left);
    cout << "ISBN: " << root->book.isbn << ", Title: " << root->book.title << ", Author: " << root->book.author << endl;
    listBooks(root->right);
}

int main() {
    TreeNode* bookCollection = NULL;

    // Insert some books
    insertBook(bookCollection, Book(123, "Introduction to Algorithms", "Thomas H. Cormen"));
    insertBook(bookCollection, Book(456, "Clean Code", "Robert C. Martin"));
    insertBook(bookCollection, Book(789, "The Great Gatsby", "F. Scott Fitzgerald"));

    // List all books
    cout << "Book Collection (ISBN order):" << endl;
    listBooks(bookCollection);

    // Delete a book
    int isbnToDelete = 456;
    bookCollection = deleteNode(bookCollection, isbnToDelete);
    cout << "\nAfter deleting book with ISBN " << isbnToDelete << ":" << endl;
    listBooks(bookCollection);

    return 0;
}

