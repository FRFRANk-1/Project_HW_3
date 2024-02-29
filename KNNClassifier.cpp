#include "KNNClassifier.h"
#include <cmath>

KNNClassifier::KNNClassifier(int k) : k(k) {}

void KNNClassifier::train(const std::string& label, const std::vector<double>& features) {
    trainingData[label].push_back(features);
}

std::string KNNClassifier::classify(const std::vector<double>& features) {
    std::priority_queue<DistanceLabelPair> nearestNeighbors;

    for (const auto& labelAndFeatures : trainingData) {
        for (const auto& trainFeatures : labelAndFeatures.second) {
            double distance = euclideanDistance(features, trainFeatures);
            nearestNeighbors.push({distance, labelAndFeatures.first});

            if (nearestNeighbors.size() > k) {
                nearestNeighbors.pop();
            }
        }
    }

    std::map<std::string, int> labelCount;
    while (!nearestNeighbors.empty()) {
        auto neighbor = nearestNeighbors.top();
        nearestNeighbors.pop();
        labelCount[neighbor.label]++;
    }

    std::string bestLabel;
    int maxCount = 0;
    for (const auto& labelAndCount : labelCount) {
        if (labelAndCount.second > maxCount) {
            maxCount = labelAndCount.second;
            bestLabel = labelAndCount.first;
        }
    }

    return bestLabel;
}

bool KNNClassifier::DistanceLabelPair::operator<(const DistanceLabelPair& other) const {
    return distance > other.distance; // Greater distance means lower priority
}

double KNNClassifier::euclideanDistance(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return std::sqrt(sum);
}
