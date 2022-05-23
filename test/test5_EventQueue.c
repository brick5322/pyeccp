#include <ECCP.h>
#include <ECCP_event.h>
#include <stdio.h>

int main() {
    char buffer[sizeof(EventQueue)];
    EventQueue *queue = EventQueue_init(buffer);
    ECCP_set_message_1(queue);
    ECCP_set_message_2(queue);
    ECCP_set_message_3(queue);
    ECCP_set_message_4(queue, 2);
    ECCP_set_message_6(queue);
    ECCP_message *message;
    message = EventQueue_out(queue);
    printf("%d\n",message->func_code);
    message = EventQueue_out(queue);
    printf("%d\n",message->func_code);
    message = EventQueue_out(queue);
    printf("%d\n",message->func_code);
    message = EventQueue_out(queue);
    printf("%d\n",message->func_code);
    message = EventQueue_out(queue);
    printf("%d\n",message->func_code);
    return 0;
}