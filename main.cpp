//
// Created by mahmuds on 1/28/17.
//


#include "Job.h"
#include "ThreadPool.h"
#include <iostream>
#include <unistd.h>
using namespace std;

void* print(void *id_ptr) {
    int id = *(int *)id_ptr;
    for (int i = 1; i <= 10; i++) {
        cout << "print " << id << ": " << i << endl;
        sleep(1);
    }
    return NULL;
}

int mains() {
    char ch;
    ThreadPool pool(5);

    Job *arr[5];
    int num[5] = {1, 2, 3, 4, 5};


    for (int i = 0; i < 5; i++) {

        arr[i] = new Job(print, num + i);
        pool.addJob(arr[i]);
    }

    cout << "type char to exit" << endl;
    cin >> ch;
    for (int i =0; i< 5; i++) {
        delete arr[i];
    }

    pool.terminate();
    cout << "end of main" << endl;
}
