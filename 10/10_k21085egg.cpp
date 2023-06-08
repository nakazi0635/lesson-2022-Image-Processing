#include <iostream>
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME_1 "../Debug/challenge.jpg"

#define TH (200)


#define WINDOW_NAME_INPUT_1 "input"
#define WINDOW_NAME_OUTPUT "output"
#define WINDOW_NAME_OUTPUT_2 "output_2"

int main(int argc, const char * argv[]) {

    
    
    
    //1. 画像の宣言 (入力画像，グレースケール画像，二値画像，一時的な画像，出力画像)
    cv::Mat src_img, gray_img, bin_img, tmp_img, dst_img;

    //色値の設定
    
    //2. 輪郭の座標リストの宣言
    std::vector< std::vector< cv::Point > > contours;
    
    src_img = cv::imread(FILE_NAME_1);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    
    
    //4. 入力画像を結果画像にコピー
    dst_img = src_img.clone();
    
    //5. グレースケール化
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    //6. 二値化 (固定閾値で実装．閾値: 100)
    cv::threshold(gray_img, bin_img, TH, 255, cv::THRESH_BINARY);
    
    //二値画像コピー
    tmp_img = bin_img.clone();
    
    //7. 輪郭抽出
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    
    int count = 0;
    //8. 輪郭の描画
    for (int i=0; i<contours.size(); i++) {
        if (cv::contourArea(contours[i]) < 50) {
            cv::drawContours(tmp_img, contours, i, CV_RGB(0, 0, 0), cv::FILLED);
        }else{
            //printf("%d\n",contours[i].size());
            count++;
        }
    }
    printf("%d\n",count);
    //出力
    cv::imshow(WINDOW_NAME_INPUT_1, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, bin_img);
    cv::imshow(WINDOW_NAME_OUTPUT_2, tmp_img);
    cv::waitKey();

    return 0;
}
