//
// Created by mahmuds on 1/28/17.
//

#ifndef EX3_JOB_H
#define EX3_JOB_H




class Job {
private:
    void *arg;
    void * (*func)(void *arg);
public:
    Job(void * (*func)(void *arg), void* arg);
    void execute();
    virtual ~Job();
};





#endif //EX3_JOB_H
