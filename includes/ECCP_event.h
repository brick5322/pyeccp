//
// Created by bric on 2022/4/12.
//

#ifndef PYECCP_ECCP_EVENT_H
#define PYECCP_ECCP_EVENT_H

#include <ECCP.h>

typedef struct EventQueue EventQueue;
typedef struct EventNode EventNode;

struct EventQueue{
    EventNode* headNode;
    EventNode* tailNode;
    int length;
};

struct EventNode{
    ECCP_message * msg_data;
    EventNode* next;
};



ECCP_message* queue_in_new_message(EventQueue* queue, int length);
void queue_in_message(EventQueue* queue, ECCP_message* msg);
ECCP_message* queue_out_move_message(EventQueue* queue);

EventNode* EventNode_alloc(ECCP_message* msg);
EventNode* EventNode_free(EventNode* n);

void ECCP_set_message_1(EventQueue* queue);
void ECCP_set_message_2(EventQueue* queue);
void ECCP_set_message_3(EventQueue* queue);
void ECCP_set_message_4(EventQueue* queue, int duration);
void ECCP_set_message_6(EventQueue* queue);

#endif //PYECCP_ECCP_EVENT_H
