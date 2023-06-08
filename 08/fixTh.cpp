#include <iostream>
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME_1 "../Debug/red_rectangle.jpg"

#define HIGHVAL (255)//閾値
#define LOWVAL (0)
#define TH (100)


#define WINDOW_NAME_INPUT_1 "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img1 = cv::imread(FILE_NAME_1,0); //画像の型と変数
    if (src_img1.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME_1);
        return (-1);
    }
    
    cv::Mat gray_img = cv::Mat(src_img1.size(), CV_8UC1);//グレー変数


    for(int y = 0; y < src_img1.rows; y++){
        for (int x = 0; x < src_img1.cols; x++) {
            if (src_img1.at<uchar>(y, x) < TH){
                gray_img.at<uchar>(y, x) = HIGHVAL;
            }else{
                gray_img.at<uchar>(y, x) = LOWVAL;
            }
        }
    }

    //出力
    cv::imshow(WINDOW_NAME_INPUT_1, src_img1);
    cv::imshow(WINDOW_NAME_OUTPUT, gray_img);
    cv::waitKey();

    return 0;
}

