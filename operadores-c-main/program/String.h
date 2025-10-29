#ifndef STRING_H
#define STRING_H

#include <cstring> 

class String {
private:
    char* data;
    int current_size;
    int capacity;

    void resize(int new_capacity) {
        char* new_data = new char[new_capacity];
        if (data != nullptr) {
            strcpy(new_data, data);
            delete[] data;
        } else {
            new_data[0] = '\0';
        }
        data = new_data;
        capacity = new_capacity;
    }

public:
    String() : current_size(0), capacity(16) {
        data = new char[capacity];
        data[0] = '\0';
    }

    String(const char* s) {
        if (s == nullptr) {
            current_size = 0; capacity = 16;
            data = new char[capacity]; data[0] = '\0';
        } else {
            current_size = strlen(s); capacity = current_size + 1;
            data = new char[capacity]; strcpy(data, s);
        }
    }

    String(const String& other) {
        current_size = other.current_size; capacity = other.capacity;
        data = new char[capacity]; strcpy(data, other.data);
    }

    ~String() { delete[] data; }

    String& operator=(const String& other) {
        if (this == &other) return *this;
        delete[] data;
        current_size = other.current_size; capacity = other.capacity;
        data = new char[capacity]; strcpy(data, other.data);
        return *this;
    }

    const char* c_str() const { return data; }
    int length() const { return current_size; }
    void append(char c) {
        if (current_size + 1 >= capacity) resize(capacity * 2);
        data[current_size] = c;
        current_size++;
        data[current_size] = '\0';
    }

    char& operator[](int index) { return data[index]; }
    const char& operator[](int index) const { return data[index]; }

    bool operator==(const char* other) const { return strcmp(this->data, other) == 0; }
    bool operator==(const String& other) const { return strcmp(this->data, other.data) == 0; }
};

#endif // STRING_H