List all tracepoint in `sock`
```bash
sudo ls -la /sys/kernel/debug/tracing/events/sock/
```

Show the args of `inet_sock_set_state`
```bash
sudo cat /sys/kernel/debug/tracing/events/sock/inet_sock_set_state/format
```

Generate the vmlinux
https://blog.aquasec.com/vmlinux.h-ebpf-programs