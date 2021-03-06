#pragma comment(lib,"C:\ypspur\lib\libypspur-md_dll.lib")

#include "stdafx.h"

//#include <stdio.h>
//#include <unistd.h>
#include <math.h>
#include <ypspur.h>

#include <windows.h>


#define TREAD 590
#define PI 3.14159265359
#define TIRE 290

#define MODE 1

int main(void){

	char key = 0x20;

	double vel = 3.14;

	double ang = 90;

	double x, y, theta;

	// Windows環境で標準出力がバッファリングされないように設定
	setvbuf(stdout, 0, _IONBF, 0);

	// 初期化
	if (Spur_init() < 0)
	{
		fprintf(stderr, "ERROR : cannot open spur.\n");
		return -1;
	}


	Spur_set_vel(0.3);		//速度0.3m/sec
	Spur_set_accel(1.0);	//加速度（m/s/s）
	Spur_set_angvel(1.5);	//角速度（rad/s)
	Spur_set_angaccel(2.0);		//角加速度（rad/s/s)

	YP_set_wheel_vel(PI, PI);
	YP_set_wheel_accel(PI/2, PI/2);

	Spur_set_pos_GL(0, 0, 0);

	if (MODE == 1){
		while (true){
			key = getchar();
			switch (key){
			case ' ':	//スペースで停止
				Spur_stop();
				break;
			case 'y':  //↑で前進y

				//YP_wheel_vel(-3.1, 3.1);
				Spur_line_GL(1.0, 0.0, 0.0);
				break;
				/*	case 'j':	//↓で後退
				YP_wheel_vel(-vel, -vel);
				break;*/
			case 'g':	//←で左回転
				//YP_wheel_ang(-TREAD*(ang / 360) / TIRE, TREAD*(ang / 360) / TIRE);
				Spur_spin_GL(3.14 / 2);
				while (!Spur_near_ang_GL(ang*3.14 / 180, 0.1))
					Sleep(100);
				Spur_stop();
				break;
			case 'j': //→で右回転
				//YP_wheel_ang(TREAD*(ang / 360) / TIRE, -TREAD*(ang / 360) / TIRE);
				Spur_spin_GL(-3.14 / 2);
				while (!Spur_near_ang_GL(-ang*3.14 / 180, 0.1))
					Sleep(100);
				Spur_stop();
				break;
			case 'v':	//速度変更
				printf("\033[2J");
				printf("速度変更\n");
				scanf("%f", &vel);
				break;
			case 'a':	//回転角度変更
				printf("\033[2J");
				printf("回転角度変更\n");
				scanf("%f", &ang);
				break;
			case 'o':	//原点リセット
				Spur_set_pos_GL(0, 0, 0);
				break;
			case 'f':
				Spur_free();
				break;
			}

			Spur_get_pos_GL(&x, &y, &theta);

			printf("\033[2J");
			printf("矢印キーで方向制御\n");
			printf("スペースで停止\n");
			printf("v:速度変更\n");
			printf("a:回転角度変更\n");
			printf("o:原点リセット\n\n\n");
			printf("現在位置\n");
			printf("%f,%f,%f\n", x, y, theta);


		}
	}

	else {
		while (true){
			Spur_get_pos_GL(&x, &y, &theta);
			printf("現在位置\n");
			printf("%f,%f,%f\n", x, y, theta);
			Sleep(1000);

		}
	}
}