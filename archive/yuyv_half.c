#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <stdlib.h>

uint8_t *buffer;

const int height = 480;
const int width = 720;
const int length = 345600;
const int buffer_size = 100;

#include "met.h"

static int xioctl(int fd, int request, void *arg)
{
        int r;

        do r = ioctl (fd, request, arg);
        while (-1 == r && EINTR == errno);

        return r;
}

int print_caps(int fd)
{
        struct v4l2_capability caps = {};
        if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &caps))
        {
                perror("Querying Capabilities");
                return 1;
        }

        printf( "Driver Caps:\n"
                "  Driver: \"%s\"\n"
                "  Card: \"%s\"\n"
                "  Bus: \"%s\"\n"
                "  Version: %d.%d\n"
                "  Capabilities: %08x\n",
                caps.driver,
                caps.card,
                caps.bus_info,
                (caps.version>>16)&&0xff,
                (caps.version>>24)&&0xff,
                caps.capabilities);

        struct v4l2_format fmt = {0};
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt.fmt.pix.width = 720;
        fmt.fmt.pix.height = 480;
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
        fmt.fmt.pix.field = V4L2_FIELD_NONE;
        //fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	//fmt.fmt.pix.bytesperline = 0;

        if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
        {
            perror("Setting Pixel Format");
            return 1;
        }

        printf( "Selected Camera Mode:\n"
                "  Width: %d\n"
                "  Height: %d\n"
                "  Field: %d\n",
                fmt.fmt.pix.width,
                fmt.fmt.pix.height,
                fmt.fmt.pix.field);
        return 0;
}

int init_mmap(int fd)
{
    struct v4l2_requestbuffers req = {0};
    req.count = 1;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req))
    {
        perror("Requesting Buffer");
        return 1;
    }

    struct v4l2_buffer buf = {0};
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;
    if(-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf))
    {
        perror("Querying Buffer");
        return 1;
    }

    buffer = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
    printf("Length: %d\nAddress: %p\n", buf.length, buffer);
    printf("Image Length: %d\n", buf.bytesused);

    return 0;
}

int grab_frame(int fd, struct image *img){

	struct v4l2_buffer buf = {0};
	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_MMAP;
	buf.index = 0;
	
	if(-1 == xioctl(fd, VIDIOC_STREAMON, &buf.type)){
		perror("Start Capture");
		return 1;
	}
	
	int i, j;
	
	for(i = 0; i < buffer_size; i++){
	
		if(-1 == xioctl(fd, VIDIOC_QBUF, &buf)){
			perror("Query Buffer");
			return 1;
		}
		
		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		struct timeval tv = {0};
		tv.tv_sec = 2;
		int r = select(fd+1, &fds, NULL, NULL, &tv);
		
		if(-1 == r){
			perror("Waiting for Frame");
			return 1;
		}
	    
		if(-1 == xioctl(fd, VIDIOC_DQBUF, &buf)){
			perror("Retrieving Frame");
			return 1;
		}

		struct timeval time;
		gettimeofday(&time, NULL);
		printf("time: %i", time.tv_usec);
	    
		unsigned char *yuyv = buffer;
	    
		for(j = 0; j < length/2; j++){
			img->data[0] = yuyv[0];
			img->data[1] = yuyv[2];
			img->data += 2;
			yuyv += 4;
		}
		printf("read: %i\n", img->index);
		img = img->next;
	}
	
	int outfd = open("out.bwv", O_RDWR);
	write(outfd, img->data, length);
	close(outfd);
	
	return 0;
}


int write_video(struct image *img){
	int i;
	int outfd = open("video.bwv", O_RDWR | O_APPEND);
	
	for(i = 0; i < buffer_size; i++){
		write(outfd, img->data, length);
		printf("write: %i\n", img->index);
		img = img->next;
	}
	close(outfd);

	return 0;
}

int main()
{
        int fd;

        fd = open("/dev/video0", O_RDWR/* | O_NONBLOCK*/);
        if (fd == -1)
        {
                perror("Opening video device");
                return 1;
        }

        if(print_caps(fd))
            return 1;

        if(init_mmap(fd))
            return 1;

        struct image *img = buildBuffer(buffer_size);
	
	int i;
	for (i = 0; i < buffer_size; i++) {
		printf("%i ", img->index);
		img = img ->next;
	}

	printf("foo\n");
	
	if(grab_frame(fd, img))
        	return 1;
	
	write_video(img);
	
	/*
	for(i = 0; i < length; i++){
		if(grab_frame(fd, img))
            		return 1;
		img = img->next;
	}
	*/

        close(fd);
        return 0;
}
