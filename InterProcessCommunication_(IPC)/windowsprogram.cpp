#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

void run_server();
void run_client();

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "client") {
        run_client();
    } else {
        // Launch client process
        STARTUPINFOA si = { sizeof(si) };
        PROCESS_INFORMATION pi;
        BOOL ok = CreateProcessA(
            NULL,
            (LPSTR)"program.exe client", // Make sure exe name matches!
            NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi
        );
        if (!ok) {
            std::cerr << "Failed to launch client process. Error: " << GetLastError() << std::endl;
        } else {
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
        }
        // Give the client a moment to start
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        run_server();
    }
    return 0;
}

void run_server() {
    const char* pipeName = R"(\\.\pipe\MyPipe)";
    HANDLE hPipe = CreateNamedPipeA(
        pipeName,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1, 1024, 1024, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Server: Failed to create pipe. Error: " << GetLastError() << std::endl;
        return;
    }

    std::cout << "Server: Waiting for client to connect...\n";
    BOOL connected = ConnectNamedPipe(hPipe, NULL) ? TRUE :
                     (GetLastError() == ERROR_PIPE_CONNECTED);

    if (!connected) {
        std::cerr << "Server: Failed to connect to client. Error: " << GetLastError() << std::endl;
        CloseHandle(hPipe);
        return;
    }

    char buffer[128] = {0};
    DWORD bytesRead = 0;
    if (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        std::cout << "Server: Received: " << buffer << std::endl;
    } else {
        std::cerr << "Server: Failed to read. Error: " << GetLastError() << std::endl;
    }

    // Optionally, send response to client
    const char* response = "Hello from server!";
    DWORD bytesWritten = 0;
    if (WriteFile(hPipe, response, strlen(response), &bytesWritten, NULL)) {
        std::cout << "Server: Sent response to client." << std::endl;
    } else {
        std::cerr << "Server: Failed to write. Error: " << GetLastError() << std::endl;
    }

    FlushFileBuffers(hPipe);
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
    std::cout << "Server: Done." << std::endl;
}

void run_client() {
    // Wait for server to be ready
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    const char* pipeName = R"(\\.\pipe\MyPipe)";
    HANDLE hPipe;
    // Attempt connection a few times (give server a chance)
    for (int tries = 0; tries < 5; ++tries) {
        hPipe = CreateFileA(
            pipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (hPipe != INVALID_HANDLE_VALUE) {
            break;
        }
        if (GetLastError() != ERROR_PIPE_BUSY) {
            std::cerr << "Client: Could not open pipe. Error: " << GetLastError() << std::endl;
            return;
        }
        // All pipe instances are busy, wait for server
        if (!WaitNamedPipeA(pipeName, 1000)) {
            std::cerr << "Client: WaitNamedPipe failed. Error: " << GetLastError() << std::endl;
            return;
        }
    }

    const char* msg = "Hello from client!";
    DWORD bytesWritten = 0;
    if (WriteFile(hPipe, msg, strlen(msg), &bytesWritten, NULL)) {
        std::cout << "Client: Sent: " << msg << std::endl;
    } else {
        std::cerr << "Client: Failed to write. Error: " << GetLastError() << std::endl;
    }

    char buffer[128] = {0};
    DWORD bytesRead = 0;
    if (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        std::cout << "Client: Received: " << buffer << std::endl;
    } else {
        std::cerr << "Client: Failed to read. Error: " << GetLastError() << std::endl;
    }

    CloseHandle(hPipe);
    std::cout << "Client: Done." << std::endl;
}