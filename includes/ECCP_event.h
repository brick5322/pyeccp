//
// Created by bric on 2022/4/12.
//

#ifndef PYECCP_ECCP_EVENT_H
#define PYECCP_ECCP_EVENT_H

#include <ECCP.h>

typedef struct EventQueue EventQueue;
typedef struct EventNode EventNode;

/**
 * @class EventQueue
 * @brief 相机的事件队列
 * @details 会被 @ref PyCameraObject 继承
 */
struct EventQueue{
    EventNode* headNode;
    EventNode* tailNode;
    int length;
};
/**
 * @brief 相机的事件结点
 */
struct EventNode{
    ECCP_message * msg_data;
    EventNode* next;
};


/**
 * @brief 构造一个新的ECCP事件置入队列中
 * 
 * @param queue 要被置入的队列
 * @param length ECCP事件长度（Byte）
 * @return 新构造的ECCP事件指针
 */
ECCP_message* queue_in_new_message(EventQueue* queue, int length);

/**
 * @brief 将一个ECCP事件置入队列中
 * 
 * @param queue 要被置入的队列
 * @param msg 一个已经构造的ECCP事件
 */
void queue_in_message(EventQueue* queue, ECCP_message* msg);

/**
 * @brief 从队列中取出一个ECCP事件
 * 
 * @param queue 要被取出的队列
 * @return 取出的ECCP事件指针 
 */
ECCP_message* queue_out_move_message(EventQueue* queue);
void EventQueue_clear(EventQueue* queue);

/**
 * @brief 清除队列中所有的事件节点
 * 
 * @param queue 要被清空的队列
 */
void EventQueue_clear(EventQueue* queue);

/**
 * @brief 构造ECCP事件结点
 * 
 * @param msg ECCP事件指针
 * @return 构造的ECCP事件结点
 */
EventNode* EventNode_alloc(ECCP_message* msg);

/**
 * @brief 要释放的ECCP事件结点
 * 
 * @param n ECCP事件指针
 * @return 被释放的下一个结点
 */
EventNode* EventNode_free(EventNode* n);

void ECCP_set_message_1(EventQueue* queue);
void ECCP_set_message_2(EventQueue* queue);
void ECCP_set_message_3(EventQueue* queue);
void ECCP_set_message_4(EventQueue* queue, int duration);
void ECCP_set_message_6(EventQueue* queue);

#endif //PYECCP_ECCP_EVENT_H
