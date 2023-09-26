#/bin/sh
CC=clang CGO_CFLAGS="-I/home/tahir.linux/libbpfgo-tools/bcc/libbpf-tools/.output" \
CGO_LDFLAGS="-lelf -lz -lzstd ./libbpf/src/build/libbpf.a" go build -tags netgo -ldflags '-w -extldflags "-static"' main.go