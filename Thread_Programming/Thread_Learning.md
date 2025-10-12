##Threads
- A thread library provides the programmer with an API for creating and man-
aging threads.  
    
- There are two primary ways of implementing a thread library.
    
- The ***first approach*** is to provide a **library entirely in user space with no kernel support**. All code and data structures for the library exist in user space. This means that invoking a function in the library results in a local function call in user space and not a system call.
    
- The ***second approach*** is to implement a **kernel-level library supported directly by the operating system**. In this case, code and data structures for the library exist in kernel space. Invoking a function in the API for the library typically results in a system call to the kernel.
    
- **Three main thread libraries** are in use today: **POSIX Pthreads, Windows, and Java.** 
- Pthreads, the threads extension of the POSIX standard, may be provided as either a user-level or a kernel-level library.
- The Windows thread library is a kernel-level library available on Windows systems.
- The Java thread API allows threads to be created and managed directly in Java programs.
    
- However, because in most instances the JVM is running on top of a host operating system, the **Java thread API is generally implemented** using a **thread library** available on the **host system**. This means that on **Windows systems, Java threads are typically implemented using** the ***Windows API; UNIX, Linux, and macOS systems.***

typically use Pthreads.
For POSIX and Windows threading, any data declared globally— that is,
declared outside of any function—are shared among all threads belonging to
the same process. Because Java has no equivalent notion of global data, access
to shared data must be explicitly arranged between threads.

>Scope Contention
>LWP (Light Weight Process)
- On systems implementing the many-to-one and many-to-many models, the thread library schedules user-
level threads to run on an available LWP.
- This scheme is known as process-contention scope (PCS), since competition for the CPU takes place among threads belonging to the same process.
- To decide which kernel-level thread to schedule onto a CPU, the kernel uses system-contention scope (SCS). - Competition for the CPU with SCS scheduling takes place among all threads in the system. Systems using the one-to-one model, such as Windows and Linux schedule threads using only SCS.