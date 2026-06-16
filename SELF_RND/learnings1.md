# 16th June 2026

## 1. "How do you distinguish a normal exit from a crash or signal?"
- `WIFEXITED / WEXITSTATUS / WIFSIGNALED`:  **interviewers** often ask how a parent distinguishes a **normal exit from a signal-induced termination** of a child — these macros operating on the status returned by `wait()` answer that.

- In systems programming, particularly when dealing with *Unix/Linux processes*, managing child processes is a core responsibility of the parent. When a child process terminates, it doesn't just vanish; it leaves behind a "final report" known as its **termination status**.
- The parent retrieves this status using the `wait()` or `waitpid()` system calls. However, the `int` *status variable* populated by these calls isn't a simple integer—it's a *bitmask* that packs multiple pieces of information together.
- Because you can't just read the integer directly, the POSIX standard provides a **set of macros to decode** it.

#### The Core Breakdown
To determine how a child died, you always use a two-step process:
- Check the cause (Did it exit on its own, or was it killed?).
- Extract the details (What was the exit code, or what signal killed it?).

1. Normal Termination: WIFEXITED and WEXITSTATUS
- WIFEXITED(status): Evaluates to true if the child process terminated normally. "Normally" means the child called exit(), _exit(), or returned from the main() function.

- WEXITSTATUS(status): If (and only if) WIFEXITED is true, this macro extracts the actual exit code code standardly passed to exit() or returned from main (e.g., 0 for success, 1 or higher for an error).

⚠️ Crucial Detail: WEXITSTATUS only isolates the lowest 8 bits of the exit status. This is why exit codes in Unix are always between 0 and 255.

2. Signal Termination: WIFSIGNALED and WTERMSIG
- WIFSIGNALED(status): Evaluates to true if the child process was abruptly terminated by a signal that it didn't catch (e.g., SIGKILL, SIGSEGV for a segmentation fault, or SIGINT via Ctrl+C).

- WTERMSIG(status): If WIFSIGNALED is true, this macro extracts the specific signal number that caused the child to terminate.

## 2. "Why can't I just check if (status == 0)?"
- `waitpid(pid, &status,0);` kyu required hai?
- Because `status` contains encoded bits. A child that exits normally with `exit(0)` might yield a `status` of 0, but a child killed by a signal will have specific bits flipped high up in the integer. Checking `status == 0` blindly will completely miss signal deaths or non-zero exit codes.

## 3. "What is WCOREDUMP?"
- When a program breaks, the operating system dumps the contents of the RAM the program was using into a file (usually named `core` or `core.<pid>`) so a developer can inspect it later.

### Why Don't You See Core Dumps All The Time?
- By default, many modern Linux distributions and operating systems have core dumps disabled or restricted. There are two main reasons for this:  
1. **Storage Space**: If a program utilizing 16 GB of RAM crashes, it will attempt to write a 16 GB file to the hard drive. If a broken service keeps crashing and restarting in a loop, it can completely fill up a server's disk in minutes.
2. **Security**: Core dumps contain everything that was in memory. If your program was handling user passwords, unencrypted SSL keys, or credit card numbers, all of that sensitive data will be written in plain text into the core dump file.

- (Note: In Linux, you can check your system's core dump size limit using the terminal command `ulimit -c`. If it is 0, core dumps are disabled).

