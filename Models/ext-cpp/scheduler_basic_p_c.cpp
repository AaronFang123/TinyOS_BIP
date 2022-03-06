#include "scheduler_basic_p_c.hpp"
// Helper functions (internal functions) intentionally do not have atomic
// sections.  It is left as the duty of the exported interface functions to
// manage atomicity to minimize chances for binary code bloat.

// move the head forward
// if the head is at the end, mark the tail at the end, too
// mark the task as not in the queue 
// uint8_t

int pop_task()
{
    if (m_head != NO_TASK)
    {
        int id = m_head;
        m_head = m_next[m_head];
        if (m_head == NO_TASK)
        {
            m_tail = NO_TASK;
        }
        m_next[id] = NO_TASK;
        return id;
    }
    else
    {
        return NO_TASK;
    }
}

int is_waiting(int id)
{
    return (m_next[id] != NO_TASK) || (m_tail == id);
}


int push_task(int id)
{
    if (!is_waiting(id))
    {
        if (m_head == NO_TASK)
        {
            m_head = id;
            m_tail = id;
        }
        else
        {
            m_next[m_tail] = id;
            m_tail = id;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

void scheuler_init()
{
    /**
        command void Scheduler.init()
        {
            atomic
            {
                memset( (void *)m_next, NO_TASK, sizeof(m_next) );
                m_head = NO_TASK;
                m_tail = NO_TASK;
            }
        }
    */
    memset((void *)m_next, NO_TASK, sizeof(m_next));
    m_head = NO_TASK;
    m_tail = NO_TASK;
}

int scheduler_run_next_task()
{
    int next_task;
    next_task = pop_task();
    if (next_task == NO_TASK)
    {
        return 0;
    }

    task_basic_runTask(123);
    return 1;
}

void scheduler_task_loop()
{
    for (;;)
    {
        int nextTask;

        while ((nextTask = pop_task()) == NO_TASK)
        {
            // call McuSleep.sleep();
            // printf("call McuSleep.sleep()");
        }

        //  signal TaskBasic.runTask[nextTask]();
        task_basic_runTask(123);
    }
}

/**
 * Return SUCCESS if the post succeeded, EBUSY if it was already posted.
 */
int task_basic_postTask(int id)
{
    return pop_task() > 0 ? 1 : 0;
}

void task_basic_runTask(int id)
{
}
