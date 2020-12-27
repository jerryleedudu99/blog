#include<iostream>
#include<vector>
#include<iterator>
#include<string>
#include<map>
using namespace std;

/*存储每一只牛的坐标及状态*/
class  Cow {
public:
	char direction;
	int x;
	int y;
	int x_pre, y_pre;//重点，需要保存移动前的坐标，后续会用到
	int selfgrass = 0;
	int state = 0;//0代表运动中，1代表停下；
public:
	void move() {
		x_pre = x;
		y_pre = y;
		if (this->direction == 'N') {
			y++;
		}
		else if (this->direction == 'E') {
			x++;
		}
		selfgrass++;//如果奶牛可以运动，则所吃的草格数必加一
	}
};
int main() {
	int max_x = 0;
	int max_y = 0;
	int N;
	cin >> N;
	Cow cows[50];
	map<string, int> location;//键值对用来记录已经被吃掉的草原的坐标，string为x y；int为1代表已被吃掉；

	/* 输入奶牛的方向及初始坐标*/
	for (int i = 0; i < N; i++) {
		cin >> cows[i].direction >> cows[i].x >> cows[i].y;
		cows[i].x_pre = cows[i].x;
		cows[i].y_pre = cows[i].y;
		//string dir = to_string(cows[i].x) + ' ' + to_string(cows[i].y);
		//location[dir] = 1; 位置上的草被吃掉了
		if (cows[i].x > max_x) {
			max_x = cows[i].x;
		}
		if (cows[i].y > max_y) {
			max_y = cows[i].y;
		}
	}
	int loop = max_x + max_y;//奶牛走的步数最大不会超过这个上界
	for (int i = 0; i < loop; i++) {//每一小时奶牛运动的一轮变化
		for (int j = 0; j < N; j++) {
			if (cows[j].state == 0) {//如果奶牛还在运动中
				string cow_location = to_string(cows[j].x) + ' ' + to_string(cows[j].y);
				map<string, int>::iterator iter = location.find(cow_location);
				if (iter != location.end()) {//判断地图上当前所在方格的草已经被吃掉了
					cows[j].state = 1;//此奶牛停止运动
				}
				else {//没有被吃掉 do not found
					//location[cow_location] = 1;
					cows[j].move();//奶牛移动一步
				}
			}
		}
		/*这里之所以需要重新判段是因为，有可能出现两只奶牛同在一个方格的情况，因此当本轮的所有奶牛都走完，再记录地图已被吃掉的情况*/
		for (int j = 0; j < N; j++) {
			if (cows[j].state == 0) {
				string cow_prelocation = to_string(cows[j].x_pre) + ' ' + to_string(cows[j].y_pre);//奶牛已经移动，被吃掉的上一步的草
				location[cow_prelocation] = 1;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		if (cows[i].selfgrass == loop) {//奶牛将永远不会停下
			cout << "Infinity" << endl;
		}
		else {
			cout << cows[i].selfgrass << endl;
		}
	}

}
