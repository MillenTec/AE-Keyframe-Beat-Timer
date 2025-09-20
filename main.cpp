#include <iostream>
#include "the-third-party/json.hpp"
#include <Windows.h>
#include <chrono>
#include <conio.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
using namespace std::chrono;
using json = nlohmann::json;

json frame_array = json::array();
vector<chrono::time_point<system_clock> > frame_time_point;

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
        frame_array.clear();
        while (true) {
            if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                frame_time_point.push_back(high_resolution_clock::now());
                while (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                    // 空循环等待释放
                }
                // 等待空格键按下（停止）
                cout << "打了第" << frame + 1 << "个关键帧" << endl;
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

        for (int i = 0; i < frame_time_point.size() - 1; i++) {
            json frame_table;
            auto time0 = frame_time_point[i];
            auto time1 = frame_time_point[i + 1];
            auto duration_us = duration_cast<microseconds>(time1 - time0);
            float duration_ms = static_cast<float>(duration_us.count()) / 1000.0f;
            frame_table["..from"]=i + 1;  //".."是为了改变排序
            frame_table["..to"]=i + 2;
            frame_table[".time-ms"] = duration_ms;
            frame_table["120fps"] = floor(duration_ms / 8.3);
            frame_table["60fps"] = floor(duration_ms / 16.7);
            frame_table["30fps"] = floor(duration_ms / 33.3);
            frame_table["24fps"] = floor(duration_ms / 42.0);
            frame_array.push_back(frame_table);
        }

        cout << frame_array.dump(4) << endl;
        cout << "记录以完成，您接下来可以使用一些命令进行操作，输入“help”获取帮助" << endl;
        while (true) {
            string command;
            cout << ">";
            getline(cin, command);
            if (command == "help") {
                cout << "save       保存文件" << endl
                     << "set_frame  自定义帧速率" << endl
                     << "print      打印文件" << endl
                     << "repeat     再次记录" << endl
                     << "exit       退出程序" << endl
                     << "help       显示帮助" << endl;
            } else if (command == "save") {
                string file_name;
                cout << "请输入文件名：";
                getline(cin, file_name);
                ofstream out(file_name + ".json");
                if (out) {
                    out << frame_array.dump(4);
                    cout << "文件保存成功！" << endl;
                } else {
                    cerr << "文件保存失败！" << endl;
                }
            } else if (command == "set_frame") {
                float user_frame;
                json user_array = json::array();
                cout << "请输入帧速率：";
                cin >> user_frame;
                for (int i = 0; i < frame_time_point.size() - 1; i++) {
                    json user;
                    auto time0 = frame_time_point[i];
                    auto time1 = frame_time_point[i + 1];
                    auto duration_us = duration_cast<microseconds>(time1 - time0);
                    float duration_ms = static_cast<float>(duration_us.count()) / 1000.0f;
                    user["..from"]=i + 1;
                    user["..to"]=i + 2;
                    user[".time-ms"] = duration_ms;
                    user[to_string(user_frame) + "fps"] = floor(duration_ms / (1 / user_frame * 1000));
                    user_array.push_back(user);
                }
                for (int i = 0; i < user_array.size(); i++) {
                    frame_array[i][to_string(user_frame) + "fps（user_set）"] = user_array[i][to_string(user_frame) + "fps"];
                }
                cout << user_array.dump(4) << endl;
            } else if (command == "exit") {
                return 0;
            } else if (command == "repeat") {
                break;
            } else if (command == "print") {
                cout << frame_array.dump(4) << endl;
            } else {
                cout << "无可用命令" << endl;
            }
        }
    }
    return 0;
}
