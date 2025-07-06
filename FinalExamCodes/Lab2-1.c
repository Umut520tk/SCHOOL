#include <stdio.h>


typedef struct Students
{
    char name[50];
    int age;
    float gpa;
}Students;


int main(){

    Students student;

    printf("Please enter your students detail: [Name] [Age] [Gpa] \n  ");

    scanf("%s %d %f",&student.name,&student.age,&student.gpa);


    /*
    printf("Name: ");
    scanf("%[^\n]",&student.name);

    printf("age: ");
    scanf("%d",&student.age);

    printf("gpa: ");
    scanf("%f",&student.gpa);
    */

    printf("\nName: %s\n",student.name);
    printf("age: %d\n",student.age);
    printf("gpa: %f\n",student.gpa);

    return 0;
}