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
    list->Size = 0;
    MakeList(frequences, list);
    PrintList(list);
    MakeTree(list);
    char ** codes = (char**)malloc(256*sizeof (char*));
    MakeCodes(list, codes);
    int i = 0;
    for (; i < 256; i++) {
        if (codes[i] != NULL) {
            printf("%s\n", codes[i]);
        }
    }

    FILE * output = fopen(resultFilename, "wb");
    if (output == NULL) {
        return 2;
    }
    fwrite(frequences, 4, 256, output);
    //PrintTree(list);
    //PrintList(list);

    rewind(input);

    int ch = 0;
    RValue result;
    result.currPos = 7;
    result.currChar = 0;
    while ((ch = fgetc(input)) != EOF) {
        result = WriteChar(codes[ch], result, output);
    }
    WriteChar("", result, output);
    fclose(output);
    return 0;
}

void ListInsert(int Char, int Freq, Node* right, Node* left, List* list) {
    list->Size++;
    Node * newNode = (Node*)malloc(sizeof (Node));
    newNode->Char = Char;
    newNode->Freq = Freq;
    newNode->next = NULL;
    newNode->left = left;
    newNode->right = right;
    if (list->Head == NULL) {
        list->Head = newNode;
    } else {
        Node * ptr = NULL;
        if (list->Head->Freq >= newNode->Freq) {
            Node * nextNode = list->Head;
            list->Head = newNode;
            newNode->next = nextNode;
            return;
        }
        for (ptr = list->Head; ptr->next != NULL; ptr = ptr->next) {
            if (ptr->next->Freq >= newNode->Freq) {
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
        if (frequnces[i]) {
            ListInsert(i, frequnces[i], NULL, NULL, list);
        }
    }
}

void PrintList(List *list) {
    Node * ptr = NULL;
    for (ptr = list->Head; ptr; ptr = ptr->next) {
        printf("%d -- %d,  ", ptr->Char, ptr->Freq);
    }
    printf("\n");
}

void MakeTree(List *list) {
    if (list->Head) {
        while (list->Size > 2) {
            list->Size-=2;
            Node * TwoLast = list->Head;
            list->Head = TwoLast->next->next;
            Node * right = TwoLast; //less
            Node * left = TwoLast->next;
            int Char = -1;
            int Freq = left->Freq+right->Freq;
            ListInsert(Char, Freq, right, left, list);
            //PrintList(list);
        }
        if (list->Size == 1) {
            return;
        } else {
            list->Size--;
            Node * TwoLast = list->Head;
            Node * right = TwoLast; //less
            Node * left = TwoLast->next;
            int Char = -1;
            int Freq = left->Freq+right->Freq;
            list->Head = NULL;
            ListInsert(Char, Freq, right, left, list);
        }
    }
}

void PrintTree(List *list) {
    PrintNode(list->Head);
}

void PrintNode(Node *node) {
    printf("Current node: %d, its frequency: %d, ", node->Char, node->Freq);
    if (node->left) {
        printf("left: %d", node->left->Freq);
    } else {
        printf("left: NULL, ");
    }
    if (node->right) {
        printf("right: %d.\n", node->right->Freq);
    } else {
        printf("right: NULL.\n");
    }
    if (node->left) {
        PrintNode(node->left);
    }
    if (node->right) {
        PrintNode(node->right);
    }
}



void MakeCodes(List *tree, char **codes) {
    char a[MAXLEN] = "";
    MakeCode(tree->Head, codes, 0, a);
}

void MakeCode(Node *node, char **codes, int length, char * curr) {
    if (node->left) {
        char a[MAXLEN];
        strcpy(a, curr);
        a[length] = '1';
        MakeCode(node->left, codes, length+1, a);
    }
    if (node->right) {
        char a[MAXLEN];
        strcpy(a, curr);
        a[length] = '0';
        MakeCode(node->right, codes, length+1, a);
    }
    if (node->left == NULL && node->right == NULL) {
        codes[node->Char] = (char*)malloc(MAXLEN*sizeof (char));
        char a[MAXLEN];
        strcpy(a, curr);
        a[length] = '\0';
        strcpy(codes[node->Char], a);
    }

}

RValue WriteChar(char* symbol, RValue curr, FILE* output) {
    RValue result = curr;
    if (strcmp(symbol, "") == 0) {//if end of string
        WriteBit(result, -1, output);
    } else {
        int i = 0;
        for (; symbol[i]; i++) {
            result = WriteBit(result, symbol[i] == '1' ? 1 : 0, output);
        }
    }
    return result;
}

RValue WriteBit(RValue curr, int bit, FILE* output) { //returns current char
    if (bit == -1) {
        if (curr.currPos != 7) {
            fputc(curr.currChar, output);
        }
        return curr;
    }
    RValue result;
    result.currPos = (curr.currPos - 1 < 0) ? 7 : curr.currPos-1;
    result.currChar = curr.currPos;
    int add = 1 << curr.currPos;
    if (bit == 1) {
        result.currChar |= add;
    }
    if (curr.currPos == 0) {
        fputc(result.currChar, output);
        result.currChar = 0;
    }
    return result;
}
