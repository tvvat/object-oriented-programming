#pragma once
template<typename T>
class Vector {
private:
    T* arr_;
    size_t size_{};
    static const int Quota = 100;
    size_t MS{};
    int iter;
   
public:
    Vector() {
        arr_ = new T[Quota];
        MS = Quota;
    }

    Vector(Vector& other) {
        if (this != &other) {
            arr_ = new T[other.MS];
            for (size_t i = 0; i < other.size_; ++i) arr_[i] = other.arr_[i];
            size_ = other.size_;
            MS = other.MS;
        }
        else
        {
            throw std::exception "didnt it"
        }
    }
    Vector(Vector&& other)  noexcept {
        if (this != &other) {
            delete[] arr_;
            arr_ = other.arr_;
            size_ = other.size_;
            MS = other.MS;
            other.arr_ = nullptr;
            other.size_ = other.MS = 0;
        }
        else
        {
            throw std::exception "didnt it"
        }
    }


    bool isEmpty() const {
        return size_ == 0;
    }
    void resize(size_t N) {
        MS = N;
        T* tmp = arr_;
        arr_ = new T[N];
        for (size_t i = 0; i < size_; ++i) arr_[i] = tmp[i];
        delete[] tmp;



    }
    size_t size() const {
        return size_;
    }

   size_t capacity() const {
        return MS;
    }
   void addMemory() {
       capacity_ *= 2;
       T* tmp = arr_;
       arr_ = new T[MS];
       for (size_t i = 0; i < size_; ++i) arr_[i] = tmp[i];
       delete[] tmp;
       
   }

   void pushBack(const T& value) {
       if (size_ >= MS) addMemory();
       arr_[size_++] = value;
   }
   void remove(size_t index) {
       for (size_t i = index + 1; i < size_; ++i) {
           arr_[i - 1] = arr_[i];
       }
       --size_;
   }
   T& operator[](size_t index) {
       size_++;
       return arr_[index];
   }

   const T& operator[](size_t index) const {
       return arr_[index];
   }

   ~Vector() {
       delete[] arr_;
   }
   /*template<typename T>
   friend std::ostream& operator <<(std::ostream& os, const Vector<T>& vec) {
       for (size_t i = 0; i < vec.size(); ++i) os << vec[i] << " ";
       return os;
   }*/
   Vector& operator =(Vector& other) {
       if (this != &other) {
           delete[] arr_;
           arr_ = new T[other.MS];
           MS= other.MS;
           for (size_t i = 0; i < other.size_; ++i) arr_[i] = other.arr_[i];
           size_ = other.size_;
       }
       else
       {
           throw std::exception "didnt it"
       }

       return *this;
   }

   Vector& operator=(Vector&& other) noexcept {
       if (this != &other) {
           delete[] arr_;
           arr_ = other.arr_;
           other.size_ = 0;
           other.MS = 0;
           MS = other.MS;
           other.arr_ = nullptr;
           size_ = other.size_;
       }
       else
       {
           throw std::exception "didnt it"
       }

       return *this;
   }
  
   T* begin() {
       return &arr_[0];
   }

   const T* begin() const {
       return &arr_[0];
   }

   T* end() {
       return &arr_[size_];
   }

   const T* end() const {
       return &arr_[size_];
   }


};
//template <typename T>
//class iterator {
//private:
//    vector k;
//    int index;
//public:
//    iterator(vector t) {
//        k = t;
//
//    }
//
//
//};