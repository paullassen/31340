#include <stdio.h>

#include <sys/mman.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

#include "rtai_shm.h"
#include "rtai_lxrt.h"


int main()
{
    unsigned int name, i;
    RT_TASK *task;
    RTIME last_time, current_time;
    pid_t pid;
    RTIME log[10] = {0};
    RTIME log2[10] = {0};

    struct sched_param params = 
                {   .sched_priority = sched_get_priority_max(SCHED_FIFO)    };

    mlockall(MCL_FUTURE);

    printf("Initializing Real Time System...\n");
    
    name = nam2num("h27pr1");

    //Initialize rt system
    rt_allow_nonroot_hrt();
    task = rt_task_init(name, 1, 0,0);
    
    if (task == NULL){
        puts("Something went wrong: RT_TASK* is null");
        return -1;
    }



    printf("Initializing Scheduler ...\n");    
    pid = getpid();
    sched_setscheduler(pid, SCHED_FIFO, &params);


    printf("Making perodic tasks...\n");
    rt_task_make_periodic_relative_ns(task, 1e9, 1e6);
    last_time = rt_get_time_ns();
    rt_task_wait_period();
    for (i = 0; i < 10; i++)
    {
        current_time = rt_get_time_ns();
        log[i] = current_time-last_time;
        last_time = current_time;
        
        rt_task_wait_period();
        
    }

    for (i = 0; i < 10; i++)
    {
        printf("Period #: %d \t time: %lld ns\n", i, log[i]);
    }
    
    
    printf("Cleaning Up...\n\n\n");
    rt_task_delete(task);

    return 0;
}