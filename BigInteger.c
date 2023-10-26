#include "BigInteger.h"
struct BigInteger initialize(char *s)
{
    SBI x;
    x.length = strlen(s);
    x.L = NULL; struct Node *temp;
    for(int i=0; *(s+i)!='\0'; i++)
    {
        struct Node *t = (struct Node*)malloc(sizeof(struct Node));
        if(t==NULL)
        printf("Heap Memory Allocation Failed\n");
        else
        {
            t->data = (*(s+i))-48;
            t->next = NULL;
            if(x.L==NULL)
            x.L = t;
            else
            {
                temp = x.L;
                x.L = t;
                t->next = temp;
            }
        }
    }
    return x;
}



void display(struct BigInteger x)
{
    struct Node *itr = x.L;
    if(itr==NULL)
    return;
    while(itr!=NULL)
    {
        printf("%d ", itr->data);
        itr=itr->next;
    }
    printf("\n");
}

struct BigInteger reverse(struct BigInteger x)
{
    struct Node *p=NULL, *q=x.L, *temp=NULL;
    while(q!=NULL)
    {
        temp = q->next;
        q->next = p;
        p = q;
        q = temp;
    }
    x.L = p;
    return x;
}


struct BigInteger insert(struct BigInteger x, int n)
{
    struct Node *t = (struct Node*)malloc(sizeof(struct Node));
    if(t==NULL)
    printf("Memory Allocation Failed\n");
    else
    {
        t->data = n;
        t->next = NULL;
        if(x.L == NULL)
        x.L = t;
        else
        {
            struct Node *itr = x.L;
            while(itr->next!=NULL)
            {
                itr = itr->next;
            }
            itr->next = t;
        }
    }
    return x;
}


struct BigInteger add(struct BigInteger a, struct BigInteger b)
{
    int sum=0, carry=0;
    struct Node *itr1= a.L, *itr2= b.L;
    SBI c;
    c.L = NULL;
    while(itr1!=NULL && itr2!=NULL)
    {
        sum = itr1->data + itr2->data + carry;
        if(sum>9)
        carry = sum/10;
        else
        carry = 0;
        c = insert(c, sum%10);
        itr1 = itr1->next;
        itr2 = itr2->next;
    }
    while(itr1!=NULL)
    {
        sum = itr1->data + carry;
        if(sum>9)
        carry = sum/10;
        else
        carry = 0;
        c = insert(c, sum%10);
        itr1 = itr1->next;
    }
    while(itr2!=NULL)
    {
        sum = itr2->data + carry;
        if(sum>9)
        carry = sum/10;
        else
        carry = 0;
        c = insert(c, sum%10);
        itr2 = itr2->next;
    }
    if(itr1==NULL && itr2==NULL && carry!=0)
    {
        c = insert(c, carry);
        carry=0;
    }
    c = reverse(c);
    return c;
}

int length(struct BigInteger x)
{
    int count = 0; struct Node *p = x.L;
    if(x.L==NULL)
    return 0;
    while(p!=NULL)
    {
        count++;
        p=p->next;
    }
    return count;
}

int compare(struct BigInteger a, struct BigInteger b)
{
    a = reverse(a);
    b = reverse(b);
    struct Node *p = a.L, *q = b.L;
    int l1 = length(a);
    int l2 = length(b);
    if(l1>l2)
    {
        a = reverse(a);
        b = reverse(b);
        return 1;
    }
    else if(l1<l2)
    {
        a = reverse(a);
        b = reverse(b);
        return 0;
    }
    else
    {
        while(p!=NULL && q!=NULL)
        {
            if(p->data>q->data)
            {
                a = reverse(a);
                b = reverse(b);
                return 1;
            }
            else if(p->data<q->data)
            {
                a = reverse(a);
                b = reverse(b);
                return 0;
            }
            p=p->next;
            q=q->next;
        }
        a = reverse(a);
        b = reverse(b);
        return 1;
    }
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b)
{
    if(compare(a, b)==0)
    {
        SBI temp = a;
        a = b;
        b = temp;
    }
    int borrow = 0, new_digit;
    struct Node *p = a.L, *q = b.L;
    SBI c;
    c.L = NULL;
    while(q!=NULL)
    {
        new_digit = p->data - q->data - borrow;
        if (new_digit<0)
        {
            new_digit += 10;
            borrow = 1;
        }
        else
        borrow = 0;
        c = insert(c, new_digit);
        p = p->next;
        q = q->next;
    }
    while(p!=NULL)
    {
        new_digit = p->data - borrow;
        if (new_digit<0)
        {
            new_digit += 10;
            borrow = 1;
        }
        else
        borrow = 0;
        c = insert(c, new_digit);
        p = p->next;
    }
    c = reverse(c);
    struct Node *u = c.L;
    while(u->data==0 && u->next!=NULL) //To remove tailing pointers
    {
        u=u->next;
    }
    c.L=u;
    return c;
}

struct BigInteger insert_head(struct BigInteger x, int num)
{
    struct Node *t = (struct Node*)malloc(sizeof(struct Node));
    struct Node *temp;
    if(t==NULL)
    printf("Memory Allocation Failed\n");
    else
    {
        t->data = num;
        t->next = NULL;
        if(x.L==NULL)
        x.L = t;
        else
        {
            temp = x.L;
            x.L = t;
            t->next = temp;
        }
    }
    return x;
}

struct BigInteger mul(struct BigInteger a, struct BigInteger b)
{
    struct Node *p = a.L, *q = b.L;
    int l = b.length, carry=0, product=1, x;
    SBI* *r=(SBI**)malloc(sizeof(SBI*)*l); //To create a pointer r which points to an array of pointers where each pointer points to a structure
    int i;
    for(i=0; i<l; i++)
    {
        (*(r+i)) = (SBI*)malloc(sizeof(SBI));
    }
    for(i=0; i<l; i++)
    {
        (*(r+i))->L = NULL;
    }
    i=0;
    while(q!=NULL)
    {
        carry=0;
        while(p!=NULL)
        {
            product = (p->data*q->data)+carry;
            if(product>9)
            carry = product/10;
            else
            carry=0;
            **(r+i) = insert(**(r+i), product%10);
            p=p->next;
        }
        if(carry!=0)
        **(r+i) = insert(**(r+i), carry);
        p=a.L;
        q=q->next;
        x=i;
        while(x!=0)
        {
            **(r+i) = insert_head(**(r+i), 0);
            x--;
        }
        i++;
    }
    struct Node *t = (struct Node*)malloc(sizeof(struct Node));
    t->data = 0;
    t->next = NULL;
    SBI res;
    res.L = t;
    for(i=0; i<l; i++)
    {
        res = add(res, **(r+i));
        res = reverse(res);
    }
    res = reverse(res);
    struct Node *u = res.L;
    while(u->data==0 && u->next!=NULL)
    {
        u=u->next;
    }
    res.L=u;
    return res;
}

struct BigInteger div1(struct BigInteger a, struct BigInteger b)
{
    SBI c1, c2;
    struct Node *t1 = (struct Node*)malloc(sizeof(struct Node));
    t1->data = -1;
    t1->next = NULL;
    c1.L = t1;
    struct Node *t2 = (struct Node*)malloc(sizeof(struct Node));
    t2->data = 1;
    t2->next = NULL;
    c2.L = t2;
    SBI res;
    struct Node *t = (struct Node*)malloc(sizeof(struct Node));
    t->data = 0;
    t->next = NULL;
    res.L = t;
    res.length = 0;
    if(compare(a, b)==0)
    return res;
    int f=0, count=0;
    if(b.L->next==NULL && b.L->data==0)
    {
        printf("Indeterminate form\n");
        f=1;
        exit(1);
    }
    while(compare(a, res)==1 && f==0)
    {
        res = add(res, b);
        res = reverse(res);
        c1 = add(c1, c2);
        c1 = reverse(c1);
    }
    c1 = reverse(c1);
    struct Node *u = c1.L;
    while(u->data==0 && u->next!=NULL) //To remove tailing pointers
    {
        u=u->next;
    }
    c1.L=u;
    return c1;
}

struct BigInteger mod(struct BigInteger a, struct BigInteger b)
{
    SBI res;
    struct Node *t = (struct Node*)malloc(sizeof(struct Node));
    t->data = 0;
    t->next = NULL;
    res.L = t;
    res.length = 0;
    if(compare(a, b)==0)
    return a;
    int f=0, count=0;
    if(b.L->next==NULL && b.L->data==0)
    {
        printf("Indeterminate form\n");
        f=1;
        exit(1);
    }
    while(compare(a, res)==1 && f==0)
    {
        res = add(res, b);
        res = reverse(res);
    }
    res = sub(res, b);
    res = reverse(res);
    res = sub(a, res);
    struct Node *u = res.L;
    while(u->data==0 && u->next!=NULL) //To remove tailing pointers
    {
        u=u->next;
    }
    res.L=u;
    return res;
}