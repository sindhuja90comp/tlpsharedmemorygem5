# tlpsharedmemorygem5
# gem5 Simulation: MinorCPU with Multi-threaded DAXPY

This project demonstrates a shared-memory simulation using gem5's `MinorCPU` and analyzes thread-level parallelism through a multi-threaded DAXPY kernel.

---

## 📁 Project Structure

gem5/ 
# gem5 source directory ├── build/X86/gem5.opt 
# gem5 binary (compiled for X86) 
├── configs/ 
│ └── learning_gem5/ 
│ └── part1/ 
│ └── simple.py 

# Main config file for simulation ├── m5out/ 
# Output directory for gem5 results newcode/ ├── daxpy_threaded.cpp 
# Multi-threaded DAXPY C++ code ├── daxpy_threaded 
# Compiled binary (for X86) ├── BasicMinorCPU_1.py 
# Script with modified FU parameters

yaml

---

## 🔧 Requirements

- gem5 v23.0.0.1 or compatible
- Python 3.x
- pydot (optional for dot graph generation)

```bash
sudo apt install python3-pydot
If using a virtual environment:
python3 -m venv venv
source venv/bin/activate
pip install pydot

⚙️ Compilation Steps
1. Build gem5
From the gem5/ directory:
scons build/X86/gem5.opt -j$(nproc)

2. Compile DAXPY C++ Code
Navigate to your code directory and compile:
cd ~/newcode
g++ daxpy_threaded.cpp -o daxpy_threaded
Make sure this binary is specified in the simulation script.

▶️ Run Simulation
From the gem5/ directory:

build/X86/gem5.opt configs/learning_gem5/part1/simple.py \
  --cpu-type=MinorCPU \
  --sys-clock=1GHz \
  --num-cpus=4 \
  --script=newcode/BasicMinorCPU_1.py
Ensure the path to BasicMinorCPU_1.py is correct.

📊 Output
Simulation output will be stored in m5out/. Key files include:

stats.txt — Performance statistics

config.ini — Simulation configuration

config.dot — System graph (requires pydot)

Terminal log — Simulation progress and debug messages

📝 Notes
The warning DRAM device capacity... is expected if memory sizes mismatch but doesn’t break simulation.

The message Exiting @ tick... means the simulation completed execution.

