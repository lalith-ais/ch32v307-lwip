#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

/* ========== SYSTEM CONFIGURATION ========== */
#define NO_SYS                      1
#define SYS_LIGHTWEIGHT_PROT        0
#define NO_SYS_NO_TIMERS            0
#define LWIP_DEBUG                  0

/* ========== MEMORY CONFIGURATION ========== */
#define MEM_ALIGNMENT               4
#define MEM_SIZE                   (3*1024)     /* 3KB heap for MQTT */

#define MEMP_NUM_PBUF               4
#define MEMP_NUM_UDP_PCB            2
#define MEMP_NUM_TCP_PCB            2
#define MEMP_NUM_TCP_PCB_LISTEN     0
#define MEMP_NUM_TCP_SEG            TCP_SND_QUEUELEN
#define MEMP_NUM_SYS_TIMEOUT        6

/* ========== PBUF CONFIGURATION ========== */
#define PBUF_POOL_SIZE              6           /* For TCP_WND 4KB */
#define PBUF_POOL_BUFSIZE           768         /* 768 bytes each */

/* ========== TCP CONFIGURATION ========== */
#define LWIP_TCP                    1
#define TCP_MSS                     536         /* Reduced for MQTT */
#define TCP_WND                    (4*TCP_MSS)  /* 2144 bytes */
#define TCP_SND_BUF                (4*TCP_MSS)
#define TCP_SND_QUEUELEN           (4* TCP_SND_BUF/TCP_MSS)
#define TCP_TTL                     255
#define TCP_QUEUE_OOSEQ             0

/* ========== PROTOCOL ENABLE ========== */
#define LWIP_UDP                    1
#define LWIP_ICMP                   1
#define LWIP_DHCP                   1
#define LWIP_NETIF_HOSTNAME         1
#define LWIP_RAW                    0            /* Disable for MQTT */

/* ========== DISABLE UNUSED ========== */
#define LWIP_IPV6                   0
#define LWIP_SNMP                   0
#define LWIP_IGMP                   0
#define LWIP_AUTOIP                 0
#define LWIP_DNS                    0
#define LWIP_ALTCP                  0
#define LWIP_ALTCP_TLS              0
#define LWIP_NETCONN                0
#define LWIP_SOCKET                 0
#define LWIP_NETIF_LINK_CALLBACK    0

/* ========== MQTT SPECIFIC ========== */
#define LWIP_MQTT                   1
#define MQTT_REQ_MAX_IN_FLIGHT      2
#define MQTT_OUTPUT_BUFFER_LEN      128
#define MQTT_INPUT_BUFFER_LEN       128
#define MQTT_VAR_HEADER_BUFFER_LEN  64

/* ========== STATISTICS & DEBUG ========== */
#define LWIP_STATS                  0
#define LWIP_PROVIDE_ERRNO          1

/* ========== HARDWARE CHECKSUM ========== */
#define CHECKSUM_BY_HARDWARE

#ifdef CHECKSUM_BY_HARDWARE
  #define CHECKSUM_GEN_IP           0
  #define CHECKSUM_GEN_UDP          0
  #define CHECKSUM_GEN_TCP          0
  #define CHECKSUM_CHECK_IP         0
  #define CHECKSUM_CHECK_UDP        0
  #define CHECKSUM_CHECK_TCP        0
  #define CHECKSUM_GEN_ICMP         0
#else
  #define CHECKSUM_GEN_IP           1
  #define CHECKSUM_GEN_UDP          1
  #define CHECKSUM_GEN_TCP          1
  #define CHECKSUM_CHECK_IP         1
  #define CHECKSUM_CHECK_UDP        1
  #define CHECKSUM_CHECK_TCP        1
  #define CHECKSUM_GEN_ICMP         1
#endif

/* ========== OS/THREAD COMPATIBILITY ========== */
#define DEFAULT_UDP_RECVMBOX_SIZE   10
#define DEFAULT_TCP_RECVMBOX_SIZE   10
#define DEFAULT_ACCEPTMBOX_SIZE     10
#define DEFAULT_THREAD_STACKSIZE    1024
#define TCPIP_THREAD_NAME           "lwip"
#define TCPIP_THREAD_STACKSIZE      512
#define TCPIP_MBOX_SIZE             8
#define TCPIP_THREAD_PRIO           3

#endif /* __LWIPOPTS_H__ */
