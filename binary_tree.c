#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define RR 5
#define RL 9
#define LR 6
#define LL 10
typedef double Data_type;
typedef struct node
{
    Data_type val;
    node *lchld;node *rchld;
}*Node;
typedef struct binary_tree
{
    Node root;
    size_t size;
    size_t high;
}binary_tree;
binary_tree create_btree()
{
    binary_tree tree={NULL,0,0};
    return tree;
}
Node create_node()
{
    Node new_node =  (Node)malloc(sizeof(struct node));
    if(new_node!=NULL)
    new_node->rchld = new_node->lchld = NULL;
    return new_node;
}
int maxhigh(Node p)
{
    if(p==NULL)return 0;
    int lh = maxhigh(p->lchld);
    int rh = maxhigh(p->rchld);
    return lh>rh?(lh+1):(rh+1);
}
int minhigh(Node p)
{
    if(p==NULL)return 0;
    int lh = minhigh(p->lchld);
    int rh = minhigh(p->rchld);
    return lh>rh?(rh+1):(lh+1);
}
int get_high(binary_tree* btp,bool max = true)
{
    if(btp->root==NULL)return 0;
    return max?maxhigh(btp->root):minhigh(btp->root);
}
bool node_link(Node *p,const Data_type* val)
{
    *p = create_node();
    if(p==NULL)return false;
    (*p)->val = *val;
    return true;
}
bool insert(Node p,const Data_type *val,Node *trace)
{
    bool flag = false;
    while(p){
        if(*val == p->val)break;
        if((p->lchld && p->rchld)||(!p->lchld && !p->rchld)){
            if(*val < p->val){
                if(NULL != p->lchld){
                    *trace++ = p;
                    p=p->lchld;
                }else{
                    *trace++ = p;
                    flag = node_link(&p->lchld,val);
                    break;
                }
            }else{
                if(NULL != p->rchld){
                    *trace++ = p;
                    p=p->rchld;
                }
                else{
                    *trace++ = p;
                    flag = node_link(&p->rchld,val);
                    break;
                }
            }
        }else{
            if(p->lchld == NULL){
                if(*val<p->val){
                    *trace++ = p;
                    flag = node_link(&p->lchld,val);
                    break;
                }else if(*val<p->rchld->val){
                    *trace++ = p;
                    Data_type ori = p->val;
                    p->val = *val;
                    flag = node_link(&p->lchld,&ori);
                    break;
                }else{
                    *trace++ = p;
                    Data_type ori = p->val;
                    p->val = p->rchld->val;
                    p->rchld->val = *val;
                    flag = node_link(&p->lchld,&ori);
                    break;
                }
            }else{
                if(*val>p->val){
                    *trace++ = p;
                    flag = node_link(&p->rchld,val);
                    break;
                }else if(*val>p->lchld->val){
                    *trace++ = p;
                    Data_type ori = p->val;
                    p->val = *val;
                    flag = node_link(&p->rchld,&ori);
                    break;
                }else{
                    *trace++ = p;
                    Data_type ori = p->val;
                    p->val = p->lchld->val;
                    p->lchld->val = *val;
                    flag = node_link(&p->rchld,&ori);
                    break;
                }
            }
        }
    }
    return flag;
}
void mid_order(Node p)
{
    if(NULL == p)return;
    mid_order(p->lchld);
    printf("%.2f   ",p->val);
    mid_order(p->rchld);
}
void btree_Travel_midorder(binary_tree *btp)
{
    if(btp->root == NULL)return;
    printf("mid_order:\n");
    mid_order(btp->root);
    printf("\n");
}
void pre_order(Node p)
{    
    if(NULL == p)return;
    printf("%.2f   ",p->val);
    pre_order(p->lchld);
    pre_order(p->rchld);
}
void btree_Travel_preorder(binary_tree *btp)
{
    if(btp->root == NULL)return;
    printf("pre_order:\n");
    pre_order(btp->root);
    printf("\n");
}
void las_order(Node p)
{    
    if(NULL == p)return;
    las_order(p->lchld);
    las_order(p->rchld);
    printf("%.2f   ",p->val);
}
void btree_Travel_lasorder(binary_tree *btp)
{
    if(btp->root == NULL)return;
    printf("last_order:\n");
    las_order(btp->root);
    printf("\n");
}
//Caution!!! high is the value before inserting.
int categlory(binary_tree *btp,Node *trace,int *index)
{
    Node *p = trace;
    for(int i=btp->high-3;i>=0;--i){
        if(abs(maxhigh(p[i]->lchld)-maxhigh(p[i]->rchld))>=2){
            *index = i;
            break;
        }
    }
    // printf("index is %d\n",*index);
    unsigned up = (trace[*index]->rchld->val==trace[*index+1]->val)?(1<<0):(1<<1);
    unsigned down = (trace[*index+1]->rchld->val==trace[*index+2]->val)?(1<<2):(1<<3);
    return up|down;
}
Node balanceSubTree(Node root)
{
    Node new_root = root;
    int l_high = maxhigh(root->lchld);
    int r_high = maxhigh(root->rchld);
    if(abs(l_high-r_high)>=2){
        if(l_high>r_high){
            new_root=root->lchld;
            root->lchld = new_root->rchld;
            new_root->rchld = root;
        }else{
            new_root=root->rchld;
            root->rchld = new_root->lchld;
            new_root->lchld = root;
        }
    }
    return new_root;
}
//refresh high
void refreshHigh(binary_tree *btp,Node *trace)
{
    int l_high = maxhigh(btp->root->lchld);
    int r_high = maxhigh(btp->root->rchld);
    if(abs(l_high-r_high)>=2){
        int index = 0;
        int kind = categlory(btp,trace,&index);
        // printf("kind is %d\n",kind);
        if(kind == RR || kind == LL){
            if(kind == RR){
                trace[index]->rchld = trace[index+1]->lchld;
                trace[index+1]->lchld = trace[index];
            }else{
                trace[index]->lchld = trace[index+1]->rchld;
                trace[index+1]->rchld = trace[index];
            }
            if(index>0){
                trace[index-1]->lchld==trace[index]?trace[index-1]->lchld=trace[index+1]:trace[index-1]->rchld=trace[index+1];
            }else{
                btp->root = trace[index+1];
            }          
        }else if(kind == RL || kind == LR){
            if(kind == RL){
                trace[index+1]->lchld = trace[index+2]->rchld;
                trace[index+2]->rchld = trace[index+1];
                trace[index]->rchld = trace[index+2]->lchld;
                trace[index+2]->lchld = trace[index];
            }else{
                trace[index+1]->rchld = trace[index+2]->lchld;
                trace[index+2]->lchld = trace[index+1];
                trace[index]->lchld = trace[index+2]->rchld;
                trace[index+2]->rchld = trace[index];
            }
            if(index>0){
                trace[index-1]->lchld==trace[index]?trace[index-1]->lchld=trace[index+2]:trace[index-1]->rchld=trace[index+2];
            }else{
                btp->root = trace[index+2];
            }
        }
    }else{
        btp->high = l_high>r_high?l_high+1:r_high+1;
    }
}
void btree_insert(binary_tree *btp,const Data_type *val){
    if(NULL == btp->root)
    {
        btp->root = create_node();
        btp->root->val = *val;
        btp->size++;btp->high++;
        return;
    }
    Node* trace = (Node*)malloc(sizeof(Node)*btp->high);
    if(insert(btp->root,val,trace)){
        btp->size++;
        refreshHigh(btp,trace);   
    }
}
void clean(Node p){
    if(NULL == p)return;
    clean(p->lchld);
    clean(p->rchld);
    free(p);
}
void btree_clean(binary_tree *btp){
    clean(btp->root);
}
static Node find_min(Node p)
{
    while(NULL != p->rchld)
    {
        p = p->rchld;
    }
    return p;  
}
static Node find_max(Node p)
{
    while(NULL != p->lchld)
    {
        p = p->lchld;
    }
    return p;    
}
Data_type btree_find_max(binary_tree *btp){
    return find_max(btp->root)->val;
}
Data_type btree_find_min(binary_tree *btp){
    return find_min(btp->root)->val; 
}
bool btree_find(binary_tree *btp,const Data_type* vp){
    Node p = btp->root;
    while (p !=NULL && p->val != *vp)
    {
        if(*vp>p->val)p=p->rchld;
        else p=p->lchld;
    }
    return p==NULL?false:true;
}
void btree_delete(binary_tree *btp,const Data_type *vp){
    Node p = btp->root;
    //empty tree
    if(p==NULL)return;
    Node pre = NULL;
    while (p != NULL && p->val != *vp)
    {
        pre = p;
        if(*vp>p->val)p=p->rchld;
        else p=p->lchld;
    }
    //find the val
    if(p!=NULL){
        if(p->lchld&&p->rchld){
            //double node
            Node min = p->rchld,p_min = NULL;
            while(min->lchld != NULL){
                p_min = min;
                min = min->lchld;
            }
            //the min val is next the p node
            if(p_min==NULL){
                min->lchld = p->lchld;
                // p is root 
                if(pre==NULL){
                    btp->root = min;   //is root or normal node?
                    btp->root = balanceSubTree(btp->root);
                }
                else{
                    pre->lchld==p?pre->lchld=(min):pre->rchld=min;
                    // min->rchld = 
                }
                free(p);
            }else{
                p_min->lchld = min->rchld;
                min->lchld = p->lchld;min->rchld = p->rchld;
                if(pre==NULL)btp->root = min;
                else pre->lchld==p?pre->lchld = min:pre->rchld = min;
                free(p);
            }
        }else if(p->lchld||p->rchld){
            //single son ,let son replace it
            Node son = NULL;
            p->rchld != NULL?son=p->rchld:son=p->lchld;
            if(pre==NULL)btp->root = son;
            else pre->rchld == p ?pre->rchld=son:pre->lchld=son;
            free(p);
        }else{
            //terminal node,delete directly
            if(pre==NULL)btp->root = NULL;
            else pre->rchld==p?pre->rchld=NULL:pre->lchld=NULL;
            free(p);
        }
        --btp->size;
    }
}

void test()
{
    binary_tree tree = create_btree(); 
    double b = 1.0;
    for(int i=1;i<6;++i)
    {      
        b = i*1.0;
        btree_insert(&tree,&b);
        // printf("root val is %.f\n",tree.root->val);
    }
    printf("max val = %.f\n",btree_find_max(&tree));
    // printf("19999 is %d\n",btree_find(&tree,&b));
    printf("min val = %.f\n",btree_find_min(&tree));
    printf("max high of the tree:%d\n",get_high(&tree));
    // b = 2;
    // btree_delete(&tree,&b);
    printf("size is %d\n",tree.size);
    btree_Travel_preorder(&tree);
    btree_Travel_midorder(&tree);
    // btree_Travel_lasorder(&tree);
    // printf("min high of the tree:%d\n",get_high(&tree,false));
    btree_clean(&tree);

}

int main()
{   clock_t tStart = clock();
    test();
    printf("Time taken: %.5fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}