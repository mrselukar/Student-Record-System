FILE* fetch_file(char *retval)
{
  //This Function takes the ipname of a database and opens ir returns the File pointer
  printf("Enter the database to be loaded\n" );
  printf("NOTE IF THE FILE DOESNT EXIST THE A NEW FILE WILL BE CREATED \n");
  char db_name[50];
  scanf("%s",db_name);
  FILE *fp = fopen(db_name,"r+");
  if(fp == NULL)
  {
    fp = fopen(db_name,"w+");
  }
  strcpy(retval,db_name);
  return fp;
}

//-------------------------------------------------------------------------------------------------------


tree_node* load_list(FILE *fp)
{

  tree_node *root = NULL;
  while (!feof(fp))
    {
      tree_node* temp = (tree_node*)malloc(sizeof(tree_node));
      temp->left =temp->right =NULL;
      temp->height = 1;
      char str[256];
      fscanf(fp,"%s %s %s %s %d %d",temp->id.roll_no,temp->id.sub_code,temp->data.dept,str,&temp->data.marks,&temp->data.sem);
      temp->data.name = (char *)malloc(sizeof(str)+1);
      strcpy(temp->data.name,str);
      if(strcmp(temp->id.roll_no,"")!= 0 && strcmp(temp->id.sub_code,"") !=0)
      {
           insert_node(&root,temp);
      }
      //print_database(root);
      //printf("///////////////////////////////////////////////////////////////////////////////////\n" );
    }
    return(root);
}

//-------------------------------------------------------------------------------------------------------
int get_max(int a ,int b)
{
    if(a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
int Height(tree_node *ptr)
{
    if(ptr==NULL)
    {
        return 0;
    }
    else
    {
        return ptr->height;
    }
}
int b_fact(tree_node *rptr)
{
    if(rptr == NULL)
    {
        return 0;
    }
    else
    {
        int balance_fact = Height(rptr->right)-Height(rptr->left);
        return(balance_fact);
    }
}
void print_node(tree_node *ptr)
{
    if(ptr!=NULL)
    {
        printf("---------------------------------------------\n" );
        printf("ROLL NO: " );
        printf(" %s \n",ptr->id.roll_no);
        printf("Subject Code: " );
        printf(" %s\n",ptr->id.sub_code );
        printf("Name: " );
        printf(" %s\n",ptr->data.name);
        printf("Department: ");
        printf(" %s\n",ptr->data.dept );
        printf("Semester: " );
        printf(" %d\n",ptr->data.sem );
        printf("Marks: ");
        printf(" %d\n",ptr->data.marks);
        printf("        Height is %d\n",ptr->height );
        printf("---------------------------------------------\n" );
    }
}
tree_node *rotate_right(tree_node *ptr)
{
    tree_node *temp = NULL;
    if(ptr == NULL)
    {
        //this should never happen
        printf("ERROR in rotate_right operation sent pointer NULL\n");
    }
    else if(ptr->left == NULL)
    {
        //this will also never happen
        printf("Error cant be null as left will be the new root \n");
    }
    else
    {
        temp = ptr->left;
        ptr->left = temp->right;
        temp->right = ptr;
        ptr->height = get_max(Height(ptr->left),Height(ptr->right))+1;
        temp->height = get_max(Height(temp->left),Height(temp->right))+1;
    }
    return temp;
}

tree_node *rotate_left(tree_node *ptr)
{
    tree_node *temp = NULL;
    if(ptr == NULL)
    {
        //this should never happen
        printf("ERROR in rotate_left operation sent pointer NULL\n");
    }
    else if(ptr->right == NULL)
    {
        //this will also never happen
        printf("Error cant be null as right will be the new root \n");
    }
    else
    {
        temp = ptr->right;
        ptr->right = temp->left;
        temp->left = ptr;
        ptr->height = get_max(Height(ptr->left),Height(ptr->right))+1;
        temp->height = get_max(Height(temp->left),Height(temp->right))+1;
    }
    return temp;
}

int key_comp(key *ptr, key *id) // id - ptr
{
  int retval = strcmp(ptr->roll_no,id->roll_no);
  if(retval == 0)
  {
    retval = strcmp(ptr->sub_code,id->sub_code);
  }
  return (-1*retval);
}

tree_node *search_node(tree_node *root,key *id)
{
    tree_node *rptr =root;
    int isFound = 0;
    while (rptr != NULL && isFound == 0)
    {
      int temp = key_comp(&(rptr->id),id);//id - rptr->id
      if (temp == 0)
      {
        isFound = 1;
      }
      else if (temp < 0)
      {
        //parent = rptr;
        rptr = rptr->left;
      }
      else
      {
        //parent = rptr;
        rptr = rptr->right;
      }
    }
    //free(id); // freeing up the id variale
    return(rptr);
}


int insert(tree_node **root)
{
    tree_node *ptr= (tree_node*)malloc(sizeof(tree_node));
    ptr->left = ptr->right = NULL;
    ptr->height = 1;
    printf("Enter roll_no\n");
    scanf("%s",ptr->id.roll_no );
    printf("Enter sub_code\n");
    scanf("%s",ptr->id.sub_code );
    printf("Enter Department\n");
    scanf("%s",ptr->data.dept );
    char name[200];
    printf("Enter Name\n");
    scanf("%s",name);
    ptr->data.name = (char*)malloc(sizeof(strlen(name)+1));
    strcpy(ptr->data.name,name);
    printf("Enter Marks\n");
    scanf("%d",&(ptr->data.marks) );
    printf("Enter Semister in Integer\n" );
    scanf("%d",&(ptr->data.sem));
    return(insert_node(root,ptr));

}


int insert_node(tree_node **root,tree_node *node)
{
  int retval = 1;
  tree_node *ptr = NULL ,*parent = NULL;
    if(*root == NULL)
    {
      *root = node;
      node->left = node->right = NULL;
      node->height = 1;
      retval = 1;
    }
    else
    {
          tree_node *rptr= *root;
          int done = 0;
          //while (!done)
          //{
          int temp = key_comp(&rptr->id,&node->id);
          if(temp < 0 )//rptr is greater
          {
                if(rptr->left == NULL)
                {
                  rptr->left = node;
                  done = 1;

                }
                else
                {
                    insert_node(&(rptr->left),node);
                  //rptr=rptr->left;
                }
          }
          else if (temp > 0)//node is greater
          {
                if(rptr->right == NULL)
                {
                  rptr->right = node;
                  done =1;
                }
                else
                {
                    insert_node(&(rptr->right),node);
                  //rptr = rptr->right;
                }
          }
          else
          {
                printf("NODE ALREADY EXISTS WITH DATA\n");
                print_node(rptr);
                int updt = 0;
                printf("Do You Want to update the node enter 1 to update with the data\n");
                print_node(node);
                scanf("%d",&updt);
                if(updt == 1)
                {
                    strcpy(rptr->data.dept,node->data.dept);
                    free(rptr->data.name);
                    rptr->data.name = (char*)malloc(sizeof(strlen(node->data.name + 1)));
                    strcpy(rptr->data.name,node->data.name);
                    rptr->data.marks = node->data.marks;
                    rptr->data.sem = node->data.sem;
                    printf("Record Updated\n");
                }
                done = 2;
          }
          //update height
          rptr->height = get_max(Height(rptr->left),Height(rptr->right))+1;//THIS WILL NEVER BE NULL
          int balance_fact = b_fact(rptr);
          retval = done;
            // 4 cases
            //left left
          if(balance_fact == -2 && b_fact(rptr->left) < 0 )
          {
            rptr =  rotate_right(rptr);
          }
          //left right
          else if( balance_fact == -2 && b_fact(rptr->left) > 0 )
          {
             rptr->left =  rotate_left(rptr->left);
             rptr =  rotate_right(rptr);
          }
          //right right
          else if( balance_fact == +2 && b_fact(rptr->right) > 0 )
          {
             rptr =  rotate_left(rptr);
          }
          //right left
          else if(  balance_fact == +2 && b_fact(rptr->right) < 0)
          {
              rptr->right=rotate_right(rptr->right);
              rptr = rotate_left(rptr);
          }
          //rptr->height = get_max(Height(rptr->left),Height(rptr->right))+1;
          *root = rptr;
    }
    return retval;
  }

void print_database(tree_node *root)
{
    if(root != NULL)
    {
        print_node(root);
        print_database(root->left);

        print_database(root->right);
    }
}

int getNumRecords (tree_node *root)
{
    int retval;
    if (root == NULL)
    {
        retval = 0;
    }
    else
    {
        retval = 1+ getNumRecords(root->left)+getNumRecords(root->right);
    }
}

int get_Height(tree_node *root)
{
    if(root != NULL)
    {

        return root->height;
    }
    else
    {
        return 0;
    }
}

int delete_node(tree_node **root,key *id)
{
    int retval = 0;
    if(*root == NULL)
    {
        printf("NO RECORD EXISTS FOR THE GIVEN KEY\n");
    }
    else
    {
        retval =1;
        tree_node *rptr = *root;
        int temp = key_comp(&rptr->id,id);
        if(temp < 0)
        {
            delete_node(&rptr->left,id);
        }
        else if(temp >0)
        {
            delete_node(&rptr->right,id);
        }
        else//match
        {
            tree_node *replacement;
            //single child and leaf node cases
            if(rptr->left == NULL)
            {
                *root = rptr->right;
                free(rptr);
            }
            else if(rptr->right == NULL) //single left child case
            {
                *root = rptr->left;
                free(rptr);
            }
            else//internal node`
            {
                replacement = right_most_node(&rptr->left);
                replacement->left = rptr->left;
                replacement->right = rptr->right;
                *root = replacement;
                free(rptr);
            }
            rptr = *root;
        }
        //update height
        if(rptr != NULL)
        {
            rptr->height = get_max(Height(rptr->left),Height(rptr->right))+1;
            int balance_fact = b_fact(rptr);
             // 6 cases
              //left left
            if(balance_fact == -2 && b_fact(rptr->left) <= 0 )
            {
              rptr =  rotate_right(rptr);
            }
            //left right
            else if( balance_fact == -2 && b_fact(rptr->left) > 0 )
            {
               rptr->left =  rotate_left(rptr->left);
               rptr =  rotate_right(rptr);
            }
            //right right
            else if( balance_fact == +2 && b_fact(rptr->right) >= 0 )
            {
               rptr =  rotate_left(rptr);
            }
            //right left
            else if(  balance_fact == +2 && b_fact(rptr->right) < 0)
            {
                rptr->right=rotate_right(rptr->right);
                rptr = rotate_left(rptr);
            }
            *root = rptr;
            if(rptr != NULL)
            {
                rptr->height = get_max(Height(rptr->left),Height(rptr->right))+1;
            }
        }
    }
    return retval;
}

tree_node *right_most_node(tree_node **root)
{
    tree_node *rptr = *root;
    tree_node *retval = NULL;
    if(rptr != NULL)
    {
        if(rptr->right == NULL)
        {
            *root = rptr ->left;
            retval = rptr;
        }
        else
        {
            retval = right_most_node(&rptr->right);
            //update height
            rptr->height = get_max(Height(rptr->left),Height(rptr->right))+1;
            int balance_fact = b_fact(rptr);
              // 4 cases
              //left left
            if(balance_fact == -2 && b_fact(rptr->left) <= 0 )
            {
              rptr =  rotate_right(rptr);
            }
            //left right
            else if( balance_fact == -2 && b_fact(rptr->left) > 0 )
            {
               rptr->left =  rotate_left(rptr->left);
               rptr =  rotate_right(rptr);
            }
            //right right
            else if( balance_fact == +2 && b_fact(rptr->right) >= 0 )
            {
               rptr =  rotate_left(rptr);
            }
            //right left
            else if(  balance_fact == +2 && b_fact(rptr->right) < 0)
            {
                rptr->right=rotate_right(rptr->right);
                rptr = rotate_left(rptr);
            }
            *root = rptr;
            if(rptr != NULL)
            {
                rptr->height = get_max(Height(rptr->left),Height(rptr->right))+1;
            }
        }
    }
    else
    {
        printf("Unexpected Error in right most node\n");
    }
    return(retval);

}

void range_search(tree_node**root,key *low,key *high)
{
       if(*root != NULL)
    {
        tree_node *rptr = *root;
        int cmp1 = key_comp(&(rptr->id),low);
        int cmp2 = key_comp(&(rptr->id),high);
        if(cmp1<=0)
        {
            range_search(&rptr->left,low,high);
        }
        if(cmp1<=0 && cmp2 >= 0)
        {
            print_node(rptr);
        }
        if(cmp2 >= 0)
        {
            range_search(&rptr->right,low,high);
        }
    }
}

tree_node *remove_tree(tree_node *root)
{
    if(root != NULL)
    {
        tree_node *rptr = root;
        remove_tree(rptr->left);
        remove_tree(rptr->right);
        free(rptr);
    }
}


void list_faiures(tree_node *root,char *sc ,int k)
{
    //tree_node *retval = NULL;
    if(root != NULL)
    {
        list_faiures(root->left,sc,k);
        if(strcmp(root->id.sub_code,sc)==0)
        {
            if(root->data.marks < k)
            {
                print_node(root);
                //a new tree consisting of only failures can also be retured
            }
        }
        list_faiures(root->right,sc,k);
    }
    //return retval;
}

void list_toppers(tree_node *root,topper_node **head)
{
    if(root != NULL)
    {
        list_toppers(root->left,head);
        topper_node *lptr = *head;
        int isFound = 0;
        while (lptr!=NULL && isFound == 0)
        {
            if(strcmp(lptr->roll_no,root->id.roll_no)==0)
            {
                isFound = 1;
                lptr->data.marks += root->data.marks;
            }
            lptr = lptr->next;
        }
        if(lptr == NULL)
        {
            topper_node *ptr = (topper_node*)malloc(sizeof(topper_node));
            strcpy(ptr->roll_no,root->id.roll_no);
            strcpy(ptr->data.dept,root->data.dept);
            ptr->data.name = (char*)malloc(sizeof(root->data.name+1));
            strcpy(ptr->data.name,root->data.name);
            ptr->data.marks = root->data.marks;
            ptr->data.sem= root->data.sem;
            ptr->next = *head;
            *head = ptr;
        }
        list_toppers(root->right,head);
    }
    else
    {
        ;
    }
}

void print_max(topper_node *head)
{
    int max = 0;
    topper_node *ptr = head;
    while (ptr != NULL)
    {
        if(ptr->data.marks > max)
        {
            max = ptr->data.marks;
        }
        ptr = ptr->next;
    }
    ptr = head;
    while (ptr != NULL)
    {
        if(ptr->data.marks == max)
        {
            printf("---------------------------------------------\n" );
            printf("ROLL NO: " );
            printf(" %s \n",ptr->roll_no);
            printf("Name: " );
            printf(" %s\n",ptr->data.name);
            printf("Department: ");
            printf(" %s\n",ptr->data.dept );
            printf("Semester: " );
            printf(" %d\n",ptr->data.sem );
            printf("Marks: ");
            printf(" %d\n",ptr->data.marks);
            printf("---------------------------------------------\n" );

        }
        ptr=ptr->next;
    }
}

void freeList(topper_node *lptr)
{
    topper_node *ptr = lptr;
    while (ptr != NULL)
    {
        topper_node *prev = ptr;
        ptr = ptr->next;
        free(prev);
    }
}

void getMax(tree_node *root,topper_node **head,char *sc)
{
    if(root != NULL)
    {
        getMax(root->left,head,sc);
        if(strcmp(sc,root->id.sub_code)==0)//node is of the given subject
        {
            topper_node *lptr = *head;
            if(lptr!=NULL)//the output list is not empty
            {
                if(lptr->data.marks == root->data.marks)//root is another topper
                {
                    topper_node *ptr = (topper_node*)malloc(sizeof(topper_node));
                    strcpy(ptr->roll_no,root->id.roll_no);
                    strcpy(ptr->data.dept,root->data.dept);
                    ptr->data.name = (char*)malloc(sizeof(root->data.name+1));
                    strcpy(ptr->data.name,root->data.name);
                    ptr->data.marks = root->data.marks;
                    ptr->data.sem= root->data.sem;
                    ptr->next = *head;
                    *head = ptr;
                }//new topper added to the list of toppers for the subject code
                else if(lptr->data.marks < root->data.marks)//new max marks found so updating list by removing old entries and adding the new topper
                {
                    freeList(lptr);
                    topper_node *ptr = (topper_node*)malloc(sizeof(topper_node));
                    strcpy(ptr->roll_no,root->id.roll_no);
                    strcpy(ptr->data.dept,root->data.dept);
                    ptr->data.name = (char*)malloc(sizeof(root->data.name+1));
                    strcpy(ptr->data.name,root->data.name);
                    ptr->data.marks = root->data.marks;
                    ptr->data.sem= root->data.sem;
                    ptr->next = NULL;
                    *head = ptr;
                }
                else
                {
                    //do nothig altough the sc matches the marks are below the current topper
                }
            }
            else//op list was empty start from node 1
            {
                topper_node *ptr = (topper_node*)malloc(sizeof(topper_node));
                strcpy(ptr->roll_no,root->id.roll_no);
                strcpy(ptr->data.dept,root->data.dept);
                ptr->data.name = (char*)malloc(sizeof(root->data.name+1));
                strcpy(ptr->data.name,root->data.name);
                ptr->data.marks = root->data.marks;
                ptr->data.sem= root->data.sem;
                ptr->next = NULL;
                *head = ptr;
            }
        }
        getMax(root->right,head,sc);
    }
}
 void print_list(topper_node *ptr)
 {
     if(ptr == NULL)
     {
         printf("NO Entries for the given SC\n" );
     }
     while (ptr!= NULL)
     {
         printf("---------------------------------------------\n" );
         printf("ROLL NO: " );
         printf(" %s \n",ptr->roll_no);
         printf("Name: " );
         printf(" %s\n",ptr->data.name);
         printf("Department: ");
         printf(" %s\n",ptr->data.dept );
         printf("Semester: " );
         printf(" %d\n",ptr->data.sem );
         printf("Marks: ");
         printf(" %d\n",ptr->data.marks);
         printf("---------------------------------------------\n" );
         ptr = ptr->next;
     }
 }

void get_Kth_highest(tree_node *root,topper_node **head,char *sc ,int k)
{
        topper_node *lptr = NULL;
        make_list(root,&lptr,sc);//gives out sorted list of all student records for the given sc
        int count = 0;
        topper_node *prev = NULL;
        topper_node *rptr = lptr;
        while(count < k && rptr != NULL)
        {
            if(prev == NULL && rptr != NULL)
            {
                count++;
            }
            else
            {
                if(prev->data.marks != rptr->data.marks)
                {
                    count++;
                }
            }
            prev = rptr;
            rptr = rptr->next;
        }
        rptr = prev;
        if(count == k)
        {
            while(prev->data.marks == rptr->data.marks)
            {
                printf("---------------------------------------------\n" );
                printf("ROLL NO: " );
                printf(" %s \n",rptr->roll_no);
                printf("Name: " );
                printf(" %s\n",rptr->data.name);
                printf("Department: ");
                printf(" %s\n",rptr->data.dept );
                printf("Semester: " );
                printf(" %d\n",rptr->data.sem );
                printf("Marks: ");
                printf(" %d\n",rptr->data.marks);
                printf("---------------------------------------------\n" );
                prev = rptr;
                rptr = rptr->next;
            }
        }
        else
        {
            printf("No Record For the given selection \n");
        }
        *head = lptr;
}

void make_list(tree_node *root,topper_node **head,char *sc)//forms a liat of student records for the same subject code
{
    if(root != NULL)
    {
        make_list(root->left,head,sc);
        if(strcmp(sc,root->id.sub_code)==0)//node is of the given subject
        {
            topper_node *lptr = *head;
            if(lptr!=NULL)//the output list is not empty
            {

                    topper_node *ptr = (topper_node*)malloc(sizeof(topper_node));
                    strcpy(ptr->roll_no,root->id.roll_no);
                    strcpy(ptr->data.dept,root->data.dept);
                    ptr->data.name = (char*)malloc(sizeof(root->data.name+1));
                    strcpy(ptr->data.name,root->data.name);
                    ptr->data.marks = root->data.marks;
                    ptr->data.sem= root->data.sem;
                    //inserting at appopriate location
                    topper_node *rptr = *head;
                    topper_node *prev = NULL;
                    int isFound = 0;
                    while (isFound == 0 && rptr != NULL)
                    {
                        if(rptr->data.marks <= root->data.marks)
                        {
                            isFound = 1;
                        }
                        else
                        {
                            prev =rptr;
                            rptr = rptr->next;
                        }
                    }
                    if(prev == NULL)//head is updated
                    {
                        ptr->next = rptr;
                        *head = ptr;
                    }
                    else
                    {
                        prev->next = ptr;
                        ptr->next = rptr;
                    }
            }
            else//op list was empty start from node 1
            {
                topper_node *ptr = (topper_node*)malloc(sizeof(topper_node));
                strcpy(ptr->roll_no,root->id.roll_no);
                strcpy(ptr->data.dept,root->data.dept);
                ptr->data.name = (char*)malloc(sizeof(root->data.name+1));
                strcpy(ptr->data.name,root->data.name);
                ptr->data.marks = root->data.marks;
                ptr->data.sem= root->data.sem;
                ptr->next = NULL;
                *head = ptr;
            }
        }
        make_list(root->right,head,sc);
    }
}
