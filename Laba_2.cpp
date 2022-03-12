#include <iostream>
#include "priority_queue.h"

using namespace std;

void Menu() {
    cout << "1 - Count of elements in the queue & with priority" << endl;
    cout << "2 - Is the queue empty" << endl;
    cout << "3 - Input an element" << endl;
    cout << "4 - Delete the element from the queue" << endl;
    cout << "5 - The head element & his priority" << endl;
    cout << "6 - Print all elements of queue" << endl;
    cout << "0 - Exit" << endl;
}

int main() {
    PriorityQueue queue;
    Menu();
    int operation;
    while (true) {
        cin >> operation;
        if (cin.fail()) {
            cin.clear();
            cout << "Error : number is not integer" << endl;
            return 0;
        }
        switch (operation) {
        case 0: {
            return 0;
        }
        case 1: {
            cout << "Count of all elements: " << queue.Size() << '\n';
            cout << "High priority count: " << queue.GetSizeHigh() << '\n';
            cout << "Medium priority count: " << queue.GetSizeHigh() << '\n';
            cout << "Low priority count: " << queue.GetSizeHigh() << '\n';
            break;
        }
        case 2: {
            if (queue.IsEmpty()) {
                cout << "Queue is empty\n";
            }
            else {
                cout << "Queue is not empty\n";
            }
            break;
        }
        case 3: {
            cout << "Enter two integers:" <<
                " a value and a priority(Low = 0, Medium = 1, High = 2)";
            int value;
            int priority;
            cin >> value;
            cin >> priority;
            if (priority == 0) {
                queue.Push(value, Priority::Low);
            }
            else if (priority == 1) {
                queue.Push(value, Priority::Medium);
            }
            else if (priority == 2) {
                queue.Push(value, Priority::High);
            }
            else {
                cout << "Such priority doesn't exist\n";
            }
            break;
        }
        case 4: {
            queue.Pop();
            break;
        }
        case 5: {
            cout << "Head value: " << queue.GetFrontValue() << '\n';
            cout << "Head priority: " << queue.GetFrontPriority() << '\n';
            break;
        }
        case 6: {
            cout << queue;
            break;
        }
        default: {
            cout << "There is no such operation\n";
        }
        }
        cout << "\n";
    }

    return 0;
}

