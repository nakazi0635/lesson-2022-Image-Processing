
#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../Debug/01_01_face_x21085.jpg"
#define WINDOW_NAME "output"

int main(int argc, const char * argv[]) {
    cv::Mat src_img;
    src_img = cv::imread(FILE_NAME);
    if (src_img.empty()) {
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }
    
    cv::imshow(WINDOW_NAME, src_img);
    cv::waitKey();

    return 0;
}
