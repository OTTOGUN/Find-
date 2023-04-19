#include<stdio.h>
#include<malloc.h>
#include <math.h>

#define MAXEDGE 100
#define MAXVERTEX 100
typedef int KeyType;
typedef char* OtherInfo;

//������������Sequential Search(˳�����)

typedef struct Edge{
    KeyType key;
    OtherInfo other;        //����������Ϣ
}SSTElemType;

typedef struct{
    SSTElemType* base;      //���������׵�ַ(��Ԫ�������÷��ڱ�)
    int length;             //��ǰ��(����ĳ���)
}SSTable;

//�������㷨1��˳�����
int Search_SS_Original(SSTable ST,KeyType key){  //ȱ�ݣ�ִ�������αȽϳ���
    for(int i = ST.length;i > 0;i--){
        if(key == ST.base[i].key)
            return i;
    }
}

//�������Ż�֮��
int Search_SS_Enhanced(SSTable ST,KeyType key){     //�Ľ��Ժ�ֻ��Ҫ�Ƚ�һ��
    ST.base[0].key = key;
    int i = ST.length;
    while(ST.base[i].key != key){
        i--;
    }
    return i;
}

//�������㷨2:Binary Search
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
            printf("û�ҵ�\n");
            return 0;
        }
    }
}

//�������㷨3:�ֿ����(Blocking Search)
#define MAXBLOCK 20
typedef struct{
    KeyType MaxKey;
    int start,end;
}IndexElemType;         //����������ؼ��֣����俪ʼ�Լ��������±�

typedef struct _IndexTable{
    IndexElemType index[MAXBLOCK];
    int length;
}IndexTable;            //��������(����)����ľ�����Ϣ

IndexTable INDEXTABLE;
int BlockSearch(KeyType* a,KeyType key){
    int left = 1;
    int right = INDEXTABLE.length;

    while(left <= right){
        int mid = (left + right) / 2;
        if(key < INDEXTABLE.index[mid].MaxKey){ //��������ֵС�� mid����Ҫ�ж��Ƿ���� mid - 1
            if(key > INDEXTABLE.index[mid - 1].MaxKey){
                for(int i = INDEXTABLE.index[mid - 1].start;i < INDEXTABLE.index[mid - 1].end;i++){
                    if(key == a[i])
                        printf("�ҵ�\n");
                        return i;
                }
                return 0;
            }
            right = mid - 1;
        }else if(key > INDEXTABLE.index[mid].MaxKey){
            if(key < INDEXTABLE.index[mid + 1].MaxKey){
                for(int i = INDEXTABLE.index[mid + 1].start;i < INDEXTABLE.index[mid + 1].end;i++){
                    if(key == a[i])
                        printf("�ҵ�\n");
                        return i;
                }
                return 0;
            }
            left = mid + 1;
        }
    }
    printf("û�и�Ԫ��\n");
    return 0;
}

//�������㷨4:����������(Binary Sort Tree)

//�� �����������Ľ���
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

//�� BST����
BSTree Search_BST(BSTree T,BSTKeyType key){     //�ݹ����
    if(T -> data.key == key){                   //������ֵ����洢��������ͬ���ؽ��ָ��
        return T;
    }else if(key > T -> data.key){
        return Search_BST(T -> rchild,key);  //������ֵ���ڽڵ����洢�����ݣ��������Ϊ���ӽڵ�
    }else if(key < T -> data.key){
        return Search_BST(T -> lchild,key);  //������ֵС�ڵ�ǰ�ڵ�洢�����ݣ���ڵ����Ϊ���ӽڵ�
    }
}

//�� BST����
void Insert_BST(BSTree* T,BSTKeyType key){      //�������Եݹ�ķ�ʽ�ҵ�����λ�ã������½ڵ����
    if(key > (*T) -> data.key){                 //��Ŀ�����ݴ��ڵ�ǰ�Ľڵ����ݣ����½ڵ�Ϊ���ӽڵ�
        Insert_BST(&(*T) -> rchild,key);
    }else if(key < (*T) -> data.key){           //��Ŀ������С�ڵ�ǰ�ڵ����ݣ����½ڵ�Ϊ���ӽڵ�
        Insert_BST(&(*T) -> lchild,key);
    }else if(*T = NULL){                        //˵����ǰ�Ѿ��������λ��
        *T = (BSTree)malloc(sizeof(BSTNode));   //�½��ڵ�
        (*T) -> data.key = key;                 //���ýڵ���������Ϊ��Ҫ��������ֵ
        (*T) -> lchild = NULL;                  //����/���ӽڵ�����Ϊ��
        (*T) -> rchild = NULL;
    }
}