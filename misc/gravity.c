/*azhe 2013.11.18
 *Note: 地球引力, 抛物线
 * x:水平向右 y:垂直向下 角度参考方向为x, 顺时针
 *arg1: velocity, unit:m/s
 *arg2: velocity angle, unit: degree
 *arg3: 
 * */
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define START_V	2	/*m/s*/
#define PI		3.1415926
#define G		9.8		/*gravity*/
#define CLOCKID	CLOCK_REALTIME
#define DELAY	1000 /*timer间隔, ms*/

struct Ball{
	float v;	/*初始速度, m/s */
	float v_angle; /*初始速度角度, 角度参考方向为x, 顺时针, 度*/
	float force;	/*受力, N*/
	float force_angle; /*受力角度, 度*/
	float a; /*加速度m/s^2*/
	float a_angle;
	float a_x;
	float a_y;
	float m; /*质量kg*/
	float v_x; /*x方向瞬时速度*/
	float v_y; /*y方向瞬时速度*/
	float s_x; /*x方向位移*/
	float s_y; /*y方向位移*/
	float time;
};

struct Ball ball;
double angleToRadian(double angle)
{
	return angle * PI / 180;
}
void timer_thread(union sigval v)
{
	static int cnt = 0;
	static struct timeval old, new;
	float time_eclipse;	/*unit: s*/
	
	gettimeofday(&new, NULL);
	if (cnt != 0) {
		/*为了更加准确，再次计算interval*/
		time_eclipse = (new.tv_sec - old.tv_sec) + ((new.tv_usec - old.tv_usec) / 1000000);
		/*x, y方向的位移*/
		ball.s_x += ball.v_x * time_eclipse + \
				   (1.0 / 2) * ball.a_x * (time_eclipse * time_eclipse);
		ball.s_y += ball.v_y * time_eclipse + \
				   (1.0 / 2) * ball.a_y * (time_eclipse * time_eclipse);
		/*x, y方向的速度*/
		ball.v_x += ball.a_x * time_eclipse;
		ball.v_y += ball.a_y * time_eclipse;
	
		printf("t: %.10f x: %.10f, y: %.10f v_x: %.10f v_y: %.10f\n", \
			time_eclipse, ball.s_x, ball.s_y, ball.v_x, ball.v_y);
	}
	cnt++;
	gettimeofday(&old, NULL);
}
/*void initBall()*/
int main(int argc, char** argv)
{
	timer_t timerid;
	struct sigevent ev;
	struct itimerspec it;
	memset(&ev, 0, sizeof(struct sigevent));
	memset(&ball, 0, sizeof(struct Ball));

	ball.a = 9.8;
	ball.a_angle = 90;

	ball.v = START_V;
	ball.v_angle = 0;
	
	/*计算x, y方向上的速度和加速度*/
	ball.a_x = ball.a * cos(angleToRadian(ball.a_angle));
	ball.a_y = ball.a * sin(angleToRadian(ball.a_angle));
	
	ball.v_x = ball.v * cos(angleToRadian(ball.v_angle));
	ball.v_y = ball.v * sin(angleToRadian(ball.v_angle));

	// XXX int timer_create(clockid_t clockid, struct sigevent *evp, timer_t *timerid);
	// clockid--值：CLOCK_REALTIME,CLOCK_MONOTONIC，CLOCK_PROCESS_CPUTIME_ID,CLOCK_THREAD_CPUTIME_ID
	// evp--存放环境值的地址,结构成员说明了定时器到期的通知方式和处理方式等
	// timerid--定时器标识符
	/*timer event create, thread*/
	ev.sigev_value.sival_int = 111;
	ev.sigev_notify = SIGEV_THREAD;
	ev.sigev_notify_function = timer_thread;
	
	if (timer_create(CLOCKID, &ev, &timerid)) {
		perror("failed to create timer!\n");
		return -1;
	}
	/*set interval time*/	
	it.it_interval.tv_sec = DELAY / 1000;
	it.it_interval.tv_nsec = (DELAY % 1000) * 1000000;
	it.it_value.tv_sec = DELAY / 1000;
	it.it_value.tv_nsec = (DELAY % 1000) * 1000000;

	if (timer_settime(timerid, 0, &it, NULL)) {
		perror("faild to settimer!\n");
		return -2;
	}

	while(1);
	return 0;
}
