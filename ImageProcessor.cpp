#include "ImageProcessor.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <fstream>
#include <vector>
#include <string>

// Constructor
ImageProcessor::ImageProcessor() { }

cv::Mat ImageProcessor:: applyBlur(const cv:: Mat &inputImage, int kernelSize) {
    cv::Mat blurredImage;
    cv::GaussianBlur(inputImage, blurredImage, cv::Size(kernelSize, kernelSize), 0);
    return blurredImage;
}

cv::Mat ImageProcessor::applyCustomThreshold(const cv::Mat &inputImage, int thresholdValue, int maxVal) {
    
    cv::Mat thresholdedImage = inputImage.clone(); // create a copy of input image 
    int rows = thresholdedImage.rows;
    int cols = thresholdedImage.cols;

    // check the image if it is a color image or a grayscale image
    bool isColor = thresholdedImage.type() == CV_8UC3;

    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            if(isColor) {

                cv::Vec3b pixel = thresholdedImage.at<cv::Vec3b>(i, j);
                // convert the pixel to grayscale
                int gray = (pixel[0] + pixel[1] + pixel[2]) / 3;
                // if the gray value is greater than the threshold value, set the pixel to maxVal
                int binaryValue = gray > thresholdValue ? maxVal : 0;
                pixel = cv::Vec3b(binaryValue, binaryValue, binaryValue);
            } else {

                uchar& pixel = thresholdedImage.at<uchar>(i, j);
                pixel = pixel > thresholdValue ? maxVal : 0;
            }
        }
    }
    return thresholdedImage;
}

cv::Mat ImageProcessor::applyDilated(const cv::Mat &inputImage, int dilation_size) {
    cv::Mat dilatedImage;
    // create a structuring element
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1), cv::Point(dilation_size, dilation_size));
    
    cv::dilate(inputImage, dilatedImage, element);
    return dilatedImage;
}

cv::Mat ImageProcessor::applyEroded(const cv::Mat &inputImage, int erosion_size) {
    cv::Mat erodedImage;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1), cv::Point(erosion_size, erosion_size));

    cv::erode(inputImage, erodedImage, element);
    return erodedImage;
}

void ImageProcessor::findConnectedComponents(const cv::Mat &inputImage, cv::Mat &outputImage, int minSize) {
    cv::Mat labels, stats, centroids;

    // std :: cout << "debug_1 inputImage: " << inputImage << std::endl;

    //lables: output label matrix
    //stats: output statistics matrix
    //centroids: output centroids matrix
    int nLabels = cv::connectedComponentsWithStats(inputImage, labels, stats, centroids, 8, CV_32S);
    
    // std :: cout << "debug_2 inputImage: " << inputImage << std::endl;

    std::vector<cv::Vec3b> colors(nLabels);
    colors[0] = cv::Vec3b(0, 0, 0); // background color
    for(int i = 1; i < nLabels; i++) {
        colors[i] = cv::Vec3b(rand() & 255, rand() & 255, rand() & 255); // random color for each label
    }

    outputImage = cv::Mat::zeros(inputImage.size(), CV_8UC3);
    for(int y = 0; y < labels.rows; y++) {
        for(int x = 0; x < labels.cols; x++) {
            int label = labels.at<int>(y, x);
            int area = stats.at<int>(label, cv::CC_STAT_AREA);
            if (area > minSize) {
                outputImage.at<cv::Vec3b>(y, x) = colors[label];
            }
        }
    }

    std::ofstream report("D:/NEU study file/5330/Project_HW_3/Report_Folder/task_3/task3_report.txt");
    report << "Connected Components Report\n\n";

    for (int label = 1; label < nLabels; ++label) {
        int area = stats.at<int>(label, cv::CC_STAT_AREA);
        if (area > minSize) {
            int left = stats.at<int>(label, cv::CC_STAT_LEFT);
            int top = stats.at<int>(label, cv::CC_STAT_TOP);
            int width = stats.at<int>(label, cv::CC_STAT_WIDTH);
            int height = stats.at<int>(label, cv::CC_STAT_HEIGHT);
            cv::Point centroid(
                static_cast<int>(centroids.at<double>(label, 0)),
                static_cast<int>(centroids.at<double>(label, 1))
            );

            // Write the stats for each component to the file
            report << "Component " << label << ":\n";
            report << " - Area: " << area << "\n";
            report << " - Bounding Box: x=" << left << ", y=" << top
                   << ", width=" << width << ", height=" << height << "\n";
            report << " - Centroid: x=" << centroid.x << ", y=" << centroid.y << "\n\n";
        }
    }

    // Close the file
    report.close();
}

double ImageProcessor::calculatePercentFilled(const cv::Mat &stats, int label) {
    int area = stats.at<int>(label, cv::CC_STAT_AREA);
    int bboxwidth = stats.at<int>(label, cv::CC_STAT_WIDTH);
    int bboxheight = stats.at<int>(label, cv::CC_STAT_HEIGHT);
    double bboxArea = bboxwidth * bboxheight; 
    return (area / bboxArea) * 100;
}

double ImageProcessor::calculateAspectRatio(const cv::Mat &stats, int label) {
    int bboxwidth = stats.at<int>(label, cv::CC_STAT_WIDTH);
    int bboxheight = stats.at<int>(label, cv::CC_STAT_HEIGHT);
    return static_cast<double>(bboxwidth) / bboxheight;
}

void ImageProcessor::saveFeatureVector(const std::vector<double>& features, const std::string& label, const std::string& filename) {
    std::ofstream file;
    file.open(filename, std::ios_base::app);
    file << "Label: " << label << "\n";

    // Define variable names for each feature
    std::vector<std::string> variableNames = {
        "Area", "PercentFilled", "AspectRatio", 
        "HuMoment1", "HuMoment2", "HuMoment3", "HuMoment4", "HuMoment5", "HuMoment6", "HuMoment7"
    };

    // Write features with variable names to the file
    for (size_t i = 0; i < features.size(); ++i) {
        file << variableNames[i % variableNames.size()] << ": " << features[i] << "\n";
    }
    file << "\n";
    file.close();
}

size_t ImageProcessor::determineFeatureVectorSize(const std::string& databasePath) {
    std::ifstream file(databasePath);
    std::string line;
    size_t maxSize = 0;
    size_t currentSize = 0;

    // Read the file line by line
    while (std::getline(file, line)) {
        // Check for the 'Label:' identifier to reset the current size count
        if (line.rfind("Label:", 0) == 0) {
            maxSize = std::max(maxSize, currentSize);
            currentSize = 0;
        } else if (!line.empty()) {
            // Increment for each feature line that is not a label
            currentSize++;
        }
    }
    // Check last vector size
    maxSize = std::max(maxSize, currentSize);
    
    file.close();
    return maxSize;
}

std::vector<double> ImageProcessor::extractFeatures(const cv::Mat &inputImage, cv::Mat& processedImage, int minSize) {
    
    std::vector<double> features;
    
    // size_t expectedSize = determineFeatureVectorSize("D:/NEU study file/5330/Project_HW_3/Report_Folder/task_5/objectDB.txt");
    // if (features.size() < expectedSize) {
    //     features.insert(features.end(), expectedSize - features.size(), 0.0);
    // }
    
    // Convert to grayscale if the input image is colored
    if (inputImage.channels() == 3) {
        std::cout << "Input image has 3 channels. Converting to grayscale." << std::endl;
        cv::cvtColor(inputImage, processedImage, cv::COLOR_BGR2GRAY);
    } else {
        processedImage = inputImage.clone();
    }

    // Apply thresholding or not (currently set at 0)
    cv::threshold(processedImage, processedImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    // Find connected components and stats
    cv::Mat labels, stats, centroids;
    int nLabels = cv::connectedComponentsWithStats(processedImage, labels, stats, centroids, 8, CV_32S);

    for (int label = 1; label < nLabels; ++label) {
        int area = stats.at<int>(label, cv::CC_STAT_AREA);

        // Skip small components if the area is less than minSize
        if (area >= minSize) {
            double aspectRatio = calculateAspectRatio(stats, label);
            double percentFilled = calculatePercentFilled(stats, label);

            cv::Moments mu = cv::moments(cv::Mat(labels == label), true);
            double huMoments[7];
            cv::HuMoments(mu, huMoments);

            // Add the component's features to the vector
            features.push_back(area);
            features.push_back(percentFilled);
            features.push_back(aspectRatio);
            for (int i = 0; i < 7; ++i) {
                features.push_back(huMoments[i]);
            }
        }
    } 
    std:: cout << "Feature extraction complete" << std::endl; 
    return features;
}

std::string classifyObject(const std::vector<double>& features, const std::string& databasePath) {
    
    std:: cout << "Classifying object start" << std::endl;
    ImageProcessor processor;

    auto database = processor.loadDatabase(databasePath);

    std::string bestMatchLabel;
    double shortestDistance = std::numeric_limits<double>::max();

    for (const auto& entry : database) {
        double distance = processor.scaledEuclideanDistance(features, entry.second, processor.computeFeatureStdevs(database));
        if (distance < shortestDistance) {
            shortestDistance = distance;
            bestMatchLabel = entry.first;
        }
    }
    std::cout << "Classifying object complete" << std::endl;
    return bestMatchLabel;
}

std::vector<double> ImageProcessor::computeFeatureStdevs(const std::map<std::string, std::vector<double>>& database) {
    
    std::cout << "Computing feature standard deviations" << std::endl;
    if (database.empty()) return {};
    size_t featureCount = database.begin()->second.size();
    std::vector<double> means(featureCount, 0), stdevs(featureCount, 0);

    std::cout << "Feature count start: " << featureCount << std::endl;
    // Calculate means
    for (const auto& entry : database) {
        for (size_t i = 0; i < featureCount; ++i) {
            means[i] += entry.second[i];
        }
    }
    for (double& mean : means) mean /= database.size();

    std::cout << "Means calculated start" << std::endl;
    // Calculate standard deviations
    for (const auto& entry : database) {
        for (size_t i = 0; i < featureCount; ++i) {
            stdevs[i] += std::pow(entry.second[i] - means[i], 2);
        }
    }
    for (double& stdev : stdevs) stdev = std::sqrt(stdev / database.size());

    std::cout << "Standard deviations calculated" << std::endl;
    for (const auto& stdev : stdevs ) {
        std::cout << stdev << " ";
    }
    return stdevs;
}

std::map<std::string, std::vector<double>> ImageProcessor::loadDatabase(const std::string& filename) {
   
    std:: cout << "Loading database start" << std::endl;

    std::map<std::string, std::vector<double>> database;
    std::ifstream file(filename);
    std::string line, label;
    std::vector<double> featureVector;
    // const size_t EXPECTED_FEATURE_VECTOR_SIZE;
    

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        if (line.rfind("Label:", 0) == 0) { // New label found
            if (!label.empty() && featureVector.size()) {
                // Log error or handle the situation when feature vector size is not as expected
                std::cerr << "Error: Feature vector for label " << label << " has " << featureVector.size() << " features " << std::endl;
            }
            label = line.substr(7); // Extract label name
            featureVector.clear(); // Prepare for next feature vector
        } else { // Assuming line contains feature value
            double value;
            if (ss >> value) {
                featureVector.push_back(value);
            }
        }
    }
    std:: cout << "Loading database complete" << std::endl;
    return database;
}

double ImageProcessor::getBestDistance() const {
    return lastBestDistance;
}

std::string ImageProcessor::classifyFeatureVector(const std::vector<double>& featureVector, const std::map<std::string, std::vector<double>>& database) {
    
    std::cout << "Classifying feature vector" << std::endl;

    std::string filename = "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_6/data_analyzation.txt";
    std::ofstream report(filename);

    if(!report.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return "";
    }
    
    std::string bestMatch;
    double bestDistance = std::numeric_limits<double>::max();
    
    // Print the size of the feature vector to be classified
    std::cout << "Feature vector size: " << featureVector.size() << std::endl;
    std::cout << "Starting classification process." << std::endl;
    std::cout << "Loaded database size: " << database.size() << std::endl;
    std::cout << "Feature vector to classify size: " << featureVector.size() << std::endl;

    for (const auto& entry : database) {
        // Ensure vectors are the same size before calculating distance
        std::cout << "Checking entry: " << entry.first << " with vector size " << entry.second.size() << std::endl;
        if (featureVector.size() == entry.second.size()) {
            double distance = scaledEuclideanDistance(featureVector, entry.second, computeFeatureStdevs(database));
            // Print the comparison distance for each database entry
            std::cout << "Distance to label " << entry.first << ": " << distance << std::endl;

            if (distance < bestDistance) {
                bestDistance = distance;
                bestMatch = entry.first;
                lastBestDistance = bestDistance;
            }
        } else {
            std::cout << "Size mismatch for label " << entry.first << ": feature vector size = " << featureVector.size() << ", database vector size = " << entry.second.size() << std::endl;
        }
        return bestMatch;
    }

    
    // Print the best match after comparing with all entries
    if (!bestMatch.empty()) {
        std::cout << "Best match: " << bestMatch << " with a distance of " << bestDistance << std::endl;
    } else {
        std::cerr << "No suitable match found." << std::endl;
    }

    return bestMatch;
}

double ImageProcessor::scaledEuclideanDistance(const std::vector<double>& vec1, const std::vector<double>& vec2, const std::vector<double>& stdevs) {
    double distance = 0.0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        double scaledDiff = (stdevs[i] > 0) ? (vec1[i] - vec2[i]) / stdevs[i] : (vec1[i] - vec2[i]) / (stdevs[i] + std::numeric_limits<double>::epsilon());
        distance += scaledDiff * scaledDiff;
    }
    std:: cout << "Scaled Euclidean distance: " << std::sqrt(distance) << std::endl;
    return std::sqrt(distance);
}

