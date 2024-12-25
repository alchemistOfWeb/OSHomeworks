#include <iostream>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <ucontext.h>


void signalHandler(int sig, siginfo_t* info, void* context) {
    if (sig == SIGUSR1) {
        pid_t senderPid = info->si_pid;
        uid_t senderUid = info->si_uid;

        struct passwd* pw = getpwuid(senderUid);
        const char* senderUsername = pw ? pw->pw_name : "unknown";

        ucontext_t* ctx = (ucontext_t*)context;

        uintptr_t eip = ctx->uc_mcontext.gregs[REG_RIP];
        uintptr_t eax = ctx->uc_mcontext.gregs[REG_RAX];
        uintptr_t ebx = ctx->uc_mcontext.gregs[REG_RBX];

        std::cout << "Received a SIGUSR1 signal from process " << senderPid
                  << " executed by " << senderUid << " (" << senderUsername << ").\n";
        std::cout << "State of the context: EIP = " << eip
                  << ", EAX = " << eax
                  << ", EBX = " << ebx << ".\n";
    }
}

int main() {
    pid_t pid = getpid();
    std::cout << "Process PID: " << pid << std::endl;

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signalHandler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, nullptr) == -1) {
        perror("sigaction");
        return 1;
    }

    while (true) {
        std::cout << "Waiting for SIGUSR1...\n";
        sleep(10);
    }

    return 0;
}

