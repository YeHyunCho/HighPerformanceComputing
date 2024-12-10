# HighPerformanceComputing

The point of high performance computing is the speed of computer. Computer has two type, one is **sequencial** and the other one is **Parallel**. Sequencial program has one process in one task. So if you try to run 4 programs its speed is going to be four times slower. But when you use the parallel instead of sequencial, it compensates for the slowdown.

In this lecture, I could learn how to use parallel programming in computer.

## Chapter 1 Instruction

**1. Hardware**   
\- Flynn's taxonomy   
\- The Von Neumann machine   

**2. Parallel Computers**   
\- SIMD(Single instruction, Multiple data)   
\- MIMD(Multiple instruction, Multiple data)   

**3. Software for MIMD Computers**   
\- Shared memory programming   
\- Distributed memory(message passing)   

## Chapter 2 Performance

**1. Execution time**   
\- Time stamp program for wall-clock time(=elapsed time)   
\- `gettimeofday()`   

**2. CPU time**   
\- Theoretical time   
\- Clock syscles counts per instruction   

**3. MFLOPS**   
\- Millions of Floting-point Operations Per Second   

## Chapter 3 Shared Memory Programming

**1. IPC**   
\- Inter Process comunication   
\- Semaphore   

**2. OpenMP(Multi Processing)**   
\- OpenMP compiler directive   
\- Parallelizing loops   

## Chapter 4 MPI(Message Passing Interface)

**1. Compile & Run**   
\- Compile : `mpicc -o filename filename.c`   
\- Run : `mpiexc -n np filename`   

**2. Structure of MPI programs**   
\- Initialize MPI program   
\- Functions, data type and idintifier of MPI   

**3. Basic Routines**   
\- Get processes's size and rank   
\- Run on different processors   

**4. Collective coummunication**   
\- Broadcasting   
\- Reduction   
\- Scatter and Gather   
\- Scatterv and Gatherv   

**5. Grouping data for communication**   
\- Structure type    
\- Vector type   
\- Index data type   

**6. Communicators**   
\- Create a new communicator from the old communicator   
\- Splits an old communicator and create new communicators   

**7. Grid Topology**   
\- MPI_Cart_create()   
\- MPI_Cart_coords()   
\- MPI_Cart_rank()   
\- MPI_Cart_shift()   

## Chapter 5 GPU Progamming (CUDA)

**1. Introduction**   
\- GPU(Graphic Processing Unit)   
\- CUDA(Computer Unified Device Architecture)   

**2. CUDA Programming**   
\- Compile   
\- Kernel   
\- Thread Hierarchy   
