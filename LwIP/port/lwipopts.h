#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#include "../../WICED/WICED/WWD/include/network/wwd_network_constants.h"
#include <stdlib.h>

#define MEM_LIBC_MALLOC 1

#define MEM_ALIGNMENT 4

#define LWIP_DHCP 1

#define LWIP_DNS 1

#define LWIP_TIMEVAL_PRIVATE 0

#define LWIP_NETIF_HOSTNAME 1
static char *lwip_hostname_ptr="EMW3165-Template"; // For weird WICED code.

#define TCPIP_THREAD_PRIO 7

#define TCPIP_THREAD_STACKSIZE 900

#define DEFAULT_RAW_RECVMBOX_SIZE 5

#define DEFAULT_TCP_RECVMBOX_SIZE 5

#define DEFAULT_UDP_RECVMBOX_SIZE 5

#define DEFAULT_ACCEPTMBOX_SIZE 5

#define TCPIP_MBOX_SIZE 10


/**
 * MEMP_NUM_NETBUF: the number of struct netbufs.
 * (only needed if you use the sequential API, like api_lib.c)
 */
#define MEMP_NUM_NETBUF                (PBUF_POOL_SIZE)


/**
 * MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP segments.
 * (requires the LWIP_TCP option)
 */
#define MEMP_NUM_TCP_SEG               (TCP_SND_QUEUELEN+1)

/** STF 8
 * PBUF_POOL_SIZE: the number of buffers in the pbuf pool.
 *
 * This is just a default designed to be overriden by the FreeRTOS.mk makefile
 * To perform this override, define the makefile variable LWIP_NUM_PACKET_BUFFERS_IN_POOL
 */
#ifndef PBUF_POOL_TX_SIZE
#define PBUF_POOL_TX_SIZE                 (7)
#endif

#ifndef PBUF_POOL_RX_SIZE
#define PBUF_POOL_RX_SIZE                 (7)
#endif

/*
 * IP_REASS_MAX_PBUFS: Total maximum amount of pbufs waiting to be reassembled.
 * Since the received pbufs are enqueued, be sure to configure
 * PBUF_POOL_SIZE > IP_REASS_MAX_PBUFS so that the stack is still able to receive
 * packets even if the maximum amount of fragments is enqueued for reassembly!
 *
 */
#if PBUF_POOL_TX_SIZE > 2
#ifndef IP_REASS_MAX_PBUFS
#define IP_REASS_MAX_PBUFS              (PBUF_POOL_TX_SIZE - 2)
#endif
#else
#define IP_REASS_MAX_PBUFS              0
#define IP_REASSEMBLY                   0
#endif

/**
 * MEMP_NUM_REASSDATA: the number of IP packets simultaneously queued for
 * reassembly (whole packets, not fragments!)
 */
#if IP_REASS_MAX_PBUFS > 1
#ifndef MEMP_NUM_REASSDATA
#define MEMP_NUM_REASSDATA              (IP_REASS_MAX_PBUFS - 1)
#endif
#else
#define MEMP_NUM_REASSDATA              0
#endif
/**
 * PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. The default is
 * designed to accomodate single full size TCP frame in one pbuf, including
 * TCP_MSS, IP header, and link header.
 */
#define PBUF_POOL_BUFSIZE              (LWIP_MEM_ALIGN_SIZE(WICED_LINK_MTU) + LWIP_MEM_ALIGN_SIZE(16) + 1)


/**
 * TCP_MSS: TCP Maximum segment size. (default is 536, a conservative default,
 * you might want to increase this.)
 * For the receive side, this MSS is advertised to the remote side
 * when opening a connection. For the transmit size, this MSS sets
 * an upper limit on the MSS advertised by the remote host.
 */
#if 0
#define TCP_MSS                        (WICED_PAYLOAD_MTU-20-20)  /* TODO: Cannot use full Ethernet MTU since LwIP concatenates segments which are too long. */
#else /* if 0 */
#define TCP_MSS                        (1152)
#endif /* if 0 */


/**
 * TCP_SND_BUF: TCP sender buffer space (bytes).
 * must be at least as much as (2 * TCP_MSS) for things to work smoothly
 */
#ifdef TX_PACKET_POOL_SIZE
#define TCP_SND_BUF                    ((TX_PACKET_POOL_SIZE/2) * TCP_MSS)
#else
#define TCP_SND_BUF                    (6 * TCP_MSS)
#endif

/* TCP Window size */
#ifdef RX_PACKET_POOL_SIZE
#define TCP_WND                        ((RX_PACKET_POOL_SIZE/2) * TCP_MSS)
#endif

/**
 * ETH_PAD_SIZE: the header space required preceeding the of each pbuf in the pbuf pool. The default is
 * designed to accomodate single full size TCP frame in one pbuf, including
 * TCP_MSS, IP header, and link header.
 *
 * This is zero since the role has been taken over by SUB_ETHERNET_HEADER_SPACE as ETH_PAD_SIZE was not always obeyed
 */
#define ETH_PAD_SIZE                   (0)

#define SUB_ETHERNET_HEADER_SPACE      (WICED_LINK_OVERHEAD_BELOW_ETHERNET_FRAME_MAX)


/**
 * PBUF_LINK_HLEN: the number of bytes that should be allocated for a
 * link level header. The default is 14, the standard value for
 * Ethernet.
 */
#define PBUF_LINK_HLEN                 (WICED_PHYSICAL_HEADER)


/**
 * LWIP_NETIF_TX_SINGLE_PBUF: if this is set to 1, lwIP tries to put all data
 * to be sent into one single pbuf. This is for compatibility with DMA-enabled
 * MACs that do not support scatter-gather.
 * Beware that this might involve CPU-memcpy before transmitting that would not
 * be needed without this flag! Use this only if you need to!
 *
 * @todo: TCP and IP-frag do not work with this, yet:
 */
/* TODO: remove this option once buffer chaining has been implemented */
#define LWIP_NETIF_TX_SINGLE_PBUF      (1)



/**
 * SYS_LIGHTWEIGHT_PROT==1: if you want inter-task protection for certain
 * critical regions during buffer allocation, deallocation and memory
 * allocation and deallocation.
 */
#define SYS_LIGHTWEIGHT_PROT           (1)



#define TCP_LISTEN_BACKLOG     (1)


/**
 * MEMP_NUM_SYS_TIMEOUT: the number of simulateously active timeouts.
 * (requires NO_SYS==0)
  * Must be larger than or equal to LWIP_TCP + IP_REASSEMBLY + LWIP_ARP + (2*LWIP_DHCP) + LWIP_AUTOIP + LWIP_IGMP + LWIP_DNS + PPP_SUPPORT
 */
#define MEMP_NUM_SYS_TIMEOUT           (8)


/* ARP before DHCP causes multi-second delay  - turn it off */
#define DHCP_DOES_ARP_CHECK            (0)

/* ARP Queue size needs to be reduced to avoid using up all PBUFs when SoftAP is in use under load in busy environments */
#define MEMP_NUM_ARP_QUEUE              5

/**
 * LWIP_NETIF_LOOPBACK==1: Support sending packets with a destination IP
 * address equal to the netif IP address, looping them back up the stack.
 */
#define LWIP_NETIF_LOOPBACK            (0)

/**
 * MEMP_NUM_NETCONN: the number of struct netconns.
 * (only needed if you use the sequential API, like api_lib.c)
 */
#define MEMP_NUM_NETCONN               (18)

/**
 * LWIP_SO_RCVTIMEO==1: Enable SO_RCVTIMEO processing.
 */
#define LWIP_SO_RCVTIMEO               (1)


/**
 * LWIP_IGMP==1: Turn on IGMP module.
 */
#define LWIP_IGMP                      (1)


/**
 * SO_REUSE==1: Enable SO_REUSEADDR option.
 * Required by IGMP for reuse of multicast address and port by other sockets
 */
#define SO_REUSE                       (1)


#define LWIP_TCP_KEEPALIVE             (1)


#ifdef LWIP_SO_RCVBUF
#if ( LWIP_SO_RCVBUF == 1 )
#include <limits.h>  /* Needed because RECV_BUFSIZE_DEFAULT is defined as INT_MAX */
#endif /* if ( LWIP_SO_RCVBUF == 1 ) */
#endif /* ifdef LWIP_SO_RCVBUF */

/**
 * LWIP_STATS : Turn off statistics gathering
 */
#ifdef WICED_LWIP_DEBUG
#define LWIP_STATS                     (1)
#else
#define LWIP_STATS                     (0)
#endif /* ifdef WICED_LWIP_DEBUG */

/**
 * Use a random number generator to assign local TCP ports for
 * outgoing connections
 */
#define LWIP_RANDOM_INITIAL_TCP_PORT


/* Enable IP address change notification */
#define LWIP_NETIF_IP_CHANGE_CALLBACK (1)

/**
 * Debug printing
 * By default enable debug printing for debug build, but set level to off
 * This allows user to change any desired debug level to on.
 */

#ifdef WICED_LWIP_DEBUG
#define LWIP_DEBUG
#define MEMP_OVERFLOW_CHECK            ( 2 )
#define MEMP_SANITY_CHECK              ( 1 )

#define MEM_DEBUG                      (LWIP_DBG_OFF)
#define MEMP_DEBUG                     (LWIP_DBG_OFF)
#define PBUF_DEBUG                     (LWIP_DBG_OFF)
#define API_LIB_DEBUG                  (LWIP_DBG_OFF)
#define API_MSG_DEBUG                  (LWIP_DBG_OFF)
#define TCPIP_DEBUG                    (LWIP_DBG_OFF)
#define NETIF_DEBUG                    (LWIP_DBG_OFF)
#define SOCKETS_DEBUG                  (LWIP_DBG_OFF)
#define DEMO_DEBUG                     (LWIP_DBG_OFF)
#define IP_DEBUG                       (LWIP_DBG_OFF)
#define IP_REASS_DEBUG                 (LWIP_DBG_OFF)
#define RAW_DEBUG                      (LWIP_DBG_OFF)
#define ICMP_DEBUG                     (LWIP_DBG_OFF)
#define UDP_DEBUG                      (LWIP_DBG_OFF)
#define TCP_DEBUG                      (LWIP_DBG_OFF)
#define TCP_INPUT_DEBUG                (LWIP_DBG_OFF)
#define TCP_OUTPUT_DEBUG               (LWIP_DBG_OFF)
#define TCP_RTO_DEBUG                  (LWIP_DBG_OFF)
#define TCP_CWND_DEBUG                 (LWIP_DBG_OFF)
#define TCP_WND_DEBUG                  (LWIP_DBG_OFF)
#define TCP_FR_DEBUG                   (LWIP_DBG_OFF)
#define TCP_QLEN_DEBUG                 (LWIP_DBG_OFF)
#define TCP_RST_DEBUG                  (LWIP_DBG_OFF)
#define PPP_DEBUG                      (LWIP_DBG_OFF)
#define ETHARP_DEBUG                   (LWIP_DBG_OFF)
#define IGMP_DEBUG                     (LWIP_DBG_OFF)
#define INET_DEBUG                     (LWIP_DBG_OFF)
#define SYS_DEBUG                      (LWIP_DBG_OFF)
#define TIMERS_DEBUG                   (LWIP_DBG_OFF)
#define SLIP_DEBUG                     (LWIP_DBG_OFF)
#define DHCP_DEBUG                     (LWIP_DBG_OFF)
#define AUTOIP_DEBUG                   (LWIP_DBG_OFF)
#define SNMP_MSG_DEBUG                 (LWIP_DBG_OFF)
#define SNMP_MIB_DEBUG                 (LWIP_DBG_OFF)
#define DNS_DEBUG                      (LWIP_DBG_OFF)

#define LWIP_DBG_TYPES_ON              (LWIP_DBG_OFF)   /* (LWIP_DBG_ON|LWIP_DBG_TRACE|LWIP_DBG_STATE|LWIP_DBG_FRESH|LWIP_DBG_HALT) */
#endif

#endif /* __LWIPOPTS_H__ */
