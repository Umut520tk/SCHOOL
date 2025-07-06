#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>


#define MAX_QUESTIONS 100
#define MAX_WORLDCLOUD 200
#define MAX_CATEGORY 100
#define MAX_LINE_LENGTH 256
#define MAX_PARTICIPANTS 100

struct Question{
    char category[50];
    char question[200];
    char choices[4][100];
    char correctAnswer;
    int difficulty;
};

struct Participant{
    char name[50];
    int date; 
    char phoneNumber[100];
    char address[50];
    struct Question answeredQuestions[5];
    int tier;
    int prize;
    bool played;
    bool fiftyFifty;
    bool doubleDip;
};

struct QuestionList {

    struct Question *questionList;

    char wordCloud[MAX_WORLDCLOUD][25];
    struct Question questionWordCloud[MAX_WORLDCLOUD][MAX_QUESTIONS];

    char category[MAX_CATEGORY][25];
    struct Question questionCategory[MAX_WORLDCLOUD][MAX_QUESTIONS];

};

struct Statistic {
    char mostSuccefulContents[100];
    char mostCorreclyAnswered_Category[100];
    char mostBadlyAnswered_Category[100];
    float ageGroup[3];
    float ageGroupSize[3];
    char highestCity[100];

    int questionsCategory[MAX_CATEGORY];
    int contents[MAX_PARTICIPANTS];
};

struct QuestionList questions;
struct Participant *participants;
struct Statistic statistic;

int questionCount = 0;
int participantsCount = 0;
int indexWordCloud = 0;
int indexCategory = 0;
int currentTimeTaken = 0;
int currentParticipant;
int prevTime = 0;

bool askingQuestions = false;
bool questionsUploded = false;
bool participantsUploded = false;
bool stop_Gamefunction = false;
void sortQuestionsBydiffculty_WordCloud();

int countTheFile(FILE* file){
    int lines = 0;
    char buffer[100];

    while (fgets(buffer, sizeof(buffer), file)) {
        lines++;
    }
    rewind(file);  
    return lines;
}
void defineWordCloud(struct Question question){
    const char nonWordClouds[][100] = {"smallest","table","closest","`print(2**3)`","Which","which","with","does","200","two","for","was","off","own","his","The","the","has","Who","Lis","and","that","What","Call"};
    char questionCopy[200];
    strcpy(questionCopy, question.question);
    bool nonWord = false;
    char* token = strtok(questionCopy, " ");
    while(token != NULL){
        bool notExist = false;  
        
        for (size_t i = 0; i < MAX_WORLDCLOUD; i++)
        {
            if (strcmp(questions.wordCloud[i], token) == 0)
            {
                for (size_t j = 0; j < MAX_QUESTIONS ; j++)
                {
                    if (questions.questionWordCloud[i][j].question[0] == '\0')
                    {
                        questions.questionWordCloud[i][j] = question;
                        break;
                    }   
                }
                notExist = true;
                break;
            }
        }
        if(!notExist && strlen(token)>=3){
            for (size_t i = 0; i < sizeof(nonWordClouds)/sizeof(nonWordClouds[0]); i++)
            {
                if (strcmp(nonWordClouds[i],token) == 0)
                {
                    nonWord = true;
                    break;;
                }
            }
            if (!nonWord)
            {
                strcpy(questions.wordCloud[indexWordCloud],token);
                for (size_t j = 0; j < MAX_QUESTIONS ; j++)
                    {
                        if (questions.questionWordCloud[indexWordCloud][j].question[0] == '\0')
                        {
                            questions.questionWordCloud[indexWordCloud][j] = question;
                            break;
                        }   
                    }
                indexWordCloud++;
            }
            else nonWord = false;
        }
        token = strtok(NULL, " ");
    }
}
void defineCategory(struct Question question){
    bool notExist = false;  
        
    for (size_t i = 0; i < MAX_CATEGORY; i++)
    {
        if (strcmp(questions.category[i], question.category) == 0)
        {
            for (size_t j = 0; j < MAX_QUESTIONS ; j++)
            {
                if (questions.questionCategory[i][j].category[0] == '\0')
                {
                    questions.questionCategory[i][j] = question;
                    break;
                }
            }                   
            notExist = true;
            break;
        }
    }
        if(!notExist){
            strcpy(questions.category[indexCategory],question.category);

            questions.questionCategory[indexCategory][0] = question;
                        
            indexCategory++;
        }
    
}
int loadQuestions(char *filename) {
    FILE *file = fopen(filename, "r");
    questionCount = 0;
    if (!file) {
        printf("Sorular dosyası açılamadı! Lütfen Tekrar Deneyiniz\n");
        return -1;
    }
    free(questions.questionList);
    questions.questionList = (struct Question *)calloc(countTheFile(file),sizeof(struct Question));
    while (fscanf(file, "%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%c#%d\n",
                  questions.questionList[questionCount].category,
                  questions.questionList[questionCount].question,
                  questions.questionList[questionCount].choices[0],
                  questions.questionList[questionCount].choices[1],
                  questions.questionList[questionCount].choices[2],
                  questions.questionList[questionCount].choices[3],
                  &questions.questionList[questionCount].correctAnswer,
                  &questions.questionList[questionCount].difficulty) == 8) 
    {
        defineWordCloud(questions.questionList[questionCount]);
        defineCategory(questions.questionList[questionCount]);
        questionCount++;
    }
    sortQuestionsBydiffculty_WordCloud();
    fclose(file);
    questionsUploded = true;
}
int get_questions_by_word_cloud_as_index(char str[50]){
    for (size_t i = 0; i < MAX_WORLDCLOUD; i++)
    {
        if (strcmp(questions.wordCloud[i],str) == 0)
        {
            return i;
        }
    }
    return -1;
}
int get_questions_by_category_as_index(char str[50]){
    for (size_t i = 0; i < MAX_CATEGORY; i++)
    {
        if (strcmp(questions.category[i],str) == 0)
        {
            return i;
        }
    }
    return -1;
}
int askQuestion(struct Question q,int currentParticipant) {
    bool UsedFiftyFifty = false;
    bool UsedDoubleDip = false;
    srand(time(NULL));
    printf("%s\tDiffculty: %-4d\n", q.question,q.difficulty);
    while (1)
    {
        if (UsedFiftyFifty && participants[currentParticipant].fiftyFifty)
        {
            participants[currentParticipant].fiftyFifty = false;
            char choices[] = {'A','B','C','D'};
            int rnd = rand() % 4;
            while (choices[rnd] == q.correctAnswer)
            {
                rnd = rand() % 4;
            }
            choices[rnd] = q.correctAnswer;
            strcpy(q.choices[rnd],"");

            while (choices[rnd] == q.correctAnswer)
            {
                rnd = rand() % 4;
            }
            strcpy(q.choices[rnd],"");
        }

        switch (participants[currentParticipant].doubleDip&&participants[currentParticipant].fiftyFifty)
        {
        case true:
            printf("A) %-20s\t\tMoney: $%-4d\nB) %-20s\t\tDouble Dip\nC) %-20s\t\t50%% \nD) %-20s\n", q.choices[0],participants[currentParticipant].prize, q.choices[1], q.choices[2], q.choices[3]);
            break;
        case false:
            if (participants[currentParticipant].fiftyFifty)
            {
                printf("A) %-20s\t\tMoney: $%-4d\nB) %-20s\t\t50%%\nC) %-20s\t\t-\nD) %-20s\n", q.choices[0],participants[currentParticipant].prize, q.choices[1], q.choices[2], q.choices[3]);
            }
            else if(participants[currentParticipant].doubleDip){
                printf("A) %-20s\t\tMoney: $%-4d\nB) %-20s\t\tDouble Dip\nC) %-20s\t\t-\nD) %-20s\n", q.choices[0],participants[currentParticipant].prize, q.choices[1], q.choices[2], q.choices[3]);
            }
            else{
                printf("A) %-20s\t\tMoney: $%-4d\nB) %-20s\t\t-\nC) %-20s\t\t-\nD) %-20s\n", q.choices[0],participants[currentParticipant].prize, q.choices[1], q.choices[2], q.choices[3]);
            }
            break;
        default:
            printf("A) %-20s\t\tMoney: $%-4d\nB) %-20s\nC) %-20s\nD) %-20s\n", q.choices[0],participants[currentParticipant].prize, q.choices[1], q.choices[2], q.choices[3]);
            break;
        }
        

        printf("> Enter your choice (A, B, C, D) (E:Exit And Keep Your Money): ");
        char answer[25];

        scanf(" %[^\n]", &answer);
        pthread_testcancel();

        if (toupper(answer[0]) == q.correctAnswer) {
            printf("Correct answer!\n");
            return 1;
        }else if(toupper(answer[0]) == 'E') {return-1;} 
        else if(strcmp(answer,"Double Dip") == 0 && participants[currentParticipant].doubleDip){
            participants[currentParticipant].doubleDip = false;
            UsedDoubleDip = true;
            puts("\n");
        }
        else if (strcmp(answer,"Double Dip") == 0){
            printf("\nYou Already Used Your Douple Dip!!\n\n");
        }
        else if(UsedDoubleDip){
            printf("\n!You Entered Wrong Answer Try Again!\n");
            UsedDoubleDip = false;
        }
        else if(strcmp(answer,"50%") == 0 && participants[currentParticipant].fiftyFifty){
            UsedFiftyFifty = true;
            puts("\n");
        }
        else if (strcmp(answer,"50%") == 0){
            printf("\nYou Already Used Your 50%%!!\n\n");
        }
        else
        {
            printf("Wrong answer! Correct answer: %c\n", q.correctAnswer);
            return 0;
        }
    }
}
void sortQuestionsBydiffculty_WordCloud(){
    struct Question holder;
    for (size_t i = 0; i < MAX_WORLDCLOUD; i++)
    {
        if (questions.wordCloud[i][0] == '\000')break;
        
        for (size_t j = 0; j < MAX_QUESTIONS; j++)
        {
            for (size_t k = 0; k < MAX_QUESTIONS - 1; k++)
            {
                if (questions.questionWordCloud[i][k].difficulty > questions.questionWordCloud[i][k + 1].difficulty && questions.questionWordCloud[i][k + 1].question[0] != '\000'&& questions.questionWordCloud[i][k].question[0] != '\000')
                {
                    holder = questions.questionWordCloud[i][k + 1];
                    questions.questionWordCloud[i][k + 1] = questions.questionWordCloud[i][k];
                    questions.questionWordCloud[i][k] = holder;
                }
                else if (questions.questionWordCloud[i][k + 1].question[0] == '\000'|| questions.questionWordCloud[i][k].question[0] == '\000') break;
            }
        }

    }
    
}
int loadParticipants(char *filename){
    FILE *file = fopen(filename, "r");
    participantsCount = 0;
    if (!file) {
        printf("Could not open the questions file! Please try again.\n");
        return -1;
    }
    free(participants);
    participants = (struct Participant *)calloc(countTheFile(file),sizeof(struct Participant));

    while (fscanf(file, "%[^#]#%d#%[^#]#%[^\n]\n",participants[participantsCount].name,
        &participants[participantsCount].date,
        &participants[participantsCount].phoneNumber,
    participants[participantsCount].address) == 4) 
    {
        participants[participantsCount].fiftyFifty = true;
        participants[participantsCount].doubleDip = true;
        participants[participantsCount].played = false;
        participantsCount++;
    }
    fclose(file);
    participantsUploded = true;
}
void printWordCloud(int diff){
    for (size_t i = 0; i < 50; i++)
    {
        printf("-");
    }
    printf("\nWord Cloud :\n");

    for (size_t i = 0; i < MAX_WORLDCLOUD; i++)
    {
        bool diff_in= false;
        if (questions.wordCloud[i][0] != '\000')
        {
            for (size_t j = 0; j < MAX_QUESTIONS; j++)
            {
                if (questions.questionWordCloud[i][j].difficulty == diff && questions.questionWordCloud[i][j].question[0] != '\000')
                {
                    diff_in = true;
                    break;
                }
                else if (questions.questionWordCloud[i][j].question[0] == '\000') break;
            }
            if (diff_in)
            {
                printf("%s \t",questions.wordCloud[i]);
                if ((i + 1)%6 == 0)
                {
                    puts("");
                }
            }
        }
    }

    puts("\n");
}
struct Question choseeQuestion(int wordCloud,int diff){
    struct Question question = {"Couldn't find exact"};
    for (size_t i = 0; i < MAX_QUESTIONS; i++){
        {
            if (questions.questionWordCloud[wordCloud][i].difficulty == diff && questions.questionWordCloud[wordCloud][i].question[0] != '\000') return questions.questionWordCloud[wordCloud][i];
            else if(questions.questionWordCloud[wordCloud][i].question[0] == '\000')return question;        
        }
    }
    
}
void determineStatistic(){
    int current = statistic.questionsCategory[0];
    int current_index = 0;
    for (size_t i = 0; i < MAX_CATEGORY; i++)
    {
        if (current < statistic.questionsCategory[i])
        {
            current = statistic.questionsCategory[i];
            current_index = i;
        }
    }
    strcpy(statistic.mostCorreclyAnswered_Category,questions.category[current_index]);

    current = statistic.questionsCategory[0];
    current_index = 0;
    for (size_t i = 0; i < MAX_CATEGORY; i++)
    {
        if (current > statistic.questionsCategory[i])
        {
            current = statistic.questionsCategory[i];
            current_index = i;
        }
    }
    strcpy(statistic.mostBadlyAnswered_Category,questions.category[current_index]);

    char frequancy_name[participantsCount][25];
    int *frequancy_int = (int *)calloc(participantsCount,sizeof(int));
    int index = 0;
    for (size_t i = 0; i < participantsCount; i++)
    {   
        bool isexist = false;
        for (size_t j = 0; j < participantsCount; j++)
        {
            if (strcmp(frequancy_name[j],participants[i].address) == 0)
            {
                frequancy_int[j]++;
                isexist = true;
                break;
            }
        }
        if (!isexist) {
            strcpy(frequancy_name[index],participants[i].address);
            frequancy_int[index]++;
            index++;
        }
    }
    
    current = frequancy_int[0];
    current_index = 0;
    for (size_t i = 0; i < participantsCount; i++)
    {
        if (current < frequancy_int[i])
        {
            current = frequancy_int[i];
            current_index = i;
        }
    }

    for (size_t i = 0; i < participantsCount; i++)
    {   
        statistic.ageGroup[i] = 0;
        statistic.ageGroupSize[i] = 0;
    }
    
    strcpy(statistic.highestCity,frequancy_name[current_index]);

    int age;
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    current = statistic.contents[0];
    current_index = 0;
    for (size_t i = 0; i < participantsCount; i++)
    {
        if (current < statistic.contents[i])
        {
            current = statistic.contents[i];
            current_index = i;
        }
        age = tm.tm_year + 1900 - participants[i].date;
        if (age <= 30 )
        {
            statistic.ageGroup[0] += statistic.contents[i];
            statistic.ageGroupSize[0]++;
        }
        else if(age > 30 && age <= 50)
        {
            statistic.ageGroup[1] += statistic.contents[i];
            statistic.ageGroupSize[1]++;

        }
        else{
            statistic.ageGroup[2] += statistic.contents[i];
            statistic.ageGroupSize[2]++;

        }
    }
    strcpy(statistic.mostSuccefulContents,participants[current_index].name);
    free(frequancy_int);
}
void deleteQuestionAndWordCloud(struct Question question){
    bool anyQuestionsExist = false;
    for (size_t i = 0; i < MAX_WORLDCLOUD; i++)
    {
        for (size_t j = 0; j < MAX_QUESTIONS; j++)
        {
            if (strcmp(question.question,questions.questionWordCloud[i][j].question)==0)
            {
                questions.questionWordCloud[i][j].question[0] = '\000';
                break;
            }
        }
        for (size_t j = 0; j < MAX_QUESTIONS; j++)
        {
            if (questions.questionWordCloud[i][j].question[0] != '\000')
            {
                anyQuestionsExist = true;
                break;
            }
        }
        if (!anyQuestionsExist)
        {
            questions.wordCloud[i][0] = '\000';
        }
        anyQuestionsExist = false;
    }
}
void writeHistory(struct Question question,struct Participant participant,char str[]){
    FILE* file = fopen("History.txt","a");

    fprintf(file,"'%s'#%s#%s\n",question.question,participant.name,str);
    
    fclose(file);
}
void Initializers(){
    for (size_t i = 0; i < MAX_WORLDCLOUD; i++)
    {
        for (size_t j = 0; j < 25; j++)
        {
            questions.wordCloud[i][j] = '\000';
            questions.category[i][j] = '\000';
        }
    }
    for (size_t i = 0; i < MAX_WORLDCLOUD; i++)
    {
        for (size_t j = 0; j < MAX_QUESTIONS; j++)
        {
            questions.questionCategory[i][j].question[0] = '\000';
            questions.questionWordCloud[i][j].question[0] = '\000';
            questions.questionCategory[i][j].category[0] = '\000';
            questions.questionWordCloud[i][j].category[0] = '\000';
        }
    }
    


}

void* sleepThread(void* arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    pthread_t* gameFunction = (pthread_t *)arg;
    
    while (1)
    {
        prevTime = time(NULL);
        while (askingQuestions){
            if (!askingQuestions){
                currentTimeTaken = time(NULL) - prevTime;
                prevTime = time(NULL);
            }
            else if (difftime(time(NULL),prevTime) >= 20 - currentTimeTaken){
                stop_Gamefunction = true;
                pthread_cancel(*gameFunction);
                participants[currentParticipant].tier--;
                switch (participants[currentParticipant].tier)
                {
                case 0:
                    participants[currentParticipant].prize = 0;
                    break;
                case 1:
                    participants[currentParticipant].prize = 100000;
                    break;
                case 2:
                    participants[currentParticipant].prize = 500000;
                    break;
                default:
                    break;
                }
                printf("\t\t\n\n!TIME IS OVER!(Click Enter Something To Move On)\n\n");
                puts("");
                printf("You won $%d\n\n",participants[currentParticipant].prize);
                
                return NULL;
            }
            pthread_testcancel();
        }
        pthread_testcancel();
        }
    }

void* gameThread(void* arg){
        // Enable thread cancellation
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        /* Start Competition */
        int input_int;
        char input_str[100];

        srand(time(NULL));
        currentParticipant = rand() % 5;
        while (participants[currentParticipant].played)
        {
            currentParticipant = rand() % 5;   
        }
        participants[currentParticipant].played = true;

        int all_true = 1;
        int currentWordCloud;
        int diff = 1;

        printf("\nContestant: %s\n\n",participants[currentParticipant].name);
        for (int i = 0; i < 5; i++) {
            switch (diff)
            {
            case 1:
                participants[currentParticipant].prize = 0;
                participants[currentParticipant].tier = 1; 
                break;
            case 2:
                participants[currentParticipant].prize = 20000;
                participants[currentParticipant].tier = 1;
                break;
            case 3:
                participants[currentParticipant].prize = 100000;
                participants[currentParticipant].tier = 2;
                break;
            case 4:
                participants[currentParticipant].prize = 250000;
                participants[currentParticipant].tier = 2;
                break;  
            case 5:
                participants[currentParticipant].prize = 500000;
                participants[currentParticipant].tier = 3;
            default:
                break;
            }

            printWordCloud(diff);
            printf("> Enter your selection: ");
            scanf("%s",input_str);
            pthread_testcancel();
            currentWordCloud = get_questions_by_word_cloud_as_index(input_str);

            while (currentWordCloud == -1)
            {
                pthread_testcancel();
                printf("\n> Please Enter existing Word Cloud: ");
                scanf("%s",input_str);
                pthread_testcancel();
                currentWordCloud = get_questions_by_word_cloud_as_index(input_str);
            }
            pthread_testcancel();
            struct Question currentQuestion = choseeQuestion(currentWordCloud,diff);
            deleteQuestionAndWordCloud(currentQuestion);
            //questions.wordCloud[currentWordCloud][0] = '\000'; // Deleting That Word Cloud
            askingQuestions = true;
            int result = askQuestion(currentQuestion,currentParticipant);
            if (result == 0)
            {
                participants[currentParticipant].tier -= 1;
                statistic.questionsCategory[get_questions_by_category_as_index(currentQuestion.category)]--;
                deleteQuestionAndWordCloud(currentQuestion);
                writeHistory(currentQuestion,participants[currentParticipant],"False");
                break;
            }
            else if(result == -1){
                participants[currentParticipant].tier = -1;
                statistic.questionsCategory[get_questions_by_category_as_index(currentQuestion.category)]--;
                deleteQuestionAndWordCloud(currentQuestion);
                writeHistory(currentQuestion,participants[currentParticipant],"Did Not Answered");
                break;
            }
            askingQuestions = false;
            writeHistory(currentQuestion,participants[currentParticipant],"True");
            pthread_testcancel();
            statistic.contents[currentParticipant]++;
            statistic.questionsCategory[get_questions_by_category_as_index(currentQuestion.category)]++;
            puts("\n");
            diff++;
            if (diff == 6)participants[currentParticipant].prize=1000000;
        }

        switch (participants[currentParticipant].tier)
        {
        case 0:
            participants[currentParticipant].prize = 0;
            break;
        case 1:
            participants[currentParticipant].prize = 100000;
            break;
        case 2:
            participants[currentParticipant].prize = 500000;
            break;
        default:
            break;
        }
        puts("");
        if (participants[currentParticipant].prize == 1000000)
        {
            printf("Congrulations You Correcly Answered All Questions\n\n");
            printf("You won $%d\n\n",participants[currentParticipant].prize);
        }
        else{
            printf("Wrong answer, GAME OVER!\n\n");
            printf("You Won $%d\n\n",participants[currentParticipant].prize);
        }
        
}

int main() {

    int input_int;
    char input_str[100];
    int numberOfplayed = 0;
    Initializers();
    while (1)
    {
        printf("*** MENU ***\n");
        printf("1.Load questions\n");
        printf("2.Load participants\n");
        printf("3.Start competition\n");
        printf("4.Show statistics\n");
        printf("5.Exit\n\n");

        printf("> Enter your choice: ");
        scanf("%d",&input_int);
        puts("");
        


        switch (input_int)
        {
        case 1:
            printf("\n> Enter file name to load: ");
            getchar();
            scanf("%s",input_str);
           
            if (loadQuestions(input_str) == -1)break;
            
            printf("%-25s %s\n", "Category", "Number of Questions");

            for (size_t i = 0; i < MAX_CATEGORY; i++)
            {
                if (questions.category[i][0] != '\000')
                {
                    int count = 0;
                    for (size_t j = 0; j < MAX_QUESTIONS; j++)
                    {
                        if (questions.questionCategory[i][j].category[0] != '\000')
                        {
                            count++;
                        }
                        
                    }
                    
                    printf("%-25s%d\n",questions.category[i],count);
                }
                else break;
            }
            puts("\n");
            printf("%-20s %-20s\n", "Difficulty Level", "The Number of Questions");
            int difficulty = 1;
            for (size_t i = 0; i < 5; i++)
            {
                int numberOfDifficulty = 0;
                for (size_t j = 0; j < MAX_QUESTIONS; j++)
                {
                    if (questions.questionList[j].category[0] != '\000' && questions.questionList[j].difficulty == difficulty)
                    {
                        numberOfDifficulty++;
                    }  
                    else if (questions.questionList[j].category[0] == '\000') break;
                }
                printf("%10d%\t\t%5d\n",difficulty,numberOfDifficulty);
                difficulty++;
            }

            break;
        case 2:
            printf("\n> Enter file name to load: ");
            getchar();
            scanf("%s",input_str);

            

            if (loadParticipants(input_str) == -1)break;
            

            for (size_t i = 0; i < 5; i++)
            {
                printf("Name: %s\tDate: %d\tPhoneNumber: %s\tAddress: %s\n",participants[i].name,participants[i].date,participants[i].phoneNumber,participants[i].address);
            }
            
            break;
        case 3:
            /* Checking If Questions and Participants are Uploaded */
            if (!questionsUploded)
            {
                printf("\nPlease first upload questions to the game !!.\n\n");
                break;
            }
            if (!participantsUploded)
            {
                printf("\nPlease first upload participants to the game !!.\n\n");
                break;
            }
                
            while (1)
            {
                numberOfplayed++;
                if (numberOfplayed > participantsCount)
                {
                    printf("\tAll Contestan Played The Game\n\t\tGame Over\n");
                    break;
                }
                pthread_t thread_id1;
                pthread_t thread_id2;
                pthread_create(&thread_id1, NULL, sleepThread, &thread_id2);
                pthread_create(&thread_id2, NULL, gameThread, &numberOfplayed);
                pthread_join(thread_id2, NULL);
                pthread_cancel(thread_id1);
                pthread_cancel(thread_id2);
                printf("> Next contestant? (Y/N): ");
                char input_chr;
                getchar();
                input_chr = getchar();
                if (toupper(input_chr) == 'N')break;
            }
            


            break;
        case 4:
            /* Show Statistic */
            determineStatistic();
            printf("* The most successful contestant: %s\n\n",statistic.mostSuccefulContents);
            printf("* The category with the most correctly answered : %s\n\n",statistic.mostCorreclyAnswered_Category);
            printf("* The category with the most badly answered: %s\n\n",statistic.mostBadlyAnswered_Category);
            printf("* On average, how many questions did contestants in each age group answer correctly?\n");
            printf("*- Age<=30 :%3.1lf\t30<Age<=50 :%3.1lf\tAge>50 :%3.1lf\t\n\n",statistic.ageGroup[0]/statistic.ageGroupSize[0],statistic.ageGroup[1]/statistic.ageGroupSize[0],statistic.ageGroup[2]/statistic.ageGroupSize[0]);
            printf("* The city with the highest number of participants: %s\n\n",statistic.highestCity);
            break;
        case 5:
            /* Exit */
            exit(0);
            break;
        default:
            printf("!!!Please enter valid input !!!\n");
            break;
        }
    }
    free(questions.questionList);
    free(participants);
    return 0;
}