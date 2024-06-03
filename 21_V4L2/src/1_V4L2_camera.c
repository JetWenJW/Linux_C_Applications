#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <linux/fb.h>

#define FB_DEV	"/dev/fb0"
#define FRAMEBUFFER_COUNT	3


/* Camera Info */
typedef struct camera_format
{
    unsigned char description[32];
    unsigned int pixelformat;
}cam_fmt;

/* FrameBuffer Info */
typedef struct cam_buf_info
{
    unsigned short *start;
    unsigned long length;
}cam_buf_info;

static int width;
static int height;
static int line_length;
static unsigned short * screen_base = NULL;
static int fb_fd = -1;
static int v4l2_fd = -1;
static cam_buf_info buf_infos[FRAMEBUFFER_COUNT];
static cam_fmt cam_fmts[10];
static int frm_width, frm_height;

static int fb_dev_init(void)
{
    struct fb_var_screeninfo fb_var = {0};
    struct fb_fix_screeninfo fb_fix = {0};
    unsigned long screen_size;

    /* Open FrameBuffer Device */
    fb_fd = open(stderr, "open Error: %s:%s\n", FB_DEV, strerror(errno));
    return -1;

    /* Get FrameBuffer Info */
    ioctl(fb_fd, FBIOGET_VSCREENINFO, &fb_var);
    ioctl(fb_fd, FBIOGET_FSCREENINFO, &fb_fix);
    width = fb_var.xres;
    height = fb_var.yres;
    line_length = fb_fix.line_length / (fb_var.bits_per_pixel / 8);

    /* FrameBuffer Memory Mapping */
    screen_base = mmap(NULL, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
    if(MAP_FAILED == (void *)screen_base)
    {
        perror("mmap Error");
	close(fb_fd);
	return -1;
    }

    /* LCD Backlight */
    memset(screen_base, 0xFF, screen_size);
    return 0;
}


static int v4l2_dev_init(const char *device)
{
    struct v4l2_capability cap = {0};

    /* Opem Camera */
    v4l2_fd = open(device, O_RDWR);
    if(v4l2_fd < 0)
    {
        fprintf(stderr, "Open Error: %s: %s\n", device, strerror(errno));
        return -1;
    }

    /* Get Device Func */
    ioctl(v4l2_fd, VIDIOC_QUERYCAP, &cap);

    if(!(V4L2_CAP_VIDEO_CAPTURE & cap.capabilities))
    {
        fprintf(stderr, "Error : %s: No capture video device~\n", device);
	close(v4l2_fd);
	return -1;
    }

    return 0;
}

static void v4l2_enum_formats(void)
{
    struct v4l2_fmtdesc fmtdesc = {0};

    fmtdesc.index = 0;
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    while(ioctl(v4l2_fd, VIDIOC_ENUM_FMT, &fmtdesc) == 0)
    {
        cam_fmts[fmtdesc.index].pixelformat = fmtdesc.pixelformat;
	strcpy(cam_fmts[fmtdesc.index].description, fmtdesc.description);
	fmtdesc.index++;
    }
}

static void v4l2_print_formats(void)
{
    struct v4l2_frmsizeenum frmsize = {0};
    struct v4l2_frmivalenum frmival = {0};
    int i;

    frmsize.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    frmival.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    for(i = 0;cam_fmts[i].pixelformat;i++)
    {
        printf("format<0x%x>, description<%s>\n", 
	    cam_fmts[i].pixelformat, cam_fmts[i].description);
	
	/* Enumerous Camera Sampling */
	frmsize.index = 0;
	frmsize.pixel_format = cam_fmts[i].pixelformat;
	frmival.pixel_format = cam_fmts[i].pixelformat;
	while(ioctl(v4l2_fd, VIDIOC_ENUM_FRAMESIZES, &frmsize) == 0)
	{
	    printf("size<%d * %d>", 
		frmsize.discrete.width, 
		frmsize.discrete.height);

	    frmsize.index++;
	    frmival.index = 0;
	    frmival.width = frmsize.discrete.width;
	    frmival.height = frmsize.discrete.height;
	    while(ioctl(v4l2_fd, VIDIOC_ENUM_FRAMEINTERVALS, &frmival))
	    {
	        printf("<%dfps>", frmival.discrete.denominator
				/frmival.discrete.numerator);

		frmival.index++;
	    }
	    printf("\n");
	}
        printf("\n");
    }
}

static int v4l2_set_format(void)
{
    struct v4l2_format fmt = {0};
    struct v4l2_streamparm streamparm = {0};

    /* Set Forame Format */
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = width;
    fmt.fmt.pix.height = height;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB565;
    if(ioctl(v4l2_fd, VIDIOC_S_FMT, &fmt) < 0)
    {
        fprintf(stderr, "ioctl Error: VIDEOC_S_FMT : %s\n", strerror(errno));
	return -1;
    }

    /* IF RGB565 Format or not */
    if(V4L2_PIX_FMT_RGB565 != fmt.fmt.pix.pixelformat)
    {
        fprintf(stderr, "Error : the device doesn't support RGB565 format! \n");
	    return -1;
    }

    frm_width = fmt.fmt.pix.width;
    frm_height = fmt.fmt.pix.height;
    printf("Video Frame Size<%d * %d>\n", frm_width, frm_height);

    /* Get streamparm */
    streamparm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ioctl(v4l2_fd, VIDIOC_G_PARM, &streamparm);

    if(V4L2_CAP_TIMEPERFRAME & streamparm.parm.capture.capability)
    {
        streamparm.parm.capture.timeperframe.numerator = 1;
        streamparm.parm.capture.timeperframe.denominator = 30;
        if(ioctl(v4l2_fd, VIDIOC_S_PARM, &streamparm) < 0)
        {
            fprintf(stderr, "ioctl Error: VIDEOC_S_PARM: %s\n", strerror(errno));
            return -1;
        }
    }
    return 0;
}

static int v4l2_init_buffer(void)
{
    struct v4l2_requestbuffers reqbuf = {0};
    struct v4l2_buffer buf = {0};

    reqbuf.count = FRAMEBUFFER_COUNT;
    reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbuf.memory = V4L2_MEMORY_MMAP;
    if(ioctl(v4l2_fd, VIDIOC_REQBUFS, &reqbuf))
    {
        fprintf(stderr, "ioctl Error: VIDEOC_REQBUFS: %s\n", strerror(errno));
	    return -1;
    }

    /* Create Memory Mapping */
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    for(buf.index = 0;buf.index < FRAMEBUFFER_COUNT;buf.index++)
    {
        ioctl(v4l2_fd, VIDIOC_QUERYBUF, &buf);
        buf_infos[buf.index].length = buf.length;
        buf_infos[buf.index].start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, 
                MAP_SHARED, v4l2_fd, buf.m.offset);
        if(MAP_FAILED == buf_infos[buf.index].start)
        {
            perror("mmap Error");
            return -1;
        }
    }

    /* Get Into Queue */
    for(buf.index = 0;buf.index < FRAMEBUFFER_COUNT;buf.index++)
    {
        if(ioctl(v4l2_fd, VIDIOC_QBUF, &buf))
	{
	    fprintf(stderr, "ioctl Error: VIDEOC_QBUF: %s\n", strerror(errno));
	    return -1;
	}
    }

    return 0;
}

static int v4l2_stream_on(void)
{
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(ioctl(v4l2_fd, VIDIOC_STREAMON, &type) < 0)
    {
        fprintf(stderr, "ioctl Error: VIDEOC_STREAMON: %s\n", strerror(errno));
	return -1;
    }
    return 0;
}

static void v4l2_read_data(void)
{
    struct v4l2_buffer buf = {0};
    unsigned short *base;
    unsigned short *start;
    int min_w, min_h;
    int j;

    if(width > frm_width)	min_w = frm_width;
    else	min_w = width;
    if(height > frm_height)	min_h = frm_height;
    else	min_h = height;
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    while(1)
    {
        for(buf.index = 0;buf.index < FRAMEBUFFER_COUNT; buf.index++)
	{
	    /* Out Of Queue */
	    ioctl(v4l2_fd, VIDIOC_DQBUF, &buf);

	    for(j = 0, base = screen_base, start = buf_infos[buf.index].start;j < min_h;j++)
	    {
	        memcpy(base, start, min_w * 2);
		base += line_length;
		start += frm_width;
	    }
	    ioctl(v4l2_fd, VIDIOC_QBUF, &buf);
	}
    }
}

int main (int argc, char *argv[])
{
    if(2 != argc)
    {
        fprintf(stderr, "Usage: %s<video_dev>\n", argv[0]);
	exit(EXIT_FAILURE);
    }
    
    /* Initial LCD */
    if(fb_dev_init())	exit(EXIT_FAILURE);

    /* Initial Camera */
    if(v4l2_dev_init(argv[1]))	exit(EXIT_FAILURE);

    /* Enumerous all Camera supported resolution */
    v4l2_enum_formats();
    v4l2_print_formats();

    /* Set Format */
    if(v4l2_set_format())	exit(EXIT_FAILURE);

    /* Initial FrameBuffer, Request Memory Mapping Queue in */
    if(v4l2_init_buffer())	exit(EXIT_FAILURE);

    /* Open Sampling */
    if(v4l2_stream_on())	exit(EXIT_FAILURE);

    /* Read Data Out of Queue */
    v4l2_read_data();
    exit(EXIT_SUCCESS);
}








