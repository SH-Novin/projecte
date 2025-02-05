#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct doll {
    int id;
    struct doll *inside;
    struct doll *next;
};

void Free_Dolls(struct doll *head) {
    while (head != NULL) {
        Free_Dolls(head->inside);
        struct doll *temp = head;
        head = head->next;
        free(temp);
    }
}

struct doll *Add_Doll(struct doll **current, int id) {
    struct doll *new_doll = malloc(sizeof(struct doll));
    new_doll->id = id;
    new_doll->inside = NULL;
    new_doll->next = NULL;

    if (*current == NULL) {
        *current = new_doll;
    } else {
        new_doll->next = (*current)->next;
        (*current)->next = new_doll;
    }
    return new_doll;
}

void Attach_Doll(struct doll **current, struct doll **alone_doll) {
    if (*current == NULL) {
        *current = *alone_doll;
    } else {
        (*alone_doll)->next = (*current)->next;
        (*current)->next = *alone_doll;
    }
}

struct doll *Deattach_Doll(struct doll **previous) {
    if (!previous || !*previous) return NULL;

    struct doll *temp = (*previous)->next;
    if (!temp) return NULL;

    (*previous)->next = temp->next;
    temp->next = NULL;
    return temp;
}

struct doll *Attach_Inside_With_Sort(struct doll **container, struct doll **alone_doll) {
    if (!container || !alone_doll || !*alone_doll) return NULL;

    if (!(*container)->inside) {
        (*container)->inside = *alone_doll;
    } 
    else if ((*container)->inside->id > (*alone_doll)->id) {
        (*alone_doll)->next = (*container)->inside;
        (*container)->inside = *alone_doll;
    } 
    else {
        struct doll **doll_ptr = &((*container)->inside);
        while ((*doll_ptr)->next && (*doll_ptr)->next->id < (*alone_doll)->id) {
            doll_ptr = &((*doll_ptr)->next);
        }
        Attach_Doll(doll_ptr, alone_doll);
    }
    return *alone_doll;
}

void Empty_Doll(struct doll **current) {
    if (!current || !*current) return;

    struct doll *temp = (*current)->next;
    (*current)->next = (*current)->inside;
    (*current)->inside = NULL;

    while ((*current)->next) {
        current = &((*current)->next);
    }
    (*current)->next = temp;
}

int Count_Horizantaly(struct doll **current) {
    int count = 0;
    while (*current) {
        count++;
        current = &((*current)->next);
    }
    return count;
}

int Count_Inside(struct doll **current) {
    if (!current || !*current) return 0;
    return 1 + Count_Inside(&(*current)->inside) + Count_Inside(&(*current)->next);
}

struct doll *Get_Address_by_index(struct doll **current, int index) {
    int i = 1;
    while (i < index && *current) {
        current = &((*current)->next);
        i++;
    }
    return *current;
}

void Sort_Descending(int arr[], int n) {
    int i = 0;
    while (i < n-1) {
        int j = 0;
        while (j < n-i-1) {
            if (arr[j] < arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
            j++;
        }
        i++;
    }
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    
    struct doll *head = NULL;
    struct doll *current = Add_Doll(&head, 1);
    
    int i = 2;
    while (i <= n) {
        current = Add_Doll(&current, i);
        i++;
    }

    while (q--) {
        char cmd[20];
        scanf("%s", cmd);

        if (strcmp(cmd, "put") == 0) {
            int k, index;
            scanf("%d %d", &k, &index);
            struct doll *target = Get_Address_by_index(&head, index);
            
            int inputs[k];
            int a = 0;
            while (a < k) {
                scanf("%d", &inputs[a]);
                a++;
            }
            
            Sort_Descending(inputs, k);
            
            int b = 0;
            while (b < k) {
                int j = inputs[b];
                struct doll *to_attach = NULL;
                
                if (j == 1) {
                    to_attach = head;
                    head = head->next;
                    if (to_attach) to_attach->next = NULL;
                } 
                else {
                    struct doll *parent = Get_Address_by_index(&head, j-1);
                    to_attach = Deattach_Doll(&parent);
                }
                
                if (to_attach) {
                    Attach_Inside_With_Sort(&target, &to_attach);
                }
                b++;
            }
        } 
        else if (strcmp(cmd, "empty") == 0) {
            int index;
            scanf("%d", &index);
            struct doll *target = Get_Address_by_index(&head, index);
            if (target) Empty_Doll(&target);
        } 
        else if (strcmp(cmd, "main_dolls_count") == 0) {
            printf("%d\n", Count_Horizantaly(&head));
        } 
        else if (strcmp(cmd, "count") == 0) {
            int index;
            scanf("%d", &index);
            struct doll *target = Get_Address_by_index(&head, index);
            printf("%d\n", target ? Count_Inside(&target->inside) + 1 : 0);
        } 
        else if (strcmp(cmd, "get_id") == 0) {
            int index;
            scanf("%d", &index);
            struct doll *target = Get_Address_by_index(&head, index);
            printf("%d\n", target ? target->id : 0);
        }
    }

    Free_Dolls(head);
    return 0;
}