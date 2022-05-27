#pragma once

//
// Created by bric on 2022/4/12.
//

#ifndef PYECCP_ECCP_EVENT_H
#define PYECCP_ECCP_EVENT_H

#include <ECCP.h>
#include <List.h>
#include <Node.h>


/**
 * @class EventQueue
 * @brief 相机的事件队列
 * @details 会被 @ref PyCameraObject 继承
 */
typedef struct EventQueue EventQueue;

struct EventQueue
{
    BasicList_Head;
    Destructor destructors;
};

/**
 * @brief 相机的事件结点
 */
typedef struct Node EventNode;

/**
 * @brief 初始化queue
 * @param queue 要被初始化的队列
 */
EventQueue* EventQueue_init(void* queue);

/**
 * @brief 将一个ECCP事件置入队列中
 *
 * @param queue 要被置入的队列
 * @param msg 一个已经构造的ECCP事件
 */
void EventQueue_in(EventQueue* queue, ECCP_message* msg);

/**
 * @brief 从队列中取出一个ECCP事件
 *
 * @param queue 要被取出的队列
 * @return 取出的ECCP事件指针
 */
ECCP_message* EventQueue_out(EventQueue* queue);

/**
 * @brief 清除队列中所有的事件节点
 *
 * @param queue 要被清空的队列
 */
void EventQueue_clear(EventQueue* queue);



void ECCP_set_message_1(EventQueue* queue);
void ECCP_set_message_2(EventQueue* queue);
void ECCP_set_message_3(EventQueue* queue);
void ECCP_set_message_4(EventQueue* queue, int duration);
void ECCP_set_message_6(EventQueue* queue);

#endif //PYECCP_ECCP_EVENT_H
