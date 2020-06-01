#ifndef head_h
    #define head_h
    #include<string.h>
        typedef struct key_tag //structure of keys
        {
            char roll_no[12];
            char sub_code[10];
        }key;


        typedef struct record_tag // structure of record excludinf key
        {
            char dept[10];
            char *name;
            int marks;
            int sem;
        }record;

        //key+record = entry
        typedef struct tree_node_tag
        {
            key id;
            record data;
            struct tree_node_tag *left, *right;
            int height;
        }tree_node;

        typedef struct topper_node_tag
        {
            char roll_no[12];
            record data;
            struct topper_node_tag *next;
            int height;
        }topper_node;

        FILE* fetch_file(char *retval);
        tree_node* load_list(FILE *fp);
        tree_node *rotate_right(tree_node *ptr);
        tree_node *rotate_left(tree_node *ptr);
        tree_node *search_node(tree_node *root,key *id);
        int insert(tree_node **root);
        int insert_node(tree_node **root ,tree_node *ptr);
        int key_comp(key *ptr, key *id); // id - ptr
        void print_database(tree_node *null);
        int get_max(int a ,int b);
        int Height(tree_node *ptr);
        int b_fact(tree_node *rptr);
        void print_node(tree_node *ptr);
        int getNumRecords (tree_node *root);
        int get_Height(tree_node *root);
        int delete_node(tree_node **root,key *id);
        tree_node *right_most_node(tree_node **root);
        void range_search(tree_node**root,key *low,key *high);
        tree_node *remove_tree(tree_node *root);
        void list_faiures(tree_node *root,char *sc ,int k);
        void list_toppers(tree_node *root,topper_node **head);
        void print_list(topper_node *ptr);
        void get_Kth_highest(tree_node *root,topper_node **head,char *sc ,int k);
        void make_list(tree_node *root,topper_node **head,char *sc);//forms a liat of student records for the same subject code

    #endif
