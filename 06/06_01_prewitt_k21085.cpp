#include <iostream>
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "../Debug/06_01_input_k21085.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img = cv::imread(FILE_NAME); //画像の型と変数
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    cv::Mat dst_img;
    cv::cvtColor(src_img, dst_img, cv::COLOR_BGR2GRAY);
    
    double filter_h[] = {-1.,-1.,-1.,
                        0.,0.,0.,
                        1.,1.,1.};
    cv::Mat kernel = cv::Mat(3, 3, CV_64F, filter_h);
    cv::Mat tmp_img;
    cv::filter2D(dst_img, tmp_img, CV_64F, kernel);
    
    cv::convertScaleAbs(tmp_img, dst_img);
    
    cv::imshow(WINDOW_NAME_INPUT, src_img); 
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}
