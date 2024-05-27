#include "queue.h"

#include <stdlib.h>

#include "coords.h"

Queue* create_queue() {
    Queue* queue = malloc(sizeof(Queue));
    queue->front = queue->back = NULL;
    queue->size = 0;
    return queue;
}

void push(Queue* queue, unsigned x, unsigned y) {
    QueueElement* e = malloc(sizeof(QueueElement));
    e->coords.x = x;
    e->coords.y = y;
    e->next = NULL;
    if (queue->size) {
        queue->back->next = e;
    } else {
        queue->front = e;
    }
    queue->back = e;
    ++queue->size;
    return;
}

Coords pop(Queue* queue) {
    Coords coords = queue->front->coords;
    QueueElement* e = queue->front;
    queue->front = e->next;
    --queue->size;
    if (!queue->size) {
        queue->back = NULL;
    }
    free(e);
    return coords;
}

Coords front(Queue* queue) {
    return queue->front->coords;
}

size_t queue_size(Queue* queue) {
    return queue->size;
}

void clear(Queue* queue) {
    for (QueueElement* front = queue->front; front; queue->front = front) {
        front = front->next;
        free(queue->front);
    }
    queue->size = 0;
    queue->back = NULL;
    return;
}