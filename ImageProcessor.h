#ifndef ImageProcessor_H
#define ImageProcessor_H

#include <opencv2/core/mat.hpp>
#include <map>
#include <vector>
#include <string>

std::string classifyObject(const std::vector<double>& features, const std::string& databasePath);

class ImageProcessor {
public:
    // Constructor
    ImageProcessor();

    // Apply Gaussian blur to the input image
    cv::Mat applyBlur(const cv::Mat &inputImage, int kernelSize);

    // Apply thresholding to the input image
    cv::Mat applyCustomThreshold(const cv::Mat &inputImage, int thresholdValue, int maxVal);

    cv::Mat applyDilated(const cv::Mat &inputImage, int dilation_size);

    cv::Mat applyEroded(const cv::Mat &inputImage, int erosion_size);

    void ImageProcessor::findConnectedComponents(const cv::Mat &inputImage, cv::Mat &outputImage, int minSize);

    static double calculatePercentFilled(const cv::Mat &stats, int label);
    static double calculateAspectRatio(const cv::Mat &stats, int label);
    
    void ImageProcessor::saveFeatureVector(const std::vector<double>& features, const std::string& label, const std::string& filename);

    size_t ImageProcessor::determineFeatureVectorSize(const std::string& databasePath);

    std::vector<double> ImageProcessor::extractFeatures(const cv::Mat &inputImage, cv::Mat& processedImage, int minSize);

    std::map<std::string, std::vector<double>> loadDatabase(const std::string& filename);

    std::vector<double> computeFeatureStdevs(const std::map<std::string, std::vector<double>>& database);

    std::string ImageProcessor::classifyFeatureVector(const std::vector<double>& featureVector, const std::map<std::string, std::vector<double>>& database);

    double scaledEuclideanDistance(const std::vector<double>& vec1, const std::vector<double>& vec2, const std::vector<double>& stdevs);

    double getBestDistance() const;

private:
    double lastBestDistance = std::numeric_limits<double>::max();
};  

    
#endif // IMAGEPROCESSOR_H