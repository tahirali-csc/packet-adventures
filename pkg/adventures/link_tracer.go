package adventures

import (
	"github.com/cilium/ebpf"
	"github.com/packet-adventures/pkg/tracing"
)

type LinksTracer struct {
	ebpfObjects *tracing.Probes
	connections *ebpf.Map
}

func NewLinkTracer() *LinksTracer {
	return &LinksTracer{}
}

func (tracer *LinksTracer) Start() error {
	objs, connMap, err := tracing.LoadProbes()
	if err != nil {
		return err
	}

	tracer.ebpfObjects = &objs
	tracer.connections = connMap
	return nil
}

func (tracer *LinksTracer) Stop() error {
	//tracer.resolver.StopWatching()
	return tracer.ebpfObjects.UnloadProbes()
}
