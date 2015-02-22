//- Copyright (c) 2008-2014 James Grenning --- All rights reserved
//- For exclusive use by participants in Wingman Software training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.wingman-sw.com james@wingman-sw.com

#include "CircularBuffer.h"

#include <stdlib.h>     // for calloc, free

struct CircularBuffer
{
    unsigned int capacity;  // cell count, including both used and unused cells
    int * cells;            // storage for integers
    int default_;           // returned on `get` from empty buffer
    unsigned int in;        // index where the next `put` value will be stored
    unsigned int size;      // count of cells currently in use
};

struct CircularBuffer * CircularBuffer_Create(unsigned int capacity, int default_value)
{
    struct CircularBuffer * self;       // result
    if (NULL == (self = malloc(sizeof(struct CircularBuffer))))
        return NULL;
    if (NULL == (self->cells = malloc(capacity * sizeof(int)))) {
        free(self);
        return NULL;
    }
    self->capacity = capacity;
    self->default_ = default_value;
    self->in = 0;                       // begin at the beginning
    self->size = 0;                     // start empty
    return self;
}

void CircularBuffer_Destroy(struct CircularBuffer * self)
{
    free(self->cells);
    free(self);
}

bool CircularBuffer_IsEmpty(struct CircularBuffer * self)
{
    return 0 == self->size;
}

bool CircularBuffer_IsFull(struct CircularBuffer * self)
{
    return self->capacity == self->size;
}

bool CircularBuffer_Put(struct CircularBuffer * self, int value)
{
    if (self->capacity == self->size)
        return false;
    self->cells[self->in] = value;
    self->in = (self->in + 1) % self->capacity;
    self->size++;
    return true;
}

int CircularBuffer_Get(struct CircularBuffer * self)
{
    return self->size
        ? self->cells[(self->capacity - self->size-- + self->in) % self->capacity]
        : self->default_;
}

unsigned int CircularBuffer_Capacity(struct CircularBuffer * self)
{
    return self->capacity;
}
