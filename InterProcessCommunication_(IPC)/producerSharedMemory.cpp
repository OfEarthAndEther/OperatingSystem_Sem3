#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
using namespace std;

const char* shm_name = "/posix_shm_example";
const int SIZE = 4096;

int main() {
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);

    void* ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    pid_t pid = fork();

    if (pid == 0) {  // Child process (Reader)
        sleep(1);
        cout << "Child reads: " << (char*)ptr << endl;
        munmap(ptr, SIZE);
        close(shm_fd);
        shm_unlink(shm_name);
    } else {          // Parent process (Writer)
        const char* message = "Hello from parent via POSIX shared memory!";
        sprintf((char*)ptr, "%s", message);
        cout << "Parent wrote to shared memory." << endl;
        wait(NULL);
    }

    return 0;
}