//
//  labeling.cpp
//  
//
//  Created by b21702bb on 2021/06/22.
//

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

//ファイル
#define FILE_NAME "../Debug/labeling.jpg"
//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_BINARY "binary"
#define WINDOW_NAME_OUTPUT "output"

//二値化閾値
#define BIN_TH (100)


int main(int argc, const char * argv[]) {
    //1. 画像の宣言 (入力画像，グレースケール画像，二値画像，一時的な画像，出力画像)
    cv::Mat src_img, gray_img, bin_img, tmp_img, dst_img;

    //色値の設定
    
    //2. 輪郭の座標リストの宣言
    std::vector< std::vector< cv::Point > > contours;
    
    //3. 画像の入力 (カラーで入力)
    src_img = cv::imread(FILE_NAME);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    
    //4. 入力画像を結果画像にコピー
    dst_img = src_img.clone();
    
    //5. グレースケール化
    cv::cvtColor(src_img, gray_img,cv::COLOR_BGR2GRAY);
    
    //6. 二値化 (固定閾値で実装．閾値: 100)
    cv::threshold(gray_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);
    
    //二値画像コピー
    tmp_img = bin_img.clone();
    
    //7. 輪郭抽出
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    
    cv::Scalar color[]{
        CV_RGB(255, 0, 0),
        CV_RGB(0, 255, 0),
        CV_RGB(0, 0, 255),
        CV_RGB(255, 0, 255)
    };
    
    
    //8. 輪郭の描画
    for (int i=0; i<contours.size(); i++) {
        //輪郭の描画
        cv::drawContours(dst_img, contours, i, color[i%contours.size()], cv::FILLED);
    }
    
    //9. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_BINARY, bin_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    
    
    return 0;
}
