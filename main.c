

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAXSIZE 200
struct node
{
    char data;
    struct node* lchild;
    struct node* rchild;
};
typedef struct node* pnode;
int count_l = 0;
int count_n = 0;

pnode create_tree()    //��ʼ��һ�ö�����
{
    pnode pt;
    char data;
    data = getchar();
    if(data == '.')
    {
        pt = NULL;
    }
    else
    {
        pt = (pnode)malloc(sizeof(struct node));
        pt->data = data;
        pt->lchild = create_tree();
        pt->rchild = create_tree();
    }
    return pt;
}

void print_pretree(pnode ps)   //�ݹ�ǰ�����
{
    if(ps != NULL)
    {
        printf("%3c", ps->data);
        print_pretree(ps->lchild);
        print_pretree(ps->rchild);
    }
}

void print_midtree(pnode ps)   //�ݹ��������
{
    if(ps != NULL)
    {
        print_midtree(ps->lchild);
        printf("%3c", ps->data);
        print_midtree(ps->rchild);
    }
}

void print_posttree(pnode ps)   //�ݹ��������
{
    if(ps != NULL)
    {
        print_posttree(ps->lchild);
        print_posttree(ps->rchild);
        printf("%3c", ps->data);
    }
}

void PreOrder(pnode ps)  //�ǵݹ��������
{
    pnode stack[MAXSIZE], p;
    int top = -1;
    if(ps != NULL)
    {
        top++;
        stack[top] = ps;
        while(top > -1)
        {
            p = stack[top];
            top--;
            printf("%3c", p->data);
            if(p->rchild != NULL)
            {
                top++;
                stack[top] = p->rchild;
            }
            if(p->lchild != NULL)
            {
                top++;
                stack[top] = p->lchild;
            }
        }
        printf("\n");
    }
}

void InOrder(pnode ps)  //�ǵݹ��������
{
    pnode stack[MAXSIZE], p;
    int top = -1;
    if(ps != NULL)
    {
        p = ps;
        while(top > -1 || p != NULL)
        {
            while(p != NULL)
            {
                top++;
                stack[top] = p;
                p = p->lchild;
            }
            if(top > -1)
            {
                p = stack[top];
                top--;
                printf("%3c", p->data);
                p = p->rchild;
            }
        }
        printf("\n");
    }
}

void PostOrder(pnode ps)  //�ǵݹ�������
{
    pnode stack[MAXSIZE], p;
    int sign, top = -1;
    if(ps != NULL)
    {
        do{
            while(ps != NULL)
            {
                top++;
                stack[top] = ps;
                ps = ps->lchild;
            }
            p = NULL;
            sign = 1;
            while(top != -1 && sign)
            {
                ps = stack[top];
                if(ps->rchild == p)
                {
                    printf("%3c", ps->data);
                    top--;
                    p = ps;
                }
                else
                {
                    ps = ps->rchild;
                    sign = 0;
                }
            }
        }while(top != -1);
        printf("\n");
    }
}



/*
��������ǵݹ���ʣ�ʹ��ջ����ʵ�֡���������ķǵݹ���������е�
������������򵥵��ˡ���Ҫ˼������Ƚ������ѹ��ջ��Ȼ�������
ջ�����ʸ���㣬�������ν��������Һ��ӡ�������ջ��ֱ��ջΪ��
Ϊֹ��
*/
void preOrderIter1(pnode ps)  //�ǵݹ�ǰ�����1
{
    pnode stack[MAXSIZE], cur;
    int top = -1;
    if(ps == NULL)
        return;
    stack[++top] = ps;
    while(top > -1)
    {
        cur = stack[top--];
        printf("%3c", cur->data);
        if(cur->rchild != NULL)
            stack[++top] = cur->rchild;
        if(cur->lchild != NULL)
            stack[++top] = cur->lchild;
    }
    printf("\n");
}

/*
��������ķǵݹ��㷨��һ�㷨��Ҳ���õ�ջ��ֻ����΢���ӵ㣬����
�������������Ҫ���ݲ�������������
*/
void preOrderIter2(pnode ps)  //�ǵݹ�ǰ�����2
{
    pnode stack[MAXSIZE];
    int top = -1;
    if(ps == NULL)
        return;
    while(ps != NULL || top > -1)
    {
        if(ps != NULL)
        {
            printf("%3c", ps->data);
            stack[++top] = ps;
            ps = ps->lchild;
        }
        else
        {
            ps = stack[top--];
            ps = ps->rchild;
        }
    }
    printf("\n");
}

/*
��������ǵݹ��㷨Ҳ�ǲ���ջʵ�֣����������������㷨2���ƣ�
ֻ�Ƿ��ʸ�����ʱ����ͬ��
*/
void inOrderIter(pnode ps)  //�ǵݹ��������
{
    pnode stack[MAXSIZE];
    int top = -1;
    while(ps != NULL || top > -1)
    {
        if(ps != NULL)
        {
            stack[++top] = ps;
            ps = ps->lchild;
        }
        else
        {
            ps = stack[top--];
            printf("%3c", ps->data);
            ps = ps->rchild;
        }
    }
    printf("\n");
}


/*
��������ķǵݹ��㷨�ϸ��ӣ�ʹ��һ��ջ����ʵ�֣����ǹ��̺ܷ�����
������������������ջ��ʵ�ֺ�������ķǵݹ��㷨��ע�⵽�������
���Կ������������������̣����ȱ���ĳ����㣬Ȼ��������Һ��ӣ�Ȼ
����������ӡ����������������Ǻ���������㷨�������£�
1��Push����㵽��һ��ջs�С�
2���ӵ�һ��ջs��Pop��һ����㣬������Push���ڶ���ջoutput�С�
3��Ȼ��Push�������Ӻ��Һ��ӵ���һ��ջs�С�
4���ظ�����2��3ֱ��ջsΪ�ա�
5����ɺ����н���Ѿ�Push��ջoutput�У��Ұ��պ��������˳���ţ�
ֱ��ȫ��Pop�������Ƕ�����������������
*/
void PostOrderIter1(pnode ps)  //�ǵݹ�������
{
    pnode stack[MAXSIZE], output[MAXSIZE], cur;
    int top_stack = -1;
    int top_output = -1;
    if(ps == NULL)
        return;
    stack[++top_stack] = ps;
    while(top_stack > -1)
    {
        cur = stack[top_stack--];
        output[++top_output] = cur;
        if(cur->lchild != NULL)
            stack[++top_stack] = cur->lchild;
        if(cur->rchild != NULL)
            stack[++top_stack] = cur->rchild;
    }
    while(top_output > -1)
    {
        printf("%3c", output[top_output--]->data);
    }
    printf("\n");
}



/*
������һ�ڵ�P��
1���Ƚ��ڵ�P��ջ��
2����P���������Ӻ��Һ��ӣ�����P�������ӻ��Һ��ӣ������Һ���
�Ѿ�������������ֱ������ڵ�P���������ջ������ջ�ڵ�P���Ϊ��
һ������Ľڵ㣬�ٽ���ʱ��ջ�������Ϊ��ǰ�ڵ㣻
3����������2���е���������P���Һ��Ӻ�����������ջ����ǰ�ڵ�
������Ϊջ����㣬֮���ظ�����2����
4��ֱ��ջ�գ�����������
*/
void PostOrderIter2(pnode ps)
{
    pnode stack[MAXSIZE], cur, pre = NULL;
    int top = -1;
    if(ps == NULL)
        return;
    stack[++top] = ps;
    while(top > -1)
    {
        cur = stack[top];
        if((cur->lchild == NULL && cur->rchild == NULL) || (pre != NULL && (cur->lchild == pre || cur->rchild == pre)))
        {
            printf("%3c", cur->data);
            top--;
            pre = cur;
        }
        else
        {
            if(cur->rchild != NULL)
                stack[++top] = cur->rchild;
            if(cur->lchild != NULL)
                stack[++top] = cur->lchild;
        }
    }
    printf("\n");
}












int count_leaf(pnode ps)   //����Ҷ�ӽڵ����
{
    if(ps != NULL)
    {
        if(ps->lchild == NULL && ps->rchild == NULL)
            count_l++;
        count_leaf(ps->lchild);
        count_leaf(ps->rchild);
    }
    return count_l;
}

int count_node(pnode ps)   //�����ܹ��Ľڵ����
{
    if(ps != NULL)
    {
        count_n++;
        count_node(ps->lchild);
        count_node(ps->rchild);
    }
    return count_n;
}

int count_depth(pnode ps)   //�ݹ��������������
{
    int ldep, rdep;
    ldep = rdep = 0;
    if(ps == NULL)
    {
        return 0;
    }
    else
    {
        ldep = count_depth(ps->lchild);
        rdep = count_depth(ps->rchild);
        return ldep > rdep ? (ldep+1) : (rdep+1);
    }
}

int main()
{
    pnode ps;
    ps = create_tree();

    printf("pre order ...\n");
    print_pretree(ps);
    printf("\n");
    printf("mid order...\n");
    print_midtree(ps);
    printf("\n");
    printf("post order...\n");
    print_posttree(ps);
    printf("\n");
    printf("Pre Order ......\n");
    //PreOrder(ps);
    preOrderIter1(ps);
    preOrderIter2(ps);
    printf("\n");
    printf("In Order ......\n");
    //InOrder(ps);
    inOrderIter(ps);
    printf("\n");
    printf("Post Order......\n");
    PostOrder(ps);
    PostOrderIter1(ps);
    PostOrderIter2(ps);
    printf("\n");

    printf("The number of leaf is: %d\n", count_leaf(ps));
    printf("The number of node is: %d\n", count_node(ps));
    printf("Max of depth is: %d\n", count_depth(ps));
    return 0;
}







