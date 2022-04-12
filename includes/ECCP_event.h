//
// Created by bric on 2022/4/12.
//

#ifndef PYECCP_ECCP_EVENT_H
#define PYECCP_ECCP_EVENT_H

#include <ECCP.h>

typedef struct eventQueue eventQueue;
typedef struct eventNode eventNode;

struct eventQueue{
    eventNode* headNode;
    eventNode* tailNode;
    int length;
};

struct eventNode{
    ECCP_message * msg_data;
    eventNode* next;
};

ECCP_message* queue_in_new_message(eventQueue* queue,int length);
ECCP_message* queue_out_message(eventQueue* queue);

eventNode* eventNode_alloc(ECCP_message* msg);
eventNode* event_free(eventNode* n);

void ECCP_set_message_1(eventQueue* queue);
void ECCP_set_message_2(eventQueue* queue);
void ECCP_set_message_3(eventQueue* queue);
void ECCP_set_message_4(eventQueue* queue,int duration);
void ECCP_set_message_6(eventQueue* queue);

#endif //PYECCP_ECCP_EVENT_H
