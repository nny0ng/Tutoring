#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct user{
	char name[10];
	int age;
	char phoneNumber[20];
	struct user *next;
	struct user *prev;
}User;

typedef struct list{
	User *head;
	User *tail;
	int count;
}UserList;

int menu();
void AddUser(UserList *list);
void FindUser(UserList *list);
void DeleteUser(UserList *list);
void ShowUser(UserList *list);
void InitList(UserList *list);
User *MakeNode(char *name, int age, char *phoneNumber);
void AddListNode(UserList *list, User *node);
User *FindNode(UserList *list, char *name); //채워보기!! 찾으면 노드리턴,실패시 NULL리턴
int DeleteNode(UserList *list, char *name); //채워보기!! 삭제 성공시 1리턴, 실패시 0 리턴

int main()
{
	UserList list;
	int choice;

	InitList(&list);
	system("clear");	
	while(1){
		choice = menu();
		switch(choice){
			case 1 : 
				AddUser(&list);
				break;

			case 2 : 
				FindUser(&list);
				break;

			case 3 : 
				DeleteUser(&list);
				break;

			case 4 : 
				ShowUser(&list);
				break;

			case 5 :
				return 0;
		}
	}
}

int menu(){
	int menu;

	printf("====Double LinkedList Test====\n");
	printf("1. Add Node\n");
	printf("2. Find Node\n");
	printf("3. Delete Node\n");
	printf("4. Show List\n");
	printf("5. End Program\n");
	printf("Input Number => ");
	scanf("%d", &menu);
	while(getchar() != '\n');
	return menu;
}

void AddUser(UserList *list){
	User *node;

	node = (User *)malloc(sizeof(User));
	printf("====Add User====\n");
	printf("1. Input name => ");
	scanf("%s", node->name);
	printf("2. Input age => ");
	scanf("%d", &(node->age));
	printf("3. Input phoneNumber => ");
	scanf("%s", node->phoneNumber);
	while(getchar() != '\n');

	node = MakeNode(node->name, node->age, node->phoneNumber);
	AddListNode(list, node);
	printf("\n\n");
}

void FindUser(UserList *list){
	User *node;
	char name[10];

	memset(name, 0, 10); //name배열을 10크기만큼 0으로 초기화!
	printf("====Find User====\n");
	printf("1. Input Find Name => ");
	scanf("%s", name);

	node = FindNode(list, name);
	if(node == NULL){
		printf("Not exist in list!!\n");
	}
	else{
		printf("%s is exist in list!!\n", node->name);
	}
	printf("\n\n");
}

void DeleteUser(UserList *list){
	char name[10];
	int result;

	memset(name, 0, 10);
	printf("====Delete User====\n");
	printf("1. Input Delete name => ");
	scanf("%s", name);

	result = DeleteNode(list, name);
	if(result == 1){
		printf("Delete %s Success!!\n", name);
	}
	else if(result == 0){
		printf("Delete %s Fail!!\n", name);
	}
	printf("\n\n");
}

void ShowUser(UserList *list){
	User *node;
	int i = 1;

	node = list->head->next;

	printf("====Show User====\n\n");
	while(node->next != NULL){
		printf("====%d====\n", i);
		printf("Id = %s\n", node->name);
		printf("Age = %d\n", node->age);
		printf("Password = %s\n", node->phoneNumber);
		i++;
		node = node->next;
	}
	printf("\n\n");
}

void InitList(UserList *list){
	list->head = (User *)malloc(sizeof(User));
	list->tail = (User *)malloc(sizeof(User));
	list->head->next = list->tail;
	list->tail->prev = list->head;
	list->head->prev = NULL;
	list->tail->next = NULL;
	list->count = 0;
}

User *MakeNode(char *name, int age, char *phoneNumber){
	User *newNode;

	newNode = (User *)malloc(sizeof(User));

	strcpy(newNode->name, name);
	newNode->age = age;
	strcpy(newNode->phoneNumber, phoneNumber);
	newNode->next = NULL;
	newNode->prev = NULL;

	return newNode;
}

void AddListNode(UserList *list, User *node){

	if(list->head->next == list->tail){
		list->head->next = node;
		node->next = list->tail;
		node->prev = list->head;
		list->tail->prev = node;
	}
	else{
		list->tail->prev->next = node;
		node->next = list->tail;
		node->prev = list->tail->prev;
		list->tail->prev = node;
	}
	list->count++;
}

User *FindNode(UserList *list, char *name){
	User *node;
	node=list->head->next;
	while(node->next!=NULL){
		if(strcmp(node->name, name)==0)
			return node;
		else
			node=node->next;
	}
	return NULL;
}


int DeleteNode(UserList *list, char *name){
	User *node;
	node=list->head->next;
	while(node->next!=NULL){
		if(strcmp(node->name, name)==0){
			node->prev->next=node->next;
			node->next->prev=node->prev;
			node->next=NULL;
			node->prev=NULL;
			return 1;
		}
		else
			node=node->next;
	}
	return 0;
}

	//채워보기!!
	//삭제 성공시 1리턴, 삭제 실패시 0리턴
