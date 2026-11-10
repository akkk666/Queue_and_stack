#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 200

//定义循环队列结构体
typedef struct{
    int data[MAXSIZE];
    int front;
    int rear;
    int size;
}queue;

//创建队列
void InitQueue(queue *q){
    q->front=0;
    q->rear=0;
    q->size=0;

    printf("队列创建成功！\n");
}

//插入操作：入队
void EnQueue(queue *q,int x){
    if(q->size==MAXSIZE){
        printf("队列已满，无法插入！\n");
        return;
    }

    q->data[q->rear]=x;
    q->rear=(q->rear+1)%MAXSIZE;

    q->size++;
    printf("元素%d插入成功\n",x);
}

//删除操作：出队
void DeQueue(queue *q){
    if(q->size==0){
        printf("队列为空，无法删除\n");
        return;
    }

    int x=q->data[q->front];
    q->front=(q->front+1)%MAXSIZE;

    q->size--;
    printf("删除的队头元素是：%d\n",x);
}

//存取操作：读取队头元素
void GetHead(queue *q){
    if(q->size==0){
        printf("队列为空，没有队头元素\n");
        return;
    }

    printf("当前队头元素是：%d\n",q->data[q->front]);
}

//打印队列
void PrintQueue(queue *q){
    if(q->size==0){
        printf("当前队列为空\n");
        return;
    }

    printf("当前队列：");

    for(int i=0;i<q->size;i++){
        int index=(q->front+i)%MAXSIZE;
        printf("%d",q->data[index]);
    }

    printf("\n");
}

int main(void){
    system("chcp 65001");  // 控制台切换到 UTF-8，避免中文乱码
    queue q;
    int choice;
    int x;

    InitQueue(&q);
    while(1){
        printf("\n======队列操作菜单======\n");
        printf("1. 插入元素（入队）\n");
        printf("2. 删除元素（出队）\n");
        printf("3. 读取队头元素\n");
        printf("4. 打印队列\n");
        printf("0. 退出程序\n");
        printf("请选择操作：");

        if(scanf("%d",&choice)!=1){
            printf("输入错误！\n");
            return 1;
        }

       switch (choice) {
            case 1:
                printf("请输入要插入的元素：");
                if (scanf("%d", &x) != 1) {
                    printf("输入错误！\n");
                    return 1;
                }
                EnQueue(&q, x);
                break;

            case 2:
                DeQueue(&q);
                break;

            case 3:
                GetHead(&q);
                break;

            case 4:
                PrintQueue(&q);
                break;

            case 0:
                printf("程序结束！\n");
                return 0;

            default:
                printf("无效选择，请重新输入！\n");
        }
    }
    return 0;
}