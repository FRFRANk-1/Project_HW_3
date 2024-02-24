#include "TaskRunner.h"
#include "ImageProcessor.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

void TaskRunner::runTask1(const std::string& imagePath, int kernelSize, int thresholdValue, int maxVal) {
    // Load the image
    cv::Mat frame = cv::imread(imagePath);
    if (frame.empty()) {
        std::cerr << "Error: Image could not be loaded from " << imagePath << std::endl;
        return;
    }

    ImageProcessor processor;
    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Grey", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Blurred", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Threshold", cv::WINDOW_AUTOSIZE);

    // Convert to grayscale
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    
    // Apply blur and custom threshold
    cv::Mat blurred = processor.applyBlur(grayFrame, kernelSize);
    cv::Mat thresholded = processor.applyCustomThreshold(blurred, thresholdValue, maxVal);

    // Display the resulting frames
    cv::imshow("Original", frame);
    cv::imshow("Grey", grayFrame);
    cv::imshow("Threshold", thresholded);
    cv::imshow("Blurred", blurred);

    // Ensure output directory exists
    std::string outputDir = "D:/NEU study file/5330/Project_HW_3/outputs/";

    // Save the processed images
    cv::imwrite(outputDir + "original.jpg", frame);
    cv::imwrite(outputDir + "thresholded_grey.jpg", grayFrame);
    cv::imwrite(outputDir + "blurred.jpg", blurred);
    cv::imwrite(outputDir + "thresholded.jpg", thresholded);

    // Wait indefinitely until a key is pressed
    cv::waitKey(0);
}

void TaskRunner::runTask2(const std::string& imagePath, int dilation_size, int erosion_size) {
    // Load the image
    cv::Mat frame = cv::imread(imagePath);
    if (frame.empty()) {
        std::cerr << "Error: Image could not be loaded from " << imagePath << std::endl;
        return;
    }

    ImageProcessor processor;
    cv::namedWindow("Original_thresholded_image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Dilation_image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Erosion_image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Dilated+Eroded", cv::WINDOW_AUTOSIZE);
    
    cv::Mat thresholded = processor.applyCustomThreshold(frame, 125, 255); // Example thresholding

    // Apply dilation and erosion
    cv::Mat dilatedImage = processor.applyDilated(thresholded, dilation_size);
    cv::Mat erodedImage = processor.applyEroded(thresholded, erosion_size);
    cv::Mat dilated_eroded = processor.applyEroded(dilatedImage, erosion_size); 

    // Display the resulting frames
    cv::imshow("Original_thresholded_image", thresholded); // Corrected from "Original"
    cv::imshow("Dilation_image", dilatedImage);
    cv::imshow("Erosion_image", erodedImage);
    cv::imshow("Dilated+Eroded", dilated_eroded);

    // Ensure output directory exists
    std::string outputDir = "D:/NEU study file/5330/Project_HW_3/outputs/";

    // Save the processed images
    cv::imwrite(outputDir + "original_thresholded.jpg", thresholded); // Save the thresholded image as "original" for context
    cv::imwrite(outputDir + "dilated.jpg", dilatedImage);
    cv::imwrite(outputDir + "eroded.jpg", erodedImage);
    cv::imwrite(outputDir + "dilated_eroded.jpg", dilated_eroded);

    // Wait indefinitely until a key is pressed
    cv::waitKey(0);
}

void TaskRunner::runTask3(const std::string& imagePath, int minSize) {
    cv::Mat frame = cv::imread(imagePath, cv::IMREAD_GRAYSCALE); // Ensure image is in grayscale

    // std :: cout << "debug_3 inputImage: " << imagePath << std::endl;

    if (frame.empty()) {
        std::cerr << "Error: Image could not be loaded from " << imagePath << std::endl;
        return;
    }
    
    ImageProcessor processor;

    // Display the resulting frame
    cv::namedWindow("Thresholded", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Connected Components", cv::WINDOW_AUTOSIZE);

    cv::Mat thresholded;
    processor.applyCustomThreshold(frame, 128, 255); 
    thresholded = processor.applyCustomThreshold(frame, 128, 255);

    cv::Mat labeledImage;
    processor.findConnectedComponents(thresholded, labeledImage, minSize);

    std :: cout << "debug_4 inputImage: " << imagePath << std::endl;

    cv::imshow("Thresholded", thresholded);
    cv::imshow("Connected Components", labeledImage);

    std::string outputDir = "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_3/";

    cv::imwrite(outputDir + "thresholded.jpg", thresholded);
    cv::imwrite(outputDir + "connected_components.jpg", labeledImage);
    
    // std :: cout << "debug_5 inputImage: " << imagePath << std::endl;
   
    cv::waitKey(0);
}

void TaskRunner::runTask4(const std::string& imagePath, int minSize) {
    //load image
    cv::Mat frame = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    if (frame.empty()) {
        std::cerr << "Error: Image could not be loaded from " << imagePath << std::endl;
        return;
    }
    ImageProcessor processor;
    cv::Mat thresholded;
    // Apply custom threshold
    processor.applyCustomThreshold(frame, 128, 255); 
    thresholded = processor.applyCustomThreshold(frame, 128, 255);
    cv::Mat labeledImage, stats, centroids;
    int nLabels = cv::connectedComponentsWithStats(thresholded, labeledImage, stats, centroids, 8, CV_32S);

    std::cout << "Number of connected components: " << nLabels << std::endl;

    cv::Mat labeledImage8bit;
    labeledImage.convertTo(labeledImage8bit, CV_8U, 255 / nLabels);

    // create an output image to draw on
    //an empty Mat with the same size as the input image but with 3 channels (BGR)
    cv::Mat outputImage;
    cv::cvtColor(labeledImage8bit, outputImage, cv::COLOR_GRAY2BGR);
    
    std::ofstream report("D:/NEU study file/5330/Project_HW_3/Report_Folder/task_4/task4_report.txt");
    report << "computed features - task 4\n\n";
    for (int label = 1; label < nLabels; ++label) {
        int area = stats.at<int>(label, cv::CC_STAT_AREA);
        if (area > minSize) {
            // Compute the bounding box
            cv::Rect bbox (
                stats.at<int>(label, cv::CC_STAT_LEFT),
                stats.at<int>(label, cv::CC_STAT_TOP),
                stats.at<int>(label, cv::CC_STAT_WIDTH),
                stats.at<int>(label, cv::CC_STAT_HEIGHT)
            );
            double percentFilled = ImageProcessor::calculatePercentFilled(stats, label);
            double aspectRatio = ImageProcessor::calculateAspectRatio(stats, label);

            // Find central moments
            cv::Moments mu = cv::moments(cv::Mat(labeledImage == label), true);
            double huMoments[7];
            cv::HuMoments(mu, huMoments); 

            cv::rectangle(outputImage, bbox, cv::Scalar(0, 255, 0), 2);
            cv::circle(outputImage, cv::Point(static_cast<int>(centroids.at<double>(label, 0)), static_cast<int>(centroids.at<double>(label, 1))), 4, cv::Scalar(0, 255, 0), -1);

            // Write component features to file
            report << "Component " << label << ":\n";
            report << " - Area: " << area << "\n";
            report << " - Percent Filled: " << percentFilled << "%\n";
            report << " - Aspect Ratio: " << aspectRatio << "\n";
            report << " - Hu Moments: [";
            for (int h = 0; h < 7; ++h) {
                report << huMoments[h] << (h < 6 ? ", " : "");
            }
            report << "]\n\n";
        }
    }
    report.close();
    // Display the resulting frame
    cv::namedWindow("Features", cv::WINDOW_AUTOSIZE);
    cv::imshow("Features", outputImage);

    // Save the output image with the drawn features
    std::string outputDir = "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_4/";
    cv::imwrite(outputDir + "features.jpg", outputImage);

    // Wait indefinitely until a key is pressed
    cv::waitKey(0);
}

void TaskRunner::runTask5(const std::string& imagePath, int minSize) {
    std::string label;
    std::cout << "Enter label for this object: ";
    std::cin >> label;

    cv::Mat frame = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (frame.empty()) {
        std::cerr << "Error: Image could not be loaded." << std::endl;
        return;
    }

    ImageProcessor processor;
    cv::Mat processedImage;

    // Assume you have a method to process the frame and extract features
    std::vector<double> features = processor.extractFeatures(frame, processedImage, minSize);

    // Save features and label to the file
    std::string filename = "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_5/objectDB.txt"; // The file where the object database is stored
    processor.saveFeatureVector(features, label, filename);

    // Display the processed image
    cv::namedWindow("processed Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("processed Image", processedImage);
    
    // Save the processed image
    std::string imagePathToSave = "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_5/processedImage.jpg";
    cv::imwrite(imagePathToSave, processedImage);
    
    cv::waitKey(0); 

    std::cout << "Saved features for label: " << label << std::endl;
}

void TaskRunner::runTask6(const std::string& imagePath, int minSize) {
    cv::Mat frame = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (frame.empty()) {
        std::cerr << "Error: Image could not be loaded." << std::endl;
        return;
    }

    ImageProcessor processor;
    cv::Mat processedImage;
    
    // Extract features from the image
    std::vector<double> features = processor.extractFeatures(frame, processedImage, minSize);

    // Load the object database
    std::string databasePath = "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_5/objectDB.txt";
    auto database = processor.loadDatabase(databasePath);

    std::string filename = "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_6/data_analyzation.txt";
    std::ofstream report(filename, std::ios::out | std::ios::app); 

    if (!report.is_open()) {
        std::cerr << "Error: Unable to open file for writing comparison results." << std::endl;
        return;
    }

    report << "\nClassification Process for: " << imagePath << std::endl;
    report << "Feature vector size: " << features.size() << std::endl;

    std::string bestMatch;
    double bestDistance = std::numeric_limits<double>::max();

    double threshold = 100;
    if (bestDistance > threshold) {
        bestMatch = "Unknown";
    }
    
    for (const auto& entry : database) {
        std::vector<double> stdevs = processor.computeFeatureStdevs(database);
        double distance = processor.scaledEuclideanDistance(features, entry.second, stdevs);
        report << "Comparing with label " << entry.first << ", Distance: " << distance << std::endl;
        
        if (distance < bestDistance) {
            bestDistance = distance;
            bestMatch = entry.first;
        }
    }

    if (!bestMatch.empty()) {
        report << "Best match: " << bestMatch << " with a distance of " << bestDistance << std::endl;
    } else {
        report << "No suitable match found." << std::endl;
    }

    report.close();

    // Overlay the label on the image
    cv::putText(frame, bestMatch, cv::Point(10, frame.rows - 10), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);

    // Display the classified image
    cv::imshow("Classification", frame);
    cv::waitKey(0);
}
