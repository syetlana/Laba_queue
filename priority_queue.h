#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <ostream>

enum Priority {
    Low,
    Medium,
    High
};

class PriorityQueue {
public:
    struct Node {
        Node(int value_, Priority prior_) : value(value_), prior(prior_) {}
        int value;
        Priority prior;
        Node* next{ nullptr };
    };

    PriorityQueue();
    PriorityQueue(const PriorityQueue& other);
    PriorityQueue(PriorityQueue&& other);

    int Size() const;
    bool IsEmpty() const;

    int GetSizeHigh() const;
    int GetSizeMedium() const;
    int GetSizeLow() const;

    int GetFrontValue() const;
    Priority GetFrontPriority() const;

    void Push(int value, Priority prior);
    void Pop();
    void Clear();

    PriorityQueue& operator=(const PriorityQueue& other);
    PriorityQueue& operator=(PriorityQueue&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& out, const PriorityQueue& queue);

private:
    Node* head{ nullptr };
    Node* rear_high{ nullptr };
    Node* rear_medium{ nullptr };
    Node* rear_low{ nullptr };

    int prior_sizes[3]{ 0, 0, 0 };
    int size{ 0 };

    void Clone(const PriorityQueue& other);
    void Move(PriorityQueue& other) noexcept;
};

#endif  // PRIORITY_QUEUE_H_
