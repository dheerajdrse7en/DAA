#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<unordered_set>
using namespace std;

int main(){
    srand(time(0));
    unordered_set<int> nums;
    int count=10000;
    while(nums.size()<count){
        int num=rand()%20000+1;
        nums.insert(num);
    }
    ofstream f1("frame_sizes.txt");
    for(int num:nums){
        f1 << num << endl;
    }        
    f1.close();
    return 0;
}