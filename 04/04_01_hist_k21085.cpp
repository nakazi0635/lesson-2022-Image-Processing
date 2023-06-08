
#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../Debug/image1.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define COLOR_NUM (256) //色値

int main(int argc, const char * argv[]) {
    int hist[COLOR_NUM];
    
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    
    if (src_img.empty()) {
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    
    for (int i = 0; i < COLOR_NUM; i++) {
        hist[i] = 0;
    }
    
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            hist[src_img.at<uchar>(y, x)]++;
        }
    }
    for (int i = 0; i < COLOR_NUM; i++) {
        //std::cout << hist[i] << std::endl;
        printf("%d %d\n",i ,hist[i]);
    }
    cv::waitKey();
    
    return 0;
}

