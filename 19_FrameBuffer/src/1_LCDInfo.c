#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/fb.h>

int main(int argc, char *argv[])
{
    struct fb_fix_screeninfo fb_fix;
    struct fb_var_screeninfo fb_var;
    int fd;
    
    /* Open FraneBuffer Device */
    fd = open("/dev/fb0", O_WRONLY);
    if(fd < 0)
    {
        perror("Open Error");
	exit(-1);
    }

    /* Get Screen Info */
    ioctl(fd, FBIOGET_VSCREENINFO, &fb_var);
    ioctl(fd, FBIOGET_FSCREENINFO, &fb_fix);
    printf("Resolution: %d * %d\n"
	   "Pixel Depth(bpp): %d\n"
	   "Bytes of Oneline: %d\n"
	   "Pixel Format: R<%d %d>, G<%d %d>, B<%d %d>\n",
	   fb_var.xres, fb_var.yres, fb_var.bits_per_pixel,
	   fb_fix.line_length,
	   fb_var.red.offset, fb_var.red.length,
	   fb_var.green.offset, fb_var.green.length,
	   fb_var.blue.offset, fb_var.blue.length);

    close(fd);
    exit(0);
}
