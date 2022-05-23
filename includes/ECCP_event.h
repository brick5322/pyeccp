#pragma once

//
// Created by bric on 2022/4/12.
//

#ifndef PYECCP_ECCP_EVENT_H
#define PYECCP_ECCP_EVENT_H

#include <ECCP.h>
#include "List.h"
#include "Node.h"


/**
 * @class EventQueue
 * @brief ������¼�����
 * @details �ᱻ @ref PyCameraObject �̳�
 */
typedef struct EventQueue EventQueue;

struct EventQueue
{
    BasicList_Head;
    Destructor destructors;
};

/**
 * @brief ������¼����
 */
typedef struct Node EventNode;

/**
 * @brief ��ʼ��queue
 * @param queue Ҫ����ʼ���Ķ���
 */
EventQueue* EventQueue_init(void* queue);

/**
 * @brief ��һ��ECCP�¼����������
 *
 * @param queue Ҫ������Ķ���
 * @param msg һ���Ѿ������ECCP�¼�
 */
void EventQueue_in(EventQueue* queue, ECCP_message* msg);

/**
 * @brief �Ӷ�����ȡ��һ��ECCP�¼�
 *
 * @param queue Ҫ��ȡ���Ķ���
 * @return ȡ����ECCP�¼�ָ��
 */
ECCP_message* EventQueue_out(EventQueue* queue);

/**
 * @brief ������������е��¼��ڵ�
 *
 * @param queue Ҫ����յĶ���
 */
void EventQueue_clear(EventQueue* queue);



void ECCP_set_message_1(EventQueue* queue);
void ECCP_set_message_2(EventQueue* queue);
void ECCP_set_message_3(EventQueue* queue);
void ECCP_set_message_4(EventQueue* queue, int duration);
void ECCP_set_message_6(EventQueue* queue);

#endif //PYECCP_ECCP_EVENT_H
