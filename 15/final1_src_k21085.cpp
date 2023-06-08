#include <iostream>
#include <opencv2/opencv.hpp>

//----------------------------

//全体の画像 (探索対象画像) のファイル名
#define TARGET_IMG_FILE "../Debug/input1.jpg"

//テンプレート画像
#define TEMPLATE_NUM (8)

//----------------------------


int main (int argc, const char * argv[]){
    //手順：必要画像読み込み　→　類似度マップ作成　→ （これを8回繰り返す）類似度マップの閾値を調べ、閾値が最小の時のx,y座標記録。
    cv::Mat src_img, compare_img;
    //入力画像読み込み
    src_img = cv::imread(TARGET_IMG_FILE);
    //画像読み込みのテンプレート
    cv::Mat template_img[TEMPLATE_NUM];
    char buf[256];
    for (int i=0; i < TEMPLATE_NUM; i++) {
        sprintf(buf, "template-%d.jpg", i);
        //fprintf(stderr, "%s\n", buf);
        template_img[i] = cv::imread(buf);
        if (template_img[i].empty()) {
            fprintf(stderr, "%s cannot be opened.", buf);
            return 0;
        }
    }
    //画像読み込みに成功したか判定
    if(src_img.empty()) {
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    float s,min = 1.0; //類似度マップはfloat型
    int min_x,min_y;
    //類似度マップを入力画像-テンプレート+1 1チャンネルで作成
    compare_img = cv::Mat(cv::Size(src_img.rows - template_img[0].rows + 1, src_img.cols - template_img[0].cols + 1), CV_32F, 1);
    //テンプレートが8枚あるので8回繰り返す
    for (int i = 0; i < TEMPLATE_NUM; i++) {
        cv::matchTemplate(src_img, template_img[i], compare_img, cv::TM_SQDIFF_NORMED);
        //類似度マップで画像操作
        for (int y = 0; y < compare_img.rows; y++) {
            for (int x = 0; x < compare_img.cols; x++) {
                //閾値を取得してそれが一番小さい座標を記録
                s = compare_img.at<float>(y, x);
                if (s < min) {
                    min = s;
                    min_x = x;
                    min_y = y;
                }
            }
        }
        //結果表示とmin変数リセット
        fprintf(stderr, "%d,%d\n",min_x,min_y);
        min = 1.0;
    }
    cv::waitKey(0);


    return 0;
}
