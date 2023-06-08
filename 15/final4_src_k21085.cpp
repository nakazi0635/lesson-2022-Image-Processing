#include <iostream>
#include <opencv2/opencv.hpp>

//----------------------------

//全体の画像 (探索対象画像) のファイル名
#define TARGET_IMG_FILE "../Debug/input1.jpg"

//テンプレート画像
#define TEMPLATE_NUM (8)
//右側につながる画像がないことを表す−１の閾値
#define Upper_limit (12000)
//----------------------------


int main (int argc, const char * argv[]){
    
    //テンプレート画像を読み込むためのテンプレート
    cv::Mat template_img[TEMPLATE_NUM];
    char buf[256];
    for (int i=0; i < TEMPLATE_NUM; i++) {
        sprintf(buf, "template-%d.jpg", i);
        template_img[i] = cv::imread(buf);
        if (template_img[i].empty()) {
            fprintf(stderr, "%s cannot be opened.", buf);
            return 0;
        }
    }
    
    cv::Vec3b val_right,val_left;
    
    int i,j,min_img = 10;
    int min = 100000,judge = 0;
    
    //手順：テンプレート0番目の右側とテンプレート0-8番目の左側の色値の誤差の絶対値を取る
    //→色値の誤差の絶対値の合計が一番小さい画像を記録し、結果を表示。これをテンプレートの枚数繰り返す。
    for (i = 0; i < TEMPLATE_NUM; i++) {
        for (j = 0; j < TEMPLATE_NUM; j++) {
            for (int y = 0; y < template_img[i].rows; y++){
                //右側の色値をとる
                val_right = template_img[i].at<cv::Vec3b>(y,template_img[i].cols-1);
                //左側の色値をとる
                val_left = template_img[j].at<cv::Vec3b>(y,0);
                //誤差の絶対値を足していく
                judge += abs(val_left[0]-val_right[0]);
                judge += abs(val_left[1]-val_right[1]);
                judge += abs(val_left[2]-val_right[2]);
            }
            //誤差の絶対値を足した変数が一番小さい画像番号を記録
            if (min > judge) {
                min = judge;
                min_img = j;
            }
            //変数リセット
            judge = 0;
        }
        //右側につながる画像がないことを表す−１の閾値
        if (min > Upper_limit) {
            min_img = -1;
        }
        //結果を表示
        fprintf(stderr, "%d -> %d \n",i,min_img);
        //変数リセット
        min = 100000;
        min_img = 10;
    }
    
    
    cv::waitKey(0);
    return 0;
}


