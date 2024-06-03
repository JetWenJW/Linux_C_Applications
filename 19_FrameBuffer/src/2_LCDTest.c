#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>


#define argb8888_to_rgb565(color)	({	\
		unsigned int temp = (color);	\
		((temp & 0xF80000UL) >> 8) | 	\
		((temp & 0xFC00UL) >> 5) | 	\
		((temp & 0xF8UL) >> 3);		\
		})


static int width;
static int height;
static unsigned short *screen_base = NULL;

static void lcd_draw_point(unsigned int x, unsigned int y, unsigned int color)
{
    unsigned short rgb565_color = argb8888_to_rgb565(color);
    if(x >= width) x = width - 1;
    if(y >= height) y = height - 1;

    /* Fill Colour */
    screen_base[y * width + x] = rgb565_color;
}

static void lcd_draw_line(unsigned int x, unsigned int y, int dir, unsigned int length, unsigned int color)
{
    unsigned short rgb565_color = argb8888_to_rgb565(color);
    unsigned int end;
    unsigned long temp;
    if(x >= width) x = width - 1;
    if(y >= height) y = height - 1;

    /* Fill With Colour */
    temp = y * width + x;
    if(dir)	/* Horozontal line */
    {
        end = x + length - 1;
	if(end >= width) end = width - 1;
	for(;x<=end;temp++)
	{
	    screen_base[temp] = rgb565_color;
	}
    }
    else	/* Vertical line */
    {
        end = y + length - 1;
	if(end >= height) end = height - 1;
	for(; y <= end;temp += width)
	{
	    screen_base[temp] = rgb565_color;
	}
    }
}

static void lcd_draw_rectangle(unsigned int start_x, 
		unsigned int end_x, 
		unsigned int start_y, 
		unsigned int end_y, 
		unsigned int color)
{
    int x_len = end_x - start_x + 1;
    int y_len = end_y - start_y + 1;

    lcd_draw_line(start_x, start_y, 1, x_len, color);
    lcd_draw_line(start_x, end_y, 1, x_len, color);
    lcd_draw_line(start_x, start_y + 1, 0, y_len, color);
    lcd_draw_line(end_x, start_y + 1, 0, y_len, color);
}

static void lcd_fill(unsigned int start_x,
                unsigned int end_x,
                unsigned int start_y,
                unsigned int end_y,
                unsigned int color)
{
    unsigned short rgb565_color = argb8888_to_rgb565(color);
    unsigned long temp;
    unsigned int x;

    if(end_x >= width)	end_x = width - 1;
    if(end_y >= height)	end_y = height - 1;

    /* Fill with Color */
    temp = start_y *width;
    for(;start_y <= end_y;temp += width)
    {
        for(x = start_x;x <= end_x;x++)
	{
	    screen_base[temp + x] = rgb565_color;
	}
    }
}

int main(int argc, char *argv[])
{
    struct fb_fix_screeninfo fb_fix;
    struct fb_var_scerrninfo fb_var;
    unsigned int screen_size;
    int fd;

    /* Open FrameBuffer Device */
    fd = open("/dev/fb0", O_RDWR)
    if(fd < 0)
    {
        perror("Open Error");
	exit(EXIT_FAILURE);
    }

    ioctl(fd, FBIOGET_VSCREENINFO, &fb_var);
    ioctl(fd, FBIOGET_FSCREENINFO, &fb_fix);

    screen_size = fb_fix.line_length * fb_var.yres;
    width = fb_fix.line_length / (fb_var.bits_per_pixel / 8);
    height = fb_var.yres;

    /* Memory Mapping */
    screen_base = mmap(NULL, screen_size, PROT_WRITE, MAP_SHARED, fd, 0);
    if(MAP_FAILED == (void *)screen_base)
    {
        perror("mmap Error");
	close(fd);
	exit(EXIT_FAILURE);
    }

    /* Draw Squre */
    int w = height * 0.25;
    lcd_fill(0, fb_var.xres - 1, 0, height - 1, 0x0);
    lcd_fill(0, w, 0, w, 0xFF0000);
    lcd_fill(fb_var.xres - w, fb_var.xres - 1, 0, w, 0xFF00);
    lcd_fill(0, w, height - w, height - 1, 0xFF);
    lcd_fill(fb_var.xres - w, fb_var.xres - 1, height - w, height - 1, 0xFFFF00);

    /* Draw Cross line */
    lcd_draw_line(0, height * 0.5, 1, fb_var.xres, 0xFFFFFF);
    lcd_draw_line(fb_var.xres * 0.5, 0, 0, height, 0xFFFFFF);

    /* Draw Rectangle */
    unsigned int s_x, s_y, e_x, e_y;
    s_x = 0.25 * fb_var.xres;
    s_y = w;
    e_x = fb_var.xres - s_x;
    e_y = height - s_y;
    for(;(s_x <= e_x) && (s_y <= e_y);s_x += 5, s_y += 5, e_x -= 5, e_y -= 5)
    {
        lcd_draw_rectangle(s_x, e_x, s_y, e_y, 0xFFFFFF);
    }

    /* Exit */
    munmap(screen_base, screen_size);
    close(fd);
    exit(EXIT_SUCCESS);
}










