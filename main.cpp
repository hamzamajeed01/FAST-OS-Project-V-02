#include <SFML/Graphics.hpp>
#include <iostream>
#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <ctime>
#include <string>
#include <time.h>
#include <utility>
#include <vector>
#include <math.h>
#include <vector>
#include <string>
#include <queue>
using namespace std;
void generateRandomColor(int &r, int &g, int &b)
{
    r = rand() % 256;
    g = rand() % 256;
    b = rand() % 256;
}

class Bankers_Process
{
public:
    vector<int> resouces;

public:
    Bankers_Process()
    {
    }

    void Max_Matrix(int num_of_resources, vector<int> instances, int id)
    {

        int random_num;
        int a, b, c;
        cout << "Enter P" << id << " " << num_of_resources << " Max attributes : ";
        for (int j = 0; j < num_of_resources; j++)
        {
            if (instances[j] != 0)
            {

                cin >> a;
                while (a > instances[j])
                {
                    cout << "Wrong Input " << endl;
                    cin >> a;
                }

                resouces.push_back(a);
            }
            else
            {
                resouces.push_back(0);
            }
        }
    }

    void Need_Matrix(Bankers_Process &Max_obj, Bankers_Process &Allocted_obj, int num_of_resources)
    {

        int random_num;
        for (int j = 0; j < num_of_resources; j++)
        {

            random_num = Max_obj.resouces[j] - Allocted_obj.resouces[j];
            resouces.push_back(random_num);
        }
    }

    void Allocated_Matrix(Bankers_Process &obj, int num_of_resources, int id)
    {

        int random_num;
        int a;
        cout << "Enter P" << id << " " << num_of_resources << "allocated attributes : ";
        for (int j = 0; j < num_of_resources; j++)
        {
            if (obj.resouces[j] != 0)
            {
                cin >> a;
                while (a > obj.resouces[j])
                {
                    cout << "Wrong Input " << endl;
                    cin >> a;
                }

                resouces.push_back(a);
            }
            else
            {
                resouces.push_back(0);
            }
        }
    }

    bool Avaliable_Matrix(int num_of_process, int num_of_resources, Bankers_Process obj[], vector<int> instances, Bankers_Process &Avaliable)
    {
        int sum = 0;

        sum = 0;
        for (int j = 0; j < num_of_resources; j++)
        {
            sum = 0;
            for (int i = 0; i < num_of_process; i++)
            {
                sum += obj[i].resouces[j];
            }

            if (sum <= instances[j])
            {
                Avaliable.resouces.push_back(instances[j] - sum);
            }
            else
            {
                cout << endl
                     << endl;
                cout << "Error Error OS Allocated more intance to Process " << endl
                     << endl;
                return false;
            }
        }
        return true;
    }

    void Print_Banker_Process(int num_of_resources, int id)
    {

        int i = 0;
        while (i != 9)
        {
            cout << " ";
            i++;
        }

        for (int j = 0; j < num_of_resources; j++)
        {

            // cout << resouces[j] << " ";
            int r, g, b;
            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m" << resouces[j] << " "
                 << "\033[0m";
        }
    }
    void Update_Avaliable_(int num_of_resources, Bankers_Process &Allocated)
    {
        for (int j = 0; j < num_of_resources; j++)
        {

            resouces[j] += Allocated.resouces[j];
        }
    }

    bool Check_Need(int num_of_resources, Bankers_Process &request)
    {
        for (int j = 0; j < num_of_resources; j++)
        {

            if (request.resouces[j] > resouces[j])
            {
                cout << "Request cannot be Granted  " << endl;
                return false;
            }
        }
    }

    void Update_Matrixes(int num_of_resources, Bankers_Process &Avaliable, Bankers_Process &Allocation, Bankers_Process &Need)
    {
        for (int j = 0; j < num_of_resources; j++)
        {

            Avaliable.resouces[j] = Avaliable.resouces[j] - resouces[j];
            Allocation.resouces[j] = Allocation.resouces[j] + resouces[j];
            Need.resouces[j] = Need.resouces[j] - resouces[j];
        }
    }
};

void Banker_Algorithm()
{

    int r, g, b;

    int num_of_process;
    int num_of_resources;

    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Enter number of Process : "
         << "\033[0m";
    cin >> num_of_process;

    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Enter number of Resources : "
         << "\033[0m";
    cin >> num_of_resources;

    vector<int> instances;
    // vector <int> request;
    bool *arr = new bool[num_of_process];
    for (int i = 0; i < num_of_process; i++)
    {
        arr[i] = false;
    }
    int a;
    //////////////////////////////////////////////////Istances like tape drive , Printer , Scanner////////////////////////////////
    for (int i = 0; i < num_of_resources; i++)
    {
        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "Enter Instance " << i + 1 << " : "
             << "\033[0m";
        cin >> a;
        instances.push_back(a);
    }
    srand(time(nullptr));

    int random_num = rand() % 10;

    Bankers_Process *Max_Matrix_Process = new Bankers_Process[num_of_process];
    Bankers_Process *Allocation_Matrix_Process = new Bankers_Process[num_of_process];
    Bankers_Process *Need_Matrix_Process = new Bankers_Process[num_of_process];
    Bankers_Process Avaliable_Resources;
    Bankers_Process Request;
    //             Max  Matrix

    srand(time(0));

    ///////////////////////////////////////////////////Taking Input of Max , Allocated , Need Matrix ////////////////////////////////
    for (int i = 0; i < num_of_process; i++)
    {
        Max_Matrix_Process[i].Max_Matrix(num_of_resources, instances, i);
        Allocation_Matrix_Process[i].Allocated_Matrix(Max_Matrix_Process[i], num_of_resources, i);
        Need_Matrix_Process[i].Need_Matrix(Max_Matrix_Process[i], Allocation_Matrix_Process[i], num_of_resources);
    }

    ///////////////////////////////////////////////Printing All Matrices//////////////////////////////////////////////////
    // cout << "     Max    Allocated    Need\n";

    // generateRandomColor(r, g, b);
    // cout << "\033[38;2;" << r << ";" << g << ";" << b << "m" <<  "          Max            Allocated            Need\n" << "\033[0m";
    int ii = 1;
    for (int i = 0; i < num_of_process; i++)
    {
        // cout << "P" << i << "  ";
        ii = 1;
        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "P" << i << "  "
             << "\033[0m";
        Max_Matrix_Process[i].Print_Banker_Process(num_of_resources, ii);
        ii++;
        Allocation_Matrix_Process[i].Print_Banker_Process(num_of_resources, ii);
        ii++;
        Need_Matrix_Process[i].Print_Banker_Process(num_of_resources, ii);
        cout << endl;
    }

    /////////////////////////////////////////////////Making Available Matrix ////////////////////////////////////
    if (!Avaliable_Resources.Avaliable_Matrix(num_of_process, num_of_resources, Allocation_Matrix_Process, instances, Avaliable_Resources))
    {
        return;
    }

    int req;
    // cout << "Press 1 for Extra instances Request : ";

    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Press 1 for Extra instances Request : "
         << "\033[0m";
    cin >> req;

    if (req == 1)
    {
        int a = 999;
        while (a >= num_of_process)
        {
            // cout << "Enter Process Id : ";
            int r, g, b;
            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "Enter Process Id : "
                 << "\033[0m";
            cin >> a;
        }

        int rr;
        for (int i = 0; i < num_of_resources; i++)
        {

            // cout << "Enter R" << i + 1 << " for P" << a << " : ";
            int r, g, b;
            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "Enter R" << i + 1 << " for P" << a << " : "
                 << "\033[0m";
            cin >> rr;
            Request.resouces.push_back(r);
        }
        //////////////////////////////////////////////Check Condition1 and Condition2 of Request Algorithm//////////////////////
        if (Need_Matrix_Process[a].Check_Need(num_of_resources, Request) && Avaliable_Resources.Check_Need(num_of_resources, Request))
        {
            Request.Update_Matrixes(num_of_resources, Avaliable_Resources, Allocation_Matrix_Process[a], Need_Matrix_Process[a]);
        }
        else
        {
            return;
        }
    }

    ////////////////////////////////////////////////Safety Algorithm Started//////////////////////////////////////////

    int idx = -1;
    int counter = 0;

    cout << endl
         << endl;
    while (1)
    {
        idx++;
        idx = idx % num_of_process;
        bool check = true;
        if (arr[idx] == false)
        {
            for (int k = 0; k < num_of_resources; k++)
            {
                if (Need_Matrix_Process[idx].resouces[k] > Avaliable_Resources.resouces[k])
                {
                    check = false;
                    break;
                }
            }
            if (check)
            {
                counter++;
                arr[idx] = true;
                Avaliable_Resources.Update_Avaliable_(num_of_resources, Allocation_Matrix_Process[idx]);

                // cout << "P" << idx << " , ";
                int r, g, b;
                generateRandomColor(r, g, b);
                cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                     << "P" << idx << " , " << a << " : "
                     << "\033[0m";
                if (counter == num_of_process)
                {
                    // cout << "\n Safe Sequence " << endl << endl;
                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "\n Safe Sequence " << endl
                         << endl
                         << "\033[0m";
                    if (req == 1)
                    {
                        // cout << "Yes request, would be Granted " << endl;
                        generateRandomColor(r, g, b);
                        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                             << "Yes request, would be Granted " << endl
                             << "\033[0m";
                    }
                    break;
                }
                idx = -1;
            }
            else
            {
                if (idx == num_of_process - 1)
                {
                    // cout << endl << "This is Unsafe Sequence " << endl << endl;
                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m" << endl
                         << "This is Unsafe Sequence " << endl
                         << endl
                         << "\033[0m";
                    break;
                }
            }
        }
    }
}

class Node
{
public:
    int data;
    Node *next;
    int use_bit;

    Node(int data)
    {
        this->data = data;
        this->use_bit = 1;
        this->next = NULL;
    }
};

class CircularLinkedList
{
public:
    Node *head;
    Node *curr;
    CircularLinkedList()
    {
        this->head = NULL;
    }

    // Insert a new node at the beginning of the list
    void insert(int data)
    {
        Node *newNode = new Node(data);
        if (this->head == NULL)
        {
            this->head = newNode;
            this->curr = head;
            newNode->next = head;
        }
        else
        {
            Node *temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }

    // Display the list
    void display()
    {
        if (head == NULL)
        {
            int r, g, b;
            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "The list is empty." << endl
                 << "\033[0m";
        }
        else
        {
            Node *temp = head;
            do
            {
                int r, g, b;
                generateRandomColor(r, g, b);
                cout << "\033[38;2;" << r << ";" << g << ";" << b << "m" << temp->data << "(" << temp->use_bit << ")"
                     << "  "
                     << "\033[0m";

                temp = temp->next;
            } while (temp != head);
            cout << endl;
        }
    }

    // Delete a node from the list

    // Traverse the list and perform some operation on each node
    bool found(int page_data)
    {
        if (head == NULL)
        {
            return false;
        }
        else
        {
            Node *temp = head;
            do
            {

                if (page_data == temp->data)
                {
                    temp->use_bit = 1;

                    return true;
                }

                temp = temp->next;

            } while (temp != head);
        }
        return false;
    }

    void Second_Chance_Algo(int page_data)
    {

        while (1)
        {
            if (curr->use_bit == 0)
            {
                curr->data = page_data;
                curr->use_bit = 1;
                curr = curr->next;
                return;
            }
            else
            {
                curr->use_bit = 0;
                curr = curr->next;
            }
        }
    }
};

void Second_Chance_Algorithm()
{
    int frames;
    int num_of_page_fault = 0;

    int r, g, b;
    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Enter number of frames of Ram : "
         << "\033[0m";
    cin >> frames;

    int page_data;
    int counter = 1;
    CircularLinkedList Ram;
    while (1)
    {

        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "Enter Page data : "
             << "\033[0m";
        cin >> page_data;

        if (page_data == -1)
        {
            system("cls");
            break;
        }

        if (counter <= frames)
        {
            if (Ram.found(page_data) == false)
            {

                Ram.insert(page_data);
                counter++;
            }
            else
            {
                cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                     << "PAGE____Hit_____Occured" << endl
                     << "\033[0m";
            }
        }

        else
        {
            if (Ram.found(page_data) == false)
            {
                generateRandomColor(r, g, b);
                cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                     << "PAGE____Fault_____Occured" << endl
                     << "\033[0m";
                num_of_page_fault++;
                Ram.Second_Chance_Algo(page_data);
            }
        }

        Ram.display();
        cout << endl
             << endl;
    }
}

struct Node_
{
    int key;
    int value;
    Node_ *next;
};

// Hash table class using chaining
class HashTable
{
private:
    std::vector<Node_ *> table;
    int size;

    // Hash function to map keys to indices
    int hash(int key)
    {
        return key % size;
    }

public:
    // Constructor to create hash table with given size
    HashTable(int size)
    {
        this->size = size;
        table.resize(size, nullptr);
    }

    // Destructor to delete all nodes in the hash table
    ~HashTable()
    {
        for (int i = 0; i < size; i++)
        {
            Node_ *current = table[i];
            while (current != nullptr)
            {
                Node_ *temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    // Insert a key-value pair into the hash table
    void insert(int key, int value)
    {
        int index = hash(key);
        Node_ *node = new Node_;
        node->key = key;
        node->value = value;
        node->next = table[index];
        table[index] = node;
    }

    // Search for a value associated with a key in the hash table
    int search(int key)
    {
        int index = hash(key);
        Node_ *current = table[index];
        while (current != nullptr)
        {
            if (current->key == key)
            {
                return current->value;
            }
            current = current->next;
        }
        return -1; // Not found
    }

    // Remove a key-value pair from the hash table
    void remove(int key)
    {
        int index = hash(key);
        Node_ *current = table[index];
        Node_ *previous = nullptr;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                if (previous == nullptr)
                {
                    table[index] = current->next;
                }
                else
                {
                    previous->next = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    // Traverse the hash table and print all indices
    void traverse()
    {
        int r, g, b;
        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "Hashed Page Table " << endl
             << "\033[0m";

        for (int i = 0; i < size; i++)
        {
            if (i == 0)
            {
                generateRandomColor(r, g, b);
                cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                     << "_____" << endl
                     << "\033[0m";
            }
            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "| " << i << " |"
                 << "\033[0m";

            Node_ *current = table[i];
            while (current != nullptr)
            {
                generateRandomColor(r, g, b);
                cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                     << "->(" << current->key << " , " << current->value << ")"
                     << "\033[0m";
                current = current->next;
            }
            cout << endl;
        }
        cout << endl
             << endl;
    }
};

bool TLB_Miss_Or_Hit(vector<pair<int, int>> TLB, int Page_no, float &hit, float &miss)
{

    int r, g, b;
    for (int i = 0; i < 10; i++)
    {
        if (Page_no == TLB[i].first)
        {
            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m" << endl
                 << endl
                 << "-------------TLB Hit------------" << endl
                 << "\033[0m";
            hit++;
            return true;
        }
    }

    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m" << endl
         << endl
         << "-------------TLB Miss------------" << endl
         << "\033[0m";
    miss++;
    return false;
}

bool check_Ram_have_space(bool visited[], int total)
{
    int count = 0;
    for (int i = 0; i < total; i++)
    {
        if (visited[i] == true)
        {
            count++;
        }
    }

    float per = float(count) / float(total);
    per = per * 100;

    if (per > 80)
    {
        return false;
    }

    return true;
}
void Print_TLB_Table(vector<pair<int, int>> TLB)
{

    int r, g, b;
    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "  TLB Table  " << endl
         << "\033[0m";
    for (int i = 0; i < 10; i++)
    {

        if (i == 0)
        {
            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "__________" << endl
                 << "\033[0m";
        }
        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "| " << TLB[i].first << " | " << TLB[i].second << " | " << endl
             << "\033[0m";
    }

    cout << endl
         << endl;
}

void Hashed_Table_With_TLB()
{
    int Ram_size;
    int TLB_ptr = 0;
    int r, g, b;
    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Enter the size of Ram : "
         << "\033[0m";
    cin >> Ram_size;
    float missratio = 0, hitratio = 0, total = 0;
    cout << endl;

    int Frame_size;

    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Enter the size of Frame : "
         << "\033[0m";
    cin >> Frame_size;
    cout << endl;

    // unordered_map<int , int> Page_Table;
    ////////////////////////////////////////////inserting dummy values into hash table///////////////////
    HashTable Page_Table(10);
    int Total_Locations_of_Ram = Ram_size / Frame_size;
    int h = 0;
    int rr;
    int ff;
    while (h != 3)
    {
        rr = rand() % 100;
        ff = rand() % Total_Locations_of_Ram;
        Page_Table.insert(rr, ff);
        h++;
    }

    vector<pair<int, int>> TLB(10, std::make_pair(0, 0));

    int *Ram = new int[Total_Locations_of_Ram];
    bool *visited = new bool[Total_Locations_of_Ram];
    for (int i = 0; i < Total_Locations_of_Ram; i++)
    {
        Ram[i] = -1;
        visited[i] = false;
    }

    int Logical_add;
    int Page_No;
    int select_frame;
    int offset;

    Print_TLB_Table(TLB);
    Page_Table.traverse();
    while (1)
    {

        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "Enter Logical Address : "
             << "\033[0m";

        cin >> Logical_add;
        cout << endl;

        TLB_ptr = TLB_ptr % 10;

        if (Logical_add == -1)
        {
            system("cls");
            break;
        }
        srand(time(0));
        offset = Logical_add % Frame_size;
        Page_No = Logical_add / Frame_size;

        int ar = 0;
        total++;
        if (TLB_Miss_Or_Hit(TLB, Page_No, hitratio, missratio) == false)
        {
            if (ar = Page_Table.search(Page_No) != -1)
            {

                TLB[TLB_ptr].first = Page_No;
                TLB[TLB_ptr].second = select_frame;
                TLB_ptr++;
            }
            else
            {
                if (check_Ram_have_space(visited, Total_Locations_of_Ram) == true)
                {

                    select_frame = Page_No % Total_Locations_of_Ram;

                    while (visited[select_frame] == true)
                    {
                        select_frame = rand() % Total_Locations_of_Ram;
                    }
                    visited[select_frame] = true;
                    Page_Table.insert(Page_No, select_frame);
                    TLB[TLB_ptr].first = Page_No;
                    TLB[TLB_ptr].second = select_frame;
                    TLB_ptr++;
                    Ram[select_frame] = 1;
                }
                else
                {
                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "Ram is Full" << endl
                         << endl
                         << "\033[0m";
                    break;
                }
            }
        }

        Print_TLB_Table(TLB);
        Page_Table.traverse();
    }

    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Hit Ratio: " << hitratio / total << endl
         << "\033[0m";
    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Miss Ratio: " << missratio / total << endl
         << "\033[0m";
}

void Print_Page_Tables(vector<vector<int>> &Outer_And_Inner_Table, int outer, int inner, vector<vector<bool>> &visited, int outer_idx, int inner_idx)
{
    cout << endl
         << endl;
    int r, g, b;
    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Outer Page Table" << endl
         << "\033[0m";

    for (int i = 0; i < outer; i++)
    {
        if (visited[i][0] == true)
        {
            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "|  Ptr" << i + 1 << "  | " << endl
                 << "\033[0m";
        }
        else
        {
            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "|  Null  |" << endl
                 << "\033[0m";
        }
    }

    for (int i = 0; i < outer; i++)
    {
        if (visited[i][0] == true)
        {
            cout << endl;
            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "Inner Page Table" << i + 1 << endl
                 << "\033[0m";

            for (int k = 1; k <= inner; k++)
            {
                if (visited[i][k] == true)
                {
                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "|   " << k - 1 << "  |  " << Outer_And_Inner_Table[i][k] << "  |" << endl
                         << "\033[0m";
                }
                else
                {
                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "|  "
                         << "    |    "
                         << "  |" << endl
                         << "\033[0m";
                }
            }
        }
    }
    cout << endl
         << endl;
}

void Two_Level_Paging()
{
    int Log_add_bits = 0;
    int r, g, b;
    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Enter Logical Address Bits : "
         << "\033[0m";
    cin >> Log_add_bits;
    cout << endl;

    int offset_in_bits = 0;
    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Enter Page size  : "
         << "\033[0m";
    cin >> offset_in_bits;

    while (offset_in_bits > Log_add_bits)
    {
        cout << endl;
        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "----Wrong Input-----"
             << "\033[0m";

        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "Enter Offset in Bits : "
             << "\033[0m";
        cin >> offset_in_bits;
    }
    cout << endl;

    int Page_No = Log_add_bits - offset_in_bits;
    int inner, outer;

    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Enter Size of Outer Page Table in Bits : "
         << "\033[0m";
    cin >> outer;
    cout << endl;
    srand(time(0));

    while (outer > Page_No)
    {
        cout << endl;
        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "----Wrong Input-----"
             << "\033[0m";

        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "Enter Outer Page Table Bits : "
             << "\033[0m";
        cin >> outer;
    }
    cout << endl;

    inner = Page_No - outer;
    int offset;
    int outer_idx;
    int inner_idx;
    int select_frame = 0;
    int simpler_outer = outer;
    int simpler_inner = inner;
    outer = pow(2, outer);
    inner = pow(2, inner);

    vector<vector<int>> Outer_And_Inner_Table(outer, vector<int>(inner + 1));
    vector<vector<bool>> visited(outer, vector<bool>(inner + 1));

    for (int i = 0; i < outer; i++)
    {
        for (int j = 0; j < inner + 1; j++)
        {
            visited[i][j] = false;
        }
    }

    int log_add;

    while (1)
    {

        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "Enter Logical Address : "
             << "\033[0m";
        cin >> log_add;
        if (log_add == -1)
        {
            system("cls");
            break;
        }
        int num_bits = log2(log_add) + 1;
        while (num_bits > Log_add_bits)
        {

            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "----Wrong Input-----" << endl
                 << "\033[0m";

            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "Enter Logical Address : "
                 << "\033[0m";
            cin >> log_add;
            num_bits = log2(log_add) + 1;
        }

        offset = log_add % offset_in_bits;
        log_add = log_add / pow(2, offset_in_bits);
        inner_idx = log_add % inner;
        outer_idx = log_add / inner;

        if (visited[outer_idx][inner_idx + 1] == true)
        {

            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m" << endl
                 << "Hit Page Table" << endl
                 << "\033[0m";
            Print_Page_Tables(Outer_And_Inner_Table, outer, inner, visited, outer_idx, inner_idx);
        }
        else
        {
            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m" << endl
                 << "Page Fault Occur" << endl
                 << endl
                 << "\033[0m";

            select_frame = rand() % 100;
            Outer_And_Inner_Table[outer_idx][inner_idx + 1] = select_frame;
            visited[outer_idx][0] = true;
            visited[outer_idx][inner_idx + 1] = true;
            Print_Page_Tables(Outer_And_Inner_Table, outer, inner, visited, outer_idx, inner_idx);
        }
    }
}

class Process
{
public:
    int id;
    int Arrival_Time;
    int Burst_Time;
    float Waiting_Time;
    float Feedback_Ratio;

public:
    Process()
    {
    }

    void Input_LJF(int num)
    {
        int arr;
        int burst;
        int r, g, b;
        for (int i = 0; i < num; i++)
        {
            this[i].id = i + 1;

            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "Enter Arrival Time for Process" << i << " : "
                 << "\033[0m";
            cin >> arr;
            this[i].Arrival_Time = arr;

            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "Enter Burst Time for Process" << i << " : "
                 << "\033[0m";
            cin >> burst;

            this[i].Burst_Time = burst;
            cout << endl;

            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "--------------------------------" << endl
                 << "\033[0m";
        }
    }

    void Print_LJF(int num)
    {
        int r, g, b;
        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "	Table	" << endl
             << endl
             << "\033[0m";

        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "      A.T    B.T" << endl
             << endl
             << "\033[0m";

        for (int i = 0; i < num; i++)
        {

            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "P" << this[i].id << "  |  " << this[i].Arrival_Time << "  |  " << this[i].Burst_Time << endl
                 << "\033[0m";

            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "____________________" << endl
                 << "\033[0m";
        }
    }

    void Print_LFRN(int num)
    {
        int r, g, b;
        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "	Table	" << endl
             << endl
             << "\033[0m";
        // cout << "	Table	" << endl << endl;
        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "      A.T    B.T   W.T   F.R" << endl
             << endl
             << "\033[0m";

        for (int i = 0; i < num; i++)
        {
            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "P" << this[i].id << "  |  " << this[i].Arrival_Time << "  |  " << this[i].Burst_Time << "  |  " << this[i].Waiting_Time << "  |  " << this[i].Feedback_Ratio << endl
                 << "\033[0m";
            // cout << "P" << this[i].id << "  |  " << this[i].Arrival_Time << "  |  " << this[i].Burst_Time << "  |  " << this[i].Waiting_Time << "  |  " << this[i].Feedback_Ratio << endl;

            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "__________________________" << endl
                 << "\033[0m";
        }
    }

    void bubbleSort(int n)
    {
        int i, j;
        for (i = 0; i < n - 1; i++)

            // Last i elements are already
            // in place
            for (j = 0; j < n - i - 1; j++)
                if (this[j].Arrival_Time > this[j + 1].Arrival_Time)
                    swap(this[j], this[j + 1]);
                else if (this[j].Arrival_Time == this[j + 1].Arrival_Time)
                {
                    if (this[j].Burst_Time < this[j + 1].Burst_Time)
                    {
                        swap(this[j], this[j + 1]);
                    }
                }
    }

    void LJF(int num)
    {
        this->bubbleSort(num);
        this->Print_LJF(num);
        bool *visited = visited = new bool[num];
        for (int i = 0; i < num; i++)
        {
            visited[i] = false;
        }

        int counter = 1;
        int selector = this[0].Arrival_Time + this[0].Burst_Time;
        visited[0] = true;
        int r, g, b;
        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
             << "Sequence  = P" << this[0].id << " , "
             << "\033[0m";

        int max = 0;
        int idx = 0;

        while (counter != num)
        {
            int i = 0;
            max = 0;
            while (this[i].Arrival_Time <= selector && i < num)
            {
                if (!visited[i])
                {

                    if (this[i].Burst_Time > max)
                    {
                        max = this[i].Burst_Time;
                        idx = i;
                    }
                }
                i++;
            }

            generateRandomColor(r, g, b);
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                 << "P" << this[idx].id << " , "
                 << "\033[0m";

            counter++;
            visited[idx] = true;
            selector += this[idx].Burst_Time;
        }

        cout << endl
             << endl;
    }

    void LFRN(int num)
    {
        this->bubbleSort(num);
        // this->Print_LFRN(num);
        bool *visited = visited = new bool[num];
        for (int i = 0; i < num; i++)
        {
            visited[i] = false;
        }

        int counter = 1;
        int selector = this[0].Arrival_Time + this[0].Burst_Time;
        visited[0] = true;
        this[0].Waiting_Time = 0;

        this[0].Feedback_Ratio = (this[0].Waiting_Time + this[0].Burst_Time) / this[0].Burst_Time;

        string s = "Sequence  = P" + to_string(this[0].id) + " , ";
        float min = 0;
        int idx = 0;
        int r, g, b;
        while (counter != num)
        {
            int i = 0;
            min = 9999;
            while (this[i].Arrival_Time <= selector && i < num)
            {

                if (!visited[i])
                {

                    this[i].Waiting_Time = selector - this[i].Arrival_Time;
                    this[i].Feedback_Ratio = (this[i].Waiting_Time + this[i].Burst_Time) / this[i].Burst_Time;

                    //	generateRandomColor(r, g, b);
                    //	cout << "\033[38;2;" << r << ";" << g << ";" << b << "m" << this[i].Waiting_Time << "---" << this[i].Arrival_Time << endl << "\033[0m";

                    if (this[i].Feedback_Ratio < min)
                    {
                        min = this[i].Feedback_Ratio;
                        idx = i;
                    }
                }
                i++;
            }

            s += "P" + to_string(this[idx].id) + " , ";
            counter++;
            visited[idx] = true;
            selector += this[idx].Burst_Time;
        }

        cout << endl
             << endl;
        this->Print_LFRN(num);
        cout << endl;
        generateRandomColor(r, g, b);
        cout << "\033[38;2;" << r << ";" << g << ";" << b << "m" << s << endl
             << "\033[0m";
    }
};

void Longest_Job_First()
{

    int a = 0;
    system("cls");
    int r, g, b;
    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "------------------Welcome to Longest Job First Algorithm------------------------" << endl
         << endl
         << "\033[0m";

    int num = 0;
    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Enter number of Process : "
         << "\033[0m";
    cin >> num;

    Process *P = new Process[num];

    P->Input_LJF(num);

    P->LJF(num);

    cout << endl;
    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Enter -1 for Clear : "
         << "\033[0m";
    cin >> a;

    if (a == -1)
    {
        system("cls");
    }
}

void Longest_Job_Feedback_Ratio()
{
    int a = 0;
    system("cls");
    int r, g, b;
    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "------------------Welcome to Longest Job Feedback Ratio ------------------------" << endl
         << endl
         << "\033[0m";

    int num = 0;
    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Enter number of Process : "
         << "\033[0m";
    cin >> num;

    Process *P = new Process[num];

    P->Input_LJF(num);

    P->LFRN(num);

    cout << endl;
    generateRandomColor(r, g, b);
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
         << "Enter -1 for Clear : "
         << "\033[0m";
    cin >> a;

    if (a == -1)
    {
        system("cls");
    }
}
class Process_MLQ
{
public:
    int id;
    int Arr_Time;
    int Bur_Time;
    int priority;
    int wait_Time;
    Process_MLQ()
    {
        Arr_Time = -1;
        Bur_Time = -1;
        id = -1;
        wait_Time = -1;
        priority = -1;
    }
    void bubbleSort(vector<Process_MLQ> &P, vector<bool> &visited)
    {
        int i, j;
        for (i = 0; i < P.size() - 1; i++)

            for (j = 0; j < P.size() - i - 1; j++)
                if (P[j].Arr_Time > P[j + 1].Arr_Time)
                {
                    swap(P[j], P[j + 1]);
                    swap(visited[j], visited[j + 1]);
                }
                else if (P[j].Arr_Time == P[j + 1].Arr_Time)
                {
                    if (P[j].Bur_Time < P[j + 1].Bur_Time)
                    {
                        swap(P[j], P[j + 1]);
                        swap(visited[j], visited[j + 1]);
                    }
                }
    }
    void bubbleSort(vector<Process_MLQ> &P, bool visited[])
    {
        int i, j;
        for (i = 0; i < P.size() - 1; i++)

            for (j = 0; j < P.size() - i - 1; j++)
                if (P[j].Arr_Time > P[j + 1].Arr_Time)
                {
                    swap(P[j], P[j + 1]);
                    swap(visited[j], visited[j + 1]);
                }
                else if (P[j].Arr_Time == P[j + 1].Arr_Time)
                {
                    if (P[j].Bur_Time < P[j + 1].Bur_Time)
                    {
                        swap(P[j], P[j + 1]);
                        swap(visited[j], visited[j + 1]);
                    }
                }
    }

    void BubbleSort(int n)
    {
        int i, j;
        for (i = 0; i < n - 1; i++)

            // Last i elements are already
            // in place
            for (j = 0; j < n - i - 1; j++)
                if (this[j].Arr_Time > this[j + 1].Arr_Time)
                    swap(this[j], this[j + 1]);
                else if (this[j].Arr_Time == this[j + 1].Arr_Time)
                {
                    if (this[j].Bur_Time < this[j + 1].Bur_Time)
                    {
                        swap(this[j], this[j + 1]);
                    }
                }
    }

    bool Check_All_Processes_are_Executed(bool visited[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            if (visited[i] == false)
            {
                return false;
            }
        }
        return true;
    }
    bool Check_All_Processes_are_Executed(vector<bool> visited)
    {
        for (int i = 0; i < visited.size(); i++)
        {
            if (visited[i] == false)
            {
                return false;
            }
        }
        return true;
    }

    void Run_Priority_Queue(int num, vector<Process_MLQ> &P, bool visited[], int size, int &cum_time, int &t)
    {
        if (P.size() > 0)
        {

            bubbleSort(P, visited);

            int pr = 0;
            int idx = 0;
            while (Check_All_Processes_are_Executed(visited, size) == false)
            {
                pr = 999;
                idx = 0;
                if (Check_Cumulative_Time(P, cum_time, visited) == false)
                {
                    return;
                }
                else
                {
                    for (int i = 0; i < P.size(); i++)
                    {
                        if ((P[i].Arr_Time <= cum_time) && (P[i].priority < pr) && (visited[i] == false))
                        {
                            pr = P[i].priority;
                            idx = i;
                            t = 1;
                        }
                    }
                }
                cout << "P" << P[idx].id << " , ";
                cum_time += P[idx].Bur_Time;
                visited[idx] = true;
            }
        }
    }

    bool Check_Cumulative_Time(vector<Process_MLQ> &v, int &cum_time, bool visited[])
    {
        bool flag = false;
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].Arr_Time <= cum_time && visited[i] == false)
            {

                return true;
            }
        }
        return false;
    }
    bool Check_Cumulative_Time(vector<Process_MLQ> &v, int &cum_time, vector<bool> &visited)
    {
        bool flag = false;
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].Arr_Time <= cum_time && visited[i] == false)
            {

                return true;
            }
        }
        return false;
    }
    void Run_SRJ(int num, vector<Process_MLQ> &SRJ, bool visited[], int size, vector<Process_MLQ> &P, bool P_visited[], vector<Process_MLQ> &RR, bool RR_visited[], int &cum_time, int &t)
    {
        if (SRJ.size() > 0)
        {

            bubbleSort(SRJ, visited);

            if (Check_Cumulative_Time(SRJ, cum_time, visited) == false)
            {
                return;
            }

            int pr = 0;
            int idx = 0;
            bool flag = false;
            int small_b_time = 0;

            while (Check_All_Processes_are_Executed(visited, size) == false)
            {

                idx = 0;
                small_b_time = 999;
                flag = false;
                for (int i = 0; i < SRJ.size(); i++)
                {
                    if ((SRJ[i].Arr_Time <= cum_time) && (visited[i] == false) && (SRJ[i].Bur_Time < small_b_time))
                    {
                        small_b_time = SRJ[i].Bur_Time;
                        idx = i;
                        flag = true;
                        t = 1;
                    }
                }

                if (flag == false)
                {
                    if (Check_Cumulative_Time(SRJ, cum_time, visited) == false)
                    {
                        return;
                    }
                }
                else
                {
                    cum_time += 1;
                    SRJ[idx].Bur_Time = SRJ[idx].Bur_Time - 1;
                    if (SRJ[idx].Bur_Time <= 0)
                    {
                        visited[idx] = true;
                        cout << "P" << SRJ[idx].id << " , ";
                    }
                    if (Check_Cumulative_Time(P, cum_time, P_visited) == true || Check_Cumulative_Time(RR, cum_time, RR_visited) == true)
                    {
                        return;
                    }
                }
            }
        }
    }

    bool Run_Round_Robin(int num, vector<Process_MLQ> &RR, int time_slice, vector<Process_MLQ> P, bool visited[], int size, int &cum_time, bool valid[], queue<int> &Ready_queue, bool P_visited[], int &t)
    {
        if (RR.size() > 0)
        {

            bubbleSort(RR, visited);
            // cout << "Sequence  = P" << RR[0].id << " , ";

            if (Check_Cumulative_Time(RR, cum_time, visited) == false)
            {
                return false;
            }

            for (int i = 0; i < RR.size(); i++)
            {
                if ((RR[i].Arr_Time <= cum_time) && (valid[i] == false) && (visited[i] == false))
                {
                    Ready_queue.push(i);
                    valid[i] = true;
                    t = 1;
                }
            }

            int mem = 0;
            int front = 0;
            int slice = 0;
            //     cout << "Order = ";
            while (!Ready_queue.empty())
            {
                t = 1;
                front = Ready_queue.front();
                Ready_queue.pop();
                valid[front] = false;
                slice = 0;
                while (slice != time_slice)
                {

                    cum_time += 1;
                    RR[front].Bur_Time = RR[front].Bur_Time - 1;

                    if (Check_Cumulative_Time(P, cum_time, P_visited) == true)
                    {
                        if (RR[front].Bur_Time > 0)
                        {
                            Ready_queue.push(front);
                            valid[front] = true;
                        }
                        else
                        {
                            visited[front] = true;
                            cout << "P" << RR[front].id << " , ";
                        }
                        return true;
                    }
                    if (RR[front].Bur_Time <= 0)
                    {
                        break;
                    }
                    slice++;
                }

                for (int i = 0; i < RR.size(); i++)
                {
                    if (i == front)
                    {
                    }
                    else if ((RR[i].Arr_Time <= cum_time) && (valid[i] == false) && (visited[i] == false))
                    {
                        Ready_queue.push(i);
                        valid[i] = true;
                        t = 1;
                    }
                }

                if (RR[front].Bur_Time > 0)
                {
                    Ready_queue.push(front);
                    valid[front] = true;
                }
                else
                {
                    visited[front] = true;
                    cout << "P" << RR[front].id << " , ";
                }

                if (Check_Cumulative_Time(RR, cum_time, visited) == false)
                {
                    return false;
                }
            }
        }

        return false;
    }

    bool Run_Round_Robin_MLFQ(int num, vector<Process_MLQ> &FCFS, vector<bool> &FCFS_visited, vector<Process_MLQ> &SJF, vector<bool> &SJF_visited, vector<Process_MLQ> &RR, vector<bool> &RR_visited, int &promotion, int &demotion, int &cum_time, int &t, bool &flag, queue<int> &Ready_queue, vector<bool> &valid, string &s)
    {
        if (RR.size() > 0)
        {
            if (flag == false)
            {
                bubbleSort(RR, RR_visited);
                flag = true;
            }

            // cout << "Sequence  = P" << RR[0].id << " , ";

            if (Check_Cumulative_Time(RR, cum_time, RR_visited) == false)
            {
                return false;
            }

            for (int i = 0; i < RR.size(); i++)
            {
                if ((RR[i].Arr_Time <= cum_time) && (valid[i] == false) && (RR_visited[i] == false))
                {
                    Ready_queue.push(i);
                    valid[i] = true;
                    t = 1;
                }
            }

            int mem = 0;
            int front = 0;
            int slice = 0;
            //     cout << "Order = ";
            while (!Ready_queue.empty())
            {
                t = 1;
                front = Ready_queue.front();
                while (RR_visited[Ready_queue.front()] == true)
                {
                    Ready_queue.pop();
                }
                Ready_queue.pop();
                valid[front] = false;
                slice = 0;
                while (slice != demotion)
                {

                    cum_time += 1;
                    RR[front].Bur_Time = RR[front].Bur_Time - 1;

                    if ((Check_Cumulative_Time(FCFS, cum_time, FCFS_visited) == true) || (Check_Cumulative_Time(SJF, cum_time, SJF_visited) == true))
                    {
                        if (RR[front].Bur_Time > 0)
                        {
                            Ready_queue.push(front);
                            valid[front] = true;
                        }
                        else
                        {
                            RR_visited[front] = true;
                            s += "P";
                            s += to_string(RR[front].id);
                            s += " , ";
                        }
                        int value = 1;
                        Aging(SJF, RR, SJF_visited, RR_visited, value);
                        if (Promotion(SJF, RR, SJF_visited, RR_visited, promotion, demotion, FCFS, FCFS_visited) == true)
                        {
                            cout << "-------------------" << endl;
                            Print_After_Promotion(FCFS, FCFS_visited, SJF, SJF_visited, RR, RR_visited);
                            cout << "-------------------" << endl;
                            return true;
                        }
                        cout << "-------------------" << endl;
                        Print_After_Promotion(FCFS, FCFS_visited, SJF, SJF_visited, RR, RR_visited);
                        cout << "-------------------" << endl;

                        return true;
                    }
                    if (RR[front].Bur_Time <= 0)
                    {
                        break;
                    }
                    slice++;
                }

                for (int i = 0; i < RR.size(); i++)
                {
                    if (i == front)
                    {
                    }
                    else if ((RR[i].Arr_Time <= cum_time) && (valid[i] == false) && (RR_visited[i] == false))
                    {
                        Ready_queue.push(i);
                        valid[i] = true;
                        t = 1;
                    }
                }

                if (RR[front].Bur_Time > 0)
                {
                    Ready_queue.push(front);
                    valid[front] = true;
                }
                else
                {
                    RR_visited[front] = true;
                    cout << "P" << RR[front].id << " , ";
                }

                if ((Check_Cumulative_Time(FCFS, cum_time, FCFS_visited) == true) || (Check_Cumulative_Time(SJF, cum_time, SJF_visited) == true))
                {
                    return true;
                }
                if (Check_Cumulative_Time(RR, cum_time, RR_visited) == false)
                {
                    return false;
                }
            }
        }

        return false;
    }
    void Print_Q(vector<Process_MLQ> P)
    {
        cout << "	Table	" << endl
             << endl;
        cout << "      Pr    A.T    B.T" << endl
             << endl;

        for (int i = 0; i < P.size(); i++)
        {

            cout << "P" << P[i].id << "  |  " << P[i].priority << "  |  " << P[i].Arr_Time << "  |  " << P[i].Bur_Time << endl;
            cout << "____________________" << endl;
        }
    }

    void Print_Q(int num_of_process)
    {
        cout << "	Table	" << endl
             << endl;
        cout << "      Pr    A.T    B.T" << endl
             << endl;

        for (int i = 0; i < num_of_process; i++)
        {

            cout << "P" << this[i].id << "  |  " << this[i].priority << "  |  " << this[i].Arr_Time << "  |  " << this[i].Bur_Time << endl;
            cout << "____________________" << endl;
        }
    }
    void Print_After_Promotion(vector<Process_MLQ> &FCFS, vector<bool> &FCFS_visited, vector<Process_MLQ> &SJF, vector<bool> &SJF_visited, vector<Process_MLQ> &RR, vector<bool> &RR_visited)
    {
        cout << "Q1 : ";
        for (int i = 0; i < FCFS.size(); i++)
        {
            if (FCFS_visited[i] == false)
            {
                cout << "P" << FCFS[i].id << " ,  ";
            }
        }
        cout << endl;

        cout << "Q2 : ";
        for (int i = 0; i < SJF.size(); i++)
        {
            if (SJF_visited[i] == false)
            {
                cout << "P" << SJF[i].id << " ,  ";
            }
        }
        cout << endl;

        cout << "Q3 : ";
        for (int i = 0; i < RR.size(); i++)
        {
            if (RR_visited[i] == false)
            {
                cout << "P" << RR[i].id << " ,  ";
            }
        }
        cout << endl;
    }

    void Perform_MLQ(int num, vector<Process_MLQ> &P, vector<Process_MLQ> &RR, vector<Process_MLQ> &SRJ, int time_slice)
    {
        int size1 = P.size();
        bool *P_visited = new bool[size1];
        for (int i = 0; i < size1; i++)
        {
            P_visited[i] = false;
        }

        int size2 = RR.size();
        bool *RR_visited = new bool[size2];
        bool *valid = new bool[size2];
        for (int i = 0; i < size2; i++)
        {
            RR_visited[i] = false;
            valid[i] = false;
        }

        int size3 = SRJ.size();
        bool *SRJ_visited = new bool[size3];
        for (int i = 0; i < size3; i++)
        {
            SRJ_visited[i] = false;
        }
        int cum_time = 0;
        int t = -1;
        queue<int> Ready_queue;
        cout << "Priority Queue : " << endl;
        Print_Q(P);

        cout << "Round Robin Queue : " << endl;
        Print_Q(RR);

        cout << "Shortest Job Queue : " << endl;
        Print_Q(P);

        cout << endl
             << "<";
        while ((Check_All_Processes_are_Executed(P_visited, size1) == false) || (Check_All_Processes_are_Executed(RR_visited, size1) == false) || (Check_All_Processes_are_Executed(SRJ_visited, size1) == false))
        {
            t = -1;
            Run_Priority_Queue(num, P, P_visited, size1, cum_time, t);
            if (Run_Round_Robin(num, RR, time_slice, P, RR_visited, size2, cum_time, valid, Ready_queue, P_visited, t) == false)
            {
                Run_SRJ(num, SRJ, SRJ_visited, size3, P, P_visited, RR, RR_visited, cum_time, t);
            }

            if (t == -1)
            {
                cum_time++;
            }
        }
        cout << ">" << endl
             << endl;
    }

    void Input_Process(int num, vector<Process_MLQ> &P, vector<Process_MLQ> &RR, vector<Process_MLQ> &SRJ, int &time_slice)
    {
        int arr;
        int burst;
        int pr;

        bool flag = false;
        for (int i = 0; i < num; i++)
        {

            this[i].id = i + 1;
            cout << "Priority 1--5 (Highest)" << endl;
            cout << "Priority 6--10 (Medium)" << endl;
            cout << "Priority 11--15 (Lowest)" << endl;
            cout << "Enter Priority of Prcess" << i + 1 << " : ";
            cin >> pr;
            this[i].priority = pr;
            if ((pr >= 6 && pr <= 10) && flag == false)
            {
                cout << "Enter Time Slice for Round Robin : ";
                cin >> time_slice;
                flag = true;
            }

            cout << "Enter Arrival Time for Process" << i + 1 << " : ";
            cin >> arr;
            this[i].Arr_Time = arr;

            cout << "Enter Burst Time for Process" << i + 1 << " : ";
            cin >> burst;
            this[i].Bur_Time = burst;
            cout << endl;
            cout << "--------------------------------" << endl
                 << endl;

            if (pr >= 1 && pr <= 5)
            {
                P.push_back(this[i]);
            }
            else if (pr >= 6 && pr <= 10)
            {
                RR.push_back(this[i]);
            }
            else
            {
                SRJ.push_back(this[i]);
            }
        }
    }
    void Aging(vector<Process_MLQ> &SJF, vector<Process_MLQ> &RR, vector<bool> &SJF_visited, vector<bool> &RR_visited, int value)
    {
        for (int i = 0; i < SJF.size(); i++)
        {
            if (SJF_visited[i] == false)
                SJF[i].wait_Time += value;
        }

        for (int i = 0; i < RR.size(); i++)
        {
            if (RR_visited[i] == false)
                RR[i].wait_Time += value;
        }
    }
    bool Promotion(vector<Process_MLQ> &SJF, vector<Process_MLQ> &RR, vector<bool> &SJF_visited, vector<bool> &RR_visited, int &promotion, int &demotion, vector<Process_MLQ> &FCFS, vector<bool> &FCFS_visited)
    {
        bool flag = false;
        for (int i = 0; i < SJF.size(); i++)
        {
            if (SJF[i].wait_Time >= promotion && SJF_visited[i] == false)
            {
                SJF[i].wait_Time = 0;
                // SJF[i].Arr_Time = 0;
                FCFS.push_back(SJF[i]);
                FCFS_visited.push_back(false);

                SJF_visited[i] = true;
                flag = true;
            }
        }

        for (int i = 0; i < RR.size(); i++)
        {
            if (RR[i].wait_Time >= promotion && RR_visited[i] == false)
            {
                RR[i].wait_Time = 0;
                //  RR[i].Arr_Time = 0;
                SJF.push_back(RR[i]);
                SJF_visited.push_back(false);
                RR_visited[i] = true;
                flag = true;
            }
        }

        return flag;
    }
    void Print_visited(vector<bool> visisted)
    {
        cout << endl;
        for (int i = 0; i < visisted.size(); i++)
        {
            if (visisted[i] == false)
            {
                cout << "F ";
            }
            else
            {
                cout << "T ";
            }
        }
        cout << endl
             << endl;
    }
    bool Run_FCFS(int num, vector<Process_MLQ> &FCFS, vector<bool> &FCFS_visited, vector<Process_MLQ> &SJF, vector<bool> &SJF_visited, vector<Process_MLQ> &RR, vector<bool> &RR_visited, int &promotion, int &demotion, int &cum_time, int &t, bool &flag, string &s)
    {
        bool flag1 = false;
        if (FCFS.size() > 0)
        {
            if (flag == false)
            {
                bubbleSort(FCFS, FCFS_visited);
                flag = true;
            }

            if (Check_Cumulative_Time(FCFS, cum_time, FCFS_visited) == false)
            {
                return false;
            }
            else
            {
                for (int i = 0; i < FCFS.size(); i++)
                {
                    t = 1;
                    if ((FCFS[i].Arr_Time <= cum_time) && (FCFS_visited[i] == false))
                    {
                        FCFS[i].Bur_Time = FCFS[i].Bur_Time - demotion;
                        cum_time += demotion;
                        int value = demotion;

                        if (FCFS[i].Bur_Time > 0)
                        {
                            ///////// demotion
                            FCFS[i].wait_Time = -1;
                            // FCFS[i].Arr_Time = 0;
                            FCFS_visited[i] = true;
                            //  Print_visited(FCFS_visited);
                            SJF.push_back(FCFS[i]);
                            SJF_visited.push_back(false);
                        }
                        else if (FCFS[i].Bur_Time <= 0)
                        {
                            s += "P";
                            s += to_string(FCFS[i].id);
                            s += " , ";

                            FCFS_visited[i] = true;
                            cout << "-------------------" << endl;
                            Print_visited(FCFS_visited);
                            cout << "-------------------" << endl;
                        }

                        Aging(SJF, RR, SJF_visited, RR_visited, value);
                        if (Promotion(SJF, RR, SJF_visited, RR_visited, promotion, demotion, FCFS, FCFS_visited) == true)
                        {
                        }
                        cout << "-------------------" << endl;
                        Print_After_Promotion(FCFS, FCFS_visited, SJF, SJF_visited, RR, RR_visited);
                        cout << "-------------------" << endl;
                    }
                }
            }
        }
        return false;
    }

    bool Run_SJF(int num, vector<Process_MLQ> &FCFS, vector<bool> &FCFS_visited, vector<Process_MLQ> &SJF, vector<bool> &SJF_visited, vector<Process_MLQ> &RR, vector<bool> &RR_visited, int &promotion, int &demotion, int &cum_time, int &t, bool &flag, vector<bool> &valid, string &s)
    {
        if (SJF.size() > 0)
        {
            if (flag == false)
            {
                bubbleSort(SJF, SJF_visited);
                flag = true;
            }

            if (Check_Cumulative_Time(SJF, cum_time, SJF_visited) == false)
            {
                return false;
            }

            int pr = 0;
            int idx = 0;
            bool flag2 = false;
            int small_b_time = 0;

            while (Check_All_Processes_are_Executed(SJF_visited) == false)
            {

                idx = 0;
                small_b_time = 999;
                flag2 = false;
                for (int i = 0; i < SJF.size(); i++)
                {
                    if ((SJF[i].Arr_Time <= cum_time) && (SJF_visited[i] == false) && (SJF[i].Bur_Time < small_b_time))
                    {
                        t = 1;
                        small_b_time = SJF[i].Bur_Time;
                        idx = i;
                        flag2 = true;
                        t = 1;
                    }
                }

                if (flag2 == false)
                {
                    if (Check_Cumulative_Time(FCFS, cum_time, FCFS_visited) == true)
                    {
                        return true;
                    }

                    if (Check_Cumulative_Time(SJF, cum_time, SJF_visited) == false)
                    {
                        return false;
                    }
                }
                else
                {
                    cum_time += demotion;
                    int value = demotion;
                    SJF[idx].Bur_Time = SJF[idx].Bur_Time - demotion;

                    if (SJF[idx].Bur_Time <= 0)
                    {
                        SJF_visited[idx] = true;
                        s += "P";
                        s += to_string(SJF[idx].id);
                        s += " , ";
                    }
                    else
                    {
                        SJF[idx].wait_Time = -1;
                        SJF_visited[idx] = true;
                        RR.push_back(SJF[idx]);
                        RR_visited.push_back(false);
                        valid.push_back(false);
                    }
                    Aging(SJF, RR, SJF_visited, RR_visited, value);
                    if (Promotion(SJF, RR, SJF_visited, RR_visited, promotion, demotion, FCFS, FCFS_visited) == true)
                    {
                        cout << "-------------------" << endl;
                        Print_After_Promotion(FCFS, FCFS_visited, SJF, SJF_visited, RR, RR_visited);
                        cout << "------------------" << endl;
                        return true;
                    }
                    cout << "-------------------" << endl;
                    Print_After_Promotion(FCFS, FCFS_visited, SJF, SJF_visited, RR, RR_visited);
                    cout << "-------------------" << endl;
                    if (Check_Cumulative_Time(FCFS, cum_time, FCFS_visited) == true)
                    {
                        return true;
                    }
                }
            }
        }
    }
    void Perform_MLFQ(int num, vector<Process_MLQ> &FCFS, vector<Process_MLQ> &SJF, vector<Process_MLQ> &RR, int &promotion, int &demotion)
    {
        vector<bool> FCFS_visited;
        vector<bool> SJF_visited;
        vector<bool> RR_visited;
        vector<bool> valid;
        bool flag1 = false;
        bool flag2 = false;
        bool flag3 = false;
        for (int i = 0; i < FCFS.size(); i++)
        {

            FCFS_visited.push_back(false);
        }

        queue<int> Ready_queue;
        int t = -1;
        string s = "<";
        int cum_time = 0;
        while ((Check_All_Processes_are_Executed(FCFS_visited) == false) || (Check_All_Processes_are_Executed(SJF_visited) == false) || (Check_All_Processes_are_Executed(RR_visited) == false))
        {
            t = -1;
            if (Run_FCFS(num, FCFS, FCFS_visited, SJF, SJF_visited, RR, RR_visited, promotion, demotion, cum_time, t, flag1, s) == false)
            {
                if (Run_SJF(num, FCFS, FCFS_visited, SJF, SJF_visited, RR, RR_visited, promotion, demotion, cum_time, t, flag2, valid, s) == false)
                {
                    Run_Round_Robin_MLFQ(num, FCFS, FCFS_visited, SJF, SJF_visited, RR, RR_visited, promotion, demotion, cum_time, t, flag3, Ready_queue, valid, s);
                }
            }

            if (t == -1)
            {
                cum_time++;
            }
        }
        s += ">";
        cout << endl;
        cout << s << endl;
    }

    void Input_For_Feedback_Queue(int num, vector<Process_MLQ> &FCFS, int &pro, int &demo)
    {
        int arr;
        int burst;
        int pr;
        bool flag = false;

        for (int i = 0; i < num; i++)
        {
            this[i].id = i + 1;
            cout << "Enter Arrival Time for Process" << i + 1 << " : ";
            cin >> arr;
            this[i].Arr_Time = arr;

            cout << "Enter Burst Time for Process" << i + 1 << " : ";
            cin >> burst;
            this[i].Bur_Time = burst;
            cout << endl;
            cout << "--------------------------------" << endl
                 << endl;

            FCFS.push_back(this[i]);
        }

        cout << "Enter promotion time : ";
        cin >> pro;

        cout << "Enter demotion time : ";
        cin >> demo;
        cout << endl;
        cout << "--------------------------------" << endl
             << endl;
    }
};
void multi_level_queue()
{
    int num;
    cout << "Enter Number of Processes : ";
    cin >> num;
    // for multilevel
    vector<Process_MLQ> Priority;
    vector<Process_MLQ> RR;
    vector<Process_MLQ> SJRT;

    // for feedback
    vector<Process_MLQ> FCFS;
    vector<Process_MLQ> SJF;

    int promotion_time;
    int demotion_time;

    int time_slice;

    Process_MLQ *P = new Process_MLQ[num];
    P->Input_Process(num, Priority, RR, SJRT, time_slice);
    P->BubbleSort(num);
    P->Print_Q(num);
    P->Perform_MLQ(num, Priority, RR, SJRT, time_slice);
}
void feedback_queue()
{
    int num;
    cout << "Enter Number of Processes : ";
    cin >> num;
    // for multilevel
    vector<Process_MLQ> Priority;
    vector<Process_MLQ> RR;
    vector<Process_MLQ> SJRT;

    // for feedback
    vector<Process_MLQ> FCFS;
    vector<Process_MLQ> SJF;

    int promotion_time;
    int demotion_time;

    int time_slice;
    Process_MLQ *P = new Process_MLQ[num];
    P->Input_For_Feedback_Queue(num, FCFS, promotion_time, demotion_time);
    P->Perform_MLFQ(num, FCFS, SJF, RR, promotion_time, demotion_time);
}
int main()
{
    srand(time(NULL));
    int r, g, b;
    // Get the desktop's current video mode for fullscreen
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();

    // Create the window
    sf::RenderWindow window(fullscreenMode, "My Game", sf::Style::Fullscreen);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("download.jpg"))
    {
        return 1;
    }
    sf::Sprite background(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, fullscreenMode.width, fullscreenMode.height));

    // Adjust the scale of the background sprite to fit the window size
    float scaleX = static_cast<float>(fullscreenMode.width) / static_cast<float>(backgroundTexture.getSize().x);
    float scaleY = static_cast<float>(fullscreenMode.height) / static_cast<float>(backgroundTexture.getSize().y);
    background.setScale(scaleX, scaleY);

    // Set the window's icon
    sf::Image icon;
    if (icon.loadFromFile("icon.png"))
    {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    // Load a font
    sf::Font font;
    if (!font.loadFromFile("MorganChalk-L3aJy.ttf"))
    {
        return 1;
    }

    // Create a sprite
    sf::Texture texture;
    if (!texture.loadFromFile("image.png"))
    {
        return 1;
    }
    sf::Sprite sprite(texture);
    sf::FloatRect spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin(spriteBounds.width / 2.f, spriteBounds.height / 2.f);
    sprite.setPosition(fullscreenMode.width / 2.f, fullscreenMode.height / 2.f - 180);

    ///////////image 2
    sf::Texture texture2;
    if (!texture2.loadFromFile("image2.png"))
    {
        return 1;
    }
    sf::Sprite sprite2(texture2);
    sf::FloatRect spriteBounds2 = sprite2.getLocalBounds();
    sprite2.setOrigin(spriteBounds2.width / 2.f, spriteBounds2.height / 2.f);
    sprite2.setPosition(fullscreenMode.width / 2.f, fullscreenMode.height / 2.f + 165);

    // Create a menu
    sf::Text menuText("CPU SCHEDULING", font, 32);
    menuText.setFillColor(sf::Color::Black);
    menuText.setPosition(fullscreenMode.width / 2.f - menuText.getLocalBounds().width / 2.f, fullscreenMode.height / 2.f - 320);

    // Create menu options
    sf::Text option1Text("SEMAPHORES", font, 32);
    option1Text.setFillColor(sf::Color::Black);
    option1Text.setPosition(fullscreenMode.width / 2.f - option1Text.getLocalBounds().width / 2.f, fullscreenMode.height / 2.f - 200);

    sf::Text option2Text("DEADLOCK", font, 32);
    option2Text.setFillColor(sf::Color::Black);
    option2Text.setPosition(fullscreenMode.width / 2.f - option2Text.getLocalBounds().width / 2.f, fullscreenMode.height / 2.f - 78);

    sf::Text option3Text("MEM MANAGMENT", font, 32);
    option3Text.setFillColor(sf::Color::Black);
    option3Text.setPosition(fullscreenMode.width / 2.f - option3Text.getLocalBounds().width / 2.f, fullscreenMode.height / 2.f + 25);

    sf::Text option4Text("REPLACEMENT", font, 32);
    option4Text.setFillColor(sf::Color::Black);
    option4Text.setPosition(fullscreenMode.width / 2.f - option4Text.getLocalBounds().width / 2.f, fullscreenMode.height / 2.f + 148);

    sf::Text exitText("EXIT", font, 34);
    exitText.setFillColor(sf::Color::Black);
    exitText.setPosition(fullscreenMode.width / 2.f - exitText.getLocalBounds().width / 2.f, fullscreenMode.height / 2.f + 265);

    // Create a view that covers the entire screen
    sf::View view(sf::FloatRect(0.f, 0.f, static_cast<float>(fullscreenMode.width), static_cast<float>(fullscreenMode.height)));
    window.setView(view);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (menuText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    window.close();
                    int inp;
                    system("cls");

                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "1)Longest Job First  " << endl
                         << "\033[0m";

                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "2)Longest Job Feedback Ratio  " << endl
                         << "\033[0m";
                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "3)MultiLevel Queue " << endl
                         << "\033[0m";
                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "3)MultiLevel FeedBack Queue " << endl
                         << "\033[0m";
                    cin >> inp;

                    if (inp == 1)
                    {
                        Longest_Job_First();
                    }

                    else if (inp == 2)
                    {
                        Longest_Job_Feedback_Ratio();
                    }
                    else if (inp == 3)
                    {
                        multi_level_queue();
                    }
                    else if (inp == 4)
                    {
                        feedback_queue();
                    }
                }
                if (option1Text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    window.close();
                }
                if (option2Text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    window.close();
                    system("cls");
                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "Banker Algorithm" << endl
                         << "\033[0m";
                    Banker_Algorithm();
                    int i;
                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "Enter -1 to exit:" << endl
                         << "\033[0m";
                    cin >> i;
                }
                if (option3Text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    window.close();
                    system("cls");
                    int inp;

                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "1)Hashed Table with TLB  " << endl
                         << "\033[0m";

                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "2)Two Level Paging  " << endl
                         << "\033[0m";

                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "Your Choice : "
                         << "\033[0m";

                    cin >> inp;

                    if (inp == 1)
                    {
                        Hashed_Table_With_TLB();
                    }

                    if (inp == 2)
                    {
                        Two_Level_Paging();
                    }
                    int j;
                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "Enter -1 to exit : "
                         << "\033[0m";
                    cin >> j;
                }
                else if (option4Text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    window.close();
                    system("cls");
                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << " Second Chance Algorithm" << endl
                         << "\033[0m";
                    Second_Chance_Algorithm();
                    int k;
                    generateRandomColor(r, g, b);
                    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                         << "Enter -1 to exit : "
                         << "\033[0m";
                    cin >> k;
                }
                else if (exitText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    window.close();
                }
            }
            if (!window.isOpen() && !exitText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            {
                window.create(fullscreenMode, "My Game", sf::Style::Fullscreen);
            }
        }
        sf::Color customColor(255, 128, 0); // orange color
        // Clear the screen
        window.clear(customColor);
        window.draw(background);
        // Draw the graphics
        window.draw(sprite);
        window.draw(sprite2);

        // Draw the menu
        window.draw(menuText);
        window.draw(option1Text);
        window.draw(option2Text);
        window.draw(option3Text);
        window.draw(option4Text);
        window.draw(exitText);

        // Display the window
        window.display();
    }

    return 0;
}

///////////Semaphores/////////////
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

#define N 5

sem_t chopsticks[N];
sem_t room;

void *philosopher(void *arg)
{
    int id = *((int *)arg);

    sem_wait(&room);
    if (id == N - 1)
    {

        sem_wait(&chopsticks[0]);
        cout << "Philosopher " << id << " is picking up Right ChopStick" << endl;

        sem_wait(&chopsticks[id]);
        cout << "Philosopher " << id << " is picking up Left ChopStick" << endl;
    }
    else
    {

        sem_wait(&chopsticks[id]);
        cout << "Philosopher " << id << " is picking up Left ChopStick" << endl;

        sem_wait(&chopsticks[(id + 1) % N]);
        cout << "Philosopher " << id << " is picking up Right ChopStick" << endl;
    }
    sem_post(&room);

    cout << "Philosopher " << id << " is eating." << endl;

    sem_post(&chopsticks[id]);
    cout << "Philosopher " << id << " is putting down Left ChopStick" << endl;

    sem_post(&chopsticks[(id + 1) % N]);
    cout << "Philosopher " << id << " is putting down Right ChopStick" << endl;

    return NULL;
}

int main()
{
    pthread_t philosophers[N];
    int ids[N];

    sem_init(&room, 0, 1);
    for (int i = 0; i < N; i++)
    {
        sem_init(&chopsticks[i], 0, 1);
    }

    for (int i = 0; i < N; i++)
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    sem_destroy(&room);
    for (int i = 0; i < N; i++)
    {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}

// g++ -g -pthread diningprob.cpp -o out
//.\out.exe