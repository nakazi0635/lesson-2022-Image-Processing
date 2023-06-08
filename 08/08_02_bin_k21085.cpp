#include <iostream>
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME_1 "../Debug/red_green_rectangle.jpg"

//#define HIGHVAL (255)//閾値
//#define LOWVAL (0)
#define COLOR_NUM (256) //色値


#define WINDOW_NAME_INPUT_1 "input"
#define WINDOW_NAME_OUTPUT_1 "output_1"
#define WINDOW_NAME_OUTPUT_2 "output_2"

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img = cv::imread(FILE_NAME_1); //画像の型と変数
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME_1);
        return (-1);
    }
    
    cv::Mat ans_img_1 = cv::Mat(src_img.size(), CV_8UC3);
    cv::Mat ans_img_2 = cv::Mat(src_img.size(), CV_8UC3);
    //cv::Mat ans_img_2 = cv::Mat(src_img.size(), CV_8UC1);


    cv::Vec3b s;
    int TH_red = 157,TH_green = 155;
        for (int y=0; y<src_img.rows; y++) {
            for (int x=0; x<src_img.cols; x++) {
                s = src_img.at<cv::Vec3b>(y,x);
                if (s[1] > TH_green) {
                    s[0] = 255;
                    s[1] = 255;
                    s[2] = 255;
                }else{
                    s[0] = 0;
                    s[1] = 0;
                    s[2] = 0;
                }
                ans_img_1.at<cv::Vec3b>(y,x) = s;
            }
        }
    
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            s = src_img.at<cv::Vec3b>(y,x);
            if (s[2] > TH_red) {
                s[0] = 255;
                s[1] = 255;
                s[2] = 255;
            }else{
                s[0] = 0;
                s[1] = 0;
                s[2] = 0;
            }
            ans_img_2.at<cv::Vec3b>(y,x) = s;
        }
    }
    
//    cv::Mat dst_img;
//    cv::cvtColor(src_img, dst_img, cv::COLOR_BGR2GRAY);
//
//    for(int y = 0; y < dst_img.rows; y++){
//        for (int x = 0; x < dst_img.cols; x++) {
//            if (dst_img.at<uchar>(y, x) < TH){
//                ans_img_2.at<uchar>(y, x) = HIGHVAL;
//            }else{
//                ans_img_2.at<uchar>(y, x) = LOWVAL;
//            }
//        }
//    }
    //出力
    cv::imshow(WINDOW_NAME_INPUT_1, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT_1, ans_img_1);
    cv::imshow(WINDOW_NAME_OUTPUT_2, ans_img_2);
    cv::waitKey();

    return 0;
}

