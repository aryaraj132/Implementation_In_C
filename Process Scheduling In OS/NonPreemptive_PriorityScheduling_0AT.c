#include<stdio.h>
#include <stdlib.h>
struct node{
    int ID,BT,priority,CT,WT,TAT;
    struct node *next;
};
void insert(struct node** root, int id, int bt, int prior){
    struct node *new = (struct node*)malloc(sizeof(struct node));
    struct node *ptr = *root;
    new->ID = id;
    new->BT = bt;
    new->priority = prior;
    new->next = NULL;
    new->CT = 0;
    new->WT = 0;
    new->TAT = 0;
    if (*root == NULL)
    {
        *root = new;
        return;
    }
    while (ptr->next!=NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = new;
    return;
}
void delete(struct node** root,int id){
    struct node *ptr = *root, *prev;
    if (ptr==NULL)
    {
        return;
    }
    if (ptr->ID == id)
    {
        *root = ptr->next;
        free(ptr);
        return;
    }
    while(ptr!=NULL && ptr->ID != id)
    {
        prev = ptr;
        ptr = ptr->next;
    }
    if(ptr==NULL){
        return;
    }
    prev->next = ptr->next;
    free(ptr);
}
void showList(struct node* head){
    printf("Process Priority BT CT TAT WT \n");
    while (head!=NULL)
    {
        printf("P%d. %d %d %d %d %d \n",head->ID,head->priority,head->BT,head->CT,head->TAT,head->WT);
        head=head->next;
    }
}
int LLength(struct node **root){
    int count = 0;
    struct node *ptr = *root;
    while (ptr!=NULL)
    {
        count++;
        ptr=ptr->next;
    }
    return count;
}
void update(struct node **root, int id, int ct, int wt, int tat){
    struct node *ptr = *root;
    if (ptr!=NULL && ptr->ID==id)
    {
        if (ct!=0)
        {
            ptr->CT=ct;
        }
        if (wt!=0)
        {
            ptr->WT=wt;
        }
        if (tat!=0)
        {
            ptr->TAT=tat;
        }
        return;
    }
    while (ptr!=NULL && ptr->ID!=id)
    {
        ptr=ptr->next;
    }
    if (ct!=0)
    {
        ptr->CT=ct;
    }
    if (wt!=0)
    {
        ptr->WT=wt;
    }
    if (tat!=0)
    {
        ptr->TAT=tat;
    }
    return;
}
float CalculateCT(struct node **root){
    struct node *ptr = *root,*prior;
    int ct = 0,i;
    int n = LLength(root);
    float avg,sum=0;
    struct node *duproot = NULL;
    while (ptr!=NULL)
    {
        insert(&duproot,ptr->ID,ptr->BT,ptr->priority);
        ptr=ptr->next;
    }
    for (i=0;i<n;i++)
    {
        ptr = duproot;
        prior = ptr;
    while (ptr->next!=NULL)
    {
        ptr=ptr->next;
        if(ptr->priority < prior->priority){
            prior = ptr;
        }        
    }
    ct+=prior->BT;
    sum+=ct;
    update(root,prior->ID,ct,0,0);
    delete(&duproot,prior->ID);
    }
    avg = sum/n;
    return avg;
}
float CalculateTAT(struct node **root){
    float avg,sum=0;
    int n = LLength(root);
    struct node *ptr = *root;
    if (ptr->CT==0)
    {
        CalculateCT(root);
    }
    while (ptr!=NULL)
    {
        ptr->TAT = ptr->CT;
        sum += ptr->TAT;
        ptr = ptr->next;
    }
    avg = sum/n;
    return avg;
}
float CalculateWT(struct node **root){
    float avg,sum=0;
    int n = LLength(root);
    struct node *ptr = *root;
    if (ptr->CT==0)
    {
        CalculateCT(root);
    }
    while (ptr!=NULL)
    {
        ptr->WT = (ptr->CT - ptr->BT);
        sum += ptr->WT;
        ptr = ptr->next;
    }
    avg = sum/n;
    return avg;
}
void main(){
    struct node *root = NULL;
    int option = 0,prior,bt,id;
    while (option!=7)
    {
        printf("1. Enter Process Details \n");
        printf("2. Delete Process \n");
        printf("3. Display Process \n");
        printf("4. Calculate Avg C.T. \n");
        printf("5. Calculate Avg T.A.T. \n");
        printf("6. Calculate Avg W.T. \n");
        printf("7. Exit. \n");
        scanf("%d",&option);
        switch (option)
        {
        case 1:
            printf("Enter Process Id \n");
            scanf("%d",&id);
            printf("Enter Process Priority \n");
            scanf("%d",&prior);
            printf("Enter Process B.T. \n");
            scanf("%d",&bt);
            insert(&root, id, bt, prior);
            break;
        case 2:
            printf("Enter Process Id \n");
            scanf("%d",&id);
            delete(&root,id);
            break;
        case 3:
            showList(root);
            break;
        case 4:
            printf("Average Completion Time is : %f \n",CalculateCT(&root));
            break;
        case 5:
            printf("Average Turn Around Time is : %f \n",CalculateTAT(&root));
            break;
        case 6:
            printf("Average Waiting Time is : %f \n",CalculateWT(&root));
            break;
        default:
            break;
        }
    }
}
