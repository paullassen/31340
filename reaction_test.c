#include <stdio.h>

#include "rtai_shm.h"
#include "rtai_lxrt.h"



RTIME get_reaction_time (char *prompt)
{
  int input;
  RTIME start_time, end_time;
  //Prompts user and gets start and end time
  printf(prompt);
  start_time = rt_get_time_ns();
  input = getchar();
  end_time = rt_get_time_ns();

  // returns the difference
  return end_time - start_time;
}


int main()
{


  unsigned int name;
  RT_TASK *task;
  RTIME reaction_time;

  printf("Initializing Real Time System...\n");
  
  name = nam2num("h27pr1");

  //Initialize rt system
  rt_allow_nonroot_hrt();
  task = rt_task_init(name, 1, 0,0);
  
  if (task == NULL){
    puts("Something went wrong: RT_TASK* is null");
    return -1;
  }


  puts("Welcome to reaction_test. Press <ENTER> when you see go!");
  reaction_time = get_reaction_time("G0!");
  printf("You took %0.9f seconds\n\n", reaction_time/((float) 1e9));
  
  printf("Cleaning Up...\n\n\n");
  rt_task_delete(task);

  return 0;
}