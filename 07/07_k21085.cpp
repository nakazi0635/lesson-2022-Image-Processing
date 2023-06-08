#include <iostream>
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME_1 "../Debug/issue_input1.jpg"
#define FILE_NAME_2 "../Debug/issue_input2.jpg"
#define THRESHOLD (5)//閾値
#define FILTER_SIZE (5)


#define WINDOW_NAME_INPUT_1 "input"
#define WINDOW_NAME_INPUT_2 "input_2"
#define WINDOW_NAME_SUB "sub"
#define WINDOW_NAME_OUTPUT "output"
#define WINDOW_NAME_OUTPUT_2 "output_2"

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img1 = cv::imread(FILE_NAME_1,0); //画像の型と変数
    cv::Mat src_img2 = cv::imread(FILE_NAME_2,0); //画像の型と変数
    if (src_img1.empty()||src_img2.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME_1);
        return (-1);
    }
    
    
    cv::Mat result_img = cv::Mat(src_img2.size(), CV_8UC3);//カラー変数
    cv::Mat gaussian_img = cv::Mat(src_img2.size(), CV_8UC1);//グレー変数
    
    //src_img2 -> gaussian_imgにgaussianフィルター
    cv::GaussianBlur(src_img2, gaussian_img, cv::Size(FILTER_SIZE,FILTER_SIZE),0);


    for(int y = 0; y < src_img1.rows; y++){
        for (int x = 0; x < src_img2.cols; x++) {
            int s1 = (int)src_img1.at<unsigned char>(y, x);
            int s2 = (int)gaussian_img.at<unsigned char>(y, x);
            //src_img2 と gaussian_imgを引き算した絶対値を取得
            int s_result = abs(s1-s2);
            
            cv::Vec3b s;//ベクターカラー変数宣言

            //設定した閾値より大きい値は赤色になる
            if (s_result > THRESHOLD) {
                s[0] = 0;
                s[1] = 0;
                s[2] = 255;//Red
            }else{
                s[0] = 0;
                s[1] = 0;
                s[2] = 0;
            }
            result_img.at<cv::Vec3b>(y,x) = s;
        }
    }

    //出力
    cv::imshow(WINDOW_NAME_INPUT_1, src_img1);
    cv::imshow(WINDOW_NAME_INPUT_2, src_img2);
    cv::imshow(WINDOW_NAME_OUTPUT_2, result_img);
    cv::waitKey();

    return 0;
}

