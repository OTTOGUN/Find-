#include<stdio.h>
#include<malloc.h>
#include <math.h>

#define MAXEDGE 100
#define MAXVERTEX 100
typedef int KeyType;
typedef char* OtherInfo;

//》》》》》》Sequential Search(顺序查找)

typedef struct Edge{
    KeyType key;
    OtherInfo other;        //储存其他信息
}SSTElemType;

typedef struct{
    SSTElemType* base;      //存放数组的首地址(首元素用于置放哨兵)
    int length;             //当前表长(数组的长度)
}SSTable;

//》》》算法1：顺序查找
int Search_SS_Original(SSTable ST,KeyType key){  //缺陷：执行了两次比较程序
    for(int i = ST.length;i > 0;i--){
        if(key == ST.base[i].key)
            return i;
    }
}

//》》》优化之后
int Search_SS_Enhanced(SSTable ST,KeyType key){     //改进以后，只需要比较一次
    ST.base[0].key = key;
    int i = ST.length;
    while(ST.base[i].key != key){
        i--;
    }
    return i;
}

//》》》算法2:Binary Search
int Search_BS(SSTable ST,KeyType key){
    int left = 1;
    int right = ST.length;

    while(left <= right){
        int mid = (left + right) / 2;
        if(key = ST.base[mid].key){
            return mid;
        }else if(key < ST.base[mid].key){
            right = mid - 1;
        }else if(key > ST.base[mid].key){
            left = mid + 1;
        }else{
            printf("没找到\n");
            return 0;
        }
    }
}

//》》》算法3:分块查找(Blocking Search)
#define MAXBLOCK 20
typedef struct{
    KeyType MaxKey;
    int start,end;
}IndexElemType;         //表包含有最大关键字，区间开始以及结束的下标

typedef struct _IndexTable{
    IndexElemType index[MAXBLOCK];
    int length;
}IndexTable;            //索引表：表长(块数)，表的具体信息

IndexTable INDEXTABLE;
int BlockSearch(KeyType* a,KeyType key){
    int left = 1;
    int right = INDEXTABLE.length;

    while(left <= right){
        int mid = (left + right) / 2;
        if(key < INDEXTABLE.index[mid].MaxKey){ //若被查找值小于 mid，需要判断是否大于 mid - 1
            if(key > INDEXTABLE.index[mid - 1].MaxKey){
                for(int i = INDEXTABLE.index[mid - 1].start;i < INDEXTABLE.index[mid - 1].end;i++){
                    if(key == a[i])
                        printf("找到\n");
                        return i;
                }
                return 0;
            }
            right = mid - 1;
        }else if(key > INDEXTABLE.index[mid].MaxKey){
            if(key < INDEXTABLE.index[mid + 1].MaxKey){
                for(int i = INDEXTABLE.index[mid + 1].start;i < INDEXTABLE.index[mid + 1].end;i++){
                    if(key == a[i])
                        printf("找到\n");
                        return i;
                }
                return 0;
            }
            left = mid + 1;
        }
    }
    printf("没有该元素\n");
    return 0;
}

//》》》算法4:二叉排序树(Binary Sort Tree)

//Ⅰ 二叉排序树的建立
#define ENDFALG 0
#define OK 1
typedef int BSTKeyType;
typedef char* BSTOtherInfo;
typedef int Status;

typedef struct _BSTElemType{
    BSTKeyType key;
    BSTOtherInfo other;
}BSTElemType;

typedef struct _BSTNode{
    BSTElemType data;
    struct _BSTNode* lchild,*rchild;
}BSTNode,*BSTree;

Status CreatBSTree(BSTree* T){
    BSTKeyType key;
    scanf("%d",&key);
    if(0 == key){
        *T = NULL;
    }else{
        if(!(*T = (BSTree)malloc(sizeof(BSTNode)))){
            exit(OVERFLOW);
        }else{
            (*T) -> data.key = key;
            CreatBSTree(&(*T) -> lchild);
            CreatBSTree(&(*T) -> lchild);
        }
    }
    return OK;
}

//Ⅱ BST查找
BSTree Search_BST(BSTree T,BSTKeyType key){     //递归查找
    if(T -> data.key == key){                   //若被查值与结点存储的数据相同返回结点指针
        return T;
    }else if(key > T -> data.key){
        return Search_BST(T -> rchild,key);  //若被查值大于节点所存储的数据，则结点更换为右子节点
    }else if(key < T -> data.key){
        return Search_BST(T -> lchild,key);  //若被查值小于当前节点存储的数据，则节点更换为左子节点
    }
}

//Ⅲ BST插入
void Insert_BST(BSTree* T,BSTKeyType key){      //依旧是以递归的方式找到合适位置，创建新节点插入
    if(key > (*T) -> data.key){                 //若目标数据大于当前的节点数据，跟新节点为右子节点
        Insert_BST(&(*T) -> rchild,key);
    }else if(key < (*T) -> data.key){           //若目标数据小于当前节点数据，跟新节点为左子节点
        Insert_BST(&(*T) -> lchild,key);
    }else if(*T = NULL){                        //说明当前已经到达合适位置
        *T = (BSTree)malloc(sizeof(BSTNode));   //新建节点
        (*T) -> data.key = key;                 //将该节点数据设置为需要被插入数值
        (*T) -> lchild = NULL;                  //将左/右子节点设置为空
        (*T) -> rchild = NULL;
    }
}