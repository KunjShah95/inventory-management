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

// Sorting algorithms
namespace SortAlgorithms
{
    // Selection Sort
    void selectionSort(Item *items, int n)
    {
        for (int i = 0; i < n - 1; i++)
        {
            int min_idx = i;
            for (int j = i + 1; j < n; j++)
            {
                if (items[j].id < items[min_idx].id)
                {
                    min_idx = j;
                }
            }
            if (min_idx != i)
            {
                Item temp = items[i];
                items[i] = items[min_idx];
                items[min_idx] = temp;
            }
        }
    }

    // Insertion Sort
    void insertionSort(Item *items, int n)
    {
        for (int i = 1; i < n; i++)
        {
            Item key = items[i];
            int j = i - 1;
            while (j >= 0 && items[j].id > key.id)
            {
                items[j + 1] = items[j];
                j = j - 1;
            }
            items[j + 1] = key;
        }
    }

    // Quick Sort
    int partition(Item *items, int low, int high)
    {
        int pivot = items[high].id;
        int i = low - 1;

        for (int j = low; j <= high - 1; j++)
        {
            if (items[j].id < pivot)
            {
                i++;
                Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
        Item temp = items[i + 1];
        items[i + 1] = items[high];
        items[high] = temp;
        return i + 1;
    }

    void quickSortHelper(Item *items, int low, int high)
    {
        if (low < high)
        {
            int pi = partition(items, low, high);
            quickSortHelper(items, low, pi - 1);
            quickSortHelper(items, pi + 1, high);
        }
    }

    void quickSort(Item *items, int n)
    {
        if (n > 0)
        {
            quickSortHelper(items, 0, n - 1);
        }
    }

    // Merge Sort
    void merge(Item *items, int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        // Create temp arrays
        Item *L = new Item[n1];
        Item *R = new Item[n2];

        // Copy data to temp arrays
        for (int i = 0; i < n1; i++)
            L[i] = items[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = items[mid + 1 + j];

        // Merge the temp arrays back into items[left..right]
        int i = 0;    // Initial index of first subarray
        int j = 0;    // Initial index of second subarray
        int k = left; // Initial index of merged subarray

        while (i < n1 && j < n2)
        {
            if (L[i].id <= R[j].id)
            {
                items[k] = L[i];
                i++;
            }
            else
            {
                items[k] = R[j];
                j++;
            }
            k++;
        }

        // Copy the remaining elements of L[], if there are any
        while (i < n1)
        {
            items[k] = L[i];
            i++;
            k++;
        }

        // Copy the remaining elements of R[], if there are any
        while (j < n2)
        {
            items[k] = R[j];
            j++;
            k++;
        }

        delete[] L;
        delete[] R;
    }

    void mergeSortHelper(Item *items, int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            mergeSortHelper(items, left, mid);
            mergeSortHelper(items, mid + 1, right);
            merge(items, left, mid, right);
        }
    }

    void mergeSort(Item *items, int n)
    {
        if (n > 0)
        {
            mergeSortHelper(items, 0, n - 1);
        }
    }
}

// Searching algorithms
namespace SearchAlgorithms
{
    // Binary search
    bool binarySearch(Item *items, int n, int id, Item &result)
    {
        int left = 0;
        int right = n - 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (items[mid].id == id)
            {
                result = items[mid];
                return true;
            }

            if (items[mid].id < id)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return false;
    }
}

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
    int choice, mainMenuChoice;

    // Sample data for demonstration
    Item item1 = {101, "Laptop", 10, 999.99};
    Item item2 = {102, "Phone", 20, 599.99};
    Item item3 = {103, "Tablet", 15, 399.99};

    inventory.addItem(item1);
    inventory.addItem(item2);
    inventory.addItem(item3);

    do
    {
        cout << "\n===== INVENTORY MANAGEMENT SYSTEM =====\n";
        cout << "1. Inventory Operations\n";
        cout << "2. Data Structure Demonstrations\n";
        cout << "3. Sorting Algorithms\n";
        cout << "4. Searching Algorithms\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainMenuChoice;

        switch (mainMenuChoice)
        {
        case 1: // Inventory Operations
            do
            {
                cout << "\n----- INVENTORY OPERATIONS -----\n";
                cout << "1. Add Item\n2. Display Inventory\n3. Add Restock Order\n";
                cout << "4. Process Restock Order\n5. Record Sale\n6. Sort Inventory by ID\n";
                cout << "7. Search Item by ID\n8. Back to Main Menu\nChoice: ";
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
                    cout << "\n-- Linked List Implementation --\n";
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
                    cout << "Processed restock order (dequeued)\n";
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
                        cout << "Sale recorded. Quantity updated.\n";
                    }
                    else
                    {
                        cout << "Item not found!\n";
                    }
                    break;
                }
                case 6:
                    inventory.sortById();
                    cout << "Inventory Sorted by ID (Bubble Sort)!\n";
                    break;
                case 7:
                {
                    int id;
                    cout << "Enter Search ID: ";
                    cin >> id;

                    cout << "\n-- Linear Search Result (from LinkedList) --\n";
                    Node *result = inventory.searchById(id);
                    if (result)
                    {
                        cout << "Found: " << result->data.name
                             << ", Qty: " << result->data.quantity
                             << ", Price: $" << result->data.price << endl;
                    }
                    else
                    {
                        cout << "Item not found using linear search!\n";
                    }
                    break;
                }
                case 8:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
                }
            } while (choice != 8);
            break;

        case 2: // Data Structure Demos
            do
            {
                cout << "\n----- DATA STRUCTURE DEMONSTRATIONS -----\n";
                cout << "1. LinkedList (Display Inventory)\n";
                cout << "2. Queue (Display Restock Orders)\n";
                cout << "3. Stack (Display Recent Sales)\n";
                cout << "4. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    cout << "\n-- Linked List Implementation --\n";
                    inventory.display();
                    break;
                case 2:
                    cout << "\n-- Queue Implementation (FIFO) --\n";
                    restockQueue.display();
                    break;
                case 3:
                    cout << "\n-- Stack Implementation (LIFO) --\n";
                    salesStack.display();
                    break;
                case 4:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
                }
            } while (choice != 4);
            break;

        case 3: // Sorting Algorithms
            do
            {
                cout << "\n----- SORTING ALGORITHMS -----\n";
                cout << "1. Bubble Sort\n";
                cout << "2. Selection Sort\n";
                cout << "3. Insertion Sort\n";
                cout << "4. Quick Sort\n";
                cout << "5. Merge Sort\n";
                cout << "6. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> choice;

                // Convert linked list to array for sorting demonstrations
                int n = 0;
                Node *temp = inventory.searchById(0); // Just to get head pointer
                while (temp)
                {
                    n++;
                    temp = temp->next;
                }
                Item *items = new Item[n];
                temp = inventory.searchById(0); // Just to get head pointer
                for (int i = 0; i < n; i++)
                {
                    items[i] = temp->data;
                    temp = temp->next;
                }

                switch (choice)
                {
                case 1:
                    cout << "\n-- Bubble Sort --\n";
                    inventory.sortById();
                    inventory.display();
                    break;
                case 2:
                    cout << "\n-- Selection Sort --\n";
                    SortAlgorithms::selectionSort(items, n);
                    for (int i = 0; i < n; i++)
                    {
                        cout << "ID: " << items[i].id << ", Name: " << items[i].name
                             << ", Qty: " << items[i].quantity << ", Price: $" << items[i].price << endl;
                    }
                    break;
                case 3:
                    cout << "\n-- Insertion Sort --\n";
                    SortAlgorithms::insertionSort(items, n);
                    for (int i = 0; i < n; i++)
                    {
                        cout << "ID: " << items[i].id << ", Name: " << items[i].name
                             << ", Qty: " << items[i].quantity << ", Price: $" << items[i].price << endl;
                    }
                    break;
                case 4:
                    cout << "\n-- Quick Sort --\n";
                    SortAlgorithms::quickSort(items, n);
                    for (int i = 0; i < n; i++)
                    {
                        cout << "ID: " << items[i].id << ", Name: " << items[i].name
                             << ", Qty: " << items[i].quantity << ", Price: $" << items[i].price << endl;
                    }
                    break;
                case 5:
                    cout << "\n-- Merge Sort --\n";
                    SortAlgorithms::mergeSort(items, n);
                    for (int i = 0; i < n; i++)
                    {
                        cout << "ID: " << items[i].id << ", Name: " << items[i].name
                             << ", Qty: " << items[i].quantity << ", Price: $" << items[i].price << endl;
                    }
                    break;
                case 6:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
                }
                delete[] items;
            } while (choice != 6);
            break;

        case 4: // Searching Algorithms
            do
            {
                cout << "\n----- SEARCHING ALGORITHMS -----\n";
                cout << "1. Linear Search (from LinkedList)\n";
                cout << "2. Binary Search\n";
                cout << "3. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> choice;

                int searchId;
                Item result;
                bool found = false;

                if (choice >= 1 && choice <= 2)
                {
                    cout << "Enter ID to search: ";
                    cin >> searchId;
                }

                // Convert linked list to array for binary search demonstration
                int n = 0;
                Node *temp = inventory.searchById(0); // Just to get head pointer
                while (temp)
                {
                    n++;
                    temp = temp->next;
                }
                Item *items = new Item[n];
                temp = inventory.searchById(0); // Just to get head pointer
                for (int i = 0; i < n; i++)
                {
                    items[i] = temp->data;
                    temp = temp->next;
                }
                SortAlgorithms::quickSort(items, n);

                switch (choice)
                {
                case 1:
                    cout << "\n-- Linear Search --\n";
                    temp = inventory.searchById(searchId);
                    if (temp)
                    {
                        cout << "Found: " << temp->data.name
                             << ", Qty: " << temp->data.quantity
                             << ", Price: $" << temp->data.price << endl;
                    }
                    else
                    {
                        cout << "Item not found!\n";
                    }
                    break;
                case 2:
                    cout << "\n-- Binary Search --\n";
                    found = SearchAlgorithms::binarySearch(items, n, searchId, result);
                    if (found)
                    {
                        cout << "Found: " << result.name
                             << ", Qty: " << result.quantity
                             << ", Price: $" << result.price << endl;
                    }
                    else
                    {
                        cout << "Item not found!\n";
                    }
                    break;
                case 3:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
                }
                delete[] items;
            } while (choice != 3);
            break;

        case 5:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (mainMenuChoice != 5);

    return 0;
}