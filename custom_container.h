#include <iostream>
#include <memory>
#include <utility> 


template <typename T, typename Allocator = std::allocator<T>>
class CustomContainer {
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    Allocator alloc_;

public:
    explicit CustomContainer(size_t initial_capacity = 10) : size_(0), capacity_(initial_capacity) {
        data_ = alloc_.allocate(capacity_);
    }

    ~CustomContainer() {
        alloc_.deallocate(data_, capacity_);
    }

    void add(const T& value) {
        if (size_ == capacity_) {
            capacity_ *= 2;
            T* new_data = alloc_.allocate(capacity_);

            for (size_t i = 0; i < size_; ++i) {
                new(&new_data[i]) T(std::move(data_[i]));
            }

            alloc_.deallocate(data_, size_);
            data_ = new_data;
        }

        new(&data_[size_]) T(value);
        ++size_;
    }

    // Итератор для обхода контейнера в одном направлении
    class Iterator {
    private:
        T* ptr_;
    public:
        explicit Iterator(T* p) : ptr_(p) {}

        T& operator*() { return *ptr_; }
        T* operator->() { return ptr_; }

        Iterator& operator++() {
            ++ptr_;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return ptr_ != other.ptr_;
        }
    };

    Iterator begin() { return Iterator(data_); }

    Iterator end() { return Iterator(data_ + size_); }

    size_t get_size() const { return size_; }
};
