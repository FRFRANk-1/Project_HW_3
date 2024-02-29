#ifndef LABELER_H
#define LABELER_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

struct BoxLabel {
    std::string file;
    cv::Rect box;
    std::string label;
};

class labeler {
public:
    explicit labeler(const std::string& folderPath);
    void Run();

private:
    static void MouseCallback(int event, int x, int y, int flags, void* userdata);
    void ClickAndCrop(int event, int x, int y);
    void SaveData(const std::string& filename);

    std::string folderPath;
    cv::Mat image;
    cv::Mat clone;
    std::vector<BoxLabel> data;
    bool cropping = false;
    cv::Point refPt[2];
    std::string label;
};

#endif // LABELER_H
