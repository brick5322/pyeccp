//
// Created by bric on 2022/4/12.
//

#include <ECCP_event.h>
#include <stdlib.h>

EventNode* EventNode_alloc(ECCP_message* msg)
{
    EventNode* ret = malloc(sizeof(EventNode));
    ret->msg_data = msg;
    return ret;
}

EventNode* EventNode_free(EventNode* n)
{
    EventNode* ret = n->next;
    free(n);
    return ret;
}

ECCP_message* queue_in_new_message(EventQueue* queue, int msg_length)
{
    ECCP_message *msg = malloc(msg_length);

    if(queue->length)
        queue->tailNode = queue->tailNode->next = EventNode_alloc(msg);
    else
        queue->tailNode = queue->headNode = EventNode_alloc(msg);

    queue->length++;
    return msg;
}

void queue_in_message(EventQueue *queue, ECCP_message *msg) {

    if(queue->length)
        queue->tailNode = queue->tailNode->next = EventNode_alloc(msg);
    else
        queue->tailNode = queue->headNode = EventNode_alloc(msg);

    queue->length++;
}

ECCP_message* queue_out_move_message(EventQueue* queue)
{
    ECCP_message* msg = NULL;
    if(queue->length)
    {
        EventNode* head = queue->headNode;
        msg = head->msg_data;
        queue->headNode = head->next;
        EventNode_free(head);
    }
    return msg;
}

void ECCP_set_message_1(EventQueue* queue)
{
    ECCP_message* msg = queue_in_new_message(queue,sizeof(clock_t)+4);
    msg->length = sizeof(clock_t);
    msg->func_code = 1;
    *(clock_t*)msg->data = time(0);
}

void ECCP_set_message_2(EventQueue* queue)
{
    ECCP_message* msg = queue_in_new_message(queue,4);
    msg->length = 0;
    msg->func_code = 2;
}

void ECCP_set_message_3(EventQueue* queue)
{
    ECCP_message* msg = queue_in_new_message(queue,4);
    msg->length = 0;
    msg->func_code = 3;
}

void ECCP_set_message_4(EventQueue* queue, int duration)
{
    ECCP_message* msg = queue_in_new_message(queue,4+sizeof(unsigned int));
    msg->length = 0;
    msg->func_code = 4;
    *(int*)msg->data = duration;
}

void ECCP_set_message_6(EventQueue* queue)
{
    ECCP_message* msg = queue_in_new_message(queue,4);
    msg->length = 0;
    msg->func_code = 6;
}