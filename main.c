//- Copyright (c) 2008-2014 James Grenning --- All rights reserved
//- For exclusive use by participants in Wingman Software training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.wingman-sw.com james@wingman-sw.com

#include <stdio.h>
#include "CircularBuffer.h"

//please do not change these messages
const char * writing = "OK writing";
const char * testing = "FAILED testing";
const char * working = "OK working";

int main(int ac, char** av)
{
    unsigned int capacity = 10;
    int empty_value = -1;
    const char * exercise_state = writing;

    struct CircularBuffer * b = CircularBuffer_Create(capacity, empty_value);
    CircularBuffer_Destroy(b);


    printf("%s code\n", exercise_state);
    return 0;
}

