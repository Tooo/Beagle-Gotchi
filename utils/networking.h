#ifndef _NETWORKING_H_
#define _NETWORKING_H_
// networking.h
// This module handles the website UDP networking

#include <stdbool.h>

// Initialize starting up a udp thread to talk to the node website
void udp_init(void);
void udp_clean_up(void);

bool udp_usingLEDMatrix(void);

#endif
