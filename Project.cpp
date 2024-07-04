#include <iostream>
#include <list>
#include <queue>

using namespace std;

class Node
{
public:
    int accountNumber;
    string Name;
    string Address;
    long long int contactInfo;
    string type; // Withdrawal Deposit or Fund Transfer
    double amount;
    queue<Node> transactionHistory; // Queue for transaction history
    Node *next;                     // Next node to traverse
    Node *left;
    Node *right;

    Node(int accNum, string name, string address, long long int contact_Info)
    {
        accountNumber = accNum;
        Name = name;
        Address = address;
        contactInfo = contact_Info;
        left = NULL;
        right = NULL;
    }
    Node(string t, double amt)
    {
        type = t;
        amount = amt;
    }
};

class Customer
{
public:
    // Size of Hash Table

    int table_size;

    // Pointer to an array containing the accNums
    list<Node> *table;

    Node *head;
    Node *root; // Binary Search Tree root

    Customer(int size) // Constructor to initialize head to NULL and root to NULL when object is made
    {
        table_size = size;
        table = new list<Node>[table_size];
        head = NULL;
        root = NULL;
    }

    int hashFunction(int accNum)
    {
        return (accNum % table_size);
    }

    // Chaining Mechanism of Hash Function Applied
    //     void insertElement(int accNum, long long int contact_Info, string name, string address)
    //     {
    //         int index = hashFunction(accNum);

    //         // Check if the account number already exists in the linked list
    //         for (auto &customer : table[index])
    //         {
    //             if (customer.accountNumber == accNum)
    //             {
    //                 // Handle collision using chaining
    //                 cout << "Collision occurred for Account Number: " << accNum << ". Resolving using chaining." << endl;

    //                 // Insert the new account into the linked list at the same index
    //                 Node newAccount(accNum, name, address, contact_Info);
    //                 table[index].push_back(newAccount);
    //                 root = insertBST(root, &table[index].back());

    //                 cout << "Account successfully inserted using chaining at index: " << index << endl;

    //                 return;
    //             }
    //         }
    //             // If no collision, proceed with inserting the new account
    //     Node newAccount(accNum, name, address, contact_Info);
    //     table[index].push_back(newAccount);
    //     root = insertBST(root, &table[index].back());
    // }

    // Open Addressing Mechanism of Hash Function Applied
    void insertElement(int accNum, long long int contact_Info, string name, string address)
    {
        int index = hashFunction(accNum);

        // Check if the account number already exists in the linked list
        for (int i = 0; i < table_size; i++)
        {
            int probing_index = (index + i) % table_size;

            if (table[probing_index].empty())
            {
                // If the slot is empty, insert the new account here
                Node newAccount(accNum, name, address, contact_Info);
                table[probing_index].push_back(newAccount);
                root = insertBST(root, &table[probing_index].back());

                cout << "Account successfully inserted at index: " << probing_index << endl;

                return;
            }
            else if (table[probing_index].front().accountNumber == accNum)
            {
                // Handle the case where the same account number already exists
                cout << "Account with the same number already exists. Choose a different account number." << endl;
                return;
            }
        }

        // If no available slot is found after linear probing, print an error message
        cout << "Error: Unable to insert account. Hash table is full." << endl;
    }

    bool searchAccount(int accNum)
    {
        int index = hashFunction(accNum);
        for (const auto &customer : table[index])
        {
            if (customer.accountNumber == accNum)
            {
                return true;
            }
        }
        return false;
    }

    void displayHashTable()
    {
        for (int i = 0; i < table_size; i++)
        {
            cout << i;
            for (const auto &customer : table[i])
            {
                cout << " ==> Account Number: " << customer.accountNumber
                     << ", Name: " << customer.Name
                     << ", Contact Info: +92" << customer.contactInfo
                     << ", Address: " << customer.Address;
            }
            cout << endl;
        }
    }

    // Function to insert a new customer in the linked list
    void newAccount(int accNum, long long int contact_Info, string name, string address)
    {
        Node *newAccount = new Node(accNum, name, address, contact_Info);

        if (head == NULL)
        {
            head = newAccount;
        }
        else
        {
            Node *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newAccount;
        }

        // Insert into Binary Search Tree for efficient account verification
        root = insertBST(root, newAccount);
    }

    // Function to search for an account in the Binary Search Tree
    bool searchBST(Node *root, int accNum)
    {
        if (root == NULL)
        {
            return false;
        }
        if (root->accountNumber == accNum)
        {
            return true;
        }

        if (root->accountNumber > accNum)
        {
            return searchBST(root->left, accNum);
        }
        else
        {
            return searchBST(root->right, accNum);
        }
    }

    // Function to insert a node into the Binary Search Tree
    Node *insertBST(Node *root, Node *newNode)
    {
        if (root == NULL)
        {
            return newNode;
        }

        if (newNode->accountNumber < root->accountNumber)
        {
            root->left = insertBST(root->left, newNode);
        }
        else if (newNode->accountNumber > root->accountNumber)
        {
            root->right = insertBST(root->right, newNode);
        }

        return root;
    }

    void enqueueTransaction(int accNum, string type, double amount)
    {
        int index = hashFunction(accNum);
        for (auto &customer : table[index])
        {
            if (customer.accountNumber == accNum)
            {
                // Enqueue the new transaction in the customer's transaction history
                customer.transactionHistory.push(Node(type, amount));
                cout << "Transaction successfully enqueued for Account Number: " << accNum << endl;
                return;
            }
        }
        cout << "Account not found. Unable to enqueue transaction." << endl;
    }

    void dequeueTransaction(int accNum)
    {
        int index = hashFunction(accNum);
        for (auto &customer : table[index])
        {
            if (customer.accountNumber == accNum && !customer.transactionHistory.empty())
            {
                // Dequeue the oldest transaction from the customer's transaction history
                customer.transactionHistory.pop();
                cout << "Oldest transaction successfully dequeued for Account Number: " << accNum << endl;
                return;
            }
        }
        cout << "Account not found or transaction history is empty. Unable to dequeue transaction." << endl;
    }

    void displayTransactionHistory(int accNum)
    {
        int index = hashFunction(accNum);
        for (auto &customer : table[index])
        {
            if (customer.accountNumber == accNum)
            {
                // Display the transaction history for the given account
                cout << "Transaction History for Account Number: " << accNum << endl;
                queue<Node> tempQueue = customer.transactionHistory;
                while (!tempQueue.empty())
                {
                    Node t = tempQueue.front();
                    cout << "Type: " << t.type << ", Amount: " << t.amount << endl;
                    tempQueue.pop();
                }
                return;
            }
        }
        cout << "Account not found. Unable to display transaction history." << endl;
    }

    // Destructor
    ~Customer()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            Node *nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = NULL;
    }
};

int main()
{
    Customer c1(10); // Size of Hash Table
    int choice, account_Number;
    long long int contact_Info;
    string name, address;
    string transactionType;
    double transactionAmount;

    while (true)
    {
        cout << "1) Open New Account" << endl;
        cout << "2) Search Account" << endl;
        cout << "3) Search Account by BST" << endl;
        cout << "4) Display Accounts by Hash Table" << endl;
        cout << "5) Add New Transaction" << endl;
        cout << "6) Remove Older Transaction" << endl;
        cout << "7) Display Transaction History" << endl;

        cout << "6) Press -1 to Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter your information to open a new account:" << endl;
            cout << "Account Number" << endl;
            cin >> account_Number;
            cout << "Contact Info" << endl;
            cin >> contact_Info;
            cout << "Name" << endl;
            cin >> name;
            cout << "Address" << endl;
            cin >> address;
            c1.insertElement(account_Number, contact_Info, name, address);
            // c1.newAccount(account_Number, contact_Info, name, address);
            c1.displayHashTable();
            break;
        case 2:
            cout << "Enter the account number to search: ";
            cin >> account_Number;
            if (c1.searchAccount(account_Number))
            {
                cout << "Account found!" << endl;
            }
            else
            {
                cout << "Account not found." << endl;
            }
            break;
        case 3:
            // Search By BST
            cout << "Enter the account number to search: ";
            cin >> account_Number;
            if (c1.searchBST(c1.root, account_Number))
            {
                cout << "Account found!" << endl;
            }
            else
            {
                cout << "Account not found." << endl;
            }
            break;

            break;
        case 4:
            c1.displayHashTable();
            break;
        case 5:
            // Enqueue Transaction
            cout << "Enter the account number: ";
            cin >> account_Number;
            cout << "Enter transaction type (Deposit/Withdrawal/Fund Transfer): ";
            cin >> transactionType;
            cout << "Enter transaction amount: ";
            cin >> transactionAmount;
            c1.enqueueTransaction(account_Number, transactionType, transactionAmount);
            break;
        case 6:
            // Dequeue Transaction
            cout << "Enter the account number: ";
            cin >> account_Number;
            c1.dequeueTransaction(account_Number);
            break;
        case 7:
            // Display Transaction History
            cout << "Enter the account number: ";
            cin >> account_Number;
            c1.displayTransactionHistory(account_Number);
            break;
        default:
            cout << "Invalid Choice" << endl;
            break;
        }
    }

    return 0;
}
