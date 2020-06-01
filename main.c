//USING AVL TREES
#include<stdio.h>
#include<stdlib.h>
#include"head.h"
#include"func.c"
int main()
{
        //Assignment By Mayur Selukar IIITN BT16CSE003
        char db_name[50];
        FILE *fp = fetch_file(db_name);
        //Loads the contents of File in memory as a Linked List of nodes;
        tree_node *root = load_list(fp);
        //NOW THAT THE List in in memory we will update the list and then at end store the updated
        //outputs in new file
    printf("DS Assignment 2 Using AVL TREES\n");
    int run = 1;
    while (run == 1)
    {
            int c;
            printf("Select one of the following\n");
            printf("1.To Print the Database\n");
            printf("2.To Search for a node \n" );
            printf("3.To insert a node \n" );
            printf("4.To Delete a node\n" );
            printf("5.To get the number of active records\n");
            printf("6.To get the height\n");
            printf("7.For Range Search\n");
            printf("8.For Listing Failures for a given Subject\n");
            printf("9.For Listing Topper\n");
            printf("10.For getting max marks in a given subject code\n");
            printf("11.To get the Kth Highest marks scorers in a given subject code \n" );
            int x ;
            scanf("%d",&x );
            switch(x)
            {
                case 1:
                    {
                        print_database(root);
                        break;
                    }
                case 2:
                    {
                        key id1;
                        printf("Enter roll_no\n");
                        scanf("%s",id1.roll_no );
                        printf("Enter sub_code\n");
                        scanf("%s",id1.sub_code );
                        tree_node *ptr =search_node(root,&id1);
                        if(ptr!=NULL)
                        {
                            printf("NODE FOUND\n" );
                            print_node(ptr);
                        }
                        else
                        {
                            printf("No Node for the given key exists in the database\n");
                        }
                        break;
                    }
                case 3:
                    {
                        insert(&root);
                        break;
                    }
                case 4:
                    {
                        key id1;
                        printf("Enter roll_no\n");
                        scanf("%s",id1.roll_no );
                        printf("Enter sub_code\n");
                        scanf("%s",id1.sub_code );
                        delete_node(&root,&id1);
                        break;
                    }
                case 5 :
                    {
                        printf("The number of active records are %d \n",getNumRecords(root) );
                        break;
                    }
                case 6:
                    {
                        printf("The height of the Tree is %d\n",get_Height(root) );
                        break;
                    }
                case 7:
                    {
                        key id1;
                        printf("Enter lower roll_no\n");
                        scanf("%s",id1.roll_no );
                        /*printf("Enter lower sub_code\n");
                        scanf("%s",id1.sub_code );*/
                        strcpy(id1.sub_code, "AAAA");
                        key id2;
                        printf("Enter higher roll_no\n");
                        scanf("%s",id2.roll_no );
                        /*printf("Enter higher sub_code\n");
                        scanf("%s",id2.sub_code );*/
                        strcpy(id2.sub_code,"zzzz");
                        range_search(&root,&id1,&id2);
                        break;
                    }
                case 8:
                    {
                        char sc[10];
                        int k;
                        printf("Enter the Subject Code\n" );
                        scanf("%s",sc );
                        printf("Enter Passing Marks \n" );
                        scanf("%d",&k );
                        list_faiures(root,sc ,k);
                        break;
                    }
                case 9:
                    {
                        //list toppers
                        topper_node *lptr = NULL;
                        list_toppers(root,&lptr);
                        print_max(lptr);
                        freeList(lptr);
                        break;
                    }
                case 10:
                    {
                        //get max marks in a given sub Code
                        topper_node *lptr = NULL;
                        char sc[10];
                        printf("Enter Subject Code\n");
                        scanf("%s",sc);
                        getMax(root,&lptr,sc);
                        print_list(lptr);
                        freeList(lptr);
                        break;
                    }
                case 11 :
                    {
                        //get kth highest
                        topper_node *lptr = NULL;
                        char sc[10];
                        printf("Enter Subject Code\n");
                        scanf("%s",sc);
                        int k;
                        printf("Enter K \n");
                        scanf("%d",&k);
                        get_Kth_highest(root,&lptr,sc,k);
                        //print_list(lptr);
                        freeList(lptr);
                        break;
                    }
                default:
                    {
                        run =0;
                        break;
                    }

            }
    }
    fclose(fp);
    return 0;
}
