# Philosophers
The aim of this project is to resolve [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) with threads and mutexes

## Rules
• One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.

• The philosophers alternatively **eat**, **think**, or **sleep**.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.

• There are also forks on the table. There are as many forks as philosophers.

• Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.

• When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.

• Every philosopher needs to eat and should never starve.

• Philosophers don’t speak with each other.

• Philosophers don’t know if another philosopher is about to die.

• Philosophers should avoid dying!

## Parallel Computing

Traditionally, software has been written for **serial** computation (meaning discrete series of instructions, executed on a single processor and sequentially). However, in **parallel computing**, parts of the problem can be executed concurrently and simultaneously on different processors.

![image](https://github.com/valentinefleith/Philosophers/assets/125041345/b5281f55-4331-4460-a37c-93f503af732e)
It is closer to real world problems, where many events happen at the same time (planetary movement etc.) and can help modelling and solving complex problems.
Also this is closer to computer architecture with parallel CPU.

#### Neumann Computer Architecture
First computer has 4 main components:
- **Memory**
- **Control Unit**, which fetches instructions/data from memory, decodes the instructions and then sequentially coordinates operations to accomplish the programmed task.
- **Arithmetic Logic Unit** which performs basic arithmetic operations
- **Input/Output**
  
![image](https://github.com/valentinefleith/Philosophers/assets/125041345/614782d7-a480-467f-adef-f66c5482e090)

Parallel computers still follow this basic architecture, but multiplied in units. 
#### Flynn's taxonomy

There are many different parallel computer types :
- **Single Instruction, Multiple Data (SIMD)**, all processors execute the same instruction at any given clock cycle, but can operate on a different data element.
- **Multiple Instruction, Single Data (MISD)**, each processing unit operates on the data independantly via separate instruction streams, but a single data stream is fed into multiple processing units.
- **Multiple Instruction, Multiple Data (MIMD)**, every processor may exec diffrent instruction and work on a different data stream.

#### Parallel Computer Memory Architectures
There are 3 main architectures : **Shared Memory**, **Distributed Memory** and **Hybrid Distributed-Shared Memory**.

**Shared Memory** : all processors can access all memory as global address space. Can be uniform memory access (equal access) or non-uniform memory access (linking, not all processors have equal access time).

Advantages are data sharing between tasks is fast and uniform, but disadvantage is more responsability for programmer to ensure correct access and traffic on the memory and memory path.

![image](https://github.com/valentinefleith/Philosophers/assets/125041345/8b71cb1a-5371-424f-9272-a6fedacf7e16)

**Distributed Memory** : processors have their own local memory (it operates independently). 

Advantages are that each processor has fast access to its own memory, but inconvenients are non uniform access time + programmer is responsible for data communication between processors.

![image](https://github.com/valentinefleith/Philosophers/assets/125041345/f337c359-b2ba-46b8-bb6d-f6911393dd25)

**Hybrid Distributed-Shared Memory** : also shared with GPU, used by the largest and fastest computers in the world.

Advantage is increased scalability, disadvantage is increased programmer complexity.

![image](https://github.com/valentinefleith/Philosophers/assets/125041345/debd3492-0d35-4406-a6cd-c78f4ac9ca4c)



## Threads
A thread of execution is the smallest sequence of programmed instructions that can be managed independently by a scheduler. There is always at least 1 thread for a process. Also each thread has its private data.

Threads model is a type of shared memory programming. Threads communicate with each other through global memory (updating address locations).

![image](https://github.com/valentinefleith/Philosophers/assets/125041345/4ace7b77-ee52-4869-89f2-f764749f5e9d)

The programmer is responsible for determining the parallelism. 2 implementations of threads : *POSIX Threads* and *OpenMP*. (for this project, we use POSIX Threads, also referred as Pthreads).

3 essential facilities : _Execution context_, _Scheduling_, and _Synchronization_. Few examples :

![image](https://github.com/valentinefleith/Philosophers/assets/125041345/181ee8f0-04df-4403-b436-ef32f2196d60)


## Ressources
- [Threads (Wikipedia)](https://en.wikipedia.org/wiki/Thread_(computing))
- [Parallel Computing](https://hpc.llnl.gov/documentation/tutorials/introduction-parallel-computing-tutorial)
- [POSIX Threads](https://hpc-tutorials.llnl.gov/posix/)
- [Programming with POSIX Threads](https://books.google.fr/books?id=_xvnuFzo7q0C&printsec=frontcover&redir_esc=y#v=onepage&q&f=false)
