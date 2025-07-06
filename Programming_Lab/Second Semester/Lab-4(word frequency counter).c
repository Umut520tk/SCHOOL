#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct wordCloud {
    char words[100][50];
    int counts[100];
};
void countWords(FILE *,struct wordCloud *);

int main(){

    FILE *fptr = fopen("sentences.txt","r");
    if (fptr == NULL) {
        printf("Error opening file");
        return 1;
    }

    struct wordCloud myCloud = {.counts = {0}};
    countWords(fptr,&myCloud);
    fclose(fptr);

    fptr = fopen("word_frequencies.txt","w");
    if (fptr == NULL) {
        printf("Error opening file");
        return 1;
    }

    for (size_t i = 0; i < sizeof(myCloud.words) / sizeof(myCloud.words[0]); i++)
    {   
        if (strcmp(myCloud.words[i],"") != 0)
        {
            fprintf(fptr,"%s : %d\n",myCloud.words[i],myCloud.counts[i]);
        }
    }

    fclose(fptr);
    return 0;
}
void countWords(FILE *fptr,struct wordCloud *Words){
    char buff[1000];
    int index = 0;
    while (fgets(buff,sizeof(buff),fptr))
    {
        char* token = strtok(buff, " ");
        while (token != NULL) {
            printf(" %s\n", token);
            int all_checked = 0;
            for (size_t i = 0; i < 100; i++)
            {
                if (strcmp(Words->words[i],token) == 0)
                {
                    Words->counts[i]++;
                    all_checked++;
                    break;
                }
            }
            if (all_checked == 0 && strlen(token) > 4)
            {
                strcpy(Words->words[index],token);
                Words->counts[index]++;
                index++;
            }
            token = strtok(NULL, " ");
        }
    }
}