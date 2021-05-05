#include <stdio.h>
#include <stdlib.h>

typedef unsigned short int boolean;
#define TRUE 1
#define FALSE 0

struct listA {
    int value;
    struct listA *next_ptr;
};

void init_A(struct listA **ptr);

void visit_A(struct listA *ptr);

boolean pre_insert_A(struct listA **ptr, int value);

boolean suf_insert_A(struct listA **ptr, int value);


struct listB {
    int value;
    int occur;
    struct listB *next_ptr;
};

void init_B(struct listB **ptr);

void visit_B(struct listB *ptr);

boolean pre_insert_B(struct listB **ptr, int value, int occur);

boolean suf_insert_B(struct listB **ptr, int value, int occur);

boolean consume_first(struct listA **ptr, int *value);

void remove_equal(struct listA **src_ptr, struct listB **dst_ptr);

int main() {
    struct listA *src_ptr;
    struct listB *dst_ptr;

    init_A(&src_ptr);
    init_B(&dst_ptr);

    int s, value;
    boolean exit = FALSE;
    while (exit == FALSE) {
        printf("\n Premere 1 per inserire un elemento in coda alla lista A \n Premere 2 stampare la lista A \n Premere 3 eseguire la funzione  ");
        scanf("%d", &s);
        switch (s) {
            case 1: {
                printf("\n Inserire valore: ");
                scanf("%d", &value);
                suf_insert_A(&src_ptr, value);
                break;

            }
            case 2: {
                printf("\n Lista A: ");
                visit_A(src_ptr);
                break;
            }
            case 3: {
                remove_equal(&src_ptr, &dst_ptr);
                printf("\n Lista A: ");
                visit_A(src_ptr);
                printf("\n Lista B: ");
                visit_B(dst_ptr);
                exit = TRUE;
                break;
            }
            default:
                printf("\n Opzione non valida \n");
        }
    }
    return 0;
}

void init_A(struct listA **ptr) {
    *ptr = NULL;
}

void visit_A(struct listA *ptr) {
    while (ptr != NULL) {
        printf("%d ", ptr->value);
        ptr = ptr->next_ptr;
    }
    printf("\n");
}

boolean pre_insert_A(struct listA **ptr, int value) {
    struct listA *tmp_ptr;
    tmp_ptr = (struct listA *) malloc(sizeof(struct listA));
    if (tmp_ptr != NULL) {
        tmp_ptr->value = value;
        tmp_ptr->next_ptr = *ptr;
        *ptr = tmp_ptr;
        return TRUE;
    } else
        return FALSE;
}

boolean suf_insert_A(struct listA **ptr, int value) {
    while (*ptr != NULL)
        ptr = &((*ptr)->next_ptr);
    if (pre_insert_A(ptr, value))
        return TRUE;
    else
        return FALSE;
}

void init_B(struct listB **ptr) {
    *ptr = NULL;
}

void visit_B(struct listB *ptr) {
    while (ptr != NULL) {
        printf("[%d,%d] ", ptr->value, ptr->occur);
        ptr = ptr->next_ptr;
    }
    printf("\n");
}

boolean pre_insert_B(struct listB **ptr, int value, int occur) {
    struct listB *tmp_ptr;
    tmp_ptr = (struct listB *) malloc(sizeof(struct listB));
    if (tmp_ptr != NULL) {
        tmp_ptr->value = value;
        tmp_ptr->occur = occur;
        tmp_ptr->next_ptr = *ptr;
        *ptr = tmp_ptr;
        return TRUE;
    } else
        return FALSE;
}

boolean suf_insert_B(struct listB **ptr, int value, int occur) {
    while (*ptr != NULL)
        ptr = &((*ptr)->next_ptr);
    if (pre_insert_B(ptr, value, occur))
        return TRUE;
    else
        return FALSE;
}

boolean consume_first(struct listA **ptr, int *value) {
    struct listA *tmp_ptr;
    if (*ptr != NULL) {
        tmp_ptr = *ptr;
        *value = tmp_ptr->value;
        *ptr = (*ptr)->next_ptr;
        free(tmp_ptr);
        return TRUE;
    } else
        return FALSE;
}

void remove_equal(struct listA **src_ptr, struct listB **dst_ptr) {
    boolean is_done = FALSE, end = FALSE;
    int tmp = (*src_ptr)->value;
    struct listA *succ;
    succ = (*src_ptr)->next_ptr;
    while (succ != NULL) {
        int count = 0;
        while ((*src_ptr)->value == succ->value && end == FALSE) {
            consume_first(src_ptr, &(succ->value));
            count += 1;
            is_done = TRUE;
            if (succ->next_ptr != NULL)
                succ = succ->next_ptr;
            else {
                suf_insert_B(dst_ptr, tmp, count);
                end = TRUE;
            }
        }
        if (is_done == TRUE && count != 0 && end == FALSE) { // se non sono alla fine e ho eliminato elementi
            suf_insert_B(dst_ptr, tmp, count);
            dst_ptr = &((*dst_ptr)->next_ptr);
        } else if (end == FALSE) {                           // se non sono alla fine
            src_ptr = &((*src_ptr)->next_ptr);
            tmp = (*src_ptr)->value;
            succ = succ->next_ptr;
        } else                                               // se sono alla fine
            succ = NULL;
    }
}