#include "core_structures.h"
#include "headers/bpf_core_read.h"
#include "headers/bpf_helpers.h"
#include "headers/bpf_tracing.h"

#include "ebpf_internal_types.h"
#include "ebpf_utils.h"

char __license[] SEC("license") = "Dual MIT/GPL";

// the main product of the tracing - map containing all connections observed,
// with metadata and throughput stats.
// key is a whole identifier struct and not a single id to split the constant
// and dynamic values ansrc_ipd to resemble as closely as possible the end result in
// the userspace code.
struct bpf_map_def SEC("maps") connections = {
    .type = BPF_MAP_TYPE_HASH,
    .key_size = sizeof(struct connection_identifier),
    .value_size = sizeof(struct connection_throughput_stats),
    .max_entries = MAX_CONNECTIONS,
};

struct bpf_map_def SEC("maps") ipv4_connections = {
  .type = BPF_MAP_TYPE_HASH,
};

struct id_t {
    u32 pid;
    char task[TASK_COMM_LEN];
};

// helper to convert short int from BE to LE
// static inline u16 be_to_le(__be16 be) { return (be >> 8) | (be << 8); }

// static inline u32 get_unique_id() {
//   return bpf_ktime_get_ns() % __UINT32_MAX__; // no reason to use 64 bit for this
// }


// function for parsing the struct sock
// static inline int
// parse_sock_data(struct sock *sock, struct connection_tuple *out_tuple,
//                 struct connection_throughput_stats *out_throughput) {

//   if (sock == NULL) {
//     return BPF_ERROR;
//   }

//   // struct sock wraps struct tcp_sock and struct inet_sock as its first member
//   struct tcp_sock *tcp = (struct tcp_sock *)sock;
//   struct inet_sock *inet = (struct inet_sock *)sock;

//   // initialize variables. IP addresses and ports are read originally
//   // big-endian, and we will convert the ports to little-endian.
//   __be16 src_port_be = 0;
//   __be16 dst_port_be = 0;

//   // read connection tuple

//   if (0 != bpf_core_read(&out_tuple->src_ip, sizeof(out_tuple->src_ip),
//                       &inet->inet_saddr)) {
//     return BPF_ERROR;
//   }

//   if (0 != bpf_core_read(&out_tuple->dst_ip, sizeof(out_tuple->dst_ip),
//                       &inet->inet_daddr)) {
//     return BPF_ERROR;
//   }

//   if (0 != bpf_core_read(&src_port_be, sizeof(src_port_be), &inet->inet_sport)) {
//     return BPF_ERROR;
//   }
//   out_tuple->src_port = be_to_le(src_port_be);

//   if (0 != bpf_core_read(&dst_port_be, sizeof(dst_port_be), &inet->inet_dport)) {
//     return BPF_ERROR;
//   }
//   out_tuple->dst_port = be_to_le(dst_port_be);

//   // read throughput data

//   if (0 != bpf_core_read(&out_throughput->bytes_received,
//                       sizeof(out_throughput->bytes_received),
//                       &tcp->bytes_received)) {
//     return BPF_ERROR;
//   }
//   if (0 != bpf_core_read(&out_throughput->bytes_sent,
//                       sizeof(out_throughput->bytes_sent), &tcp->bytes_sent)) {
//     return BPF_ERROR;
//   }

//   return BPF_SUCCESS;
// };

// static inline int handle_set_tcp_syn_recv(struct sock* sock) {
//     // this is a server getting syn after listen
//     struct connection_identifier conn_id = {};
//     struct connection_throughput_stats throughput = {};

//     if (parse_sock_data(sock, &conn_id.tuple, &throughput) == BPF_ERROR) {
//       return BPF_ERROR;
//     }

//     struct sock_info info = {
//         .pid = 0, // can't associate to process
//         .role = CONNECTION_ROLE_SERVER,
//         .is_active = true,
//         .id = get_unique_id(),
//     };

//     // bpf_map_update_elem(&sock_infos, &sock, &info, BPF_ANY);

//     // probably the dst ip will still be uninitialized
//     if (conn_id.tuple.dst_ip == 0) {
//       return BPF_SUCCESS;
//     }

//     conn_id.pid = info.pid;
//     conn_id.id = info.id;
//     conn_id.role = info.role;

//     bpf_map_update_elem(&connections, &conn_id, &throughput, BPF_ANY);

//     return BPF_SUCCESS;
// }

// static inline int handle_set_tcp_syn_sent(struct sock* sock) {
//   // start of a client session
//   u32 pid = bpf_get_current_pid_tgid() >> 32;

//   struct sock_info info = {
//       .pid = pid,
//       .role = CONNECTION_ROLE_CLIENT,
//       .is_active = true,
//       .id = get_unique_id(),
//   };

//   bpf_map_update_elem(&sock_infos, &sock, &info, BPF_ANY);

//   return BPF_SUCCESS;
// }

SEC("tracepoint/sock/inet_sock_set_state")
int handle_sock_set_state(struct set_state_args *args){
    u32 pid = bpf_get_current_pid_tgid() >> 32;
    // struct sock *sock = (struct sock *)args->skaddr;

    struct connection_identifier conn_id = {};
    // struct connection_throughput_stats throughput = {};


    // if (parse_sock_data(sock, &conn_id.tuple, &throughput) == BPF_ERROR) {
    //   return BPF_ERROR;
    // }

    if(args->newstate == TCP_SYN_SENT || args->newstate == TCP_LAST_ACK){
      struct id_t me = {.pid = pid};
      bpf_get_current_comm(&me.task, sizeof(me.task));

      if(0 != bpf_core_read(&conn_id.tuple.src_ip, sizeof(conn_id.tuple.src_ip), args->saddr)){
        return BPF_ERROR;
      }
    } else if (args->newstate == TCP_CLOSE){

    }

    // switch (args->newstate){
    //     case TCP_SYN_RECV: {
    //         return handle_set_tcp_syn_recv(sock) == BPF_ERROR;
    //     case TCP_SYN_SENT: {
    //          return handle_set_tcp_syn_sent(sock) == BPF_ERROR;
    //     }
    // }

    return 0;
}