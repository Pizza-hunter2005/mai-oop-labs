#ifndef MY_CONTAINER_H
#define MY_CONTAINER_H

#include <cassert>
#include <iostream>
#include <map>
#include <memory_resource>
#include <new>

// Класс эффективного ресурса памяти
class MemoryResource : public std::pmr::memory_resource {
private:
    std::map<void*, size_t> allocations;
    std::map<size_t, std::vector<void*>> free_blocks;
protected:
    void* do_allocate(size_t bytes, size_t alignment) override {
        if(!free_blocks[bytes].empty()) {
            void* block = free_blocks[bytes].back();
            free_blocks[bytes].pop_back();
            allocations[block] = bytes;
            return block;
        }
        void* ptr = ::operator new(bytes);
        allocations[ptr] = bytes;
        return ptr;
    }
    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override {
        free_blocks[bytes].push_back(ptr);
        allocations.erase(ptr);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
public:
    ~MemoryResource() {
        for (auto& res : allocations) {
            ::operator delete(res.first);
        }
        for (auto res : free_blocks) {
            for (void* ptr : res.second) {
                ::operator delete(ptr);
            }
        }
        allocations.clear();
        free_blocks.clear();
    }
};

// Класс динамического массива с итератором
template <typename T>
class DynamicArray {
private:
    T* data;
    size_t size_;
    size_t capacity;
    std::pmr::polymorphic_allocator<T> allocator;

    void resize() {
        size_t new_capacity = capacity * 2;
        T* new_data = allocator.allocate(new_capacity);

        for (size_t i = 0; i < size_; ++i) {
            new(new_data + i) T(std::move(data[i]));
            data[i].~T();
        }
        allocator.deallocate(data, capacity);
        data = new_data;
        capacity = new_capacity;
    }
public:
    // Итератор для MyContainer
    class Iterator {
    private:
        T* ptr;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(T* ptr) : ptr(ptr) {}

        T& operator*() const { return *ptr; }
        T* operator->() { return ptr; }

        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.ptr == b.ptr;
        }
        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return a.ptr != b.ptr;
        }
    };

    explicit DynamicArray(std::pmr::memory_resource* res, size_t initial_capacity = 10)
        : data(nullptr),
          capacity(initial_capacity),
          size_(0),
          allocator(res) {
        data = allocator.allocate(initial_capacity);
    }

    ~DynamicArray() {
        for (size_t i = 0; i < size_; ++i) {
            data[i].~T(); 
        }
        allocator.deallocate(data, capacity);
    }

    void push_back(const T& value) {
        if (size_ == capacity) {
            resize();
        }
        new(data + size_) T(value);  // Конструируем элемент на нужном месте
        ++size_;
    }

    void pop_back() {
        assert(size_ > 0 && "Container is empty");
        data[size_ - 1].~T();  // Явно вызываем деструктор
        --size_;
    }

    size_t size() const { return size_; }
    size_t get_capacity() const { return capacity; }

    T& operator[](size_t index) {
        assert(index < size_ && "Index out of bounds");
        return data[index];
    }

    const T& operator[](size_t index) const {
        assert(index < size_ && "Index out of bounds");
        return data[index];
    }

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size_); }
};

#endif // MY_CONTAINER_H