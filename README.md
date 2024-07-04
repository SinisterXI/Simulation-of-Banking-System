# Simulation-of-Banking-System
The simulated banking system is designed to provide efficient and secure operations for managing customer accounts, transactions, and account verification. The implementation utilizes various data structures and algorithms to achieve these goals. The primary components include an Account Management System using Linked List and Hash Table, Transaction History using a Queue, and Account Verification using a Binary Search Tree. This report outlines the design choices, data structures, algorithms, and testing procedures employed in the project.
# Implemented Algorithms
Inserting Elements into Hash Table
Chaining Mechanism: Handles collisions by inserting new accounts into linked lists at hashed indices.
Open Addressing Mechanism: Uses linear probing to place new accounts in the next available slot upon collisions.

Searching for an Account
Utilizes the hash function to locate the index in the hash table.
Searches the linked list at the hashed index for the specified account number.

Transaction Management
Enqueues new transactions into a customer's history.
Dequeues the oldest transaction when necessary.
Displays transaction histories for specific accounts.
Binary Search Tree (BST) Operations

Inserts nodes into the BST based on account numbers.
Searches the BST for efficient account verification.
