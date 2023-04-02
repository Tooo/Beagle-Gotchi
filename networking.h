#ifndef _NETWORKING_H_
#define _NETWORKING_H_
// networking.h
// This module handles the website UDP networking

// Initialize starting up a udp thread to talk to the node website
void init_udp_listen(void);
void udp_clean_up(void);

#endif
