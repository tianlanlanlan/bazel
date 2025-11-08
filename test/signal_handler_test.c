#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static struct sigaction old_sigint_action;

void signal_handler_new(int signum, siginfo_t *info, void *context) {
  // Step1: Call new action
  printf("Received signal: %d, call new action\n", signum);

  // Step2: Call old action
  if (old_sigint_action.sa_handler != SIG_DFL &&
      old_sigint_action.sa_handler != SIG_IGN) {
    if (old_sigint_action.sa_flags & SA_SIGINFO) {
      old_sigint_action.sa_sigaction(signum, info, context);
    } else {
      old_sigint_action.sa_handler(signum);
    }
  }
}

void signal_handler_old(int signum) {
  printf("Received signal: %d, call old action\n", signum);
}

void install_signal_handler() {
  // Install old signal hanlder for SIGINT
  {
    struct sigaction sa_action;
    sigemptyset(&sa_action.sa_mask);
    sa_action.sa_handler = &signal_handler_old;
    sigaction(SIGINT, &sa_action, NULL);
  }

  // Install newer signal hanlder for SIGINT
  {
    struct sigaction sa_action;
    sigemptyset(&sa_action.sa_mask);
    sa_action.sa_sigaction = &signal_handler_new;
    sa_action.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa_action, &old_sigint_action);
  }
}

int main() {
  install_signal_handler();
  sleep(1);
  raise(SIGINT);
}