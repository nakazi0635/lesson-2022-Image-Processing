//
//  colorBar.cpp
//  
//
//  Created by Masashi Morimoto on 2022/06/21.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define IMG_WIDTH (180) //画像の幅
#define IMG_HEIGHT (100) //画像の高さ
#define HUE_MAX (180) //Hの最大
#define SAT_MAX (255) //Sの最大
#define VAL_MAX (255) //Vの最大

int main(int argc, const char * argv[]) {
    //1. 変数の宣言
    int h, y; //色相と画像の縦方向位置
    cv::Vec3b p; //色値(HSV)
    
    //2. HSV画像・BGR画像領域の確保 3チャンネル画像
    cv::Mat hsv_img, bgr_img;
    hsv_img = cv::Mat(cv::Size(IMG_WIDTH, IMG_HEIGHT), CV_8UC3);
    bgr_img = cv::Mat(cv::Size(IMG_WIDTH, IMG_HEIGHT), CV_8UC3);
    
    //3. カラーバーの作成
    for (h=0; h<HUE_MAX; h++) { //Hの値を1つずつ変化させる (0→179)
        p[0] = h;
        p[1] = SAT_MAX;
        p[2] = VAL_MAX;
        
        for (y=0; y<IMG_HEIGHT; y++) {  //色値をセット　縦方向は同じ
            hsv_img.at<cv::Vec3b>(y, h) = p;
        }
    }

    //4. 色変換 (HSV → BGR)
    
    cv::cvtColor(hsv_img, bgr_img, cv::COLOR_HSV2BGR);

    //5. 表示
    cv::imshow("Hue Bar", bgr_img);
    cv::waitKey();
    return 0;
}
