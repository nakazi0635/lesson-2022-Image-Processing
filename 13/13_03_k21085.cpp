//
//  dft4student.cpp
//
//  Created by sawano on 2020/07/07.
//  Copyright © 2020年 AIT. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

//プロトタイプ宣言
void shiftDFT (cv::Mat &src, cv::Mat& dst);

//ファイル名
#define FILE_NAME "Fourier.jpg"

//ウィンドウ名
#define INPUT_WINDOW "input"
#define MAG_WINDOW "Magnitude"
#define RESULT_WINDOW "Result"

// swap 1,3 and 2,4 quadrants respectively
//参考URL: http://opencv.jp/opencv2-x-samples/2d_dft_idft
/* 原点（直流成分）が画像の中心にくるように，画像の象限を入れ替える関数．
 src_arr, dst_arr は同じサイズ，タイプの配列 */
void shiftDFT(cv::Mat &src, cv::Mat& dst){
    cv::Mat tmp;
    int cx = src.cols/2;
    int cy = src.rows/2;
    
    for(int i=0; i<=cx; i+=cx) {
        cv::Mat qs(src, cv::Rect(i^cx,0,cx,cy));
        cv::Mat qd(dst, cv::Rect(i,cy,cx,cy));
        qs.copyTo(tmp);
        qd.copyTo(qs);
        tmp.copyTo(qd);
    }
}


int main(int argc, const char * argv[]) {
    cv::Mat src_img; //入力画像
    cv::Mat real_mat; //実部 (実数)
    cv::Mat imaginary_mat; //虚部 (実数)
    cv::Mat complex_mat; //複素平面 (実部と虚部を持つ．2チャンネル)
    cv::Mat complexFT_mat; //フーリエ変換後の複素平面 (実部と虚部を持つ．2チャンネル)
    cv::Mat dst_img; //出力画像 (フーリエ変換->フーリエ逆変換)
    double min, max;
    
    src_img = cv::imread(FILE_NAME, 0); //グレースケールで入力
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    
    //領域確保
    src_img.convertTo(real_mat, CV_64FC1);//実部
    imaginary_mat = cv::Mat::zeros(src_img.size(), CV_64FC1); //虚部 (初期化済み)
    complex_mat = cv::Mat(src_img.size(), CV_64FC2); //複素平面 (入力用)
    complexFT_mat = cv::Mat(src_img.size(), CV_64FC2); //複素平面 (フーリエ変換後)
    dst_img = cv::Mat::zeros(src_img.size(), CV_8UC1); //最終出力画像用 (初期化済み)

    std::vector<cv::Mat> vec_mat1; //結合するためのベクトル
    vec_mat1.push_back(real_mat); //実部の登録
    vec_mat1.push_back(imaginary_mat); //虚部の登録
    cv::merge(vec_mat1, complex_mat); // 実部と虚部を合わせた変数にマージする
    
    //離散フーリエ変換
    cv::dft(complex_mat, complexFT_mat);
    
    //ここまでがフーリエ変換
    //------------------------------------------------------------------
    //ローパスフィルタ，ハイパスフィルタ
    
    //原点 (直流成分) 画像の中心にくるように，画像の象限をいれかえる
    shiftDFT(complexFT_mat, complexFT_mat);
    
    
    cv::Vec2d s; //色値
    s[0] = s[1] = 0.0;
    int cx = complexFT_mat.cols / 2;
    int cy = complexFT_mat.rows / 2;
    
    for (int y=0; y<complexFT_mat.rows; y++) {
        for (int x=0; x<complexFT_mat.cols; x++) {
            
            double dist = sqrt((cx-x)*(cx-x) + (cy-y)*(cy-y));
            if(cx - 50 <= x && cx + 50 >= x && cy - 50 <= y && cy + 50 >= y){
                complexFT_mat.at<cv::Vec2d>(y, x) = s;
            }
        }
    }
    
    
    //------------------------------------------------------------------
    //フーリエ変換画像の表示用ここから
    std::vector<cv::Mat> vec_mat2; //実部と虚部に分ける
    cv::split(complexFT_mat, vec_mat2);
    
    //スペクトルの振幅の計算 (Mag = sqrt(Re^2 + Im^2)
    cv::magnitude(vec_mat2[0], vec_mat2[1], vec_mat2[0]);
    cv::log(vec_mat2[0]+1, vec_mat2[0]); // 振幅の対数をとる log(1 + Mag)
    
    //振幅画像のピクセル値が0.0-1.0に分布するようにスケーリング
    cv::normalize(vec_mat2[0], real_mat, 0, 1, cv::NORM_MINMAX);
    
    
    //表示用ここまで
    //------------------------------------------------------------------
    //ここからがフーリエ逆変換
    //まず象限の入れ替え
    shiftDFT(complexFT_mat, complexFT_mat);
    
    //ここからがフーリエ逆変換
    //まず象限の入れ替え
    cv::dft(complexFT_mat, complex_mat, cv::DFT_INVERSE);
    //----------------------------------------------------------------------
    //画像表示用ここから
    //実部と虚部に分ける
    std::vector<cv::Mat> vec_mat; //実部と虚部に分ける
    cv::split(complex_mat, vec_mat);
    //実部の最大値と最小値の取得
    cv::minMaxLoc(vec_mat[0], &min, &max);
    //実部を0-255にスケーリング
    vec_mat[0].convertTo(dst_img, dst_img.type(), 255.0 / (max-min), 255.0*(-min)/(max-min));
    
    //画像の表示
    cv::imshow(INPUT_WINDOW, src_img);
    cv::imshow(RESULT_WINDOW, dst_img);
    cv::imshow(MAG_WINDOW, real_mat);
    
    //キー入力待ち
    cv::waitKey();
    
    return 0;
}
