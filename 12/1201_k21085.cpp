


#include <iostream>
#include <opencv2/opencv.hpp>

//----------------------------

//全体の画像 (探索対象画像) のファイル名
#define TARGET_IMG_FILE "../Debug/gazoDora.jpg"

//テンプレート画像
#define TEMPLATE_IMG_FILE_1 "../Debug/green.jpg"
#define TEMPLATE_IMG_FILE_2 "../Debug/red.jpg"
#define TEMPLATE_IMG_FILE_3 "../Debug/star.jpg"
#define TEMPLATE_IMG_FILE_4 "../Debug/yellow.jpg"

//----------------------------
cv::Mat src_img, result_img;
cv::Mat template1_img, template2_img, template3_img, template4_img;
cv::Mat compare_img;

void paint(cv::Mat temp, int r, int g, int b){
    compare_img = cv::Mat(cv::Size(src_img.rows - temp.rows + 1, src_img.cols - temp.cols + 1), CV_32F, 1);

    cv::matchTemplate(src_img, temp, compare_img, cv::TM_SQDIFF_NORMED);
    float s;
    //類似度マップの最小値最大値の計算
    for (int y = 0; y < compare_img.rows; y++) {
        for (int x = 0; x < compare_img.cols; x++) {
            s = compare_img.at<float>(y, x);
            if (s < 0.1) {
                cv::rectangle(result_img, cv::Point(x,y), cv::Point(x + temp.cols, y + temp.rows), CV_RGB(r, g, b),3);
            }
        }
    }
}


int main (int argc, const char * argv[]){
    double min_val, max_val;
    cv::Point min_loc, max_loc;
    
    //入力画像
    src_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_COLOR);
    
    result_img = cv::Mat(src_img.size(), CV_8UC1);
    result_img = src_img.clone(); //画像のコピー
    //テンプレート画像
    template1_img = cv::imread(TEMPLATE_IMG_FILE_1, cv::IMREAD_COLOR);
    template2_img = cv::imread(TEMPLATE_IMG_FILE_2, cv::IMREAD_COLOR);
    template3_img = cv::imread(TEMPLATE_IMG_FILE_3, cv::IMREAD_COLOR);
    template4_img = cv::imread(TEMPLATE_IMG_FILE_4, cv::IMREAD_COLOR);
    
    if(src_img.empty()||template1_img.empty()||template2_img.empty()||template3_img.empty()||template4_img.empty()) {
        fprintf(stderr, "File is not opened.\n");
        
        return (-1);
    }
    
    paint(template1_img, 62, 179, 112);
    paint(template2_img, 255, 0, 0);
    paint(template3_img, 139, 82, 161);
    paint(template4_img, 255, 241, 112);
    
    cv::imshow("input", src_img);
    cv::imshow("template1", template1_img);
    cv::imshow("result", result_img);
    //キー入力待ち
    cv::waitKey(0);


    return 0;
}


