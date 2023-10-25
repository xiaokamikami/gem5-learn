import m5
from m5.objects import *
from cache import *

# create config
from optparse import OptionParser

parser = OptionParser()
parser.add_option("--cpu_type", help="Cpu type")
parser.add_option("--l1i_size", help="L1 instruction cache size")
parser.add_option("--l1d_size", help="L1 data cache size")
parser.add_option("--l2_size", help="Unified L2 cache size")
parser.add_option("--l3_size", help="Unified L3 cache size")

(options, args) = parser.parse_args()
print("\033[34moptions %s ",options,"\n\033[0m")
# init
system = System()
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = "1GHz"
system.clk_domain.voltage_domain = VoltageDomain()
system.mem_mode = "timing"
system.mem_ranges = [AddrRange("4096MB")]

# create riscvCPU
if(options.cpu_type == "O3CPU") :
    print("run o3")
    system.cpu = RiscvO3CPU()
else :
    print("run simple")
    system.cpu = RiscvTimingSimpleCPU()
    
# create L1cache
system.cpu.icache = L1ICache(options)
system.cpu.dcache = L1DCache(options)

system.membus = SystemXBar()

system.cpu.icache.connectCPU(system.cpu)
system.cpu.dcache.connectCPU(system.cpu)

# system.cpu.icache_port = system.membus.cpu_side_ports
# system.cpu.dcache_port = system.membus.cpu_side_ports

# create L2 bus
system.l2bus = L2XBar()

system.cpu.icache.connectBus(system.l2bus)
system.cpu.dcache.connectBus(system.l2bus)

# create L2cache
system.l2cache = L2Cache(options)
system.l2cache.connectCPUSideBus(system.l2bus)

# create L3 bus
system.l3bus = L3XBar()
system.l2cache.connectMemSideBus(system.l3bus)

# create L3 cache
system.l3cache = L3Cache(options)
system.l3cache.connectCPUSideBus(system.l3bus)

system.l3cache.connectMemSideBus(system.membus)

system.cpu.createInterruptController()
# create a memory controller and connect it to the membus

system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR4_2400_8x8()
system.mem_ctrl.dram.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.mem_side_ports

binary = "tests/test-progs/hello/bin/riscv/linux/hello"

# for gem5 V21 and beyond
system.workload = SEWorkload.init_compatible(binary)

process = Process()
process.cmd = [binary]
system.cpu.workload = process
system.cpu.createThreads()

root = Root(full_system=False, system=system)

m5.instantiate()

print("Beginning simulation!")
exit_event = m5.simulate()
print(
    "Exiting @ tick {} because {}".format(m5.curTick(), exit_event.getCause())
)
