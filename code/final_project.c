#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
    int key;
    char color;
    struct node * left, * right, * parent;
    struct node * neigh_rb;
} Node;

typedef struct rb_tree {
    Node * root;
    Node * nil;
} RB_TREE;

typedef struct int_node {
    int key;
    struct int_node * next, * prev;
    struct node * link_rb;
} Int_node;

Node NIL_NODE;
Node * NIL = &NIL_NODE;

Int_node NIL_INT_NODE;
Int_node * NIL_INT = &NIL_INT_NODE;

Node * create_node(int key) {

    Node * new_node = (Node *)malloc(sizeof(Node));

    new_node->key = key;
    new_node->left = new_node->right = new_node->parent = NIL;
    new_node->color = 'R';
    new_node->neigh_rb = NIL;

    return new_node;
}

void left_rotate(Node ** root, Node * x) {

    Node * y = x->right; 

    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        (* root) = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;

}

void right_rotate(Node ** root, Node* y) {

    Node * x = y->left;

    y->left = x->right;

    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NIL)
        (* root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;

}

void rb_insert_fixup(Node ** root, Node* z) {

    while (z != (*root) && z->parent->color == 'R') {

        if (z->parent == z->parent->parent->left) {

            Node * y = z->parent->parent->right;

            if (y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } 

            else {

                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(root, z);
                }

                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                right_rotate(root, z->parent->parent);
            }

        } else {

            Node * y = z->parent->parent->left;

            if (y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } 
            else {

                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(root, z);
                }

                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                left_rotate(root, z->parent->parent);
            }
        }
    }

    (* root)->color = 'B';
}

void rb_insert(Node ** root, int key) {

    Node * z = create_node(key);
    Node * y = NIL;
    Node * x = (* root);

    while (x != NIL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NIL)
        (* root) = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    rb_insert_fixup(root, z);
}

void rb_delete_fixup(Node ** root, Node * x) {

    while (x != (* root) && x->color == 'B') {

        if (x == x->parent->left) {

            Node * w = x->parent->right;

            if (w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                left_rotate(root, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == 'B' && w->right->color == 'B') {

                w->color = 'R';
                x = x->parent;

            } 
            else {

                if (w->right->color == 'B') {
                    w->left->color = 'B';
                    w->color = 'R';
                    right_rotate(root, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = 'B';
                w->right->color = 'B';
                left_rotate(root, x->parent);
                x = (* root);
            }
        } 
        else {

            Node * w = x->parent->left;

            if (w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                right_rotate(root, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == 'B' && w->left->color == 'B') {
                w->color = 'R';
                x = x->parent;
            } 
            else {

                if (w->left->color == 'B') {
                    w->right->color = 'B';
                    w->color = 'R';
                    left_rotate(root, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = 'B';
                w->left->color = 'B';
                right_rotate(root, x->parent);
                x = (* root);
            }
        }
    }

    x->color = 'B';
}

void rb_transplant(Node ** root, Node * u, Node * v) {

    if (u->parent == NIL)
        (* root) = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

Node * rb_tree_minimum(Node * node) {

    while (node->left != NIL)
        node = node->left;
    return node;
}

Node * rb_tree_maximum(Node * node) {

    while (node->right != NIL)
        node = node->right;
    return node;
}

Node * rb_tree_successor(Node * x) {

    if (x->right != NIL)
        return rb_tree_minimum(x->right);

    Node * y = x->parent;

    while (y != NIL && x == y->right) {
        x = y;
        y = y->parent;
    }

    return y;
}

Node * rb_tree_predecessor(Node * x) {

    if (x->left != NIL)
        return rb_tree_maximum(x->left);

    Node * y = x->parent;

    while (y != NIL && x == y->left) {
        x = y;
        y = y->parent;
    }

    return y;
}

Node * rb_tree_search_iterative(Node * x, int k) {

    while (x != NIL && k != x->key) {
        if (k < x->key)
            x = x->left;
        else 
            x = x->right;
    }

    return x;
} 

void rb_delete(Node ** root, Node * z) {

    Node * y = z;
    Node * x;

    char y_original_color = y->color;

    if (z->left == NIL) {
        x = z->right;
        rb_transplant(root, z, z->right);
    } 
    else if (z->right == NIL) {
        x = z->left;
        rb_transplant(root, z, z->left);
    } 
    else {
        y = rb_tree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z)
            x->parent = y;
        else {
            rb_transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rb_transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == 'B')
        rb_delete_fixup(root, x);

    free(z);
}

RB_TREE * create_rb_tree() {

    RB_TREE * tree = (RB_TREE *)malloc(sizeof(RB_TREE));

    tree->nil = NIL;
    tree->root = NIL;

    return tree;    
}

void post_order_rb_delete(Node * node) {

    if (node != NIL) {
        post_order_rb_delete(node->left);
        post_order_rb_delete(node->right);
        free(node);
    }
}

// *** minimum steps greedy algorithms ***

// src->key > dest->key

void post_order_list_delete(Int_node * node) {

    Int_node * del;

    while (node != NIL_INT) {
        del = node;
        node = node->next;
        free(del);
    }
}

void maximize_3_nodes_undirect(Int_node * head, Node * src, Node * dest) {

    Int_node * curr_list;
    Node * curr, * aux_curr, * fixed_left, * fixed_left_aux;
    Node * fixed_right = dest;
    Node * best = NIL;

    curr_list = head;

    while (curr_list->key > dest->key) {
        curr_list = curr_list->next;
    }

    curr_list = curr_list->prev;

    while (curr_list->key < src->key) {

        fixed_left = curr_list->prev->link_rb;
        curr = curr_list->link_rb;
        fixed_left_aux = rb_tree_maximum(fixed_left->neigh_rb);

        curr = rb_tree_predecessor(curr);
        aux_curr = rb_tree_maximum(curr->neigh_rb);

        while (curr->key >= fixed_left->key - fixed_left_aux->key) {
            if (curr->key - aux_curr->key <= fixed_right->key) {
                best = curr;
            }
            curr = rb_tree_predecessor(curr);
            aux_curr = rb_tree_maximum(curr->neigh_rb);
        }

        if (best != NIL) {
            curr_list->key = best->key;
            curr_list->link_rb = best;
        }

        best = NIL;

        fixed_right = curr_list->link_rb;
        curr_list = curr_list->prev;

    }
}

// auxiliary data structure

Int_node * sorted_list_insert(Int_node * head, Node * p) {

    Int_node * curr, * prec;

    Int_node * new_node = (Int_node *)malloc(sizeof(Int_node));

    new_node->link_rb = p;
    new_node->key = p->key;

    if (head == NIL_INT) {
        head = new_node;
        head->next = NIL_INT;
        head->prev = NIL_INT;
    }
    else {
        curr = head;
        while (curr != NIL_INT) {
            prec = curr;
            curr = curr->next;
        }
        prec->next = new_node;
        new_node->prev = prec;
        new_node->next = NIL_INT;
    }

    return head;
}

Node * best_reachable_node_undirect(Node * curr, Node * dest) {

    Node * aux_curr = rb_tree_maximum(curr->neigh_rb);
    int lower_bound = curr->key - aux_curr->key;
    int furthest_offset = lower_bound;
    Node * best_node = NIL;
    bool flag = true;

    if (lower_bound <= dest->key)
        return dest;
    else {
        curr = rb_tree_predecessor(curr);
        aux_curr = rb_tree_maximum(curr->neigh_rb);
        while (curr->key >= lower_bound) {
            if (curr->key - aux_curr->key <= dest->key) {
                best_node = curr;
                flag = false;
            }
            else if (curr->key - aux_curr->key < furthest_offset && flag) {
                furthest_offset = curr->key - aux_curr->key;
                best_node = curr;
            }
            curr = rb_tree_predecessor(curr);
            aux_curr = rb_tree_maximum(curr->neigh_rb);
        }
    }

    return best_node;
}

Int_node * aux_list_compiler_undirect(Node * src, Node * dest) {

    Int_node * head = NIL_INT;
    Node * curr = src;

    head = sorted_list_insert(head, src);

    while (curr->key > dest->key) {

        curr = best_reachable_node_undirect(curr, dest);

        if (curr == NIL) {
            post_order_list_delete(head);
            return NIL_INT;
        }
        else {
            head = sorted_list_insert(head, curr);
        }
    }

    return head;
}

void list_printer_undirect(Node * src, Node * dest) {

    Int_node * p = aux_list_compiler_undirect(src, dest);

    if (p == NIL_INT) {
        printf("nessun percorso\n");
    }
    else {
        maximize_3_nodes_undirect(p, src, dest);
        while (p->key > dest->key) {
            printf("%d ", p->key);
            p = p->next;
        }
        printf("%d\n", dest->key);
    }

    post_order_list_delete(p);
} 

// src->key < dest->key

Node * prev_element_greedy_direct(Node * src, Node * dest, Node * curr) {

    Node * best = NIL;
    Node * aux;

    do {
        curr = rb_tree_predecessor(curr);
        aux = rb_tree_maximum(curr->neigh_rb);
        if (curr->key + aux->key >= dest->key)
            best = curr;
    } while (curr->key > src->key);

    return best;
}

bool shortest_sub_path_direct(Node * src, Node * dest, Node * curr) {

    bool flag;

    if (curr == NIL) {
        printf("nessun percorso\n");
        return false;
    }
    else {
        if (curr->key == src->key) {
            return true;
        }
        else if (curr->key > src->key) {
            curr = prev_element_greedy_direct(src, dest, curr);
            flag = shortest_sub_path_direct(src, curr, curr);
            if (flag)
                printf("%d ", curr->key);
            return flag;
        }
        else
            return false;
    }
}

// The following procedure compile the primary data structure. A node
// is an highway station. Each Highway station has a subtree of nodes, which
// are veichles with a given autonomy.

RB_TREE * tree_compiler(RB_TREE * T) {

    int val; // key of a node of the first rb
    int num; // number of elements assosiated with that element
    int metric_offset; // autonomy of a car
    int src, dest;
    char s[30];
    Node * node, * sub_node;
    Node * src_node, * dest_node;
    RB_TREE * sub_tree;

    while (!feof(stdin)) {

        memset(s, '0', sizeof(s));

        if (scanf("%s", s) == 1) {

            if (strcmp(s, "aggiungi-stazione") == 0) {

                if (scanf("%d", &(val)) == 1 && scanf("%d", &(num)) == 1) {
                
                    node = rb_tree_search_iterative(T->root, val);

                    if (node == NIL) {

                        rb_insert(&(T->root), val);
                        node = rb_tree_search_iterative(T->root, val);
                        sub_tree = create_rb_tree();
                        node->neigh_rb = sub_tree->root;
                        printf("aggiunta\n");

                        for (int i = 0; i < num; i++) {
                            if (scanf("%d", &(metric_offset)) == 1)
                                rb_insert(&(node->neigh_rb), metric_offset);
                        }
                        if (num == 0) {
                            metric_offset = 0;
                            rb_insert(&(node->neigh_rb), metric_offset);
                        }
                    }
                    else {
                        printf("non aggiunta\n");
                    }
                }
            }

            if (strcmp(s, "demolisci-stazione") == 0) {

                if (scanf("%d", &(val)) == 1) {
                    node = rb_tree_search_iterative(T->root, val);
                    if (node != NIL) {
                        post_order_rb_delete(node->neigh_rb);
                        rb_delete(&(T->root), node);
                        printf("demolita\n");
                    }
                    else {
                        printf("non demolita\n");
                    }
                }
            }

            if (strcmp(s, "aggiungi-auto") == 0) {

                if (scanf("%d", &(val)) == 1 && scanf("%d", &(metric_offset)) == 1) {

                    node = rb_tree_search_iterative(T->root, val);

                    if (node != NIL) {
                
                        if (node->neigh_rb == NIL) {
                            sub_tree = create_rb_tree();
                            node->neigh_rb = sub_tree->root;
                        }
                        rb_insert(&(node->neigh_rb), metric_offset);
                        printf("aggiunta\n");
                    }
                    else {
                        printf("non aggiunta\n");
                    }
                }
            }

            if (strcmp(s, "rottama-auto") == 0) {

                if (scanf("%d", &(val)) && scanf("%d", &(metric_offset)) == 1) {

                    node = rb_tree_search_iterative(T->root, val);

                    if (node != NIL) {

                        sub_node = rb_tree_search_iterative(node->neigh_rb, metric_offset);
                        if (sub_node != NIL) {
                            rb_delete(&(node->neigh_rb), sub_node);
                            printf("rottamata\n");
                        }
                        else {
                            printf("non rottamata\n");
                        }
                    }
                    else {
                        printf("non rottamata\n");
                   }
                }
            }

        
            if (strcmp(s, "pianifica-percorso") == 0) {

                if (scanf("%d", &(src)) == 1 && scanf("%d", &(dest)) == 1) {

                    if (src == dest)
                        printf("%d\n", src);
                    else {

                        src_node = rb_tree_search_iterative(T->root, src);
                        dest_node = rb_tree_search_iterative(T->root, dest);

                        if (src < dest) {
                            if (shortest_sub_path_direct(src_node, dest_node, dest_node))
                                printf("%d\n", dest_node->key);
                        }
                        else if (src > dest) {
                            list_printer_undirect(src_node, dest_node);
                        }
                    }
                }
            }
        }
    }

    return T;
}

// driver code

int main() {

    NIL->color = 'B';

    RB_TREE * tree = create_rb_tree();
    tree = tree_compiler(tree);

    return 0;
}