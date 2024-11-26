#include <memory>
#include <cstdlib>
#include <stdexcept>
#include <new>

const size_t DEFAULT_CHUNK_SIZE = 10;

template <typename T, std::size_t ChunkSize=DEFAULT_CHUNK_SIZE>
struct CustomAllocator {
    using value_type = T;
    typedef T* pointer;

    CustomAllocator() noexcept = default;

    template <typename U>
    CustomAllocator(const CustomAllocator<U, ChunkSize>&) noexcept {}

    pointer allocate(std::size_t n) {
        if (n == 0) return nullptr;

        pointer new_ptr = static_cast<pointer>(::operator new(n * sizeof(T)));
        if (!new_ptr) {
            throw std::bad_alloc();
        }

        ptr_ = new_ptr;
        reserved_ = n;

        return ptr_;
    }

    void deallocate(pointer p, std::size_t) noexcept {
        if (p) {
            ::operator delete(p);
        }
    }

    void deallocate_all() noexcept {
        if (ptr_) {
            ::operator delete(ptr_);
            ptr_ = nullptr;
            reserved_ = 0;
        }
    }

    template <typename U>
    struct rebind {
        using other = CustomAllocator<U, ChunkSize>;
    };

private:
    pointer ptr_ = nullptr;
    std::size_t reserved_ = 0;
};

template <typename T, typename U, std::size_t ChunkSize>
bool operator==(const CustomAllocator<T, ChunkSize>&, const CustomAllocator<U, ChunkSize>&) { return true; }

template <typename T, typename U, std::size_t ChunkSize>
bool operator!=(const CustomAllocator<T, ChunkSize>&, const CustomAllocator<U, ChunkSize>&) { return false; }
