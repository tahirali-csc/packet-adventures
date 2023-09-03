package main

import (
	"os"
	"os/signal"
	"syscall"

	tracing "github.com/packet-adventures/pkg/tracing"
)

func main() {
	probes, _, err := tracing.LoadProbes()
	if err != nil {
		panic(err)
	}

	osSignal := make(chan os.Signal, 1)
	signal.Notify(osSignal, syscall.SIGINT, syscall.SIGTERM)
	<-osSignal

	probes.UnloadProbes()
}
