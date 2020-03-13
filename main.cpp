#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <windows.h>
using namespace std;
string name[10000];
int HP[10000];
int n;
int temp;// 
bool is_TL;//是否在推理 
int TL_from;//推理者编号 
int TL_step = 5;//推理余剩步数 
void kill(int from,int to);//攻击
void message(int from,int to);//向控制台发送死亡信息
void LJS(int from);//雷击术
void TL(int from);//推理
void FX(int from);//推理后的发现
int main() {
	srand(int(time(NULL)));//设置伪随机数生成种子 
	cout << "欢迎来到MD5大作战!";//欢迎 
	Sleep(1000);//延时1秒 
	system("cls");//清屏 
	cout << "请输入游戏人数:";//提示 
	cin >> n;//输入游戏人数 
	system("cls");//清屏
	for(int i = 1; i <= n; i ++) {//输入玩家名称 
		cout << "玩家" << i << "名称:";//提示 
		cin >> name[i];//输入玩家名称  
		HP[i] = (rand() * 12345 % 200) + 100;//随机设定血量 
	}
	system("cls");//清屏
	cout << "开始游戏!";//提示开始 
	Sleep(1000);//延时 
	system("cls");//清屏 
	temp = n;//设定游戏剩余玩家数量 
	while(temp > 1) {//如果还有一个以上玩家 
		if(TL_step == 0){
			FX(TL_from);
			continue;
		}
		int opr = rand() % 14;//随机设定操作号 
		if(opr >= 11 && opr <= 13) {//推理 
			if(!is_TL) {
				int f;
				for(f = 1; f <= n; f ++) {
					if(HP[f] > 0) {
						TL(f);
						break;
					}
				}
			}
		}
		if(opr >= 4 && opr <= 10) {
			int t,f;
			for(f = 1; f <= n; f ++) {
				if(HP[f] > 0) {
					for(t = 1; t <= n; t ++) {
						if(HP[t] > 0) {
							if(f != t) {
								Sleep(rand() % 200 + 100);
								kill(t,f);
								break;
							}
						}
					}
				}
			}
		}
		if(opr >= 1 && opr <= 3) {
			int f = 9999;
			while(HP[f] == 0)f = rand() * 12 % n;
			Sleep(rand() % 200 + 100);
			LJS(f);
		}
	}
	for(int i = 1; i <= n; i ++) {
		if(HP[i] > 0) {
			cout << "赢家:" << name[i] << ",剩余血量:" << HP[i] << ".";
			break;
		}
	}
	fclose(stdin);
	return 0;
}
void kill(int from,int to) {//攻击
	int SH = rand() % (HP[to]) + 20;
	HP[to] -= SH;
	cout << name[to] << "被" << name[from] << "攻击,扣去" << SH << "滴血";
	if(HP[to] <= 0) {
		cout << "." << endl;
		message(from,to);
	} else {
		cout << ",剩余" << HP[to] << "滴血." << endl;;
	}
	TL_step --;
}
void LJS(int from) {//雷击术
	cout << name[from] << "使用了雷击术." << endl;
	int to;
	while(HP[to] == 0 || to == from) to = rand() % (n + 1);
	int SH = rand() % (HP[to] - 20) + 5;
	HP[to] -= SH;
	cout << name[to] << "被" << name[from] << "攻击,扣去" << SH << "滴血";
	if(HP[to] <= 0) {
		cout << "." << endl;
		message(from,to);
		return;
	} else {
		cout << ",剩余" << HP[to] << "滴血." << endl;;
	}
	Sleep(rand() % 50 + 50);
	HP[to] -= SH;
	cout << name[to] << "被" << name[from] << "攻击,扣去" << SH << "滴血";
	if(HP[to] <= 0) {
		cout << "." << endl;
		message(from,to);
		return;
	} else {
		cout << ",剩余" << HP[to] << "滴血." << endl;;
	}
	Sleep(rand() % 50 + 50);
	HP[to] -= SH;
	cout << name[to] << "被" << name[from] << "攻击,扣去" << SH << "滴血";
	if(HP[to] <= 0) {
		cout << "." << endl;
		message(from,to);
		return;
	} else {
		cout << ",剩余" << HP[to] << "滴血." << endl;;
	}
	Sleep(rand() % 50 + 50);
	TL_step --; 
}
void TL(int from) { //推理 
	cout << name[from] << "发动推理." << endl;//提示
	TL_from = from;//设定推理者编号 
	is_TL = true;//开始推理 
	TL_step = 5;//设定推理步数 
}
void FX(int from) {//推理后的发现
	if(HP[TL_from] > 0) {//如果推理者还没死
		int to;//尸体被发现者编号
		while(HP[to] == 0 || to == from) to = rand() % (n + 1);//随机指定尸体被发现者编号
		cout << name[from] << "在一间密室里发现了" << name[to] << "的尸体";//提示
		HP[to] = 0;//清空尸体被发现者的血
		is_TL = false;//结束推理
	}
}
void message(int from,int to) {//向控制台发送死亡信息
	cout << name[to] << "被" << name[from] << "杀死了." << endl;
	temp --;
}
