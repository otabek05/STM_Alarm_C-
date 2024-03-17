#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <cstdint> // For uint8_t
#include <cstddef> // For size_t, explicitly include this

class CircularBuffer {
public:
    CircularBuffer();

    bool isFull() const;
    bool isEmpty() const;
    bool write(uint8_t data);
    bool read(uint8_t& data);

private:
    static const size_t BUFFER_SIZE = 1024; // Adjust as needed
    uint8_t buffer[BUFFER_SIZE];
    volatile size_t head, tail;
};

#endif // CIRCULARBUFFER_H
