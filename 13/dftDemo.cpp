//
//  dftDemo.cpp
//  dftDemo
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


//ウィンドウの名前
#define INPUT_WINDOW "original"
#define MAG_WINDOW "Magnitude"
#define DFT_WINDOW "DFT"
#define MASK_WINDOW "Mask"
#define RESULT_WINDOW "Result"

//画像 (グローバル変数)
cv::Mat real_mat; //実部 (実数)
cv::Mat imaginary_mat; //虚部 (実数)
cv::Mat mask_img; //マスク画像．マウスで色を塗っていく
cv::Mat complex_mat; //複素平面 (実部と虚部を持つ．2チャンネル)
cv::Mat complexFT_mat; //フーリエ変換後の複素平面 (実部と虚部を持つ．2チャンネル)
cv::Mat complexFT_tmp_mat; //フーリエ変換後の複素平面 (実部と虚部を持つ．2チャンネル)．一時的にコピーする
cv::Mat dst_img; //出力画像 (フーリエ変換->フーリエ逆変換)

double min, max; //最小値と最大値
bool mouse_down_flag = false; //マウスダウンのフラグ (false: 押していない)
bool circle_flag = false; //フラグがたったら，circleで描画

//フーリエ逆変換と表示
void showIDFT (void) {
    
    //まず象限の入れ替え (元に戻しておく)
    shiftDFT(complexFT_tmp_mat, complexFT_tmp_mat);
    
    //離散フーリエ変換
    cv::dft(complexFT_tmp_mat, complex_mat, cv::DFT_INVERSE);
    
    //----------------------------------------------------------------------
    //画像表示用ここから
    //実部と虚部に分ける
    std::vector<cv::Mat> vec_mat; //実部と虚部に分ける
    cv::split(complex_mat, vec_mat);
    //実部の最大値と最小値の取得
    cv::minMaxLoc(vec_mat[0], &min, &max);
    //実部を0-255にスケーリング
    vec_mat[0].convertTo(dst_img, dst_img.type(), 255.0 / (max-min), 255.0*(-min)/(max-min));
    
    cv::imshow(RESULT_WINDOW, dst_img);
}

// swap 1,3 and 2,4 quadrants respectively
//参考URL: http://opencv.jp/opencv2-x-samples/2d_dft_idft
/* 原点（直流成分）が画像の中心にくるように，画像の象限を入れ替える関数．
 src_arr, dst_arr は同じサイズ，タイプの配列 */
void
shiftDFT(cv::Mat &src, cv::Mat& dst)
{
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


//マスク用のコールバック関数
void maskDraw (int event, int x, int y, int flags, void *param) {
    //マウスイベントの確認
    switch (event) {
        case cv::EVENT_LBUTTONDOWN:
            mouse_down_flag = true; //マウスボタンのダウン
            //break;
        case cv::EVENT_MOUSEMOVE:
            if (mouse_down_flag == false) { //マウスがアップしている状態
                return;
            }
            
            if (circle_flag == false) {
                //色値の設定
                unsigned char s;
                s = 255;
                mask_img.at<unsigned char>(y, x) = s; //マウスでなぞったところを塗りつぶし
                
            }else{
                cv::circle(mask_img, cv::Point(x, y), 10, CV_RGB(255, 255, 255), -1);
            }
            cv::imshow(MASK_WINDOW, mask_img);  //マスク画像の表示
            //コピー
            complexFT_mat.copyTo(complexFT_tmp_mat, mask_img);
            
            //フーリエ逆変換の結果の表示
            showIDFT();
            break;
        case cv::EVENT_LBUTTONUP:
            mouse_down_flag = false; //マウスボタンのアップ
            break;
        default:
            break;
    }
}


int main(int argc, const char * argv[]) {
    cv::Mat src_img; //入力画像
    int key; //キー入力待ち用
    
    src_img = cv::imread(FILE_NAME, 0); //グレースケールで入力
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    
    //ウィンドウの設定
    cv::namedWindow(MASK_WINDOW);
    cv::setMouseCallback(MASK_WINDOW, maskDraw); //マスク用のコールバック関数

    //領域確保
    src_img.convertTo(real_mat, CV_64FC1);//実部
    imaginary_mat = cv::Mat::zeros(src_img.size(), CV_64FC1); //虚部 (初期化済み)
    complex_mat = cv::Mat(src_img.size(), CV_64FC2); //複素平面 (入力用)
    complexFT_mat = cv::Mat(src_img.size(), CV_64FC2); //複素平面 (フーリエ変換後)
    complexFT_tmp_mat = cv::Mat(src_img.size(), CV_64FC2); //複素平面 (フーリエ変換後)

    dst_img = cv::Mat::zeros(src_img.size(), CV_8UC1); //最終出力画像用 (初期化済み)
    mask_img = cv::Mat::zeros(src_img.size(), CV_8UC1); //マスク出力画像用 (初期化済み)
    cv::imshow(MASK_WINDOW, mask_img); //マスク画像の表示
    cv::imshow(RESULT_WINDOW, dst_img); //この時点で結果画像 (黒) の表示
    src_img.convertTo(real_mat, CV_64FC1); //入力画像をスケールを変えてコピー
    
    std::vector<cv::Mat> vec_mat1; //結合するためのベクトル
    vec_mat1.push_back(real_mat); //実部の登録
    vec_mat1.push_back(imaginary_mat); //虚部の登録
    cv::merge(vec_mat1, complex_mat); // 実部と虚部を合わせた変数にマージする
    
    //離散フーリエ変換
    cv::dft(complex_mat, complexFT_mat);
    //原点 (直流成分) 画像の中心にくるように，画像の象限をいれかえる
    shiftDFT(complexFT_mat, complexFT_mat);
    //ここまでがフーリエ変換
    
    //------------------------------------------------------------------
    //フーリエ変換画像の表示用ここから
    std::vector<cv::Mat> vec_mat2; //実部と虚部に分ける
    cv::split(complexFT_mat, vec_mat2);
    
    //スペクトルの振幅の計算 (Mag = sqrt(Re^2 + Im^2)
    cv::magnitude(vec_mat2[0], vec_mat2[1], vec_mat2[0]);
    cv::log(vec_mat2[0]+1, vec_mat2[0]); // 振幅の対数をとる log(1 + Mag)
    
    //振幅画像のピクセル値が0.0-1.0に分布するようにスケーリング
    cv::normalize(vec_mat2[0], real_mat, 0, 1, cv::NORM_MINMAX);
    cv::imshow(MAG_WINDOW, real_mat);
    
    //表示用ここまで
    //------------------------------------------------------------------
    
    
    //表示
    cv::imshow(INPUT_WINDOW, src_img);
    
    while (1) {
        key = cv::waitKey(30);
        if (key == 'q') {
            break;
        }else if (key == '0') {
            mask_img.setTo(0); //マスクの初期化
            cv::imshow(MASK_WINDOW, mask_img); //マスク画像の表示
            complexFT_tmp_mat.setTo(0); //フーリエ変換後の画像の初期化
            //フーリエ逆変換の結果の表示
            showIDFT();
        }else if (key == 'c') {
            //円か点の切り替え
            circle_flag = !circle_flag;
        }
    }
    
    return 0;
}
