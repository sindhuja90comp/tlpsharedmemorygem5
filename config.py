import m5
from m5.objects import *
import sys

# Add gem5 root to path (adjust if needed)
sys.path.append('/home/sindhuja/gem5')

# Instantiate the system
system = System()
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = '1GHz'
system.clk_domain.voltage_domain = VoltageDomain()
system.mem_mode = 'timing'
system.mem_ranges = [AddrRange('512MB')]

# Create memory controller
system.mem_bus = SystemXBar()
system.bridge = ToMemoryBusBridge()
system.bridge.master = system.mem_bus.slave
system.system_port = system.bridge.slave
system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR3_1600_8x8()
system.mem_ctrl.dram.range = system.mem_ranges[0]
system.mem_ctrl.port = system.mem_bus.master

# Create multiple CPU cores
system.cpu = [DerivO3CPU() for i in range(4)]

# Create L1 and L2 caches
for cpu in system.cpu:
    cpu.icache = L1I_Cache()
    cpu.dcache = L1D_Cache()
    cpu.icache.connectCPU(cpu)
    cpu.dcache.connectCPU(cpu)
system.l2_bus = L2XBar()
system.l2cache = L2Cache()
system.l2cache.connectBus(system.l2_bus.slave)
for cpu in system.cpu:
    cpu.icache.connectBus(system.l2_bus.master)
    cpu.dcache.connectBus(system.l2_bus.master)
system.l2_bus.master = system.mem_bus.slave

# Create process for DAXPY
process = Process()
process.cmd = ['/home/sindhuja/newcode/daxpy_threaded']
system.cpu[0].workload = process
system.cpu[0].createThreads()

system.system_port = system.bridge.slave
root = Root(full_system=False, system=system)
m5.instantiate()

print("Beginning simulation!")
exit(m5.simulate())