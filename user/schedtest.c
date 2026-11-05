//our modofications start
#include "kernel/types.h"
#include "kernel/schedstat.h"
#include "user/user.h"

#define NCHILD 3

int
main(void)
{
  int i, pid, status;
  struct schedstat st;

  printf("Starting scheduling test\n");

  for (i = 0; i < NCHILD; i++) {
    pid = fork();

    if (pid < 0) {
      printf("fork failed\n");
      exit(1);
    }

    if (pid == 0) {
      volatile uint64 result = 0;
      uint64 iterations = (uint64)(i + 1) * 10000000;

      for (uint64 j = 0; j < iterations; j++) {
        result += j % 7;
      }
      (void)result;
      exit(0);
    }
  }

  printf("PID  Turnaround Response Wait CPU Switches MaxWait\n");

  for (i = 0; i < NCHILD; i++) {
    pid = waitstat(&status, &st);

    if (pid < 0) {
      printf("waitstat failed\n");
      exit(1);
    }

    printf("%d  %d  %d  %d  %d  %d  %d\n", pid,
           st.completion_tick - st.arrival_tick,
           st.first_run_tick - st.arrival_tick, st.total_wait_ticks,
           st.total_run_ticks, st.context_switches, st.max_wait_ticks);
  }

  printf("Scheduling test complete\n");
  exit(0);
}
//our modifications end
