#include "labeler.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <opencv2/opencv.hpp>

namespace fs = std::filesystem;

labeler::labeler(const std::string& folderPath) : folderPath(folderPath) {}

void labeler::Run() {
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (!entry.is_directory()) {
            std::string imagePath = entry.path().string();
            image = cv::imread(imagePath);
            if (!image.empty()) {
                clone = image.clone();
                cv::namedWindow("image");
                cv::setMouseCallback("image", MouseCallback, this);

                while (true) {
                    cv::imshow("image", image);
                    char key = (char)cv::waitKey(1);

                    if (key == 'r') {
                        image = clone.clone();
                    } else if (key == 'c') {
                        break;
                    }
                }
                cv::destroyAllWindows();
            }
        }
    }
    SaveData("D:/NEU study file/5330/Project_HW_3/Report_Folder/task_5/db.txt");
}

void labeler::MouseCallback(int event, int x, int y, int flags, void* userdata) {
    labeler* self = static_cast<labeler*>(userdata);
    self->ClickAndCrop(event, x, y);
}

void labeler::ClickAndCrop(int event, int x, int y) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        refPt[0] = cv::Point(x, y);
        cropping = true;
    } else if (event == cv::EVENT_LBUTTONUP) {
        refPt[1] = cv::Point(x, y);
        cropping = false;
        cv::rectangle(image, refPt[0], refPt[1], cv::Scalar(0, 255, 0), 2);
        std::cout << "Enter the label: ";
        std::cin >> label;
        cv::putText(image, label, refPt[0] - cv::Point(0, 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
        data.push_back({folderPath, cv::Rect(refPt[0], refPt[1]), label});
    } else if (event == cv::EVENT_MOUSEMOVE && cropping) {
        cv::Mat temp_image = image.clone();
        cv::rectangle(temp_image, refPt[0], cv::Point(x, y), cv::Scalar(0, 255, 0), 2);
        cv::imshow("image", temp_image);
    }
}

void labeler::SaveData(const std::string& filename) {
    std::ofstream file(filename, std::ios::app); // Open in append mode to add to existing file
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }
    for (const auto& item : data) {
        // The filename is now included as part of the data saved
        file << item.file << "," << item.box.x << "," << item.box.y << ","
             << item.box.width << "," << item.box.height << "," << item.label << std::endl;
    }
}
// Example usage in main.cpp
// #include "labeler.h"
// int main() {
//     std::string folderPath;
//     std::cout << "Enter the folder path: ";
//     std::cin >> folderPath;
//     labeler labeler(folderPath);
//     labeler.Run();
//     return 0;
// }