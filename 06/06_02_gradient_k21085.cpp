#include <iostream>
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "../Debug/06_02_input_k21085.jpeg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define WINDOW_NAME_OUTPUT_3 "output_3"

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img = cv::imread(FILE_NAME); //画像の型と変数
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    cv::Mat h_img;
    cv::Mat g_img = cv::Mat(src_img.size(), CV_64FC1);
    cv::Mat tmp_img,tmp2_img,tmp3_img;
    cv::cvtColor(src_img, h_img, cv::COLOR_BGR2GRAY);
    
    double filter_h[] = {0.,-1.,0.,
                        0.,0.,0.,
                        0.,1.,0.};
    
    double filter_w[] = {0.,0.,0.,
                        -1.,0.,1.,
                        0.,0.,0.};
    
    
    cv::Mat kernel = cv::Mat(3, 3, CV_64F, filter_w);
    cv::Mat kernel_2 = cv::Mat(3, 3, CV_64F, filter_h);
    cv::filter2D(h_img, tmp_img, CV_64F, kernel);
    cv::filter2D(h_img, tmp2_img, CV_64F, kernel_2);
    
    //cv::convertScaleAbs(tmp_img, w_img);
    //cv::convertScaleAbs(tmp2_img, h_img);
    
    double h,w;
    
    for(int y = 0; y < src_img.rows; y++){
        for (int x = 0; x < src_img.cols; x++) {
            h = tmp_img.at<double_t>(y, x);
            w = tmp2_img.at<double_t>(y, x);
            g_img.at<double_t>(y, x) = sqrt(h * h + w * w);
        }
    }
    cv::convertScaleAbs(g_img, g_img);
    
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT_3, g_img);
    cv::waitKey();

    return 0;
}
