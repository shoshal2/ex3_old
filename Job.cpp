//
// Created by mahmuds on 1/28/17.
//



#include "Job.h"

Job::Job(void *(*func)(void *arg), void *arg): func(func), arg(arg) {
    // TODO Auto-generated constructor stub

}

void Job::execute() {
    func(arg);
}

Job::~Job() {
    // TODO Auto-generated destructor stub
}
