OPT_LIB    =build/RISCV/gem5.opt
CPU_TYPE   ='O3CPU'
Debug_Flag =CommitLoad
OPTIONS    =--l3_size='2MB' --l2_size='256kB' --l1d_size='16kB' --l1i_size='16kB' --dump_cache='0'
scons:
	scons $(OPT_LIB) -j16

run_simple:
	$(OPT_LIB) configs/tutorial/simple.py --cpu_type='TimingSimpleCPU' \
	$(OPTIONS) PROTOCOL=MOESI_hammer RUBY=True
run:
	$(OPT_LIB) configs/tutorial/simple.py --cpu_type=$(CPU_TYPE) \
	$(OPTIONS) PROTOCOL=MOESI_hammer RUBY=True

run_debug:
	$(OPT_LIB) --debug-flags=$(Debug_Flag) \
	configs/tutorial/simple.py --cpu_type=$(CPU_TYPE) \
	$(OPTIONS) PROTOCOL=MOESI_hammer RUBY=True 

help:
	$(OPT_LIB) configs/tutorial/simple.py --help

help_trace:
	$(OPT_LIB) --debug-help configs/tutorial/simple.py