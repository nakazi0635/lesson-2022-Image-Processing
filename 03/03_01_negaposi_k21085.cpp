//
//  posterization.cpp
//
//
//  Created by Masashi Morimoto on 2022/04/19.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../Debug/fruit_image.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define COLOR_NUM (256) //色値

int main(int argc, const char * argv[]) {
    //画像の入力 (グレースケール入力)
    cv::Mat src_img = cv::imread(FILE_NAME);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    
    cv::Mat gray_img;
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    //ルックアップテーブルの生成 (4段階)
    int I = COLOR_NUM;
    uchar dst[COLOR_NUM];
    //ルックアップテーブルの生成 (4段階)
    for (int i=0; i<COLOR_NUM; i++) {
        dst[i] = I - i;
    }
    
    cv::Mat dst_img = cv::Mat(gray_img.size(), CV_8UC1);
    
    //画像の走査
    for (int y=0; y<gray_img.rows; y++) {
        for (int x=0; x<gray_img.cols; x++) {
            //uchar s = gray_img.at<uchar>(y, x); //画素値の取得
            //ルックアップテーブルによるポスタリゼーション
            dst_img.at<uchar>(y, x) = dst[gray_img.at<uchar>(y, x)];
            
        }
    }
    
    cv::imshow(WINDOW_NAME_INPUT , src_img);//入力画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);//出力画像の表示
    cv::waitKey(); //キー入力待ち (止める)
    
    return 0;
}

