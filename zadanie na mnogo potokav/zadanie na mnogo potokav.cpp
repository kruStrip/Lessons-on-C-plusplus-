#include <iostream>
#include <thread>
#include <vector>
#include <Windows.h>


void menshe(std::vector <int>* mal, std::vector <int>* nums, int count) {
    while (count != 0) {
        for (int i = 0; i < (count - 1); i++) {
            if ((*mal)[i] >= (*mal)[i + 1]) {
                (*nums)[i] = (*mal)[i + 1];
                (*mal)[i + 1] = (*mal)[i];
            }
            else {
                (*nums)[i] = (*mal)[i];
            }
        }
        count--;
    }
}
void bolshe(std::vector <int>* bol, std::vector <int>* nums, int count) {
    int size = count;
    while (count != 0) {
        for (int i = size; i < (count + (*bol).size() - 1); i++) {
            if ((*bol)[i - size] <= (*bol)[i - size + 1]) {
                (*nums)[i] = (*bol)[i - size + 1];
                (*bol)[i - size + 1] = (*bol)[i - size];
            }
            else {
                (*nums)[i] = (*bol)[i - size];
            }
        }
        count--;
    }
}

int main()
{
    setlocale(LC_ALL, "");
    std::vector <int> nums = {1, -2, 3, 4, 0, 6, -7, 8, 9, -1};
    std::vector <int> mal = {};
    std::vector <int> bol = {};
    int countMal = 0;
    int countBol = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] <= 0) {
            mal.push_back(nums[i]);
            countMal++;
        }
        else {
            bol.push_back(nums[i]);
            countBol++;
        }
    }
    std::thread thr1(menshe, &mal, &nums, countMal);
    std::thread thr2(bolshe, &bol, &nums, countMal);
    Sleep(1000);

    for (int i = 0; i < nums.size(); i++) {

        std::cout << nums[i] << "\n";
    }

    thr1.join();
    thr2.join();
}
