#include <iostream>
#include "the-third-party/json.hpp"
#include <Windows.h>
#include <chrono>
#include <conio.h>
#include <vector>

using namespace std;
using namespace std::chrono;
using json = nlohmann::json;

json frame_table;
vector<chrono::time_point<system_clock>> frame_time_point;

float measure_time(int frame_number) {

    // auto duration_us = duration_cast<microseconds>(end - start);  // 计算时间差（微秒）
    // float duration_ms = static_cast<float>(duration_us.count()) / 1000.0f;  // 转换为毫秒（float类型）
    // return duration_ms;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    cout << "Ae帧时间助手：\n心里想着你的关键帧的节奏，在你认为需要关键帧的点按下空格键，然后按下ALT键结束记录，程序就会记录你所有关键帧的间隔以及其在不同帧速率下的帧数" << endl;
    cout << "==========================" << endl;

    while (true) {
        cout << "按下空格键以开始计时，按空格键打点，按下ALT键结束..." << endl;
        // 等待初始空格键按下
        while (!(GetAsyncKeyState(VK_SPACE) & 0x8000)) {
            Sleep(10);
            // 按ESC键退出程序
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                return 0;
            }
        }
        int frame = 0;
        frame_time_point.clear();
        frame_table.clear();
        while (true) {
            if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                frame_time_point.push_back(high_resolution_clock::now());
                while (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                    // 空循环等待释放
                }
                // 等待空格键按下（停止）
                cout << "打了第" << frame+1 << "个关键帧" << endl;
                frame += 1;
                // 等待空格键释放后再继续
                while (GetAsyncKeyState(VK_SPACE) & 0x8000) {

                }
            }
            // 按下ALT键停止
            if (GetAsyncKeyState(18) & 0x8000) {
                break;
            }
        }

        for (int i = 0;i<frame_time_point.size() - 1;i++) {
            auto time0 = frame_time_point[i];
            auto time1 = frame_time_point[i+1];
            auto duration_us = duration_cast<microseconds>(time1 - time0);
            float duration_ms = static_cast<float>(duration_us.count()) / 1000.0f;
            frame_table[to_string(i+1) + "-to-" + to_string(i+2)]["time-ms"] = duration_ms;
            frame_table[to_string(i+1) + "-to-" + to_string(i+2)]["120fps"] = floor(duration_ms / 8.3);
            frame_table[to_string(i+1) + "-to-" + to_string(i+2)]["60fps"] = floor(duration_ms / 16.7);
            frame_table[to_string(i+1) + "-to-" + to_string(i+2)]["30fps"] = floor(duration_ms / 33.3);
            frame_table[to_string(i+1) + "-to-" + to_string(i+2)]["24fps"] = floor(duration_ms / 42.0);
        }

        cout << frame_table.dump(4) << endl;

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }
    }
    return 0;
}
