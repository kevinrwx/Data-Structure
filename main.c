

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

pnode create_tree()    //初始化一棵二叉树
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

void print_pretree(pnode ps)   //递归前序遍历
{
    if(ps != NULL)
    {
        printf("%3c", ps->data);
        print_pretree(ps->lchild);
        print_pretree(ps->rchild);
    }
}

void print_midtree(pnode ps)   //递归中序遍历
{
    if(ps != NULL)
    {
        print_midtree(ps->lchild);
        printf("%3c", ps->data);
        print_midtree(ps->rchild);
    }
}

void print_posttree(pnode ps)   //递归后续遍历
{
    if(ps != NULL)
    {
        print_posttree(ps->lchild);
        print_posttree(ps->rchild);
        printf("%3c", ps->data);
    }
}

void PreOrder(pnode ps)  //非递归先序遍历
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

void InOrder(pnode ps)  //非递归中序遍历
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

void PostOrder(pnode ps)  //非递归后序遍历
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
先序遍历非递归访问，使用栈即可实现。先序遍历的非递归访问在所有的
遍历中算是最简单的了。主要思想就是先将根结点压入栈，然后根结点出
栈并访问根结点，而后依次将根结点的右孩子、左孩子入栈，直到栈为空
为止。
*/
void preOrderIter1(pnode ps)  //非递归前序遍历1
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
先序遍历的非递归算法另一算法，也是用的栈，只是稍微复杂点，当左
子树遍历完后，需要回溯并遍历右子树。
*/
void preOrderIter2(pnode ps)  //非递归前序遍历2
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
中序遍历非递归算法也是采用栈实现，与上面的先序遍历算法2类似，
只是访问根结点的时机不同。
*/
void inOrderIter(pnode ps)  //非递归中序遍历
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
后序遍历的非递归算法较复杂，使用一个栈可以实现，但是过程很繁琐，
这里可以巧妙的用两个栈来实现后序遍历的非递归算法。注意到后序遍历
可以看作是下面遍历的逆过程：即先遍历某个结点，然后遍历其右孩子，然
后遍历其左孩子。这个过程逆过来就是后序遍历。算法步骤如下：
1、Push根结点到第一个栈s中。
2、从第一个栈s中Pop出一个结点，并将其Push到第二个栈output中。
3、然后Push结点的左孩子和右孩子到第一个栈s中。
4、重复过程2和3直到栈s为空。
5、完成后，所有结点已经Push到栈output中，且按照后序遍历的顺序存放，
直接全部Pop出来即是二叉树后序遍历结果。
*/
void PostOrderIter1(pnode ps)  //非递归后序遍历
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
对于任一节点P，
1）先将节点P入栈；
2）若P不存在左孩子和右孩子，或者P存在左孩子或右孩子，但左右孩子
已经被输出，则可以直接输出节点P，并将其出栈，将出栈节点P标记为上
一个输出的节点，再将此时的栈顶结点设为当前节点；
3）若不满足2）中的条件，则将P的右孩子和左孩子依次入栈，当前节点
重新置为栈顶结点，之后重复操作2）；
4）直到栈空，遍历结束。
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












int count_leaf(pnode ps)   //计算叶子节点个数
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

int count_node(pnode ps)   //计算总共的节点个数
{
    if(ps != NULL)
    {
        count_n++;
        count_node(ps->lchild);
        count_node(ps->rchild);
    }
    return count_n;
}

int count_depth(pnode ps)   //递归计算二叉树的深度
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







