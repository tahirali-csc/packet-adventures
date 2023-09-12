package main

import (
	"github.com/packet-adventures/pkg/adventures"
	"os"
	"os/signal"
	"syscall"
)

func main() {

	linkTracer := adventures.NewLinkTracer()
	if err := linkTracer.Start(); err != nil {
		panic(err)
	}

	osSignal := make(chan os.Signal, 1)
	signal.Notify(osSignal, syscall.SIGINT, syscall.SIGTERM)
	<-osSignal

	linkTracer.Stop()
}
