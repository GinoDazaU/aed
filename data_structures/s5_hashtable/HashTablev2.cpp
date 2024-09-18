#include <vector>
#include <list>
#include <stdexcept>
#include <functional>  // For hash functions
#include <random>      // For random number generators
#include <algorithm>   // For std::sort
#include <string>

using namespace std;

template <typename Key, typename Value>
class HashTable {
private:
    vector<list<pair<Key, Value>>> table;  // The hash table
    int size;       // Number of buckets
    int count;      // Number of elements in the table
    int a, b, p;    // Parameters for universal hashing
    const float loadFactorThreshold = 0.75f;  // Threshold for rehashing

    // Universal hash function
    size_t hashFunction(const Key& key) const {
        size_t key_value = hash<Key>{}(key);
        return ((a * key_value + b) % p) % size;
    }

    // Rehash the table when the load factor exceeds the threshold
    void rehash() {
        int newSize = size * 2;  // Double the size
        vector<list<pair<Key, Value>>> newTable(newSize);  // New table

        // Rehash all existing elements into the new table
        for (const auto& bucket : table) {
            for (const auto& entry : bucket) {
                size_t newIndex = ((a * hash<Key>{}(entry.first) + b) % p) % newSize;
                newTable[newIndex].emplace_back(entry.first, entry.second);
            }
        }

        table = move(newTable);  // Replace old table with the new one
        size = newSize;          // Update size
    }

public:
    // Constructor with optional initial size
    HashTable(int initialSize = 16) : size(initialSize), count(0) {
        table.resize(size);

        // Random number generator for hash function parameters
        random_device rd;
        mt19937 gen(rd());
        p = 104729;  // A large prime number
        uniform_int_distribution<> dis_a(1, p - 1);
        uniform_int_distribution<> dis_b(0, p - 1);
        a = dis_a(gen);
        b = dis_b(gen);
    }

    // Insert a key-value pair into the table
    bool insert(const Key& key, const Value& value) {
        // Check load factor before inserting
        if (static_cast<float>(count + 1) / size > loadFactorThreshold) {
            rehash();
        }

        size_t index = hashFunction(key);  // Get index
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                entry.second = value;  // Update value if key exists
                return true;
            }
        }
        table[index].emplace_back(key, value);  // Insert new key-value pair
        count++;  // Increment element count
        return true;
    }

    // Overload operator[] to access or insert elements
    Value& operator[](const Key& key) {
        // Check load factor before inserting
        if (static_cast<float>(count + 1) / size > loadFactorThreshold) {
            rehash();
        }

        size_t index = hashFunction(key);  // Get index
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                return entry.second;  // Return value if key exists
            }
        }
        // Insert default value if key does not exist
        table[index].emplace_back(key, Value());
        count++;  // Increment element count
        return table[index].back().second;  // Return reference to new value
    }

    // Search for a value by key
    Value search(const Key& key) const {
        size_t index = hashFunction(key);  // Get index
        for (const auto& entry : table[index]) {
            if (entry.first == key) {
                return entry.second;  // Return value if found
            }
        }
        throw runtime_error("Key not found");  // Throw exception if not found
    }

    // Remove a key-value pair by key
    bool remove(const Key& key) {
        size_t index = hashFunction(key);  // Get index
        auto& entries = table[index];
        for (auto it = entries.begin(); it != entries.end(); ++it) {
            if (it->first == key) {
                entries.erase(it);  // Erase the key-value pair
                count--;            // Decrement element count
                return true;
            }
        }
        return false;  // Return false if key not found
    }

    // Check if the table is empty
    bool isEmpty() const {
        return count == 0;
    }

    // Get the current size of the table (number of buckets)
    int getSize() const {
        return size;
    }

    // Get the number of elements in the table
    int getCount() const {
        return count;
    }

    // Get all values stored in the table
    vector<Value> getAllValues() const {
        vector<Value> values;
        for (const auto& bucket : table) {
            for (const auto& entry : bucket) {
                values.push_back(entry.second);
            }
        }
        return values;
    }
};
