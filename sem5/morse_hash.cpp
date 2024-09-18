
#include <cstddef>
#include <iostream>
#include <vector>
#include <utility>
#include <random>
#include <list>

using namespace std;

template <typename Key, typename Value>
class HashTable {

private: 
    vector<list<pair<Key, Value>>> table;  // Hash table with chaining (list of key-value pairs)
    int size;       // Number of buckets
    int count;      // Number of elements
    int a, b, p;    // Parameters for universal hashing
    const float loadFactorThreshold = 0.75;  // Threshold for rehashing

    // Universal hash function
    size_t hashFunction(const Key& key) const {
        size_t key_value = hash<Key>{}(key);
        return ((a * key_value + b) % p) % size;
    }

    // Resize and rehash the table when load factor exceeds the threshold
    void rehash() {
        int newSize = size * 2;  // Double the size of the table
        vector<list<pair<Key, Value>>> newTable(newSize);  // Create a new table

        // Rehash all existing elements into the new table
        for (auto& bucket : table) {
            for (auto& entry : bucket) {
                size_t newIndex = ((a * hash<Key>{}(entry.first) + b) % p) % newSize;
                newTable[newIndex].emplace_back(entry.first, entry.second);
            }
        }

        table = std::move(newTable);  // Replace the old table with the new one
        size = newSize;               // Update the size
    }

    // Check if we need to resize based on the load factor
    void checkLoadFactorAndRehash() {
        if ((float)count / size > loadFactorThreshold) {
            rehash();
        }
    }

public:
    // Constructor initializing with a default size
    HashTable(int initialSize = 16): size(initialSize), count(0) {
        table.resize(size);  // Initialize the table with empty buckets
        srand(time(NULL));   // Seed for generating a and b
        p = 104729;          // A large prime number
        a = rand() % (p - 1) + 1;  // a between 1 and p-1
        b = rand() % p;            // b between 0 and p-1
    }

    // Insert a key-value pair into the hash table
    bool insert(Key key, Value value) {
        size_t index = hashFunction(key);  // Get the bucket index
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                entry.second = value;  // If key already exists, update the value
                return true;
            }
        }
        // If the key does not exist, add a new key-value pair to the bucket
        table[index].emplace_back(key, value);
        count++;  // Increment the number of elements

        // Check the load factor and rehash if necessary
        checkLoadFactorAndRehash();

        return true;
    }

    // Search for a value by its key
    Value search(Key key) {
        size_t index = hashFunction(key);  // Get the bucket index
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                return entry.second;  // Return the value if key is found
            }
        }
        throw runtime_error("Key not found");  // If not found, throw an exception
    }

    // Remove a key-value pair by key
    bool remove(Key key) {
        size_t index = hashFunction(key);  // Get the bucket index
        auto& entries = table[index];
        for (auto it = entries.begin(); it != entries.end(); ++it) {
            if (it->first == key) {
                entries.erase(it);  // Remove the key-value pair
                count--;            // Decrement the number of elements
                return true;
            }
        }
        return false;  // Return false if key is not found
    }

    // Check if the hash table is empty
    bool isEmpty() const {
        return count == 0;
    }

    // Display the contents of the hash table (for debugging purposes)
    void display() const {
        for (int i = 0; i < size; ++i) {
            cout << "Bucket " << i << ": ";
            for (const auto& entry : table[i]) {
                cout << "(" << entry.first << ", " << entry.second << ") ";
            }
            cout << endl;
        }
    }

    int getSize(){
        return size;
    }

    int getCount(){
        return count;
    }
};


class Solution {

public:
    int uniqueMorseRepresentations(vector<string>& words) {
        vector<string> morse = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

        HashTable<string,string> hash;

        for(string word:words){
            cout << word << " ";
        } cout << endl;
        
        for(string word:words){
            string morse_word = "";
            for(char c:word){
                morse_word += morse[c - 'a'];
            }
            hash.insert(morse_word,word);
        }

        hash.display();

        return hash.getCount();
    }
};

int main(){

    vector<string> words = {"gin","zen","gig","msg"};

    Solution sol;

    cout << sol.uniqueMorseRepresentations(words) << endl;

}