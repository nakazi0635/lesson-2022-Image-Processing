#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "../Debug/input1.jpg"
#define WINDOW_NAME "intput"
#define WINDOW_NAME_A "output"
#define WINDOW_NAME_A_2 "output2"
#define R_MIN (225) //Rの最小値
#define R_MAX (255) //Rの最大値
#define G_MIN (50) //Gの最小値
#define G_MAX (200) //Gの最大値
#define B_MIN (50) //Bの最小値
#define B_MAX (200) //Bの最大値
#define Black_MIN (0) //Blackを判定するための最大値
#define Black_MAX (50) //Blackを判定するための最大値

#define MAX_VAL (255)//白画素
#define COUNT (10)//拡張収縮関数
#define TH (50) //色値
#define HIGHVAL (255) //色値

//拡張収縮関数
void expansion_contraction(cv::Mat &dst){
    cv::dilate(dst, dst, cv::Mat(), cv::Point(-1,-1), COUNT);
    cv::erode(dst, dst, cv::Mat(), cv::Point(-1,-1), COUNT*2);
    cv::dilate(dst, dst, cv::Mat(), cv::Point(-1,-1), COUNT);
}


int main(int argc, const char * argv[]) {
    //輪郭の座標リストの宣言
    std::vector< std::vector< cv::Point > > contours;
    //元画像、答え画像、if文内で使う二値化画像
    cv::Mat src_img,ans_img,insect_img;
    
    //画像の読み込み
    src_img = cv::imread(FILE_NAME);
    //元画像コピー
    ans_img = src_img.clone();
    //色値
    cv::Vec3b p;
    //二値化画像を用意する
    insect_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    
    //元画像で走査
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            //元画像の各画素のBGR値を取得。defineで指定したそれぞれの値で、RGBで赤色と黒色を判定
            p = src_img.at<cv::Vec3b>(y, x);
            if ((p[0] >= B_MIN && p[0] <=B_MAX && p[1] >= G_MIN && p[1] <=G_MAX && p[2] >= R_MIN && p[2] <=R_MAX)  ||
                (p[0] >= Black_MIN && p[0] <= Black_MAX && p[1] >= Black_MIN && p[1] <= Black_MAX && p[2] >= Black_MIN && p[2] <= Black_MAX)) {
                // 閾値条件が適合したら二値化した画像に白画素を入れる
                insect_img.at<uchar>(y,x) = MAX_VAL;
            }
        }
    }
    //拡張収縮を行い、関係ないところを取り除く
    expansion_contraction(insect_img);
    
    //輪郭追跡関数
    cv::findContours(insect_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    //長方形描画関数(今回は1つしかないが)contoursの数だけ繰り返す
    for (int i=0; i<contours.size(); i++) {
        cv::Rect bb = cv::boundingRect(contours[i]);
        //描画
        cv::rectangle(ans_img, bb, CV_RGB(0, 0, 0), 3);
    }
    //輪郭の座標リストをクリア
    contours.clear();
    
    //元画像の表示
    cv::imshow(WINDOW_NAME, src_img);
    //答えの画像の表示
    cv::imshow(WINDOW_NAME_A, ans_img);
    
    cv::waitKey();

    return 0;
}

