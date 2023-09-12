#include "epbf_shared_types.h"

#define MAX_CONNECTIONS 1000000

// internal kernel-only struct to hold socket information which can't be parsed
// from struct sock.
struct sock_info {
  u32 pid;
  enum connection_role role;
  u32 is_active;
  u32 id;
};

// partial struct of args for tcp_set_state
struct set_state_args {
  u64 padding;
  struct sock *skaddr;
  u32 oldstate;
  u32 newstate;
  // more...

  __u8 saddr[4];
	__u8 daddr[4];
	__u8 saddr_v6[16];
	__u8 daddr_v6[16];
};
