#include "core_structures.h"
#include "headers/bpf_core_read.h"
#include "headers/bpf_helpers.h"
#include "headers/bpf_tracing.h"

char __license[] SEC("license") = "Dual MIT/GPL";

SEC("tracepoint/sock/inet_sock_set_state")
int handle_sock_set_state(){
    return 0;
}