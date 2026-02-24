#ifdef UOSM_OBSERVABLES
#ifndef UOSM_CORE_DATAQUEUE_HPP
#define UOSM_CORE_DATAQUEUE_HPP

#include <stdexcept>
#include <cstdint>

template <typename T> class DataQueue;

template <typename T>
class DataQueueIterator {
private:
    const DataQueue<T>& dataQueue;
    uint8_t currentIndex;
public:
    DataQueueIterator(const DataQueue<T>& dataQueue, uint8_t index): dataQueue(dataQueue), currentIndex(index) {}
    uint8_t getCurrentIndex() const { return currentIndex; }
    bool operator!=(const DataQueueIterator& other) const { return currentIndex != other.currentIndex; }
    DataQueueIterator& operator++() { currentIndex++; return *this; }
    const T& operator*() {
        uint8_t realIndex = (dataQueue.getTailIndex() + currentIndex) % dataQueue.getSize();
        return dataQueue.getRawValues()[realIndex];
    }
};

template<typename T>
class DataQueue {
    // Changement ici : 'protected' permet aux classes enfants (ObservedDataQueue) d'accéder aux variables
protected:
    T* values;
    T* sortedCache;
    uint8_t head;
    uint8_t tail;
    uint8_t count;
    uint8_t size;

public:
    explicit DataQueue(uint8_t size): size(size), head(0), tail(0), count(0) {
        values = new T[size];
        sortedCache = new T[size];
    }
    virtual ~DataQueue() { delete[] values; delete[] sortedCache; }

    uint8_t getSize() const { return size; }
    uint8_t getNumberOfElements() const { return count; }
    uint8_t getTailIndex() const { return tail; }
    T* getRawValues() const { return values; }

    virtual void add(T value) {
        values[head] = value;
        if (count == size) { tail = (tail + 1) % size; }
        else { count++; }
        head = (head + 1) % size;
    }

    T& getLatestValue() const {
        return values[(head + size - 1) % size];
    }

    using iterator = DataQueueIterator<T>;
    iterator begin() const { return iterator(*this, 0); }
    iterator end() const { return iterator(*this, count); }
};

#endif // UOSM_CORE_DATAQUEUE_HPP
#endif // UOSM_OBSERVABLES