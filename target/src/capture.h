// Header file for streaming the webcam
#ifdef __cplusplus
extern "C" {
#endif

#ifndef CAPTURE_H
#define CAPTURE_H

#include <stdio.h>

// Exit from error
void errno_exit(const char *s);

// Open connection
void openConnectionT();

// Send response
int sendResponseT(const void *str, int size);

// Close connection
void closeConnectionT();

// System call for device control
int xioctl(int fh, int request, void *arg);

// Process image
void process_image(const void *p, int size);

// Read frame
int read_frame(void);

// Main loop for capturing and streaming
void mainloop(void);

// Stop capturing
void stop_capturing(void);

// Start capturing
void start_capturing(void);

// Uninitialize device
void uninit_device(void);

// Initialize device
void init_read(unsigned int buffer_size);

// Initialize memory mapping
void init_mmap(void);

// Initialize user pointer
void init_userp(unsigned int buffer_size);

// Initialize device
void init_device(void);

// Close device
void close_device(void);

// Open device
void open_device(void);

// Stop loop, ends the mainloop and webcam functionality
void stopLoop();

// Main function
int webcam();

#endif

#ifdef __cplusplus
}
#endif