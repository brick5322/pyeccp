#include "ECCP_event.h"
#include <time.h>
#include <stdlib.h>


/**
 * @brief ����һ���µ�ECCP�¼����������
 *
 * @param queue Ҫ������Ķ���
 * @param length ECCP�¼����ȣ�Byte��
 * @return �¹����ECCP�¼�ָ��
 */
ECCP_message* queue_in_new_message(EventQueue* queue, int length);

/**
 * @brief ����ECCP�¼����
 *
 * @param msg ECCP�¼�ָ��
 * @return �����ECCP�¼����
 */
EventNode* EventNode_alloc(ECCP_message* msg);

/**
 * @brief Ҫ�ͷŵ�ECCP�¼����
 *
 * @param n ECCP�¼�ָ��
 * @return ���ͷŵ���һ�����
 */
EventNode* EventNode_free(EventNode* n);


EventQueue* EventQueue_init(void* queue)
{
	BasicList_init(queue)->destructors[0] = NULL;
    return queue;
}

void EventQueue_in(EventQueue* queue, ECCP_message* msg)
{
	Node_getData(ECCP_message*, BasicList_queue_in(queue, 0, sizeof(ECCP_message*))) = msg;
}

ECCP_message* EventQueue_out(EventQueue* queue)
{
	Node* node = BasicList_queue_out(queue);
	ECCP_message* ret = Node_getData(ECCP_message*, node);
	Node_free(node, &queue->destructors);
	return ret;
}

void EventQueue_clear(EventQueue* queue)
{
	BasicList_clear(queue);
}

void ECCP_set_message_1(EventQueue* queue)
{
    Node* current = BasicList_queue_in(queue, 0, sizeof(ECCP_message*));
	ECCP_message* curmsg = malloc(sizeof(ECCP_message)+sizeof(clock_t));
    Node_getData(ECCP_message*, current) = curmsg;
	curmsg->length = sizeof(clock_t);
	curmsg->func_code = 1;
	*(clock_t*)curmsg->data = time(0);
}

void ECCP_set_message_2(EventQueue* queue)
{
	Node* current = BasicList_queue_in(queue, 0, sizeof(ECCP_message*));
    ECCP_message* curmsg = malloc(sizeof(ECCP_message));
    Node_getData(ECCP_message*, current) = curmsg;
    curmsg->length = 0;
	curmsg->func_code = 2;
}

void ECCP_set_message_3(EventQueue* queue)
{
	Node* current = BasicList_queue_in(queue, 0, sizeof(ECCP_message*));
    ECCP_message* curmsg = malloc(sizeof(ECCP_message));
    Node_getData(ECCP_message*, current) = curmsg;	curmsg->length = 0;
    curmsg->length = 0;
	curmsg->func_code = 3;
}

void ECCP_set_message_4(EventQueue* queue, int duration)
{
	Node* current = BasicList_queue_in(queue, 0, sizeof(ECCP_message*));
    ECCP_message* curmsg = malloc(sizeof(ECCP_message) + sizeof(uint32_t));
    Node_getData(ECCP_message*, current) = curmsg;	curmsg->length = 0;
    curmsg->length = sizeof(uint32_t);
	curmsg->func_code = 4;
	*(int*)curmsg->data = duration;
}

void ECCP_set_message_6(EventQueue* queue)
{
	Node* current = BasicList_queue_in(queue, 0, sizeof(ECCP_message*));
    ECCP_message* curmsg = malloc(sizeof(ECCP_message));
    Node_getData(ECCP_message*, current) = curmsg;	curmsg->length = 0;
    curmsg->length = 0;
	curmsg->func_code = 6;
}
