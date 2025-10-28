- If a system does not employ either a *deadlock-prevention* or a *deadlock-avoidance algorithm*, then a deadlock situation may occur. In this environment,the system may provide:
    - An algorithm that examines the state of the ***system to determine*** whether a deadlock has occurred
    - An algorithm to ***recover*** from the deadlock
- This check should be run ***periodically*** or whenever the system suspects deadlock (as too frequent checks add overhead).

- ### Single Instance Deadlock Detection (Wait-For Graph)
    - If there is only one instance of each resource type, use a graph/cycle detection algorithm:
        - Build the wait-for graph.
        - Detect cycles in the directed graph using DFS or Floyd's algorithm.
        - Any cycle implies deadlock.


##### Notes for deadlockDetection.cpp
- **Inputs (Matrices):**
    - *Allocation[n][m]*: Number of resources of each type held by each process/thread.
    - *Request[n][m]*: Number of resources each process/thread is still requesting.
    - *Available[m]*: Resources currently unallocated in the system.
- **Initialization:**
    - *Finish[i]* is true if process has no allocation (*Allocation[i][j] == 0 ∀ j*), false otherwise.
    - *Work[m]* is set to *Available[m]* (copy of current available resources).
- **Algorithm Loop:**
    - Look for a process/thread that is unfinished and whose request for resources can be satisfied (*Request[i][j] <= Work[j] for all j*).
    - If found, "pretend" it completes: release its allocation, add *Allocation[i][j]* back to *Work[j]*.
    - Mark that process as finished (*Finish[i]=true*) and repeat.
- **Result:**
    - Any process remaining (*Finish[i]==false*) is deadlocked.
    - Otherwise, print that the system is safe.