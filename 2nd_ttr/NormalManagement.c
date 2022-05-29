#include "header.h"

void ShowNormalUsers(UserTree *tree){
	char temp[256];
	User *node;
	node=tree->root;
	printf("\n*************************************\n");
	printf("**           Show Users	           **\n");
	printf("*************************************\n");	
	printf("%-15s %-15s %-15s %-15s %s\n", "Type", "Id", "Password", "Name", "Email");
	Preorder(node);
	printf("<< Press any key to go previous screen >>\n");
	scanf("%[^\n]", temp);
	system("clear");
}

void LeaveCafe(UserTree *tree){
	char temp[256];
	char answer[20];
	FILE *fp;
	int i, idx;
	User tmp;
	User *node;
	node=(User *)malloc(sizeof(User));
	printf("\n*************************************\n");
	printf("**           Leave Cafe	           **\n");
	printf("*************************************\n");	
	printf("Are you sure want to delete your account? (yes/no) >> ");
	scanf("%s", answer);
	User *user=malloc(sizeof(User));
	strcpy(user->id, nowId);
	if((strcmp("yes", answer))==0){
		DeleteNode(tree, user->id);
		tree->treeCount--;
		fp=fopen("user.txt", "r+");
		for(i=0;i<(tree->treeCount+1);i++){
			memset(&tmp, 0, sizeof(User));
			fread(&tmp, sizeof(User), 1, fp);
			if(!strcmp(tmp.name, user->id)){
				break;
			}
		}
		idx=i;
		memset(&tmp, 0, sizeof(User));
		fseek(fp, sizeof(User)*idx, SEEK_SET);
		for(i=idx;i<(tree->treeCount);i++){
			fwrite(&tmp, sizeof(User), 1, fp);
			fread(&tmp, sizeof(User)*i, 1, SEEK_SET);
			fwrite(&tmp, sizeof(User), 1, fp);
			memset(&tmp, 0, sizeof(User));
		}
		fseek(fp, sizeof(User)*tree->treeCount, SEEK_SET);
		fwrite(&tmp, sizeof(User), 1, fp);
		fclose(fp);
		printf("%s's account is deleted!!\n", user->id);
		printf("<< Press any key to go finish program >>\n");
		getchar();
		scanf("%[^\n]", temp);
		exit(1);
	}
	else{
		getchar();
		printf("<< Press any key to go previous screen >>\n");
		scanf("%[^\n]", temp);
		system("clear");
	}
}


void ShowNormalPost(FileList *flist){
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


void AddNormalPost(FileList *flist){
	FILE *fp;
	char temp[256];
	File *node;

	node=(File *)malloc(sizeof(File));
	printf("\n*************************************\n");
	printf("**             Add Post            **\n");
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

void EditNormalPost(FileList *flist){
	char temp[256];
	char see[20];
	char title[256];
	char content[256];
	int Idx_num;
	int	exist;
	int idx=1;
	File *node;
	node=flist->head->next;
	printf("\n*************************************\n");
	printf("**            Edit Post            **\n");
	printf("*************************************\n");	
	printf("%-10s %-10s %-10s %-10s %-15s %-10s\n", "Idx", "Id", "Title", "Writer", "Content", "Date");
	while(node->next!=NULL){
		if(!strcmp(node->writer, nowId)){
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
		else
			node=node->next;
	}
	printf("Input Idx >> ");
	scanf("%d", &Idx_num);
	node=flist->head->next;
	idx=0;
	while(node->next!=NULL){
		if(!strcmp(node->writer, nowId)){
			idx++;
			if(idx==Idx_num){
				break;
			}
			else
				node=node->next;
		}
		else
			node=node->next;
	}
	exist=FindFileNodeIdx(flist, node->id);
	if(exist!=-1){
		printf("Title >> ");
		scanf("%s", title);
		printf("Content >> ");
		scanf("%s", content);
		ChangeFileNode(flist, exist, title, content);

		FILE *fp = fopen("post.txt","r+");
		fseek(fp,sizeof(File)*(idx-1),SEEK_SET);
		File *edit=FindFileNode(flist, node->id);
		fwrite(edit, sizeof(File), 1, fp);
		fclose(fp);
		getchar();
		printf("%s's post id edited!!\n", nowId);
	}
	else{
		getchar();
		printf("Idx Wrong!!\n");
	}
	printf("<< Press any key to go previous screen >>\n");
	scanf("%[^\n]", temp);
	system("clear");
}

void DeleteNormalPost(FileList *flist){
	char temp[256];
	int Idx_num;
	int i;
	char see[20];
	char answer[20];
	int exist;
	int idx=1;
	FILE *fp;
	File tmp;
	File *node=(File *)malloc(sizeof(File));
	node=flist->head->next;

	printf("\n*************************************\n");
	printf("**           Delete Post           **\n");
	printf("*************************************\n");
	printf("%-10s %-10s %-10s %-10s %-15s %-10s\n", "Idx", "Id", "Title", "Writer", "Content", "Date");
	while(node->next!=NULL){
		if(!strcmp(node->writer, nowId)){
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
		else
			node=node->next;
	}
	printf("Input Idx >> ");
	scanf("%d", &Idx_num);
	if(Idx_num<idx){
		printf("Are you sure want to delete post? (yes/no) >> ");
		scanf("%s", answer);
		if(!strcmp("yes", answer)){
			idx=0;
			node=flist->head->next;
			while(node->next!=NULL){
				if(!strcmp(node->writer, nowId)){
					idx++;	
					if(Idx_num==idx)
						break;
					else
						node=node->next;
				}
				else
					node=node->next;
			}
			DeleteFileNode(flist, node->id);
			fp=fopen("post.txt", "r+");
			for(i=0;i<(flist->count);i++){
				memset(&tmp, 0, sizeof(File));
				fread(&tmp, sizeof(File), 1, fp);
				if(!strcmp(tmp.id, node->id))
					break;
			}
			idx=i;
			memset(&tmp, 0, sizeof(File));
			fseek(fp, sizeof(File)*idx, SEEK_SET);

			for(i=idx;i<(flist->count);i++){
				fwrite(&tmp, sizeof(File), 1, fp);
				fread(&tmp, sizeof(File), 1, fp);
				fseek(fp, sizeof(File)*i, SEEK_SET);
				fwrite(&tmp, sizeof(File), 1, fp);
				memset(&tmp, 0, sizeof(File));
			}
			fseek(fp, sizeof(File)*(flist->count), SEEK_SET);
			fwrite(&tmp, sizeof(File), 1, fp);
			fclose(fp);
		}
		getchar();
		printf("%s's post is deleted!!\n", nowId);
	}
	else{
		getchar();
		printf("Idx Wrong!!!\n");
	}
	printf("<< Press any key to go previous screen >>\n");
	scanf("%[^\n]", temp);
	system("clear");
}
