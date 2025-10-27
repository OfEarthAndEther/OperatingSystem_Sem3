#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

void producer(int writefd) {
    for (int i = 1; i <= 10; i++) {
        write(writefd, &i, sizeof(int));
        cout << "Producer sent: " << i << endl;
        sleep(1);
    }
    close(writefd);
}
void consumer(int readfd) {
    int item;
    while (read(readfd, &item, sizeof(int)) > 0) {
        cout << "Consumer received: " << item << endl;
        sleep(1);
    }
    close(readfd);
}

int main() {
    int pipefd[2];
    pipe(pipefd);
    
    if (fork() == 0) {
        close(pipefd[0]);
        producer(pipefd[1]);
        exit(0);
    }
    
    if (fork() == 0) {
        close(pipefd[1]);
        consumer(pipefd[0]);
        exit(0);
    }
    
    close(pipefd[0]);
    close(pipefd[1]);
    
    wait(NULL);
    wait(NULL);
    
    return 0;
}