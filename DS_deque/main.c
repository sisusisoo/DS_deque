#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#define MAX_QUEUE_SIZE 10
typedef int element;
typedef struct { 
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} DequeType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}

int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}

int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void deque_print(DequeType* q)
{
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front; // i에 현재 q의 front값을 넣음
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE); // i의 자리를 1증가
			printf("%d | ", q->data[i]); // 증가한 i 자리에 해당하는 data값을 출력
		} while (i != q->rear);
	}
	printf("\n");
}

void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; // rear값 1 증가
		q->data[q->rear] = item;
	}
}

element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q)) {
		error("큐가 공백상태입니다");
	}
	else {
		q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; // rear값 1감소
		return q->data[prev];
	}
}

element get_rear(DequeType* q)
{
	if (is_empty(q)) error("큐가 공백상태입니다");
	else { return q->data[q->rear]; }

}

void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	else{
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; // front값 1감소
	}

}

element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	else {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE; // front값 1 증가
		return q->data[q->front];
	}
}

element get_front(DequeType* q)
{
	if (is_empty(q)) {
		error("큐가 공백상태입니다");
	}
	else { return q->data[(q->front + 1) % MAX_QUEUE_SIZE]; }
}
// 메인
int main1(void)
{
	DequeType queue;

	init_deque(&queue);
	for (int i = 0; i < 3; i++) {
		add_front(&queue, i);
		deque_print(&queue);
	}
	for (int i = 0; i < 3; i++) {
		delete_rear(&queue);
		deque_print(&queue);
	}
	return 0;
}
int palindrome_check(DequeType* q) {
	while (!is_empty(q)) {
		if (delete_front(q) != delete_rear(q)) {
			return 0;
		}
		else {
			return 1;
		}
	}
	return 1;
}

int main()
{
	while(1) {
		printf("단어 입력 (exit입력시 종료): ");
		DequeType dq;
		char str[30];
		gets_s(str, 30);//문자열만 입력
		init_deque(&dq);
		if (strcmp(str, "exit", 4)==0) {
			exit(1);
		}
		for (int i = 0; i < strlen(str); i++) {
			add_rear(&dq, str[i]);
		}
		if (palindrome_check(&dq)) {
			printf("회문입니다");
		}
		else {
			printf("회문이 아닙니다");
		}
		printf("\n");
	
	}
}
