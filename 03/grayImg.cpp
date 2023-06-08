//
//  inputImgFile.cpp
//
//
//  Created by Hiroaki Sawano on 2020/04/06.
//


#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "../Debug/apple_tree.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img = cv::imread(FILE_NAME); //画像の型と変数
    //src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    //8ビットをchanell = 1 にする
    cv::Mat gray_img = cv::Mat(src_img.size(), CV_8UC1);//src_imgをコピーしてCV_8UC1適用
    /*for (int y = 0; y<src_img.rows; y++) {
        for (int x = 0; x<src_img.cols; x++) {
            cv::Vec3b s = src_img.at<cv::Vec3b>(y,x);
            uchar val = 0.114 * s[0] //B
            + 0.587 * s[1] //G
            + 0.299 * s[2]; //R
            gray_img.at<uchar>(y,x) = val;
        }
    }*/
    
    cv::Mat dst_img;
    cv::cvtColor(src_img, dst_img, cv::COLOR_BGR2GRAY);
    
    cv::imshow(WINDOW_NAME_INPUT, src_img); //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, gray_img); //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(); //キー入力待ち (止める)

    return 0;
}

