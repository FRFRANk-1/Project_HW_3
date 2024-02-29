#include "TaskRunner.h"
#include <iostream>
#include <string>
#include <utility>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <task_number> <image_path> [additional_parameters]" << std::endl;
        std::cerr << "For Task 1: [image_path] [kernel_size] [threshold_value] [max_val]" << std::endl;
        std::cerr << "For Task 2: [image_path] [dilation_size] [erosion_size]" << std::endl;
        std::cerr << "For Task 3: [image_path] [min_size]" << std::endl;
        std::cerr << "For Task 4: [image_path] [min_size]" << std::endl;
        std::cerr << "For Task 5: [folder_path] [image_path] [min_size]" << std::endl;
        std::cerr << "For Task 6: [image_path] [min_size]" << std::endl;
        std::cerr << "For Task 7: [database_path]" << std::endl;
        std::cerr << "For Task 8: [image_path] [min_size]" << std::endl;
        return -1;
    }

    int taskNumber = std::stoi(argv[1]);
    std::string imagePath = argv[2];
    TaskRunner runner;

    switch (taskNumber) {
        case 1:
            if (argc != 6) {
                std::cerr << "Usage for Task 1: " << argv[0] << " 1 <image_path> <kernel_size> <threshold_value> <max_val>" << std::endl;
                return -1;
            }
            {
                int kernelSize = std::stoi(argv[3]);
                int thresholdValue = std::stoi(argv[4]);
                int maxVal = std::stoi(argv[5]);
                runner.runTask1(imagePath, kernelSize, thresholdValue, maxVal);
            }
            break;
        case 2:
            if (argc != 5) {
                std::cerr << "Usage for Task 2: " << argv[0] << " 2 <image_path> <dilation_size> <erosion_size>" << std::endl;
                return -1;
            }
            {
                int dilationSize = std::stoi(argv[3]);
                int erosionSize = std::stoi(argv[4]);
                runner.runTask2(imagePath, dilationSize, erosionSize);
            }
            break;
        case 3:
            if (argc != 4) {
                std::cerr << "Usage for Task 3: " << argv[0] << " 3 <image_path> <min_size>" << std::endl;
                return -1;
            }
            {
                int minSize = std::stoi(argv[3]);
                runner.runTask3(imagePath, minSize);
            }
            break;
        case 4:
            if (argc != 4) {
                std::cerr << "Usage for Task 4: " << argv[0] << " 4 <image_path> <min_size>" << std::endl;
                return -1;
            }
            {
                int minSize = std::stoi(argv[3]);
                runner.runTask4(imagePath, minSize);
            }
            break;
        case 5:
            if (argc != 5) {
                std::cerr << "Usage for Task 5: " << argv[0] << " 5 <folder_path> <image_path> <min_size>" << std::endl;
                return -1;
            }
            {   
                std::string folderPath = argv[2];
                std::string imagePath = argv[3];
                int minSize = std::stoi(argv[4]);
                runner.runTask5(folderPath, imagePath, minSize);
            }
            break;
        case 6:
            if (argc != 4) {
                std::cerr << "Usage for Task 6: " << argv[0] << " 6 <image_path>" << std::endl;
                return -1;
            } 
            {
            int minSize = std::stoi(argv[3]);
            runner.runTask6(imagePath, minSize);
            }
            break;
        case 7:
            if(argc < 3) {
                std::cerr << "Usage for Task 7: " << argv[0] << " 7 <database_path>" << std::endl;
                return -1;
            }{
                std::vector<std::pair<std::string, std::string>> imageData = {
                    {"D:/NEU study file/5330/Project_HW_3/Proj03Examples/img1p3.png", "label1"},
                    {"D:/NEU study file/5330/Project_HW_3/Proj03Examples/img2p3.png", "label2"},
                    {"D:/NEU study file/5330/Project_HW_3/Proj03Examples/img5p3.png", "label3"},
                    {"D:/NEU study file/5330/Project_HW_3/Report_Folder/task_2/img2p3_ 1 2/dilated_eroded.jpg", "label4"},
                    {"D:/NEU study file/5330/Project_HW_3/Report_Folder/task_2/img1p3_ 1 2/dilated_eroded.jpg", "label5"},
                    {"D:/NEU study file/5330/Project_HW_3/Report_Folder/task_2/img5p3_ 1 2/dilated_eroded.jpg", "label6"},
                };
                std::string databasePath = argv[2];
                runner.runTask7(imageData, databasePath);
            } break;
        // case 8:
        //     if(argc < 4) {
        //         std::cerr << "Usage for Task 8: " << argv[0] << " 8 <database_path> <k>" << std::endl;
        //         return -1;
        //     } {
        //         std::vector<std::pair<std::string, std::string>> imageData = {
        //             {"D:/NEU study file/5330/Project_HW_3/Proj03Examples/img1p3.png", "label1"},
        //             {"D:/NEU study file/5330/Project_HW_3/Proj03Examples/img2p3.png", "label2"},
        //             {"D:/NEU study file/5330/Project_HW_3/Proj03Examples/img5p3.png", "label3"},
        //             {"D:/NEU study file/5330/Project_HW_3/Report_Folder/task_2/img2p3_ 1 2/dilated_eroded.jpg", "label4"},
        //             {"D:/NEU study file/5330/Project_HW_3/Report_Folder/task_2/img1p3_ 1 2/dilated_eroded.jpg", "label5"},
        //             {"D:/NEU study file/5330/Project_HW_3/Report_Folder/task_2/img5p3_ 1 2/dilated_eroded.jpg", "label6"},
        //         };
        //         std::string databasePath = argv[2];
        //         int k = std::stoi(argv[3]);
        //         runner.runTask8(imageData, databasePath, k);
        //     } 
        //     break;
        default:
            std::cerr << "Error: Unknown task number." << std::endl;
            return -1;
    }

    return 0;
}
