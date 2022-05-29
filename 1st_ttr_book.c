#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
   char name[100];
   char author[100];
   char publisher[100];
   struct node *next;
   struct node *prev;
};

void add(struct node *, struct node *);//79
void del(struct node *,struct node *);//122
void save(struct node *);//148
void call(struct node *, struct node *);//157
void sch(struct node *,struct node *,char *);//190
void prt(struct node *);//206
void enter();//212

int main(void)
{

   struct node *head = malloc(sizeof(struct node));
   struct node *tail = malloc(sizeof(struct node));
   FILE *fp;

   head -> next = tail;
   head -> prev = NULL;

   tail -> next = NULL;
   tail -> prev = head;

   char input[100];
   char info[100];

   call(head,tail);

   while(1){
      system("clear");
      printf("<도서관리 프로그램>\n1.도서 추가\t2.도서 삭제\n3.도서 검색\t4.도서 리스트 출력\n5.저장 및 종료\n\n메뉴를 선택하세요 : ");
      while(1){
         scanf("%s",input);
         if(input[0] <= '5' && input[0] >= '1')
            break;
         printf("다시 입력해주세요\n");
      }

      getchar();
      printf("\n");
      switch(input[0]){
         case '1':
            add(head, tail);
            enter();
            break;

         case '2':
            del(head, tail);
            enter();
            break;

         case '3':
            printf("검색하려는 책의 정보 입력 : ");
            gets(info);
            sch(head, tail, info);
            enter();
            break;

         case '4':
            prt(head);
            enter();
            break;

         case '5':
            save(head);
            printf("저장이 완료되었습니다. 종료합니다.\n");
            system("clear");
            return 0;
      }
   }
   return 0;
}

void add(struct node *head, struct node *tail){
   struct node *newNode = malloc(sizeof(struct node));
   printf("책 이름 : ");
   gets(newNode->name);
   printf("책 저자 : ");
   gets(newNode->author);
   printf("출판사 : ");
   gets(newNode->publisher);
   printf("\n");
   if(head==NULL)
      return;
   if(head->next == tail){
      newNode->next=head->next;
      newNode->prev=head;
      head->next=newNode;
      return;
   }
   else{
      struct node *curr=head->next;
      while(curr!= tail){
         if(strcmp(curr->name,newNode->name)>0){
            newNode->next=curr;
            newNode->prev=curr->prev;
            curr->prev->next=newNode;
            curr->prev=newNode;
            return;
         }
         if(curr->next==tail){
            newNode->next= tail;
            newNode->prev=curr;
            tail ->prev=newNode;
            curr->next=newNode;
            return;
         }
         curr = curr->next;
      }
   }
}

void del(struct node *head, struct node *tail){   
   int cnt=0;
   char info[100];
   printf("삭제할 책의 저자를 입력하세요 : ");
   gets(info);
   struct node *rmv = head -> next;
   while(rmv != tail){
      if(strcmp(info,rmv -> author) == 0){
         struct node *newnode = rmv;
         rmv -> prev -> next = rmv -> next;
         rmv -> next -> prev = rmv -> prev;
         free(rmv);
         rmv = newnode;
         cnt++;
      }
      rmv = rmv -> next;
   }
   printf("\n");
   if(cnt == 0)
      printf("삭제할 목록이 없습니다.\n");
}

void save(struct node *head){
   FILE *fp = fopen("book.txt","w");
   struct node *curr=head->next;
   while(curr -> next!=NULL){
      fprintf(fp, "%s/%s/%s\n", curr->name, curr->author, curr->publisher);
      curr=curr->next;
   }
}

void call(struct node *head,struct node *tail){
   FILE *fp = fopen("book.txt","r");
   char str[100];
   if(fp != NULL){
      while(!feof(fp)){ 
         struct node *newnode = malloc(sizeof(struct node));
         fgets(str, sizeof(str), fp);
         char *ptr = strtok(str,"/,\n");
         if(ptr == NULL)
            break;
         strcpy(newnode -> name,ptr);
         ptr = strtok(NULL,"/");
         if(ptr == NULL)
            break;
         strcpy(newnode -> author,ptr);
         ptr = strtok(NULL,"\n");
         strcpy(newnode -> publisher,ptr);
         if(head -> next == tail){
            newnode -> next = tail;
            newnode -> prev = head;
            tail -> prev = newnode;
            head -> next = newnode;
            continue;
         }
         newnode -> next = tail;
         newnode -> prev = tail -> prev;
         tail -> prev = newnode;
         newnode -> prev -> next = newnode;            
      }
      fclose(fp);
   }
}

void sch(struct node *head,struct node *tail,char *book){
   struct node *curr = head -> next;
   int cnt = 0;
   while(curr != tail){
      if((strcmp(book,curr->name) == 0 || strcmp(book,curr->author) == 0) || strcmp(book,curr->publisher) == 0){
         printf("\n******************************\n");
         printf("*       책이름 : %-12.12s*\n", curr->name);
         printf("*       저자 : %-14.14s*\n", curr->author);
         printf("*       출판사 : %-12.12s*\n", curr -> publisher);
         printf("******************************\n\n");
         cnt++;
      }
      curr = curr -> next;
   }
   if(cnt == 0)
      printf("도서 정보가 없습니다.\n");
   return;
}

void prt(struct node *head){
   struct node *curr=head->next;
   int cnt = 1;
   while(curr -> next !=NULL){
      printf("******************************\n");
      printf("*       책번호 : %-12.4d*\n",cnt);
      printf("*       책이름 : %-12.12s*\n", curr->name);
      printf("*       저  자 : %-12.12s*\n", curr->author);
      printf("*       출판사 : %-12.12s*\n", curr->publisher);
      printf("******************************\n\n");
      curr=curr->next;
      cnt++;
   }
}

void enter(){
   char temp[256];
   printf("엔터를 누르면 처음으로 돌아갑니다.\n");
   scanf("%[^\n]", temp);
   system("clear");
}
