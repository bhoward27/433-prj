#ifdef __cplusplus
extern "C" {
#endif

#ifndef CAPTURE_H
#define CAPTURE_H

#include <stdio.h>

void errno_exit(const char* s);

void openConnectionT();

int sendResponseT(const void* str, int size);

void closeConnectionT();

int xioctl(int fh, int request, void* arg);

void process_image(const void* p, int size);

int read_frame(void);

void mainloop(void);

void stop_capturing(void);

void start_capturing(void);

void uninit_device(void);

void init_read(unsigned int buffer_size);

void init_mmap(void);

void init_userp(unsigned int buffer_size);

void init_device(void);

void close_device(void);

void open_device(void);

int webcam();

#endif

#ifdef __cplusplus
}
#endif