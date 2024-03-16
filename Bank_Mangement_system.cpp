#include<iostream>
#include<string>
#include<list>
#include<queue>
using namespace std;

class information {
public:
    int account_number;
    string name;
    string address;
    string contact;
    queue<string> transaction_history;

    information(int a_n, const string& n, const string& addr, const string& cont) {
        account_number = a_n;
        name = n;
        address = addr;
        contact = cont;
    }
    void enquetransaction(const string& transaction) {
        transaction_history.push(transaction);
    }

    void dequeueold(int max_history) {
        while (transaction_history.size() > max_history) {
            transaction_history.pop();
        }
    }
    void displaytransaction() const {
        cout << "Transaction history for Account Number " << account_number << endl;
        queue<string> tempQueue = transaction_history;
        while (!tempQueue.empty()) {
            cout << tempQueue.front() << endl;
            tempQueue.pop();
        }
    }
};
class node {
public:
    information data;
    node* next;

    node(information Information) : data(Information), next(NULL) {}
};

class TreeNode {
public:
    information data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(information Information) : data(Information), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, const information& Information) {
        if (node == nullptr) {
            return new TreeNode(Information);
        }

        if (Information.account_number < node->data.account_number) {
            node->left = insert(node->left, Information);
        } else if (Information.account_number > node->data.account_number) {
            node->right = insert(node->right, Information);
        }

        return node;
    }
    TreeNode* search(TreeNode* node, int account_number) const {
        if (node == nullptr || node->data.account_number == account_number) {
            return node;
        }

        if (account_number < node->data.account_number) {
            return search(node->left, account_number);
        }

        return search(node->right, account_number);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(const information& Information) {
        root = insert(root, Information);
    }

    information* getinfo(int account_number) const {
        TreeNode* result = search(root, account_number);
        return (result != nullptr) ? &(result->data) : nullptr;
    }
};

class MyHash {
public:
    int size;
    list<node>* table;

    MyHash(int ts) {
        size = ts;
        table = new list<node>[size];
    }

    int hash_func(int account_number) {
        return (account_number % size);
    }

    void addnewcustomer(const information& Information) {
        int index = hash_func(Information.account_number);
        node* n = new node(Information);
        table[index].push_back(*n);
    }

    information* getinfo(int account_number) {
        int index = hash_func(account_number);
        for (auto& current : table[index]) {
            if (current.data.account_number == account_number) {
                return &current.data;
            }
        }
        return nullptr;
    }
};
// Function to display the menu
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Add New Customer\n";
    cout << "2. Open New Account\n";
    cout << "3. Perform Transaction\n";
    cout << "4. Display Transaction History\n";
    cout << "5. Exit\n";
}
int main() {
    MyHash hashTable(10); // Assuming hash table size is 10
    BinarySearchTree bst;

    while (true) {
        displayMenu();

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int acc_num;
            string name, address, contact;

            cout << "Enter Account Number: ";
            cin >> acc_num;

            if (bst.getinfo(acc_num) != nullptr) {
                cout << "Account number already exists. Please choose a different account number.\n";
                continue;
            }

            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter Address: ";
            getline(cin, address);

            cout << "Enter Contact Information: ";
            getline(cin, contact);

            information newCustomer(acc_num, name, address, contact);
            hashTable.addnewcustomer(newCustomer);
            bst.insert(newCustomer);

            cout << "Customer added successfully.\n";
        } else if (choice == 2) {
            int acc_num;
            string name, address, contact;

            cout << "Enter Account Number: ";
            cin >> acc_num;

            if (bst.getinfo(acc_num) != nullptr) {
                cout << "Account number already exists. Please choose a different account number.\n";
                continue;
            }

            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter Address: ";
            getline(cin, address);

            cout << "Enter Contact Information: ";
            getline(cin, contact);

            information newAccount(acc_num, name, address, contact);
            hashTable.addnewcustomer(newAccount);
            bst.insert(newAccount);

            cout << "New account opened successfully.\n";
        } else if (choice == 3) {
            int acc_num;
            string transaction;

            cout << "Enter Account Number: ";
            cin >> acc_num;

            information* customer = bst.getinfo(acc_num);

            if (customer != nullptr) {
                cout << "Enter Transaction Details: ";
                cin.ignore();
                getline(cin, transaction);

                customer->enquetransaction(transaction);
                cout << "Transaction performed successfully.\n";
            } else {
                cout << "Customer not found.\n";
            }
        } else if (choice == 4) {
            int acc_num;
            cout << "Enter Account Number to Display Transaction History: ";
            cin >> acc_num;

            information* customer = bst.getinfo(acc_num);

            if (customer != nullptr) {
                customer->displaytransaction();
            } else {
                cout << "Customer not found.\n";
            }
        } else if (choice == 5) {
            cout << "Exiting the program.\n";
            break;
        } else {
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    }
    return 0;
}
