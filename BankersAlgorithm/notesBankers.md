- Bankers algorithm is Deadlock Detection & Deadlock Avoidance Algorithm.
- Kabhi bhi in real life and practical scenarios the max need cannot be statically determined beforehand, rather it's dynamic.

##### Notes for bankersAlgo.cpp 
- **Main Data Structures:**
    - *avail[]*: Array tracking how many of each resource are free.
    - *maxm[][]*: Maximum demand of each process for each resource.
    - *allot[][]*: Currently allocated resources to each process.
    - *need[][]*: What more of each resource each process may request.
- **Setup:**
    - *calculateNeed()* computes what each process still needs: need[i][j]=maxm[i][j]-allot[i][j].
- **Algorithm:**
    - Try to find a sequence of processes (safe sequence) such that each, when run in order, can obtain its needed resources, complete, and release its allocation for others to use.
    - On each round, if a process can run (needs ≤ current available), it is marked as finished, its allocation is released back, sequence is built.
    - If at any point, no unfinished process can proceed, system is not safe.
- **Result:**
    - If you get a full sequence, system is in a safe state, and the sequence is shown.
    - Otherwise, system could deadlock.
