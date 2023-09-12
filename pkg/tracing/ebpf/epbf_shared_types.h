#ifndef __EBPF_SHARED_TYPES_H__
#define __EBPF_SHARED_TYPES_H__
#include "headers/vmlinux.h"

// helper defs for inet_sock. These are defined in inet_sock.h, but not copied
// automatically to vmlinux.h
#define inet_daddr sk.__sk_common.skc_daddr
#define inet_rcv_saddr sk.__sk_common.skc_rcv_saddr
#define inet_dport sk.__sk_common.skc_dport
#define inet_num sk.__sk_common.skc_num


enum connection_role {
  CONNECTION_ROLE_UNKNOWN = 0,
  CONNECTION_ROLE_CLIENT,
  CONNECTION_ROLE_SERVER,
};

// describing two sides of a connection. constant for each connection.
struct connection_tuple {
  __be32 src_ip;
  __be32 dst_ip;
  u16 src_port;
  u16 dst_port;
};

// all information needed to identify a specific connection.
// due to socket reuses, each of the members (beside id) may change while
// maintaining the others.
struct connection_identifier {
  u32 id; // uniquely generated id
  u32 pid;
  struct connection_tuple tuple;
  enum connection_role role;
};

struct ipv4_connection_tuple {
  __be32 src_ip;
  __be32 dst_ip;
  u16 src_port;
  u16 dst_port;
};

// dynamic information about the state of a connection.
struct connection_throughput_stats {
  u64 bytes_sent;
  u64 bytes_received;
  u64 is_active; // u64 because it will be padded anyway. should change whether
                // new members are added
};

#define TASK_COMM_LEN 16

// separate data structs for ipv4 and ipv6
struct ipv4_data_t {
    u64 ts_us;
    u32 pid;
    u32 saddr;
    u32 daddr;
    u64 ports;
    u64 rx_b;
    u64 tx_b;
    u64 span_us;
    char task[TASK_COMM_LEN];
};

struct ipv6_data_t {
    u64 ts_us;
    u32 pid;
    unsigned __int128 saddr;
    unsigned __int128 daddr;
    u64 ports;
    u64 rx_b;
    u64 tx_b;
    u64 span_us;
    char task[TASK_COMM_LEN];
};



#endif