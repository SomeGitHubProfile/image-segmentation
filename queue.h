#pragma once

#include "coords.h"

#ifndef QUEUE
#define QUEUE
typedef struct QueueElement {
    Coords coords;
    struct QueueElement* next;
} QueueElement;

typedef struct Queue {
    QueueElement* front;
    QueueElement* back;
    size_t size;
} Queue;

Queue* create_queue();
void push(Queue* queue, unsigned x, unsigned y);
Coords pop(Queue* queue);
Coords front(Queue* queue);
size_t queue_size(Queue* queue);
void clear(Queue* queue);
#endif