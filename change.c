
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define MAXSIZE 200

// ==================== 循环队列定义 ====================

typedef struct {
    int data[MAXSIZE];
    int front;
    int rear;
    int size;
} Queue;

// 初始化队列
void InitQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

// 入队：将元素插入队尾
int EnQueue(Queue *q, int x) {
    if (q->size == MAXSIZE) {
        printf("队列已满！\n");
        return 0;
    }

    q->data[q->rear] = x;
    q->rear = (q->rear + 1) % MAXSIZE;
    q->size++;

    return 1;
}

// 出队：删除队头元素，并通过x返回其值
int DeQueue(Queue *q, int *x) {
    if (q->size == 0) {
        return 0;
    }

    *x = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    q->size--;

    return 1;
}

// ==================== 顺序栈定义 ====================

typedef struct {
    int data[MAXSIZE];
    int top;
} Stack;

// 初始化栈
void InitStack(Stack *s) {
    s->top = -1;
}

// 入栈：将元素压入栈顶
int Push(Stack *s, int x) {
    if (s->top == MAXSIZE - 1) {
        printf("堆栈已满！\n");
        return 0;
    }

    s->data[++s->top] = x;
    return 1;
}

// 出栈：取出栈顶元素
int Pop(Stack *s, int *x) {
    if (s->top == -1) {
        return 0;
    }

    *x = s->data[s->top--];
    return 1;
}

// ==================== Change函数 ====================

// 将无符号十进制整数转换为八进制数
void Change(unsigned long long num) {
    Queue q;
    Stack s;

    int remainder;
    int x;

    // 初始化队列和堆栈
    InitQueue(&q);
    InitStack(&s);

    // 特殊情况：输入为0
    if (num == 0) {
        printf("八进制转换结果为：0\n");
        return;
    }

    printf("\n========== 转换过程 ==========\n");

    // 第一步：采用除8取余法，将余数依次放入队列
    while (num > 0) {
        remainder = num % 8;

        // 将余数放入队列
        EnQueue(&q, remainder);

        // 输出调试信息，方便观察转换过程
        printf("当前被除数：%llu，余数：%d，商：%llu\n",
               num, remainder, num / 8);

        // 用商替代原来的数，继续计算
        num = num / 8;
    }

    printf("\n========== 队列转堆栈 ==========\n");

    // 第二步：将队列中的元素依次出队，并压入堆栈
    while (DeQueue(&q, &x)) {
        Push(&s, x);

        // 调试信息
        printf("元素%d出队，并进入堆栈\n", x);
    }

    printf("\n========== 最终转换结果 ==========\n");

    // 第三步：依次出栈，输出正确顺序的八进制数
    printf("十进制数对应的八进制数为：");

    while (Pop(&s, &x)) {
        printf("%d", x);
    }

    printf("\n");
}

// ==================== Check函数 ====================

// 检查输入的十进制整数是否合法，并调用Change函数
int Check(const char *input) {
    char *endptr;
    unsigned long long num;
    const char *start = input;

    // 跳过开头的空白字符
    while (isspace((unsigned char)*start)) {
        start++;
    }

    // 不允许负数和空输入
    if (*start == '\0' || *start == '-') {
        printf("输入错误！请输入无符号十进制整数。\n");
        return 0;
    }

    // 将字符串转换为无符号整数
    errno = 0;
    num = strtoull(start, &endptr, 10);

    // 检查转换失败或数值溢出
    if (errno == ERANGE || endptr == start) {
        printf("输入错误！数字超出范围或格式不正确。\n");
        return 0;
    }

    // 检查数字后是否存在非法字符
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        printf("输入错误！请勿输入非数字字符。\n");
        return 0;
    }

    // 调用Change函数完成进制转换
    Change(num);

    return 1;
}

// ==================== 主函数 ====================

int main(void) {
    system("chcp 65001");
    char input[256];

    printf("========== 十进制转换八进制程序 ==========\n");

    printf("请输入一个无符号十进制整数：");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("输入失败！\n");
        return 1;
    }

    // 检查输入是否完整，防止超长输入被截断
    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        printf("输入错误！输入内容过长。\n");
        return 1;
    }

    // 调用Check函数进行输入检查和转换
    Check(input);

    return 0;
}
