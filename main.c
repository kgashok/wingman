//- Copyright (c) 2008-2014 James Grenning --- All rights reserved
//- For exclusive use by participants in Wingman Software training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.wingman-sw.com james@wingman-sw.com

#include "CircularBuffer.h"

#include <assert.h>     // for assert
#include <errno.h>      // for errno
#include <stdio.h>      // for perror, printf
#include <stdlib.h>     // for exit

//please do not change these messages
const char * writing = "OK writing";
const char * testing = "FAILED testing";
const char * working = "OK working";


// Test coverage:
//
//      ,----------------------.
//      | Operation | State    |
//      |===========|==========|
//    0 | IsEmpty   | Empty    |
//    1 |           | Partial  |
//    2 |           | Full     |
//      |-----------|----------|
//    3 | IsFull    | Empty    |
//    4 |           | Partial  |
//    5 |           | Full     |
//      |-----------|----------|
//    6 | Put       | Empty    |
//    7 |           | Partial  |
//    8 |           | Full     |
//      |-----------|----------|
//    9 | Get       | Empty    |
//   10 |           | Partial  |
//   11 |           | Full     |
//      |-----------|----------|
//   12 | Capacity  | Empty    |
//   13 |           | Partial  |
//   14 |           | Full     |
//      |___________|__________|

int main(int ac, char** av)
{
    const unsigned int capacity = 10;
    const int empty_value = -1;
    const char * exercise_state = working;
    int i;  // loop iterator

    struct CircularBuffer * b = CircularBuffer_Create(capacity, empty_value);

    if (NULL == b) {
        perror("Failed to initialize circular buffer");
        exit(1);
    }

    assert(CircularBuffer_IsEmpty(b));                      // row  0
    assert(empty_value == CircularBuffer_Get(b));           // row  9

    // Write after Read (WaR), Write after Write (WaW)
    for (i = 0; i < capacity; ++i) {
        assert(!CircularBuffer_IsFull(b));                  // row  3,  4
        assert(capacity == CircularBuffer_Capacity(b));     // row 12, 13
        CircularBuffer_Put(b, 0xDeadBeef + i);              // row  6,  7
        assert(!CircularBuffer_IsEmpty(b));                 // row  1,  2
    }

    assert(CircularBuffer_IsFull(b));                       // row  5
    assert(!CircularBuffer_Put(b, 0xDeadBeef));             // row  8
    assert(capacity == CircularBuffer_Capacity(b));         // row 14

    // Read after Write (RaW), Read after Read (RaR)
    for (i = 0; i < capacity; ++i) {
        assert(!CircularBuffer_IsEmpty(b));                 // row  1,  2
        assert(0xDeadBeef + i == CircularBuffer_Get(b));    // row 10, 11
        assert(!CircularBuffer_IsFull(b));                  // row  3,  4
    }

    assert(CircularBuffer_IsEmpty(b));                      // row  0
    assert(empty_value == CircularBuffer_Get(b));           // row  9

    CircularBuffer_Destroy(b);

    printf("%s code\n", exercise_state);
    return 0;
}
