#/bin/sh
# clang -g -O2 -Wall -target bpf -D__TARGET_ARCH_x86_64 -c tcplife.bpf.c -o tcplife.bpf.o


# clang -g -O2 -Wall -target bpf -D__TARGET_ARCH_x86	      \
# 	     -Ix86/ -I/home/tahir.linux/libbpfgo-tools/bcc/libbpf-tools/.output -I../src/cc/libbpf/include/uapi -c tcplife.bpf.c -o /home/tahir.linux/libbpfgo-tools/bcc/libbpf-tools/.output/tcplife.bpf.o &&      \
# llvm-strip -g /home/tahir.linux/libbpfgo-tools/bcc/libbpf-tools/.output/tcplife.bpf.o

clang -g -O2 -Wall -target bpf -D__TARGET_ARCH_x86 -c tcplife.bpf.c -o tcplife.bpf.o 
llvm-strip -g tcplife.bpf.o
cp tcplife.bpf.o ../
