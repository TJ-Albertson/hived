#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

// Function to handle signals
void signal_handler(int sig) {
    switch(sig) {
        case SIGHUP:
            // Handle hangup signal
            break;
        case SIGTERM:
            // Handle termination signal
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
    }
}

// Function to daemonize the process
void daemonize() {
    pid_t pid, sid;

    // Fork the process
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // Create a new session
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Change working directory
    if (chdir("/") < 0) {
        exit(EXIT_FAILURE);
    }

    // Set file mode creation mask
    umask(0);
}

int main() {
    // Daemonize the process
    daemonize();

    // Set signal handlers
    signal(SIGHUP, signal_handler);
    signal(SIGTERM, signal_handler);

    // Main loop
    while(1) {
        // Do some work here...
        sleep(1);
    }

    return EXIT_SUCCESS;
}