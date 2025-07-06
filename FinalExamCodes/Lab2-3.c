#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee
{
    int id;
    char name[100];
    float salary;
}employee;

int main(){

    employee *employees = (employee *)malloc(5 * sizeof(employee));
    /*
    printf("Please Enter Your Employee's Data:\n");

    for (size_t i = 0; i < 5; i++)
    {
        printf("\nEmployee(%d) : \nid: ",i);
        scanf("%d",&((employees + i)->id));        
        printf("Name: ");
        scanf("%s",&((employees + i)->name));
        printf("Salary: ");
        scanf("%f",&((employees + i)->salary)); 
    }
    
    FILE *fptr = fopen("employees.txt","w");

    for (size_t i = 0; i < 5; i++)
    {
        fprintf(fptr,"Employee(%d) :\tid: %d\tname: %s\tsalary: %f\n",i,employees[i].id,employees[i].name,employees[i].salary);       
    }

    fclose(fptr);
    */
    FILE *fptr_in = fopen("employees.txt","r");

    int id;
    char name[100];
    float salary;
    char den[100];

    
    for (size_t i = 0; i < 5; i++)
    {
        sprintf(den,"Employee(%d) :\tid: %%d\tname: %%s\tsalary: %%f\n",i);
        fscanf(fptr_in,den,&id,name,&salary);
        printf("Employee(%d) :\tid: %d\tname: %s\tsalary: %f\n",i,id,name,salary);
    }
    

    fclose(fptr_in);


    return 0;
}