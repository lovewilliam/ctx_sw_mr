/*
 * License: GPLv2
 * measure how fast the context switch is
 * 2014 Zhang Tong<ztong@vt.edu>
 * 2013 Zhang Tong<lovewilliam@gmail.com>
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define SLEEP_DURATION 1024
#define TEST_LOOPS 8192

int main()
{
	int i = 0;
	long max = 0;
	long min = 99999999;
	long avg = 0;
	long x = 0;
	struct timeval time_start,time_stop;
	for(i=0;i<TEST_LOOPS;i++)
	{
		gettimeofday(&time_start,NULL);
		usleep(SLEEP_DURATION);
		gettimeofday(&time_stop,NULL);
		x = (long)(((long)time_stop.tv_sec*1000000) + time_stop.tv_usec) -
			(long)(((long)time_start.tv_sec*1000000) + time_start.tv_usec)
			- SLEEP_DURATION;
		if(x>max)
		{
			max = x;
		}else if(x<min)
		{
			min = x;
		}
		avg = (avg+x)/2;
	}
	printf("Contex Switching Test Result\n");
	printf("----------------------------\n");
	printf("Max ctx_switch latency: %ld us\n",max);
	printf("Min ctx_switch latency: %ld us\n",min);
	printf("Avg ctx_switch latency: %ld us\n",avg);
	return 0;
}


