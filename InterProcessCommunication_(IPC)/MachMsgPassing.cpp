// Runs on MacOS device etc.
// for output refer the image Mach wali
#include <mach/mach.h>
#include <iostream>
#include <cstring>

// Define the structure for the Mach message
struct message {
    mach_msg_header_t header;
    int data;
};

int main() {
    kern_return_t kr;
    mach_port_t server_port, client_port;

    // Create a port for the server (receiver)
    kr = mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_RECEIVE, &server_port);
    if (kr != KERN_SUCCESS) {
        std::cerr << "Failed to allocate server port\n";
        return 1;
    }

    // Insert a send right for the client
    kr = mach_port_insert_right(mach_task_self(), server_port, server_port, MACH_MSG_TYPE_MAKE_SEND);
    if (kr != KERN_SUCCESS) {
        std::cerr << "Failed to insert send right\n";
        return 1;
    }

    // Create a port for the client (sender/for reply, if needed)
    kr = mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_RECEIVE, &client_port);
    if (kr != KERN_SUCCESS) {
        std::cerr << "Failed to allocate client port\n";
        return 1;
    }

    // Prepare the message
    struct message msg;
    msg.data = 12345;
    memset(&msg.header, 0, sizeof(mach_msg_header_t));
    msg.header.msgh_size = sizeof(struct message);
    msg.header.msgh_remote_port = server_port;
    msg.header.msgh_local_port = client_port;
    msg.header.msgh_bits = MACH_MSGH_BITS(MACH_MSG_TYPE_COPY_SEND, 0);

    // Send the message (client action)
    kr = mach_msg(&msg.header,
                   MACH_SEND_MSG,
                   sizeof(struct message),
                   0,
                   MACH_PORT_NULL,
                   MACH_MSG_TIMEOUT_NONE,
                   MACH_PORT_NULL);
    if (kr != KERN_SUCCESS) {
        std::cerr << "mach_msg send failed: " << kr << "\n";
        return 1;
    } else {
        std::cout << "Client sent data: " << msg.data << std::endl;
    }

    // Server receives the message
    struct message recv_msg;
    kr = mach_msg(&recv_msg.header,
                   MACH_RCV_MSG,
                   0,
                   sizeof(struct message),
                   server_port,
                   MACH_MSG_TIMEOUT_NONE,
                   MACH_PORT_NULL);
    if (kr != KERN_SUCCESS) {
        std::cerr << "mach_msg receive failed: " << kr << "\n";
        return 1;
    } else {
        std::cout << "Server received data: " << recv_msg.data << std::endl;
    }

    // Clean up: deallocate ports
    mach_port_deallocate(mach_task_self(), server_port);
    mach_port_deallocate(mach_task_self(), client_port);

    return 0;
}