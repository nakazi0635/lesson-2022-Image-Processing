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
#define FILE_NAME "../Debug/aquarium.jpg"
#define WINDOW_NAME "output"

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img; //画像の型と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }
    
    cv::imshow(WINDOW_NAME, src_img); //画像の表示
    cv::waitKey(); //キー入力待ち (止める)

    return 0;
}
