#include <iostream>
#include <string>
using namespace std;

struct Item
{
    int id;
    string name;
    int quantity;
    double price;
};

struct Node
{
    Item data;
    Node *next;
};

class InventoryList
{
private:
    Node *head;

public:
    InventoryList() : head(nullptr) {}

    // Add item to inventory
    void addItem(Item item)
    {
        Node *newNode = new Node{item, nullptr};
        if (!head)
            head = newNode;
        else
        {
            Node *temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    // Search item by ID (linear search)
    Node *searchById(int id)
    {
        Node *temp = head;
        while (temp)
        {
            if (temp->data.id == id)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    // Sort inventory by ID (bubble sort)
    void sortById()
    {
        if (!head)
            return;
        bool swapped;
        Node *ptr;
        Node *last = nullptr;
        do
        {
            swapped = false;
            ptr = head;
            while (ptr->next != last)
            {
                if (ptr->data.id > ptr->next->data.id)
                {
                    swap(ptr->data, ptr->next->data);
                    swapped = true;
                }
                ptr = ptr->next;
            }
            last = ptr;
        } while (swapped);
    }

    // Display all items
    void display()
    {
        Node *temp = head;
        while (temp)
        {
            cout << "ID: " << temp->data.id << ", Name: " << temp->data.name
                 << ", Qty: " << temp->data.quantity << ", Price: $" << temp->data.price << endl;
            temp = temp->next;
        }
    }
};

class RestockQueue
{
private:
    Node *front;
    Node *rear;

public:
    RestockQueue() : front(nullptr), rear(nullptr) {}

    void enqueue(Item item)
    {
        Node *newNode = new Node{item, nullptr};
        if (!rear)
            front = rear = newNode;
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue()
    {
        if (!front)
            return;
        Node *temp = front;
        front = front->next;
        if (!front)
            rear = nullptr;
        delete temp;
    }

    void display()
    {
        Node *temp = front;
        while (temp)
        {
            cout << "Restock Order - ID: " << temp->data.id << ", Name: " << temp->data.name << endl;
            temp = temp->next;
        }
    }
};

class SalesStack
{
private:
    Node *top;

public:
    SalesStack() : top(nullptr) {}

    void push(Item item)
    {
        Node *newNode = new Node{item, top};
        top = newNode;
    }

    void pop()
    {
        if (!top)
            return;
        Node *temp = top;
        top = top->next;
        delete temp;
    }

    void display()
    {
        Node *temp = top;
        while (temp)
        {
            cout << "Recent Sale - ID: " << temp->data.id << ", Name: " << temp->data.name << endl;
            temp = temp->next;
        }
    }
};

int main()
{
    InventoryList inventory;
    RestockQueue restockQueue;
    SalesStack salesStack;
    int choice;

    do
    {
        cout << "\nInventory Management System\n";
        cout << "1. Add Item\n2. Display Inventory\n3. Add Restock Order\n";
        cout << "4. Process Restock Order\n5. Record Sale\n6. Sort Inventory by ID\n";
        cout << "7. Search Item by ID\n8. Exit\nChoice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Item item;
            cout << "Enter ID, Name, Quantity, Price: ";
            cin >> item.id >> item.name >> item.quantity >> item.price;
            inventory.addItem(item);
            break;
        }
        case 2:
            inventory.display();
            break;
        case 3:
        {
            Item item;
            cout << "Enter ID, Name: ";
            cin >> item.id >> item.name;
            restockQueue.enqueue(item);
            break;
        }
        case 4:
            restockQueue.dequeue();
            break;
        case 5:
        {
            int id;
            cout << "Enter Sold Item ID: ";
            cin >> id;
            Node *soldItem = inventory.searchById(id);
            if (soldItem)
            {
                salesStack.push(soldItem->data);
                soldItem->data.quantity--;
            }
            break;
        }
        case 6:
            inventory.sortById();
            cout << "Inventory Sorted by ID!\n";
            break;
        case 7:
        {
            int id;
            cout << "Enter Search ID: ";
            cin >> id;
            Node *result = inventory.searchById(id);
            if (result)
            {
                cout << "Found: " << result->data.name << endl;
            }
            else
            {
                cout << "Item not found!\n";
            }
            break;
        }
        case 8:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 8);

    return 0;
}