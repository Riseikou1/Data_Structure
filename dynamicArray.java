#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

class SimpleHashMap {
private:
    int size;
    std::vector<std::list<std::pair<std::string, std::string>>> buckets;

    int hashFunction(const std::string& key) {
        int numericSum = 0;
        for (char ch : key) {
            if (isdigit(ch)) {
                numericSum += ch - '0';
            }
        }
        return numericSum % size;
    }

public:
    SimpleHashMap(int size = 10) : size(size), buckets(size) {}

    void put(const std::string& key, const std::string& value) {
        int index = hashFunction(key);
        auto& bucket = buckets[index];

        for (auto& pair : bucket) {
            if (pair.first == key) {
                pair.second = value; // Update existing key
                return;
            }
        }
        bucket.emplace_back(key, value); // Add new key-value pair
    }

    std::string get(const std::string& key) {
        int index = hashFunction(key);
        auto& bucket = buckets[index];

        for (const auto& pair : bucket) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return "Key not found";
    }

    void remove(const std::string& key) {
        int index = hashFunction(key);
        auto& bucket = buckets[index];

        bucket.remove_if([&](const std::pair<std::string, std::string>& pair) {
            return pair.first == key;
        });
    }

    void printMap() {
        std::cout << "Hash Map Contents:" << std::endl;
        for (size_t i = 0; i < buckets.size(); i++) {
            std::cout << "Bucket " << i << " : ";
            for (const auto& pair : buckets[i]) {
                std::cout << "(" << pair.first << ", " << pair.second << ") ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    SimpleHashMap hashMap(10);

    hashMap.put("123-4567", "Charlotte");
    hashMap.put("123-4568", "Thomas");
    hashMap.put("123-4569", "Jens");
    hashMap.put("123-4570", "Peter");
    hashMap.put("123-4571", "Lisa");
    hashMap.put("123-4572", "Adele");
    hashMap.put("123-4573", "Michaela");
    hashMap.put("123-4574", "Bob");

    hashMap.printMap();

    std::cout << "\nName associated with '123-4570': " << hashMap.get("123-4570") << std::endl;
    std::cout << "Updating the name for '123-4570' to 'Temuujin'\n";
    hashMap.put("123-4570", "Temuujin");
    std::cout << "Name associated with '123-4570': " << hashMap.get("123-4570") << std::endl;

    return 0;
}
