
#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../Debug/kagoshima.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    unsigned char Imin, Imax, Dmin, Dmax;
    Imax = 0;
    Imin = 255;
    
    Dmax = 255;
    Dmin = 0;
    
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    
    if (src_img.empty()) {
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);
    
    
    
    
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            uchar s = src_img.at<uchar>(y, x);
            
            if (Imin > s) {
                Imin = s;
            }
            if (Imax < s) {
                Imax = s;
            }
        }
    }
    
    fprintf(stderr, "Imin = %d, Imax = %d\n",Imin,Imax);
    
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            uchar s = src_img.at<uchar>(y, x);
            s = (Dmax - Dmin)/(Imax - Imin) * (s - Imin) + Dmin;
            dst_img.at<uchar>(y, x) = s;
        }
    }
    
    cv::imshow(WINDOW_NAME_INPUT , src_img);//入力画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);//出力画像の表示
    cv::waitKey();
    return 0;
}
