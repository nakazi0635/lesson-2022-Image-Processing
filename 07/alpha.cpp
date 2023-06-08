#include <iostream>
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME_1 "../Debug/input1.jpg"
#define FILE_NAME_2 "../Debug/input2.jpg"
#define ALPHA (0.3)


#define WINDOW_NAME_INPUT_1 "input"
#define WINDOW_NAME_INPUT_2 "input_2"

#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img1 = cv::imread(FILE_NAME_1,0); //画像の型と変数
    cv::Mat src_img2 = cv::imread(FILE_NAME_2,0); //画像の型と変数
    if (src_img1.empty()||src_img2.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME_1);
        return (-1);
    }
    
    cv::Mat result_img = cv::Mat(src_img1.size(), CV_8UC1);
    
    for(int y = 0; y < src_img1.rows; y++){
        for (int x = 0; x < src_img2.cols; x++) {
            double s1 = (double)src_img1.at<unsigned char>(y, x);
            double s2 = (double)src_img2.at<unsigned char>(y, x);
            int s_result = ALPHA * s1 +(1.0 - ALPHA) * s2;
            result_img.at<unsigned char>(y, x) = (unsigned char)s_result;
        }
    }
    
    cv::imshow(WINDOW_NAME_INPUT_1, src_img1);
    cv::imshow(WINDOW_NAME_INPUT_2, src_img2);
    cv::imshow(WINDOW_NAME_OUTPUT, result_img);
    cv::waitKey();

    return 0;
}
