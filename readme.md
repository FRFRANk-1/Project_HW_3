## Author: Runcheng Li
github_link_this_project: https://github.com/FRFRANk-1/Project_HW_3

## Operating system: Window11. IDE: VS code

## Project_3 - "Real-time 2-D Object Recognition"

## To run task 1: 
<image_path> <kernel_size> <threshold_value> <max_val>

Obeservation 1: The higher kernel_size value -> The more smoothness of the image is, computation become heavy if kernel_size become larger than 35, plus the best kernal_size as tested should be less than 15.

Observation 2: The lower the threshold_value, the more light comes in, effect apply contrastly. Ideal threshold_value as tested: 100.

Observatio 3: Max_value is the maxmium receive for selecting light source, automatically set to 255 is fair enough for running.

terminal input examples: .\Project_HW_3 1 "D:/NEU study file/5330/Project_HW_3/Proj03Examples/img5p3.png" 15 100 255 5

## To run task 2:
<image_path> <dilation_size> <erosion_size>

Observation 1: The larger dilation_size, the more smoothness of the image is, and the noise will be reduce. Over large value can lose details of the image, where the optimal value currently is set at 1.

Observation 2: The larger erosion_size, the more details of image it might lose, where over-smoothing effect apply which decrease the effectiveness of image processing, also more computational time required. The optimal value currently is at 2

Observation 3: Apply dilated_effect value with 1 and erode_effect value at 2 appear has the best optimal graphic output, where is futher smooth out the edges for all different image (img1p3, img2p3, img5p3)

terminal input examples ->  
Selection_1: .\Project_HW_3 2 "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_1/img1p3_15,100,255,5/thresholded.jpg" 3 2

selection_2: .\Project_HW_3 2 "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_1/img2p3_15,100,255,5/thresholded.jpg" 3 2
 
selection_3: .\Project_HW_3 2 "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_1/img5p3_15,100,255,5/thresholded.jpg" 3 2