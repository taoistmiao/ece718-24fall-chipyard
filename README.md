## Setup 
```bash
docker pull condaforge/miniforge3
docker run -it condaforge/miniforge3 /bin/bash
git clone https://github.com/taoistmiao/ece718-24fall-chipyard.git /chipyard
cd /chipyard
git switch ece718-24fall
conda install -n base conda-libmamba-solver
conda config --set solver libmamba
./build-setup.sh riscv-tools -s 6 -s 7 -s 8 -s 9
```

## run a binary
```bash
cd sims/verilator/
make run-binary BINARY=../../tests/build/hello.riscv CONFIG=SpMMRocketConfig LOADMEM=1
```
## dump wave
```bash
make run-binary-debug BINARY=../../tests/build/hello.riscv CONFIG=SpMMRocketConfig LOADMEM=1
```
