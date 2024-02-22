#include <iostream>
#include <vector>

// Define a struct to represent an object
struct Object {
    std::string name;
    std::vector<double> featureVector;
};

// Define a class to manage the object database
class ObjectDatabase {
private:
    std::vector<Object> objects;

public:
    // Add a new object to the database
    void addObject(const std::string& name, const std::vector<double>& featureVector) {
        Object obj;
        obj.name = name;
        obj.featureVector = featureVector;
        objects.push_back(obj);
    }

    // Get the number of objects in the database
    int getObjectCount() const {
        return objects.size();
    }

    // Get the feature vector of an object by its index
    std::vector<double> getFeatureVector(int index) const {
        if (index >= 0 && index < objects.size()) {
            return objects[index].featureVector;
        }
        return {};
    }
};

int main() {
    // Create an instance of the ObjectDatabase class
    ObjectDatabase database;

    // Add objects to the database
    database.addObject("Object 1", {1.0, 2.0, 3.0});
    database.addObject("Object 2", {4.0, 5.0, 6.0});

    // Get the number of objects in the database
    int objectCount = database.getObjectCount();
    std::cout << "Number of objects in the database: " << objectCount << std::endl;

    // Get the feature vector of the first object
    std::vector<double> featureVector = database.getFeatureVector(0);
    std::cout << "Feature vector of the first object: ";
    for (double value : featureVector) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
