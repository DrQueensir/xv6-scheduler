//our modifications start

#ifndef SCHEDSTAT_H
#define SCHEDSTAT_H

struct schedstat {
  uint arrival_tick;
  uint first_run_tick;
  uint completion_tick;
  uint total_wait_ticks;
  uint total_run_ticks;
  uint context_switches;
  uint max_wait_ticks;
};

#endif

//our modifications end
