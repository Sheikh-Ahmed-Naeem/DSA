#include<iostream>
#include<string>
using namespace std;

class contact {
public:
    string name;
    string number;

    contact(const string& n, const string& num) : name(n), number(num) {}
};

class node {
public:
    contact Contact;
    node* left;
    node* right;

    node(const contact& contact) : Contact(contact), left(NULL), right(NULL) {}
};

void insert(node* &root, const contact& Contact) {
    if (root == NULL) {
        root = new node(Contact);
        return;
    }
    else if (Contact.name > root->Contact.name) {
        insert(root->right, Contact);
    }
    else if (Contact.name < root->Contact.name) {
        insert(root->left, Contact);
    }
    else {
        // Contact already exists, update the phone number
        root->Contact.number = Contact.number;
    }
}

void search(node* root, const string& key) {
    if (root == NULL) {
        cout << "Tree is NULL" << endl;
        return;
    }
    else if (key == root->Contact.name) {
        cout << "Found the element" << endl;
        cout << "Name: " << root->Contact.name << ", Phone: " << root->Contact.number << endl;
        return;
    }
    else if (key < root->Contact.name) {
        search(root->left, key);
    }
    else if (key > root->Contact.name) {
        search(root->right, key);
    }
}

node* minnode(node* root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

node* deletenode(node* root, const string& name) {
    if (root == NULL) {
        cout << "No tree" << endl;
        return NULL;
    }
    else {
        if (name < root->Contact.name) {
            root->left = deletenode(root->left, name);
        }
        else if (name > root->Contact.name) {
            root->right = deletenode(root->right, name);
        }
        else {
            if (root->left == NULL) {
                node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL) {
                node* temp = root->left;
                delete root;
                return temp;
            }
            node* temp = minnode(root->right);
            root->Contact = temp->Contact;
            root->right = deletenode(root->right, temp->Contact.name);
        }
        return root;
    }
}

void inorder(node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    cout << root->Contact.name << ": " << root->Contact.number << " ";
    inorder(root->right);
}

int main() {
    node* root = NULL;

    while (true) {
        cout << "\nContact Management System\n";
        cout << "1. Add a Contact\n";
        cout << "2. Search for a Contact\n";
        cout << "3. Remove a Contact\n";
        cout << "4. Display Contacts\n";
        cout << "5. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, phone;
                cout << "Enter contact name: ";
                cin.ignore(); // Clear newline from the buffer
                getline(cin, name);
                cout << "Enter phone number: ";
                cin >> phone;

                insert(root, contact(name, phone));
                cout << "Contact added successfully!\n";
                break;
            }
            case 2: {
                string name;
                cout << "Enter contact name to search: ";
                cin.ignore(); // Clear newline from the buffer
                getline(cin, name);

                search(root, name);
                break;
            }
            case 3: {
                string name;
                cout << "Enter contact name to remove: ";
                cin.ignore(); // Clear newline from the buffer
                getline(cin, name);

                root = deletenode(root, name);
                cout << "Contact removed successfully!\n";
                break;
            }
            case 4:
                cout << "Contacts: ";
                inorder(root);
                cout << endl;
                break;
            case 5:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}
