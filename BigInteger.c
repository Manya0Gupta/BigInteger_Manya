//Manya Gupta
//13 oct 2023
#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

//for positives:sign is 0 and for negatives:sign is 1
void insert(struct node **head, int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    if (!temp)
    {
        return;
    }
    temp->data = data;
    temp->next = NULL;
    if (!*head)
    {
        *head = temp;
        return;
    }
    temp->next = *head;
    *head=temp;
    return;
}

int length(struct node* head){
    int count=0;
    while(head){
        count++;
        head=head->next;
    }
    //printf("\nlength:%d\n",count);
    return count;
}

struct BigInteger initialize(char *str)
{
    struct BigInteger n1;
    n1.head = NULL;
    int i = 0;
    if(str[0]=='-'){
        i=1;
    }
    n1.sign=i;
    while (str[i] != '\0')
    {
        insert(&(n1.head), str[i]-'0');
        i++;
    }
    int l=length(n1.head);
    n1.length=l;
    return n1;
}

void print(struct node*head){
    if(head==NULL){
        return;
    }
    print(head->next);
    printf("%d",head->data);
}

void display(struct BigInteger n){
    if(n.sign==1){
        printf("-");
    }
    print(n.head);
}

struct node* newnode(int data){
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    if(!temp){
        return NULL;
    }
    temp->data=data;
    temp->next=NULL;
    return temp;
}

void delete(struct node**head){
    struct node*itr=*head;
    if(!itr){
        return;
    }
    if(itr->next==NULL){
        return;
    }
    while(itr->next->next!=NULL){
        itr=itr->next;
    }
    free(itr->next);
    itr->next=NULL;
}

void removeZero(struct BigInteger n){
    struct node*temp;
    int l=n.length;
    while(l){
        temp=n.head;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        if(temp->data==0){
            delete(&n.head);
            l--;
        }
        else{
            break;
        }
    }
    n.length=l;
}

void compare(struct node **great,struct node** less,int *leng,int*lenl,int*sigg,int *sigl){
    struct node*g,*l,*high=*great,*low=*less;
    int signg,signl,lengthg,lengthl;
    g=*great;
    lengthg=*leng;
    signg=*sigg;
    l=*less;
    lengthl=*lenl;
    signl=*sigl;
    if(*leng>*lenl){
        return;
    }
    else if(*leng<*lenl){
        struct node*temp=*great;
        int le=*leng,sign=*sigg;
        *great=*less;
        *leng=*lenl;
        *sigg=*sigl;
        *less=temp;
        *lenl=le;
        *sigl=sign;
        return;
    }
    else{
        int len=*leng;
        while(len){
            if(high->data>low->data){
                g=*great;
                lengthg=*leng;
                signg=*sigg;
                l=*less;
                lengthl=*lenl;
                signl=*sigl;
            }
            else if(high->data<low->data){
                l=*great;
                lengthl=*leng;
                signl=*sigg;
                g=*less;
                lengthg=*lenl;
                signg=*sigl;
            }
            len--;
            high=high->next;
            low=low->next;
        }
        *great=g;
        *leng=lengthg;
        *sigg=signg;
        *less=l;
        *lenl=lengthl;
        *sigl=signl;
    }
}

int check(struct node *great,struct node *less,int leng,int lenl,int sigg,int sigl){
    struct node*g,*l,*high=great,*low=less;
    int signg,signl,lengthg,lengthl,f=2;
    g=great;
    lengthg=leng;
    signg=sigg;
    l=less;
    lengthl=lenl;
    signl=sigl;
    if(leng>lenl){
        return 1;
    }
    else if(leng<lenl){
        return 0;
    }
    else{
        int len=leng;
        while(len){
            if(high->data>low->data){
                f=1;
            }
            else if(high->data<low->data){
                f=0;
            }
            len--;
            high=high->next;
            low=low->next;
        }
        return f;
    }
    return f;
}

struct BigInteger add(struct BigInteger p1, struct BigInteger p2){
    struct BigInteger result;
    if(!p1.head||!p2.head){
        result.head=NULL;
        return result;
    }
    if((p1.sign==1&&p2.sign==0)||(p1.sign==0&&p2.sign==1)){
        int f=check(p1.head,p2.head,p1.length,p2.length,p1.sign,p2.sign);
        if(f==2){
            result.head=newnode(0);
            result.sign=0;
            result.length=1;
            return result;
        }
        else if(f==1){
            p2.sign=p1.sign;
        }
        else{
            p1.sign=p2.sign;
        }
        result=sub(p1,p2);
        if(f==1){
            result.sign=p1.sign;
        }
        else{
            result.sign=p2.sign;
        }
        return result;
    }
    struct node*res=NULL,*itr=NULL,*n1=p1.head,*n2=p2.head;
    int carry=0,sum=0;
    while(n1&&n2){
        sum=n1->data+n2->data+carry;
        if(sum>9){
            sum-=10;
            carry=1;
        }
        else{
            carry=0;
        }
        if(res==NULL){
            res=newnode(sum);
            itr=res;
        }
        else{
            itr->next=newnode(sum);
            itr=itr->next;
        }
        n1=n1->next;
        n2=n2->next;
    }
    while(n1){
        if(carry||!carry){
            itr->next=newnode(n1->data+carry);
        }
        carry=0;
        itr=itr->next;
        n1=n1->next;
    }
    while(n2){
        if(carry||!carry){
            itr->next=newnode(n2->data+carry);
        }
        carry=0;
        itr=itr->next;
        n2=n2->next;
    }
    if(carry){
        itr->next=newnode(carry);
        itr=itr->next;
    }
    result.head=res;
    if((p1.sign==1&&p2.sign==1)||(p1.sign==0&&p2.sign==0)){
        result.sign=p1.sign;
    }
    removeZero(result);
    int l=length(result.head);
    result.length=l;
    return result;
}

struct BigInteger sub(struct BigInteger p1, struct BigInteger p2){
    struct BigInteger result;
    if((p1.sign==1&&p2.sign==0)||(p1.sign==0&&p2.sign==1)){
        if(p2.sign==0){
            p2.sign=1;
        }
        else{
            p2.sign=0;
        }
        result=add(p1,p2);
        int l=length(result.head);
        result.length=l;
        if(p2.sign==0){
            p2.sign=1;
        }
        else{
            p2.sign=0;
        }
        return result;
    }
    struct BigInteger great,less;
    great=p1;
    less=p2;
    struct node*res=NULL,*n1,*n2,*itr;
     int borrow=0,diff=0;
    compare(&great.head,&less.head,&great.length,&less.length,&great.sign,&less.sign);
    n1=great.head;
    n2=less.head;
    res=NULL;
    while(n2&&n1){
        if((n1->data)<(n2->data)){
            borrow=10;
            n1->next->data-=1;
        }
        else{
            borrow=0;
        }
        diff=(n1->data+borrow-(n2->data));
        if(!res){
            res=newnode(diff);
            itr=res;
        }
        else{
            itr->next=newnode(diff);
            itr=itr->next;
        }

        n1=n1->next;
        n2=n2->next;
    }
    while(n1){
  
        if(n1->data<0){
            n1->data+=10;
            n1->next->data-=1;
        }
        itr->next=newnode(n1->data);
        itr=itr->next;
        n1=n1->next;
    }
    result.head=res;
    int f=check(p1.head,p2.head,p1.length,p2.length,p1.sign,p2.sign);
    if(f==1){
        result.sign=p1.sign;
    }
    else{
        if(p2.sign==1){
            result.sign=0;
        }
        else{
            result.sign=1;
        }
    }
    if(f==2){
        result.sign=0;
    }
    removeZero(result);
    result.length=length(result.head);
    return result;
    
}
struct BigInteger mul(struct BigInteger p1, struct BigInteger p2){
    struct BigInteger result,t;
    if(!p1.head||!p2.head){
        return result;
    }
    struct node*res=NULL,*itr=NULL,*tempn1=p1.head,*n1=p1.head,*n2=p2.head;
    int l1,l2,i,zeroes=0,len;
    l1=p1.length;
    l2=p2.length;
    len=l2+l1;
    for(i=0;i<len;i++){
        if(!res){
            res=newnode(0);
            itr=res;
        }
        else{
            itr->next=newnode(0);
            itr=itr->next;
        }
    }
    result.head=res;
    while(n2!=NULL){
        struct node*temp=NULL,*tem=NULL;
        n1=tempn1;
        int product=1,carry=0;
        while(n1!=NULL){
            product=((n1->data)*(n2->data)+carry);
            carry=product/10;
            if(product>=10){
                product=product%10;
            }
            if(!temp){
                temp=newnode(product);
                tem=temp;
            }
            else{
                tem->next=newnode(product);
                tem=tem->next;
            }
            n1=n1->next;
        }
        for(i=0;i<zeroes;i++){
            insert(&temp,0);
        }
        if(carry){
            tem=temp;
            while(tem->next!=NULL){
                tem=tem->next;
            }
            tem->next=newnode(carry);
        }
        result.head=res;
        t.head=temp;
        result=add(result,t);
        res=result.head;
        zeroes++;
        n2=n2->next;
    }
    result.head=res;
    if((p1.sign==1&&p2.sign==1)||(p1.sign==0&&p2.sign==0)){
        result.sign=0;
    }
    else{
        result.sign=1;
    }
    removeZero(result);
    if(result.head->data==0&&result.head->next==NULL){
        result.length=1;
        result.sign=0;
    }
    return result;

}
struct BigInteger div1(struct BigInteger p1, struct BigInteger p2){
    struct BigInteger result;
    if(!p1.head||!p2.head){
        return result;
    }
    if(p2.head->data==0&&p2.head->next==NULL){
        return result;
    }
    if((p1.sign==1&&p2.sign==0)||(p1.sign==0&&p2.sign==1)){
        result.sign=1;
    }
    else{
        result.sign=0;
    }
    p1.sign=0;
    p2.sign=0;
    struct BigInteger rem, quo, one;
    rem=p1;
    one.head=newnode(1);
    one.length=length(one.head);
    one.sign=0;
    quo.head=newnode(0);
    quo.length=length(quo.head);
    quo.sign=0;
    int f;
    f=check(rem.head,p2.head,rem.length,p2.length,rem.sign,p2.sign);
    while(f){
        rem=sub(rem,p2);
        quo=add(quo,one);
        f=check(rem.head,p2.head,rem.length,p2.length,rem.sign,p2.sign);
    }
    result.head=quo.head;
    result.length=length(result.head);
    if(result.head->data==0&&result.head->next==NULL){
        result.sign=0;
    }
    return result;
}

struct BigInteger mod(struct BigInteger p1, struct BigInteger p2){
    struct BigInteger result,n1,n2;
    n1=p1;
    n2=p2;
    if(!p1.head||!p2.head){
        return result;
    }
    if(p2.head->data==0&&p2.head->next==NULL){
        return result;
    }
    result.sign=p1.sign;
    p1.sign=0;
    p2.sign=0;
    struct BigInteger rem, quo, one;
    rem=p1;
    one.head=newnode(1);
    one.length=length(one.head);
    one.sign=0;
    quo.head=newnode(0);
    quo.length=length(quo.head);
    quo.sign=0;
    int f;
    f=check(rem.head,p2.head,rem.length,p2.length,rem.sign,p2.sign);
    while(f){
        rem=sub(rem,p2);
        quo=add(quo,one);
        f=check(rem.head,p2.head,rem.length,p2.length,rem.sign,p2.sign);
    }
    result.head=rem.head;
    result.length=length(result.head);
    if(result.head->data==0&&result.head->next==NULL){
        result.sign=0;
    }
    removeZero(result);
    return result;
}