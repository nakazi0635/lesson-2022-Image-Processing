//
//  extractRegion.cpp
//  
//
//  Created by Masashi Morimoto on 2022/06/22.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../Debug/hand.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define H (15) //Hのしきい値
#define H_MAX (30)
#define H_MIN (0)
#define V (200) //Vのしきい値
#define WHITE_PIXEL (255) // 出力画像の値（白）

int main(int argc, const char * argv[]) {
    //変数の宣言
    int x, y; //走査用
    cv::Vec3b p; //色値
    
    //画像の宣言 (入力画像，出力画像)
    cv::Mat src_img, dst_img, hsv_img;
    
    // 1. カラー画像の入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);
    

    // 3. しきい値処理
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            p = hsv_img.at<cv::Vec3b>(y, x);
            if (p[0] > H_MIN && p[0] < H_MAX) {
                p[0] = H;
                hsv_img.at<cv::Vec3b>(y, x) = p;
            }
        }
    }
    
    cv::cvtColor(hsv_img, dst_img, cv::COLOR_HSV2BGR);
    
    // 4. 表示
    cv::imshow(WINDOW_NAME_INPUT , src_img);//入力画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);//出力画像の表示
    cv::waitKey(); //キー入力待ち (止める)
    
    return 0;
}
