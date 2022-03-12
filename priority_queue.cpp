#include "priority_queue.h"

PriorityQueue::PriorityQueue(const PriorityQueue& other) {
    Clone(other);
}

PriorityQueue::PriorityQueue(PriorityQueue&& other) {
    Move(other);
}

void PriorityQueue::Clone(const PriorityQueue& other) {
    Node* ind = other.head;
    for (int i = 0; i < other.Size(); ++i) {
        Push(ind->value, ind->prior);
        ind = ind->next;
    }
}

void PriorityQueue::Clear() {
    while (!IsEmpty()) {
        Pop();
    }
}

int PriorityQueue::Size() const {
    return size;
}
bool PriorityQueue::IsEmpty() const {
    return (size == 0);
}

PriorityQueue& PriorityQueue::operator=(const PriorityQueue& other) {
    if (this != &other) {
        Clear();
        Clone(other);
    }
    return *this;
}
PriorityQueue& PriorityQueue::operator=(PriorityQueue&& other) noexcept {
    if (this != &other) {
        Clear();
        Move(other);
    }
    return *this;
}

void PriorityQueue::Move(PriorityQueue& other) noexcept {
    head = other.head;
    rear_high = other.rear_high;
    rear_medium = other.rear_medium;
    rear_low = other.rear_low;
    size = other.Size();

    for (int i = 0; i < 3; ++i) {
        prior_sizes[i] = other.prior_sizes[i];
        other.prior_sizes[i] = 0;
    }

    other.head = nullptr;
    other.rear_high = nullptr;
    other.rear_medium = nullptr;
    other.rear_low = nullptr;
    other.size = 0;
}

void PriorityQueue::Push(int value, Priority prior) {
    prior_sizes[prior]++;
    Node* new_node = new Node(value, prior);

    Node* new_place = nullptr;
    bool place_was_found = false;

    switch (prior) {
    case Priority::Low: {
        if (rear_low != nullptr) {
            new_place = rear_low;
            place_was_found = true;
            break;
        }
    }
    case Priority::Medium: {
        if (rear_medium != nullptr) {
            new_place = rear_medium;
            place_was_found = true;
            break;
        }
    }
    case Priority::High: {
        if (rear_high != nullptr) {
            new_place = rear_high;
            place_was_found = true;
            break;
        }
    }
    default: {
        break;
    }
    }

    size++;
    if (place_was_found) {
        new_node->next = new_place->next;
        if (new_place == rear_high) {
            rear_high->next = new_node;
        }
        else if (new_place == rear_medium) {
            rear_medium->next = new_node;
        }
        else {
            rear_low->next = new_node;
        }
    }
    else {
        if (head != nullptr) {
            new_node->next = head;
        }
        head = new_node;
    }
    if (prior == Priority::High) {
        rear_high = new_node;
    }
    if (prior == Priority::Medium) {
        rear_medium = new_node;
    }
    if (prior == Priority::Low) {
        rear_low = new_node;
    }
}
void PriorityQueue::Pop() {
    prior_sizes[head->prior]--;
    if (prior_sizes[head->prior] == 0) {
        if (head->prior == Priority::High) {
            rear_high = nullptr;
        }
        if (head->prior == Priority::Medium) {
            rear_medium = nullptr;
        }
        if (head->prior == Priority::Low) {
            rear_low = nullptr;
        }
    }
    size--;
    Node* new_head = head->next;
    delete head;
    head = new_head;
}

int PriorityQueue::GetSizeHigh() const {
    return prior_sizes[High];
}
int PriorityQueue::GetSizeMedium() const {
    return prior_sizes[Medium];
}
int PriorityQueue::GetSizeLow() const {
    return prior_sizes[Low];
}

int PriorityQueue::GetFrontValue() const {
    return head->value;
}
Priority PriorityQueue::GetFrontPriority() const {
    return head->prior;
}
std::ostream& operator<<(std::ostream& out, const PriorityQueue& queue) {
    PriorityQueue::Node* cur_elem = queue.head;
    out << "{ ";
    while (cur_elem != nullptr) {
        out << cur_elem->value << " ";
        cur_elem = cur_elem->next;
    }
    out << "}" << '\n';
    return out;
}
PriorityQueue::PriorityQueue() {

}