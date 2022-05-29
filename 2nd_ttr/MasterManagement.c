#include "header.h"

void ShowUsers(UserTree *tree){
	char temp[256];
	User *node;
	node=tree->root;
	printf("\n*************************************\n");
	printf("**            Show Users           **\n");
	printf("*************************************\n");
	printf("%-15s %-15s %-15s %-15s %s\n", "Type", "Id", "Password", "Name", "Email");
	Preorder(node);
	printf("<< Press any key to go previous screen >>\n");
	scanf("%[^\n]", temp);
	system("clear");
}

void AddNewUser(UserTree *tree){
	FILE *fp;
	char temp[256];
	User *node;
	node=(User *)malloc(sizeof(User));
	printf("\n*************************************\n");
	printf("**           Add New User          **\n");
	printf("*************************************\n");
	printf("Type (1:Master, 2:General User) >> ");
	scanf("%d", &node->type);
	printf("ID >> ");
	scanf("%s", node->id);
	printf("Password >> ");
	scanf("%s", node->password);
	printf("Name >> ");
	scanf("%s", node->name);
	printf("Email >> ");
	scanf("%s", node->email);
	node=MakeNode(node->type, node->name, node->password, node->name, node->email);
	fp=fopen("user.txt", "r+");
	int idx=tree->treeCount;
	fseek(fp, sizeof(User)*idx, SEEK_SET);
	fwrite(node, sizeof(User), 1, fp);
	fclose(fp);
	AddTree(tree, node);
	getchar();
	printf("New Member is added!\n");
	printf("<< Press any key to go previous screen >>\n");
	scanf("%[^\n]", temp);
	system("clear");
}

void EditUser(UserTree *tree){
	char temp[256];
	User *node;
	node=(User *)malloc(sizeof(User));
	User tmp;
	FILE *fp;
	int i;
	printf("\n*************************************\n");
	printf("**            Edit User            **\n");
	printf("*************************************\n");
	printf("ID >> ");
	scanf("%s", node->id);
	node=FindNode(tree, node->id);
	if(node!=NULL){
		printf("Edit %s's information!\n", node->id);
		printf("Type >> ");
		scanf("%d", &node->type);
		printf("Password >> ");
		scanf("%s", node->password);
		printf("Name >> ");
		scanf("%s", node->name);
		printf("Email >> ");
		scanf("%s", node->email);
		printf("%s's information is edited!!\n", node->id);
		fp=fopen("user.txt", "r+");
		for(i=0;i<tree->treeCount;i++){
			memset(&tmp, 0, sizeof(User));
			fread(&tmp, sizeof(User), 1, fp);
			if(!strcmp(tmp.id, node->id))
				break;
		}
		fseek(fp, sizeof(User)*i, SEEK_SET);
		fwrite(node, sizeof(User), 1, fp);
		fclose(fp);

		getchar();
		printf("<< Press any key to go previous screen >>\n");
		scanf("%[^\n]", temp);
		system("clear");
	}
	else{
		printf("wrong ID\n << Press any key to go previous screen >>\n");
		scanf("%[^\n]", temp);
		system("clear");
	}
}

void DeleteUser(UserTree *tree){
	char temp[256];
	char answer[20];
	FILE *fp;
	int i, idx;
	User tmp;
	User *node;
	node=(User *)malloc(sizeof(User));
	printf("\n*************************************\n");
	printf("**           Delete User           **\n");
	printf("*************************************\n");
	printf("ID >> ");
	scanf("%s", node->id);
	node=FindNode(tree, node->id);
	if(node!=0){
		printf("Are you sure want to delete your account? (yes/no) >> ");
		scanf("%s", answer);
		if((strcmp("yes", answer))==0){
			fp=fopen("user.txt", "r+");
			DeleteNode(tree, node->id);
			tree->treeCount--;
			for(i=0;i<(tree->treeCount+1);i++){
				memset(&tmp, 0, sizeof(User));
				fread(&tmp, sizeof(User), 1, fp);
				if(!strcmp(tmp.id, node->id))
					break;
			}
			idx=i;
			memset(&tmp, 0, sizeof(User));
			fseek(fp, sizeof(User)*idx, SEEK_SET);
			for(i=idx;i<(tree->treeCount);i++){
				fwrite(&tmp, sizeof(User), 1, fp);
				fread(&tmp, sizeof(User), 1, fp);
				fseek(fp, sizeof(User)*i, SEEK_SET);
				fwrite(&tmp, sizeof(User), 1, fp);
				memset(&tmp, 0, sizeof(User));
			}
			int t_C=tree->treeCount;
			fseek(fp, sizeof(User)*t_C, SEEK_SET);
			fwrite(&tmp, sizeof(User), 1, fp);
			fclose(fp);
			getchar();
			printf("%s's account is deleted!!\n", node->id);
			printf("<< Press any key to go previous screen >>\n");
		}
	}
	else{
		getchar();
		printf("wrong ID!!!\n<< Press any key to go previous screen >>\n");
		scanf("%[^\n]", temp);
		system("clear");
	}
}


void ShowPost(FileList *flist){
	char temp[256];
	char Id_num[20]="0";
	char see[20];
	int exist;
	int idx=1;
	File *node=(File *)malloc(sizeof(File));
	node=flist->head->next;

	printf("\n*************************************\n");
	printf("**          Show All Post          **\n");
	printf("*************************************\n");
	printf("%-10s %-10s %-10s %-10s %-15s %-10s\n", "Idx", "Id", "Title", "Writer", "Content", "Date");
	while(node->next!=NULL){
		if(strlen(node->content)>=14){
			strncat(see,node->content,12);
			strcat(see, "...");
			printf("%-10d %-10s %-10s %-10s %-15s %-10s\n", idx, node->id, node->title, node->writer, see, node->date);
		}
		else
			printf("%-10d %-10s %-10s %-10s %-15s %-10s\n", idx, node->id, node->title, node->writer, node->content, node->date);
		node=node->next;
		idx++;
	}
	printf("Choose Id = ");
	scanf("%s", Id_num);
	getchar();
	File *newnode=(File *)malloc(sizeof(File));
	newnode=FindFileNode(flist, Id_num);
	if(newnode==NULL)
		printf("non-exist\n");
	else{
		printf("\n*************************************\n");
		printf("**            Show Post            **\n");
		printf("*************************************\n");
		printf("id = %s\n", newnode->id);
		printf("title = %s\n", newnode->title);
		printf("writer = %s\n", newnode->writer);
		printf("content = %s\n", newnode->content);
		printf("date = %s\n", newnode->date);
	}

	printf("<< Press any key to go previous screen >>\n");
	scanf("%[^\n]", temp);
	system("clear");
	printf("\n\n");
}

void AddPost(FileList *flist){
	FILE *fp;
	char temp[256];
	File *node;

	node=(File *)malloc(sizeof(File));
	printf("\n*************************************\n");
	printf("**            Add Post             **\n");
	printf("*************************************\n");
	printf("ID >> ");
	scanf("%s", node->id);
	printf("TITLE >> ");
	scanf("%s", node->title);
	printf("CONTENT >> ");
	scanf("%s", node->content);
	char year[5];
	char month[5];
	char day[5];

	strcpy(year, GetYear());
	strcpy(month ,GetMonth());
	strcpy(day, GetDay());
	char date[20];
	strcpy(node->date, GetFullDate(year, month, day));	
	node= MakeFileNode(node->id, node->title, nowId, node->content, node->date);
	AddFileListNode(flist, node);
	fp=fopen("post.txt", "r+");
	fseek(fp, (flist->count-1)*sizeof(File), SEEK_SET);
	fwrite(node, sizeof(File), 1, fp);
	fclose(fp);
	getchar();
	printf("<< Press any key to go previous screen >>\n");
	scanf("%[^\n]", temp);
	system("clear");
}

void EditPost(FileList *flist){
	char temp[256];
	char title[256];
	char content[256];
	char Id_num[20];
	int	exist;
	File *node;
	node=flist->head->next;
	printf("\n*************************************\n");
	printf("**            Edit Post            **\n");
	printf("*************************************\n");
	printf("ID >> ");
	scanf("%s", Id_num);
	exist=FindFileNodeIdx(flist, Id_num);
	if(exist!=-1){
		printf("Edit %s's post!!\n", Id_num);
		printf("Title >> ");
		scanf("%s", title);
		printf("Content >> ");
		scanf("%s", content);
		ChangeFileNode(flist, exist, title, content);
		for(int i=0;i<exist;i++)
			node=node->next;

		FILE *fp = fopen("post.txt","r+");
		fseek(fp,sizeof(File)*(exist),SEEK_SET);
		File *edit=FindFileNode(flist, node->id);
		fwrite(edit, sizeof(File), 1, fp);
		fclose(fp);
		getchar();
		printf("%s's post id edited!!\n", Id_num);
	}
	else{
		getchar();
		printf("wrong ID\n");
	}
	printf("<< Press any key to go previous screen >>\n");
	scanf("%[^\n]", temp);
	system("clear");
}

void DeletePost(FileList *flist){
	char title[10];
	char temp[256];
	char answer[10];
	FILE *fp;
	File tmp;
	File *node;
	int i, idx, exist;

	memset(title, 0, 10);
	printf("\n*************************************\n");
	printf("**           Delete Post           **\n");
	printf("*************************************\n");
	printf("ID >> ");
	scanf("%s", title);
	exist=FindFileNodeIdx(flist, title);
	if(exist!=-1){
		printf("Are you sure want to delete post? (yes/no) >> ");
		scanf("%s", answer);
		if(!strcmp("yes", answer)){
			DeleteFileNode(flist, title);
			fp = fopen("post.txt", "r+");
			for(i=0;i<((flist->count)+1);i++){
				memset(&tmp, 0, sizeof(File));
				fread(&tmp, sizeof(File), 1, fp);
				if(!strcmp(tmp.id, title))
					break;
			}
			idx=i;
			memset(&tmp, 0, sizeof(File));
			fseek(fp, sizeof(File)*idx, SEEK_SET);

			for(i=idx; i<(flist->count); i++){
				fwrite(&tmp, sizeof(File), 1, fp);
				fread(&tmp, sizeof(File), 1, fp);
				fseek(fp, sizeof(File)*i, SEEK_SET);
				fwrite(&tmp, sizeof(File), 1, fp);
				memset(&tmp, 0, sizeof(File));
			}
			fseek(fp, sizeof(File)*(flist->count-1), SEEK_SET);
			fwrite(&tmp, sizeof(File), 1, fp);
			fclose(fp);
		}
		getchar();
		printf("%s's post is deleted!!\n", title);
	}
	else{
		getchar();
		printf("Wrong ID!!!\n");
	}
	printf("<< Press any key to go previous screen >>\n");
	scanf("%[^\n]", temp);
	system("clear");
}
