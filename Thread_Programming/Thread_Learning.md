## Threads
-> A **thread library provides** the programmer with an **API for creating and managing threads**.  
    
-> There are two primary ways of implementing a thread library.
    
-> The ***first approach*** is to provide a **library entirely in user space with no kernel support**. All code and data structures for the library exist in user space. This means that invoking a function in the library results in a local function call in user space and not a system call.
    
-> The ***second approach*** is to implement a **kernel-level library supported directly by the operating system**. In this case, code and data structures for the library exist in kernel space. Invoking a function in the API for the library typically results in a system call to the kernel.
    
-> **Three main thread libraries** are in use today: **POSIX Pthreads, Windows, and Java.** 

-> Pthreads, the threads *extension of the POSIX standard*, may be provided as *either a user-level* or a *kernel-level* library.

-> The Windows thread library is a *kernel-level library* available on Windows systems.

-> The Java thread API allows threads to be created and managed directly in *Java programs*.
    
-> However, because in most instances the JVM is running on top of a host operating system, the **Java thread API is generally implemented** using a **thread library** available on the **host system**. This means that on **Windows systems, Java threads are typically implemented using** the ***Windows API; UNIX, Linux, and macOS systems.*** typically use Pthreads.
-> For POSIX and Windows threading, any data declared globally — that is, declared outside of any function — are shared among all threads belonging to the same process. Because Java has no equivalent notion of global data, access to shared data must be explicitly arranged between threads.

-> *Two general strategies for creating multiple threads*: **asynchronous threading** and **synchronous threading**. 
-> With asynchronous threading, once the parent creates a child thread, the **parent resumes its execution**, so that the **parent and child execute concurrently and independently** of one another. Because the threads are independent, there is typically **little data sharing** between them. Asynchronous threading is the strategy used in the multithreaded server illustrated in Figure 4.2 and is also commonly used for designing responsive user interfaces.
-> Synchronous threading occurs when the **parent thread creates one or more children and then must wait for all of its children to terminate before it resumes**. Here, the *threads created by the parent perform work concurrently*, **but the parent cannot continue until this work has been completed**. Once each thread has finished its work, it terminates and joins with its parent. Only after all of the children have joined can the parent resume execution. Typically, synchronous threading involves **significant data sharing among threads**. For example, the parent thread may combine the results calculated by its various children.
    
#### 1. Pthreads
1. POSIX Threads (Pthreads) specification is like the abstraction layer or interface (API) for threading in C and C++.
2. Pthreads refers to the POSIX standard (IEEE 1003.1c) defining an API for thread creation and synchronization. This is a specification for thread behavior, not an implementation.
3. Many UNIX-like systems, such as Linux and macOS, include built-in support for the Pthreads specification. Windows does not support Pthreads by default, but there are some third-party libraries that make it possible to use Pthreads on Windows.
4. All Pthreads programs must include the pthread.h header file.
5. Each thread has a set of attributes, including stack size and scheduling information.
6. Synchronization mechanism:
a) MUTEX LOCKS: When a thread wants to access a shared resource, it must first acquire the associated mutex - if the mutex is already locked by another thread, the requesting thread enters a waiting state until the lock becomes available.
b) Semaphores (signalling concept)

#### 2. Windows Thread
1. We must include the
windows.h header file when using the Windows API.
2. 

#### 2. Java Threads
1. *All Java programs* comprise **at least a single thread of control** — even a simple Java program consisting of only a main() method runs as a single thread in the JVM.
2. There are **two techniques for explicitly creating threads in a Java** program.
3.(a) One approach is to **create a new class that is derived from the Thread class** and to *override its run() method*. 
3.(b) An alternative — and *more commonly* used — technique is to **define a class that implements the Runnable interface**. 
4. This interface defines a single abstract method with the signature public void run(). 
5. The code in the run() method of a class that implements Runnable is what executes in a separate thread. 
6. An example is shown below: class Task implements Runnable
```
{
    public void run() {
        System.out.println("I am a thread.");
    }
}
```    
7. *Invoking the **start() method*** for the **new Thread object** does two things:
    - 1. It **allocates memory** and **initializes a new thread in the JVM**.
    - 2. It *calls the run() method*, making the **thread eligible to be run by the JVM**.
(Note again that we *never call the run() method directly*. Rather, **we call the start() method, and it calls the run() method** on our behalf.)
8. Recall that the **parent threads in the Pthreads and Windows libraries** use ***pthread join()*** and ***WaitForSingleObject()*** (respectively) **to wait for the summation threads to finish before proceeding**. 
9. The ***join() method in Java*** provides similar functionality. (***Notice*** that **join() can throw an InterruptedException**, which we choose to ignore.)   
```
try {
    worker.join();
}
catch (InterruptedException ie) { }
```
10. Classes implementing this interface must define the *execute() method*, which is passed a *Runnable object*. 
11. For Java developers, this means **using the Executor rather than creating a separate Thread object and invoking its start() method**. 
12. The Executor is used as follows:
```
Executor service = new Executor;
service.execute(new Task());
```
13. The **Executor framework** is based on the **producer-consumer model**;
14. The **advantage** of this approach is that **it not only divides thread creation from execution** but also **provides a mechanism for communication between concurrent tasks**.
15. **Data sharing between threads belonging to the same process** occurs *easily in Windows and Pthreads*, since shared data are simply declared *globally*. As a pure object-oriented language, *Java has no such notion of global data*. We can pass parameters to a class that implements Runnable, but **Java threads cannot return results**. 
16. To address **this** need, the java.util.concurrent package additionally defines the **Callable interface**, which behaves similarly to Runnable except that a ***result can be returned***. Results returned from Callable tasks are known as **Future objects**. A result can be retrieved from the **get() method** defined in the Future interface.
17. (The primary *difference between the execute() and submit()* methods is that the **former returns no result**, whereas the **latter returns a result as a Future**.)


>Scope Contention
>LWP (Light Weight Process)
- On systems implementing the many-to-one and many-to-many models, the thread library schedules user-
level threads to run on an available LWP.
- This scheme is known as process-contention scope (PCS), since competition for the CPU takes place among threads belonging to the same process.
- To decide which kernel-level thread to schedule onto a CPU, the kernel uses system-contention scope (SCS). - Competition for the CPU with SCS scheduling takes place among all threads in the system. Systems using the one-to-one model, such as Windows and Linux schedule threads using only SCS.