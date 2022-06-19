#pragma once
template<class ItemType>
class PriorityQueueADT
{
public:
    /** Sees whether this queue is empty.
     @return  True if the queue is empty, or false if not. */
    virtual bool isEmpty() const = 0;

    // Adds a new entry to the queue accourding to its priority.
    virtual bool add(const ItemType& newEntry, double priority) = 0;

    // Copies the front item of the queue to the passed parameter and removes it from queue
    virtual bool remove(ItemType& FrontEntry) = 0;

    // Copies the front item of the queue to the passed parameter without removing it from queue
    virtual bool peek(ItemType& FrontEntry) const = 0;

    // Destroys this queue and frees its memory.
    virtual ~PriorityQueueADT() { }
}; // end QueueADT