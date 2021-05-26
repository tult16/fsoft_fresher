/*******************************************************************************
 * Assignment 3 : Chuong trinh quan ly hoc vien su dung danh sach lien ket don
   Author: LE TUAN TU
   Account: TuLT16
 ******************************************************************************/
 
 
/*******************************************************************************
 * Include
 ******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "Option.h"

 
/*******************************************************************************
 * CODE
 ******************************************************************************/

/*Declare struct hocvien*/
typedef struct HOCVIEN {
    int MSHV;
    char Hoten[30];
    char account[20];
    float dtb;
}HV;
HV HocVien[13]={{1,"TU","TuLT16",8.8},{2,"TU","TuNN15",10},{3,"QUAN","QuanPH7",9.4},{4,"HOANG","HoangTV26",8.8},\
               {5,"HUNG","HungDH9",9.2},{6,"HUY","HuyNV28",9.3},{7,"TAI","TaiNV18",8.6},{8,"THUAN","ThuanND22",10},\
               {9,"TUAN","TuanVV8",7.5},{10,"HOA","HoaTV8",8.3},{11,"CONG","CongPD4",8.7},{12,"HIEU","HieuVD8",9.1},\
               {13,"CONG","CongNH8",8.4}};

/*Declare struct NODE*/
typedef struct tagNODE {
    HV Data;
    struct tagNODE* Next;
}NODE;

/*Declare struct LISTHV*/
typedef struct tagLIST {
    NODE* Head;
    NODE* Tail;
}LISTHV;

/*Init NODE*/
NODE* InitNode()
{
    NODE* x = (NODE*)malloc(sizeof(NODE));
    if(x == NULL)
    {
        printf("\n Bo nho khong du ");
        return 0;
    }
    x->Next = NULL;
    return x;
}

/*Init linked list LISTHV*/
void InitList(LISTHV* x)
{
    x->Head = NULL;
    x->Tail = NULL;
}

/*Enter Infomation Member*/
void EnterInforHV(NODE* x)
{
    char tg[2],ac[20];
    int id;
    float gpa;
    printf("\nNhap ma Sinh vien(ID): ");
    scanf("%d", &id);
    x->Data.MSHV = id;
    fflush(stdin);
    printf("Nhap ten Sinh Vien: ");
    gets(tg);
    strcpy(x->Data.Hoten,tg);
    fflush(stdin);
    printf("Nhap account sinh vien: ");
    gets(ac);
    strcpy(x->Data.account,ac);
    do
    {
        printf("Nhap Diem Trung Binh: ");
        scanf("%f", &gpa);
    }while(gpa < 0 || gpa > 10);
    x->Data.dtb = gpa;
    fflush(stdin);
    x->Next = NULL;
}

/*Print Member*/
void PrintHV(NODE* p)
{
    printf("\n\t%d",p->Data.MSHV);
    printf("\t%s",p->Data.Hoten);
    printf("\t\t%s",p->Data.account);
    printf("\t\t\t\t%.2f\n\n\n", p->Data.dtb);
}

/*Print List Member*/
void PrinList(LISTHV x)
{
    NODE *p;
    p = x.Head;
    while(p != NULL)
    {
        PrintHV(p);
        p = p->Next;
    }
}

/*Add NODE Tail*/
void AddTail(LISTHV* x, NODE* t)
{
    if(x->Head == NULL)
    {
        x->Head = t;
        x->Tail=x->Head;
    }
   else
   {
       x->Tail->Next = t;
       x->Tail = t;
   }
}

/*Add NODE Head*/
void AddHead(LISTHV* x, NODE* t)
{	if(x->Head == NULL)
    {
        x->Head = t;
        x->Tail  = x->Head;
    }
   else
   {
   		t->Next=x->Head;
   		x->Head=t;
   }
}

/*Add member Tail, if want to add member Head replace function AddTail(x,a) by function AddHead(x,a);*/
int EnterHV(LISTHV* x)
{
    NODE* a = InitNode();
    EnterInforHV(a);
    AddTail(x,a);
	return 0;
}

/*Delete member by ID*/
int DelHV(LISTHV *x , int n)
{
    NODE *p = x->Head,*q;
    q=NULL;
    while (p!=NULL)
    {
        if (p->Data.MSHV==n)
            break;
        q=p;
        p=p->Next;
    }
    if (p==NULL)
        return 0; /* No member*/
    if (q!=NULL)
    {
        x->Tail=q;
        q->Next=p->Next;
        free(p);
    }
    else
    {
        x->Head=p->Next;
        if(x->Head==NULL)
            x->Tail=NULL;
    }
    return 1;
}

/*Function Sort up GPA*/
void SortGPAup(LISTHV x)
{
    NODE *current = x.Head, *index = NULL, *test = NULL;
    float temp_mark;
    int temp_MSSV;
    char temp_name[10], temp_account[10];
    if(x.Head == NULL) {
            return;
        }
        else {
            while(current != NULL) {
                //Node index will point to node next to current
                index = current->Next;
                while(index != NULL) {
                    //If current node's data is greater than index's node data, swap the data between them
                    if(current->Data.dtb > index->Data.dtb) {
                        temp_mark = current->Data.dtb;
                        current->Data.dtb = index->Data.dtb;
                        index->Data.dtb = temp_mark;
                    //swap MSSV
                        temp_MSSV = current->Data.MSHV;
                        current->Data.MSHV = index->Data.MSHV;
                        index->Data.MSHV = temp_MSSV;
                    //swap NAME
                        strcpy(temp_name,current->Data.Hoten);
                        strcpy(current->Data.Hoten, index->Data.Hoten);
                        strcpy(index->Data.Hoten,temp_name);
                    //swap account
                        strcpy(temp_account,current->Data.account);
                        strcpy(current->Data.account, index->Data.account);
                        strcpy(index->Data.account,temp_name);
                    }
                    index = index->Next;
                }
                current = current->Next;
            }
        }
    }


/*Function Free Memory*/
void FreeMemory(LISTHV *x)
{
    NODE *p = x->Head;
    NODE *a;
   while( p->Next != NULL)
    {
        a = p;
        p = p->Next;
        free(a);
    }
}

/*Main function*/
int main()
{
	int MSHV;
    LISTHV x;
	int key;
	InitList(&x);
 do
    {
        Option();
        scanf("%d",&key);
        switch(key)
        {
            case 1:
                {
                    int n,i;
                    printf("\nNhap so luong Hoc vien them vao : ");
                    scanf("%d",&n);
                    for(i = 1; i <= n ;i++)
                    {
                        printf("\nNhap Hoc vien thu: %d \n",i);
                        EnterHV(&x);
                    }
                    break;
                }
            case 2:
                {
                	printf("Ma Hoc vien\tTen Hoc vien\t\tAccount Hoc Vien\t\tDiem Trung Binh\n");
                    PrinList(x);
                    break;
                }
            case 3:
                {
                    fflush(stdin);
                    printf("\nNhap Ma Sinh Vien Xoa:");
                    scanf("%d",&MSHV);
                    fflush(stdin);
                    DelHV(&x ,MSHV);
                    break;
                }
            case 4:
                 {
                    SortGPAup(x);
                    printf("Ma Hoc vien\tTen Hoc vien\t\tAccount Hoc Vien\t\tDiem Trung Binh\n\n\n");
                    PrinList(x);
                    break;
                }
            case 0:
                {
                    break;
                }
            default: printf("\nBan chon sai vui long chon lai!");
        }
    }while(key != 0);
FreeMemory(&x);
 
return 0;
}



