#include <iostream>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main() {
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    // Create the pipe
    if (pipe(fd) == -1) {
        std::cerr << "Pipe failed" << std::endl;
        return 1;
    }

    // Fork a child process
    pid = fork();
    if (pid < 0) {
        std::cerr << "Fork Failed" << std::endl;
        return 1;
    }

    if (pid > 0) { // Parent process
        close(fd[READ_END]); // Close unused read end
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1); // Write to pipe
        close(fd[WRITE_END]); // Close write end
    } else { // Child process
        close(fd[WRITE_END]); // Close unused write end
        read(fd[READ_END], read_msg, BUFFER_SIZE); // Read from pipe
        std::cout << "read: " << read_msg << std::endl;
        close(fd[READ_END]); // Close read end
    }
    return 0;
}