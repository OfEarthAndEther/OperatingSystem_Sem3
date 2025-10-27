- Each process has a segment of code, called a **critical section**, in which the process may be accessing — and updating — data that is shared with at least one other process.
- The ***critical-section problem*** is to design a protocol that the processes can use to synchronize their activity so as to cooperatively share data. Each process must request permission to enter its **critical section**. The section of code implementing this request is the **entry section**. The critical section may be followed by an exit section. The remaining code is the **remainder section**.
- A solution to the critical-section problem must satisfy the following three requirements:
    1. **Mutual exclusion.** If process Pi is executing in its critical section, then no other processes can be executing in their critical sections.
    2. **Progress.** If no process is executing in its critical section and some processes wish to enter their critical sections, then only those processes that are not executing in their remainder sections can participate in deciding which will enter its critical section next, and this selection cannot be postponed indefinitely.
    3. **Bounded waiting.** There exists a bound, or limit, on the number of times that other processes are allowed to enter their critical sections after a process has made a request to enter its critical section and before that request is granted.
- Two general approaches are used to handle critical sections in operating systems: **preemptive kernels and nonpreemptive kernels**. 
- A ***preemptive kernel*** allows a process to be preempted while it is running in kernel mode. 
- A ***nonpreemptive kernel*** does not allow a process running in kernel mode to be preempted; a kernel-mode process will run until it exits kernel mode, blocks, or voluntarily yields control of the CPU.
- Obviously, a nonpreemptive kernel is essentially free from race conditions on kernel data structures, as only one process is active in the kernel at a time. We cannot say the same about preemptive kernels, so they must be carefully designed to ensure that shared kernel data are free from race conditions. 
- ***Preemptive kernels are especially difficult to design*** for SMP architectures, since in these environments it is possible for two kernel-mode processes to run simultaneously on different CPU cores.
- *Why*, then, would anyone *favor a preemptive kernel over a nonpreemptive one?* 
- A ***preemptive kernel may be more responsive***, since there is less risk that a kernel-mode process will run for an arbitrarily long period before relinquishing the processor to waiting processes. 
- (Of course, this risk can also be minimized by designing kernel code that does not behave in this way.) 
- Furthermore, a **preemptive kernel is more suitable for real-time programming**, as it will allow a real-time process to preempt a process currently running in the kernel.

##### Notes Peterson's Algorithm Implementation in C++ (using threads) ...... CodeFile PetersonAlgoThreads.cpp
- **Shared Variables:**
    - *flag[2]* array: Indicates when a process wants to enter the critical section.
    - *turn*: Solves contention, giving priority to one process.
- **Entry Section:**
    - Sets own flag to true ("I want to enter").
    - Sets turn to other process ("Let other go if it also wants in").- Busy-waits if the other process wants to enter and it's the other's turn.
- **Critical Section:**
    - Only one process can access shared_data at a time.
    - Prints who is currently inside, updates and shows shared value.
- **Exit Section:**
    - Sets own flag to false ("I'm done!").
- **Remainder Section:**
    - Sleep/delays to allow other process a turn.
- **Mutual Exclusion, Progress, Bounded Waiting:**
    - No two processes are in the critical section simultaneously.
    - If one wants in and the other doesn't, it succeeds immediately.
    - If both want in, access alternates with bounded waiting.
- **Threads:**
    - *std::thread* is used for simplicity and to simulate two concurrent processes.

