#include "haffman.h"



int EvalueateFrequences(int * frequences, FILE* stream) {
    int b;
    while((b = fgetc(stream)) != EOF) {
        frequences[b]++;
    }
    return 0;
}



int Compress(char *filename, char *resultFilename) {
    int frequences[256] = {0};
    FILE * input = fopen(filename, "rb");
    List * list = (List*)malloc(sizeof (list));
    if (input == NULL) {
        return 1;
    }
    int res = EvalueateFrequences(frequences, input);
    if (res) {
        return res;
    }
    MakeList(frequences, list);
    PrintList(list);
    return 0;
}

void ListInsert(int Char, int Freq, List* list) {
    Node * newNode = (Node*)malloc(sizeof (Node));
    newNode->Char = Char;
    newNode->Freq = Freq;
    newNode->next = NULL;
    if (list->Head == NULL) {
        list->Head = newNode;
    } else {
        Node * ptr = NULL;
        if (list->Head->Freq < newNode->Freq) {
            Node * nextNode = list->Head;
            list->Head = newNode;
            newNode->next = nextNode;
            return;
        }
        for (ptr = list->Head; ptr->next != NULL; ptr = ptr->next) {
            if (ptr->next->Freq < newNode->Freq) {
                break;
            }
        }
        Node * nextNode = ptr->next;
        ptr->next = newNode;
        newNode->next = nextNode;
    }
}

void MakeList(int *frequnces, List *list) {
    int i = 0;
    for (i = 0; i < 256; i++) {
        ListInsert(i, frequnces[i], list);
    }
}

void PrintList(List *list) {
    Node * ptr = NULL;
    for (ptr = list->Head; ptr; ptr = ptr->next) {
        printf("%d -- %d\n", ptr->Char, ptr->Freq);
    }
}

void MakeTree(Tree *tree, List *list) {
    if (list->Head) {
        Node * ptr = list->Head;
        for (; ptr; ptr = ptr->next) {
            Treenode * newNode = (Treenode *)malloc(sizeof (Treenode));
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->Char = ptr->Char;
            newNode->Freq = ptr->Freq;
        }
    }
}
