#include <iostream>
#include <vector>
#include <list>

class SimpleHashSet {
private:
    int size;
    std::vector<std::list<std::string>> buckets;

    int hashFunction(const std::string& value) {
        int sum = 0;
        for (char ch : value) {
            sum += static_cast<int>(ch);
        }
        return sum % size;
    }

public:
    SimpleHashSet(int size = 100) : size(size), buckets(size) {}

    void add(const std::string& value) {
        int index = hashFunction(value);
        std::list<std::string>& bucket = buckets[index];

        if (std::find(bucket.begin(), bucket.end(), value) == bucket.end()) {
            bucket.push_back(value);
        }
    }

    bool contains(const std::string& value) {
        int index = hashFunction(value);
        std::list<std::string>& bucket = buckets[index];

        return std::find(bucket.begin(), bucket.end(), value) != bucket.end();
    }

    void remove(const std::string& value) {
        int index = hashFunction(value);
        std::list<std::string>& bucket = buckets[index];

        bucket.remove(value);
    }

    void printSet() {
        std::cout << "Hash Set Contents:\n";
        for (size_t i = 0; i < buckets.size(); i++) {
            std::cout << "Bucket " << i << " : ";
            for (const std::string& item : buckets[i]) {
                std::cout << item << " ";
            }
            std::cout << "\n";
        }
    }

    int getHashCode(const std::string& value) {
        return hashFunction(value);
    }
};

int main() {
    SimpleHashSet hashSet(10);

    hashSet.add("Charlotte");
    hashSet.add("Thomas");
    hashSet.add("Jens");
    hashSet.add("Peter");
    hashSet.add("Lisa");
    hashSet.add("Adele");
    hashSet.add("Michaela");
    hashSet.add("Bob");

    hashSet.printSet();

    std::cout << "\n'Peter' is in the set: " << (hashSet.contains("Peter") ? "Yes" : "No") << "\n";
    std::cout << "Removing 'Peter'\n";
    hashSet.remove("Peter");

    std::cout << "'Peter' is in the set: " << (hashSet.contains("Peter") ? "Yes" : "No") << "\n";
    std::cout << "'Adele' has hash code: " << hashSet.getHashCode("Adele") << "\n";

    return 0;
}
