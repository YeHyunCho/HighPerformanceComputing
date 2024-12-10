# HighPerformanceComputing

The point of high performance computing is the speed of computer. Computer has two type, one is **sequencial** and the other one is **Parallel**. Sequencial program has one process in one task. So if you try to run 4 programs its speed is going to be four times slower. But when you use the parallel programming, it compensates for the slowdown.

In this lecture, I could learn how to use parallel programming in computer.

## Chapter 1 Instruction

**Hardware**
- Flynn'n taxonomy
- The Von Neumann machine

**Parallel Computers**
- SIMD(Single instruction, Multiple data)
- MIMD(Multiple instruction, Multiple data)

**Software for MIMD Computers**
- Shared memory programming
- Distributed memory(message passing)

## Chapter 2 Performance

**Execution time**
- Time stamp program for wall-clock time(=elapsed time)
- `gettimeofday()`

**CPU time**
- Theoretical time
- Clock syscles counts per instruction

**MFLOPS**
- Millions of Floting-point Operations Per Second

## Chapter 3 Shared Memory Programming

**IPC**
- Inter Process comunication
- Semaphore

**OpenMP(Multi Processing)**
- OpenMP compiler directive
- Parallelizing loops

## Chapter 4 MPI(Message Passing Interface)

**Compile & Run**
- Compile : `mpicc -o filename filename.c`
- Run : `mpiexc -n np filename`

**Structure of MPI programs**
- Initialize MPI program
- Functions, data type and idintifier of MPI

**Basic Routines**
- Get processes's size and rank
- Run on different processors

**Collective coummunication**
- Broadcasting
- Reduction
- Scatter and Gather
- Scatterv and Gatherv

**Grouping data for communication**
- Structure type
- Vector type
- Index data type

**Communicators**
- Create a new communicator from the old communicator
- Splits an old communicator and create new communicators

**Grid Topology**
- MPI_Cart_create()
- MPI_Cart_coords()
- MPI_Cart_rank()
- MPI_Cart_shift()

## Chapter 5 GPU Progamming (CUDA)

**Introduction**
- GPU(Graphic Processing Unit)
- CUDA(Computer Unified Device Architecture)

**CUDA Programming**
- Compile
- Kernel
- Thread Hierarchy
