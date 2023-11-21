#ifndef GPIOIN_H
#define GPIOIN_H

#include <cstdlib>  
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fcntl.h> 
#include<iostream>

#define ON "1"           //开启
#define OFF "0"          //关闭
#define BUZZER1 "492"     //控制引脚1
#define NAME1 "PAC.06"     //引脚1name
#define DIRECTION1 "in"  //引脚1方向为输出
#define BUZZER2 "454"     //控制引脚2
#define NAME2 "PQ.06"     //引脚2name
#define DIRECTION2 "in"  //引脚2方向为输出

using namespace std;

class gpio
{
private:
    /* data */
public:
    gpio(/* args */);
    ~gpio();
    int openGpio(const char *port);  //导入gpio
    int closeGpio(const char *port); //导出gpio
    int readGPIOValue(const char *port);  //读取gpio值
    int setGpioDirection(const char *port,const char *direction);  //设置gpio方向
    int setGpioValue(const char *port,const char *level);  //设置gpio值
    int setGpioEdge(const char *port,const char *edge);  //设置gpio输入模式
};


gpio::gpio(/* args */)
{
}

gpio::~gpio()
{
}

int gpio::openGpio(const char *port)
{
    int fd;
	const char *path = "/sys/class/gpio/export";

	fd = open(path, O_WRONLY);
	if(fd == -1)
	{
	   perror("Failed to open gpio! ");
	   return -1;
	}

	write(fd, port ,sizeof(port)); 
	close(fd);
	return 0; 	
}
	
int gpio::closeGpio(const char *port)
{
    int fd;
	const char *path = "/sys/class/gpio/unexport";

	fd = open(path, O_WRONLY);
	if(fd == -1)
	{
	   perror("Failed to open gpio! ");
	   return -1;
	}

	write(fd, port ,sizeof(port)); 
	close(fd); 	
	return 0;
}

int gpio::readGPIOValue(const char *port)
{
	int fd;
	char path[40];
	sprintf(path,"/sys/class/gpio/%s/value", port);
	fd = open(path, O_RDONLY);
	if(fd == -1)
	{
		perror("Failed to read GPIO value!");
		return -1;
	}
	char value[2];
	read(fd,value,1);

	return atoi(value);
}

int gpio::setGpioDirection(const char *port,const char *direction)
{
	int fd;
	char path[40];
	sprintf(path, "/sys/class/gpio/%s/direction", port);
	fd = open(path, O_WRONLY);

	if(fd == -1)
	{
	   perror("Failed to set GPIO direction. ");

	   return -1;
	}

	write(fd, direction, sizeof(direction)); 
	close(fd); 
	return 0;
}

int gpio::setGpioEdge(const char *port,const char *edge)
{
	int fd;
	char path[40];
	sprintf(path, "/sys/class/gpio/%s/edge", port);
	fd = open(path, O_WRONLY);

	if(fd == -1)
	{
	   perror("Failed to set GPIO edge. ");

	   return -1;
	}

	write(fd, edge, sizeof(edge)); 
	close(fd); 
	return 0;
}

int gpio::setGpioValue(const char *port,const char *level)
{
	int fd;
	char path[40];
	sprintf(path, "/sys/class/gpio/%s/value", port);
	fd = open(path, O_RDWR);
	if(fd == -1)
	{
	   perror("Failed to set GPIO value! ");
	   return -1;
	}       

	write(fd, level, sizeof(level));
	close(fd);
	return 0;
}

#endif


