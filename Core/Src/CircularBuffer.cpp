// CircularBuffer.cpp
#include "CircularBuffer.h"

CircularBuffer::CircularBuffer() : head(0), tail(0) {}

bool CircularBuffer::isFull() const {
    return (head + 1) % BUFFER_SIZE == tail;
}

bool CircularBuffer::isEmpty() const {
    return head == tail;
}

bool CircularBuffer::write(uint8_t data) {
    if (!isFull()) {
        buffer[head] = data;
        head = (head + 1) % BUFFER_SIZE;
        return true;
    }
    return false; // Buffer is full
}

bool CircularBuffer::read(uint8_t& data) {
    if (!isEmpty()) {
        data = buffer[tail];
        tail = (tail + 1) % BUFFER_SIZE;
        return true;
    }
    return false;
}
