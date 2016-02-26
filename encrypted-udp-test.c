// Standard Contiki Functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "contiki.h"
#include "contiki-lib.h"

// Networking
#include "contiki-net.h"
#include "ip64-addr.h"

// RPL & Mesh
#include "net/rpl/rpl.h"
#include "net/ip/uip.h"

// Texas Instruments
#include "ti-lib.h"

// Timers
#include "sys/ctimer.h"

/*
 *  Debug
 */
#define DEBUG 1

#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#define PRINT6ADDR(addr) PRINTF("[%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x]", ((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5], ((uint8_t *)addr)[6], ((uint8_t *)addr)[7], ((uint8_t *)addr)[8], ((uint8_t *)addr)[9], ((uint8_t *)addr)[10], ((uint8_t *)addr)[11], ((uint8_t *)addr)[12], ((uint8_t *)addr)[13], ((uint8_t *)addr)[14], ((uint8_t *)addr)[15])
#define PRINTLLADDR(lladdr) PRINTF("[%02x:%02x:%02x:%02x:%02x:%02x]", (lladdr)->addr[0], (lladdr)->addr[1], (lladdr)->addr[2], (lladdr)->addr[3], (lladdr)->addr[4], (lladdr)->addr[5])
#else
#define PRINTF(...)
#define PRINT6ADDR(addr)
#define PRINTLLADDR(addr)
#endif

/*
 *	Configure test message length
 */
#define MSG_LENGTH 20

/*
 *	UDP Config
 */
#define UDP_MAX_PAYLOAD 256
#define UDP_PORT 8808
uip_ipaddr_t server_ipaddr;
struct uip_udp_conn *udp_client_conn;
char udp_buf[UDP_MAX_PAYLOAD];

struct ctimer udp_send_timer;

/**
 *  Initialize connection to destination UDP server at bbbb::1
 */
void
init_udp()
{
  // (1) Define Destination IP: bbbb::1/64
	uip_ip6addr(&server_ipaddr, 0xbbbb, 0, 0, 0, 0, 0, 0, 0x1);

  // (2) Establish UDP connection with border router
  udp_client_conn = udp_new(&server_ipaddr, UIP_HTONS(UDP_PORT), NULL);
  udp_bind(udp_client_conn, UIP_HTONS(UDP_PORT));
}

/**
 *  Send a specified string (up to UDP_MAX_PAYLOAD bytes) to
 *  the BR by UDP datagrams.
 */
void
send_udp_msg(void *msg)
{
	//	(1)	Print the destination IP
	PRINTF("Client sending to: ");
	PRINT6ADDR(&udp_client_conn->ripaddr);

	//	(2)	Copy msg into a static buffer
	memset(udp_buf, 0, sizeof(udp_buf));
	memcpy(udp_buf, msg, strlen(msg));
	//sprintf(udp_buf, "%.*s", strlen(msg), udp_buf);
	PRINTF(" (msg: %s) [%i]\n", udp_buf, strlen(udp_buf));

	//	(3)	Transmit the UDP datagram
	uip_udp_packet_send(udp_client_conn, udp_buf, strlen(udp_buf));
}

void
udp_looper() {
	//	(1) Generate a string of letter a's with length max_msg
	char msg[MSG_LENGTH+1];
	for (int c=0; c<MSG_LENGTH-1; c++) {
		msg[c] = 'a';
	}
	msg[MSG_LENGTH] = '\0';

	//	(2)	Dispatch msg to destination
	send_udp_msg( msg );

	//	(3)	Reset the timer
	ctimer_reset( &udp_send_timer );
}

PROCESS( udp_sender_th, "UDP Sender" );
AUTOSTART_PROCESSES( &udp_sender_th );

PROCESS_THREAD(udp_sender_th, ev, data)
{
  PROCESS_BEGIN();

	//	(1)	Initialize UDP connection
	init_udp();

	//	(2)	Send msg to the destination IP every second
	ctimer_set( &udp_send_timer, CLOCK_SECOND, udp_looper, NULL );

	PROCESS_END();
}
