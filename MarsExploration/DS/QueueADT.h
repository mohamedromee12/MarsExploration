#ifndef QUEUE_ADT_
#define QUEUE_ADT_

template<class ItemType>
class QueueADT
{
public:
    // Sees whether this queue is empty.
    virtual bool isEmpty() const = 0;

    // Adds a new entry to the back of this queue.
    virtual bool enqueue(const ItemType& newEntry) = 0;

    // Copies the front item of the queue to the passed parameter and removes it from queue.
    virtual bool dequeue(ItemType& FrontEntry) = 0;

    // Copies the front item of the queue to the passed parameter without removing it from queue
    virtual bool peek(ItemType& FrontEntry) const = 0;

    // Destroys this queue and frees its memory.
    virtual ~QueueADT() { }
}; // end QueueADT
#endif