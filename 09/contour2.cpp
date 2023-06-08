//
//  contour4student.cpp
//
//
//  Created by Masashi Morimoto on 2022/06/07.
//

#include <iostream>
#include <opencv2/opencv.hpp>

//ファイル
#define FILE_NAME "../Debug/sample.jpg"
//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_BINARY "binary"
#define WINDOW_NAME_OUTPUT "output"

//二値化しきい値
#define BIN_TH (100)

int main(int argc, const char * argv[]) {
    //1. 画像の宣言 (入力画像，グレースケール画像，二値画像，一時的な画像，出力画像)
    cv::Mat src_img, gray_img, bin_img, tmp_img, dst_img;
    
    //2. 輪郭の座標リストの宣言 (New!)
    std::vector< std::vector< cv::Point > > contours;
    
    //3. 画像の入力 (カラーで入力)
    src_img = cv::imread(FILE_NAME);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    
    //4. 入力画像を出力画像にコピー (New!)
    dst_img = src_img.clone();
    //5. グレースケール化
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    //6. 二値化 (固定しきい値で実装．しきい値: 100)
    cv::threshold(gray_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);
    //二値画像コピー (New!)
    tmp_img = bin_img.clone();
    //7. 輪郭追跡 (New!)
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    //8. 輪郭の描画 (New!)
//    for (int i = 0; i < contours.size(); i++) {
//        cv::drawContours(dst_img, contours, i, CV_RGB(255, 0, 255), 3);
//    }
    //8.1 輪郭数の表示
    printf("輪郭数=%d\n",int(contours.size()));
    //8.2 表示する輪郭番号の入力
    int i;
    printf("輪郭番号？（0~%d）：",int(contours.size()-1));
    scanf("%d",&i);
    //8.3 領域特徴量の取得・表示
    double L,S;
    L = cv::arcLength(contours[i], true);
    S = cv::contourArea(contours[i]);
    
    printf("周囲長%lf 面積%lf \n",L,S);
    //8.4 外接長方形の取得
    cv::Rect bb;
    bb = cv::boundingRect(contours[i]);
    //8.5 外接長方形の描画
    cv::rectangle(dst_img, bb, CV_RGB(255, 0, 255), 3);
    //9. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_BINARY, bin_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
        
    return 0;
}

