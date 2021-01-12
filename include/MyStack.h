#include <cstdlib>

template <typename T>
class MyStack
{
public:
    explicit MyStack(const size_t stackSize)
    {
        if (!stackSize)
            throw std::logic_error("Null size is not allowed");
        capacity = stackSize;
        size = 0;
        tail = new T[capacity];
    }

    MyStack(const MyStack& other) : tail(new T[other.capacity]), size(other.size), capacity(other.capacity)
    {
        for (size_t i = 0; i < size; ++i)
            tail[i] = other.tail[i];
    }

    ~MyStack()
    {
        delete[] tail;
    }

    T get() const
    {
        if (isEmpty())
            throw std::out_of_range("Stack is empty");
        return tail[size - 1];
    }

    T pop()
    {
        const T value = get();
        --size;
        return value;
    }

    void push(const T& elem)
    {
        if (size == capacity)
        {
            //T* newTail = static_cast<T*>(std::realloc(tail, capacity *= 2));
            T* newTail = new T[capacity *= 2];
            if (!newTail)
            {
                std::free(tail);
                throw std::bad_alloc();
            }
            std::memcpy(newTail, tail, size * sizeof(T));
            tail = newTail;
        }
        tail[size] = elem;
        ++size;
    }

    bool isFull() const
    {
        return false; // memory reallocation is implemented - stack is never full as long as there is enough memory to store it
    }

    bool isEmpty() const
    {
        return !size;
    }

private:
    T* tail;
    size_t size;
    size_t capacity;
};