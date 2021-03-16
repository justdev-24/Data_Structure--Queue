/*==============Used Libraries==============*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
/*==============Essential Variables==============*/
int head = 0, tail = 0;
char *pdata;
char *pqueue;

/*==============Essential Variables==============*/
int getInt(int *);
void erase();
int mystrcmp(char* string1, char* string2);
void intro();
int countChars(char *filename);
void printData(char *filename);
void addToQueue(int N);
void saveToFile(char *filename);
int menu();


/*============================Fundamental Functions============================*/
int getInt(int *a){
    int n;
    do{
        n = scanf("%d", a);
        if(n<0)
            return 0;
        else if(n == 0){
            Beep(900, 400);
            printf("%s\n", "Error input! Please repeat!");
            scanf("%*c");
            
        }
    }while(n==0);
    return 1;
}

void erase(){
    free(pdata);
    free(pqueue);
    head = 0;
    tail = 0;
    pdata = NULL;
    pqueue = NULL;

}

int mystrcmp(char* string1, char* string2)
{
    int i = 0;
    int res = 0;    
    while (res == 0)
    {
        if (string1[i] > string2[i])
            res = 1;
        else if (string1[i] < string2[i])
            res = -1;
        if (string1[i] == '\0')
            break;
        i++;
    }
    return res;
}
/*==========================================Introduction==========================================*/
void intro(){
    int i,j;
    char answer[5];
    printf("\t\tGood Day!\n");
    printf("This program is specialized for copying data from one file to another.\n");
    printf("If you want to run this program enter ---> Yes\nIf you want to leave this program enter ---> No\n");
    for(;;){
        scanf("%s", answer);
        i = mystrcmp(answer,"No");
        j = mystrcmp(answer,"Yes");
        if(i == 0){
            erase();
            exit(0);
        }
        else if(j == 0)
            break;
        else{
            printf("Oops! Please repeat!\n");
        }
    }
}
/*==========================================Main Functions==========================================*/
int countChars(char *filename){
    char character;
    int count = 0;
    FILE *fptr = fopen (filename, "r");
    if (fptr == NULL) {
        printf("Error! Opening file");
        erase();
        exit(1);
    }
    character = fgetc(fptr);
    if(character == EOF){
        printf("End Of File!\n");
        erase();
        exit(1);
    }
    while(character != EOF){
        count++;
        character = fgetc(fptr);
    }
    fclose(fptr);
    return count;
}

void printData(char *filename){
    char character;
    int N, i = 0;
    N = countChars(filename);
    pdata = (char *)malloc(N * sizeof(char));
    FILE *fptr = fopen (filename, "r");
    if (fptr == NULL) {
        printf("Error! Opening file");
        erase();
        exit(1);
    }
    character = fgetc(fptr);
    if(character == EOF){
        printf("End Of File!\n");
        erase();
        exit(1);
    }
    printf("\nThere are %d chars in your file\n", N);
    while(character != EOF){
        *(pdata + i) = character;
        character = fgetc(fptr);
        printf("%c", *(pdata + i));
        i++;
    }
    fclose(fptr);
}

void addToQueue(int N){
    pqueue = (char *)malloc(N * sizeof(char));
    while(N > 0){
        pqueue[tail] = pdata[tail];
        printf("%c", *(pqueue + tail));
        tail++;
        N--;
    }

}

void saveToFile(char *filename){
    int i = 0;
    FILE *fptr = fopen(filename, "a");
    if (fptr == NULL) {
        printf("Error! Opening file");
        erase();
        exit(1);
    }
    while(tail!=head){
        *(pqueue + i) = pqueue[head];
        fputc(pqueue[head], fptr);
        head++;
        i++;
    }
    fclose(fptr);
}
/*==========================================Main Menu==========================================*/
int menu(){
    int i = 0, j = 0, k = 0;
    int opt, offer;
    const char *pr = "";
    const char *msg = "";
    const char *ms = "";
    int bytes;
    char infile[30];
    char outfile[30];
    for(;;){
    printf("\n\xB2\xB2\xB2\tWelcome to Main Menu\t\xB2\xB2\xB2\n");
    printf("Choose one of the following options\n");
    printf("1. Read data from file and print to console in the form of queue\n");
    printf("2. Remove data from queue and save to file\n");
    printf("0. Exit\n");
    
    do{
        do{
            if(i > 0)
                Beep(900, 400);
            printf("%s\n", msg);
            msg = "Error input! Please repeat!\n";
            i++;
            if(getInt(&opt) == 0)
                return 0;
        }while(opt < 0);
        msg = "";
        i = 0;
        switch (opt)
        {
            case 1:
                printf("Enter size of data in bytes to exchange: ");
                do{
                    if(k > 0)
                        Beep(900, 400);
                    printf("%s\n", ms);
                    ms = "Error input! Please repeat!\n";
                    k++;
                    if(getInt(&bytes) == 0)
                        return 0;
                }while(bytes < 0);
                ms = "";
                k = 0;
                printf("Enter input file name\n");
                scanf(" %30[^\n]", infile);
                printData(infile);
                addToQueue(bytes);
                Sleep(500);
                break;
            case 2:
                printf("Enter output file name\n");
                scanf(" %30[^\n]", outfile);
                saveToFile(outfile);
                free(pqueue);
                pqueue = NULL;
                printf("Data is saved to file and removed from the queue\n");                
                Sleep(500);
                break;
            case 0:
                erase();
                exit(0);
            default:
                printf("Please choose only 1 or 2!\n");
                break;
        }
    }while (opt > 2);
    printf("\n\nGreat! Do you want to continue?\nContinue --> 1\t\tExit -- > 0\n\n");
    do{
        do{
            if(j > 0)
                Beep(900, 400);
            printf("%s\n", pr);
            pr = "Error input! Please repeat!\n";
            j++;
            if(getInt(&offer) == 0)
                return 0;
        }while(offer < 0);
        pr = "";
        j = 0;
        switch (offer)
        {
        case 1:
            break;
        case 0:
            erase();
            exit(0);
        default:
            printf("Please choose only 1 or 0!\n");
            break;
        }
     }while(offer > 1);
     }
}
/*==========================================THE END==========================================*/
