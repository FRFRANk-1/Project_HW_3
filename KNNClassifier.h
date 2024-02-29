#ifndef KNNCLASSIFIER_H
#define KNNCLASSIFIER_H

#include <vector>
#include <string>
#include <queue>
#include <map>

class KNNClassifier {
public:
    KNNClassifier(int k);
    void train(const std::string& label, const std::vector<double>& features);
    std::string classify(const std::vector<double>& features);

private:
    struct DistanceLabelPair {
        double distance;
        std::string label;
        bool operator<(const DistanceLabelPair& other) const;
    };

    std::map<std::string, std::vector<std::vector<double>>> trainingData;
    int k;

    static double euclideanDistance(const std::vector<double>& a, const std::vector<double>& b);
};

#endif // KNNCLASSIFIER_H
