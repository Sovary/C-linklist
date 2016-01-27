#include<stdio.h>
#include<stdlib.h>
struct Person{
 char *num;
 int id;
 struct Person *next,*prev;

};
 struct Person  *head=NULL, *tail=NULL;
//Add one node
struct Person * addNode(struct Person *list,int id){
// list->num=val;
  struct Person *curr;
  list->id=id;
  if((head)==NULL){
   head=list;
  }else{
   list->prev=tail;
   tail->next=list;
  }
   tail=list;

 return tail;
}

//Current Person

 currPerson(struct Person *curr){
 printf("Current Person is %d\n",curr->id);
}
//Next
struct Person * nextPerson(struct Person *curr){
  curr=curr->next;
  if(curr==NULL)
   curr=tail;
   currPerson(curr);
return curr;
}
//Previous Person
struct Person * prevPerson(struct Person *curr){
 curr=curr->prev;
  if(curr==NULL)
   curr=head;
   currPerson(curr);
 return curr;
}
 deletePerson(int id){
   struct Person * tmp,*store;
   tmp=head;
   while(1){
   if(id==(tmp->id)&&(tmp->prev)==NULL && (tmp->next)==NULL){
//Free all element (the last element);
     printf("Free all\n");
     head->next=NULL;
     head->prev=NULL;
tail->prev=NULL;
     tail->next=NULL;
     free(tmp);
      head=NULL;
      tail=NULL;break;
    }
    else if(id==(tmp->id)&&(tmp->prev)!=NULL &&(tmp->next)!=NULL){
    tmp->prev->next=tmp->next;
    tmp->next->prev=tmp->prev;
     printf("%d body has been remove!\n",tmp->id); free(tmp);break;
    }
    if(id==(tmp->id)&&(tmp->next)==NULL){//Tail
     tail->prev->next=NULL;
     tail=tmp->prev;
     printf("%d tail has been remove!\n",tmp->id); free(tmp);break;
    }
   else if (id==(tmp->id)&&(tmp->prev)==NULL){//Head
     head->next->prev=NULL;
     store=tmp->next;
     head->next=NULL;
     head=store;
     printf("%d head has been remove!\n",tmp->id); free(tmp);break;
    }
   tmp=tmp->next;
 }
}

saveFile(){
struct Person *tmp;
tmp=head;
  FILE * fpt;
  fpt=fopen("sturct.bin","wb");
  if(fpt==NULL){
    printf("Permission denied!\n");
    exit(0);
   }
   while(tmp!=NULL){
     fwrite(tmp,sizeof(struct Person),1,fpt);
     printf("Write..!\n");
     tmp=tmp->next;
   }
  fclose(fpt);
}
readFile(){
 FILE * fpt;
 fpt=fopen("sturct.bin","rb");
   if(fpt==NULL){
    printf("Permission denied!\n");
    exit(0);
   }
struct Person p;
 struct Person *tmp;
 int i;
 while(1){
  i=fread((void*)&p,sizeof(struct Person),1,fpt);
  if(i==0)break;
 //rintf("%d\n",p.id);
  tmp=malloc(sizeof(struct Person));
  addNode(tmp,p.id);
 }

 fclose(fpt);
}
deleteFile(){
 if(remove("sturct.bin")==0)
  printf("Database has been deleted\n");

}
//Display
 display(){
 struct Person *tmp;
 tmp=head;
  if(tmp!=NULL){
    for((tmp);((tmp)!=NULL);(tmp=tmp->next)){
      printf("%d\n",tmp->id);
    }
  }else{
    printf("Element not found!\n");
}
 }
 releaseAll(){
  struct Person *tmp;
  tmp=head;
  while(tmp!=NULL){
   free(tmp);
   tmp->next=NULL;
   tmp->prev=NULL;
   printf("Free all\n");
   tmp=tmp->next;
  }
  head=NULL;
  tail=NULL;
 }
main(){
   struct Person *list;
   int chose,del;
   struct Person *curr;
   struct Person *loadFile;
 while(1){
   char *val=malloc(sizeof(char));
  printf("--------------------------------------------\n");
 printf("1.Display; 2.Add; 3.Prev; 4.Next; 5.Remove; 6.Save;\n7.Read; 8.Delete DB; 9.ReleaseAll 0.Exit;");
  printf("\n--------------------------------------------\nchoose: ");
  scanf("%d",&chose);
  switch(chose){
   case 0: exit(0);break;
   case 1:
   /*      printf("I am head %d\n",head->id);
    printf("I am tail %d\n",tail->id);
 */
     display();break;
   case 2:
    list = malloc(sizeof(struct Person));
    int id=0;
    printf("Input id: ");
    scanf("%d",&id);
    curr= addNode(list,id);
     break;
   case 3:
    curr= prevPerson(curr);break;
   case 4:
    curr= nextPerson(curr);break;
   case 5:

      printf("Delete ID: ");
      scanf("%d",&del);
 deletePerson(del);
      break;
   case 6://Save file
      saveFile();
      break;
   case 7://Read File
      readFile();
      break;
   case 8:
      deleteFile();
      break;
   case 9:
      releaseAll();
      break;
   default:

    break;
  }
 }
}
