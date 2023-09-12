#ifndef __CORE_STRUCTURES_H__
#define __CORE_STRUCTURES_H__

#include "headers/vmlinux.h"

// this is not core structure per se, but it would have been defined in a full
// vmlinux.h
enum {
  false = 0,
  true = 1,
};

enum {
  TCP_ESTABLISHED = 1,
  TCP_SYN_SENT = 2,
  TCP_SYN_RECV = 3,
  TCP_FIN_WAIT1 = 4,
  TCP_FIN_WAIT2 = 5,
  TCP_TIME_WAIT = 6,
  TCP_CLOSE = 7,
  TCP_CLOSE_WAIT = 8,
  TCP_LAST_ACK = 9,
  TCP_LISTEN = 10,
  TCP_CLOSING = 11,
  TCP_NEW_SYN_RECV = 12,
  TCP_MAX_STATES = 13,
};

struct in6_addr {
  union {
    __u8 u6_addr8[16];
  } in6_u;
};

struct sock_common {
  struct {
    __be32 skc_daddr;
    __be32 skc_rcv_saddr;
  };
  struct {
    __be16 skc_dport;
    __u16 skc_num;
  };
  unsigned short skc_family;
  struct in6_addr skc_v6_daddr;
};

struct sock {
  struct sock_common __sk_common;
};

struct ipv6_pinfo {
  struct in6_addr saddr;
};

struct inet_sock {
  struct sock sk;
  struct ipv6_pinfo *pinet6;
  __be32 inet_saddr;
  __be16 inet_sport;
};

struct tcp_sock {
  u64 bytes_received;
  u64 bytes_sent;
};

typedef u8 u_int8_t;
typedef u16 u_int16_t;

#endif // __KERNEL_CORE_STRUCTURES_H__