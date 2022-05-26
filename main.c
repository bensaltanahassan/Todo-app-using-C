#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//initialiser le nombre des tasks par 0
int nbrTasks = 0;
int permission = 0;

void printTODO ();
void espace (int nSpace);
void flecheHorizontale();
void flecheVerticale();
void buttons1();
void addTask();
void afficheAllTasks();
void afficheTask(int i);
void seConnecter (char *username,char *password,FILE *fp,int *isRegistered,char *nom,char *prenom);
void afficheMenu ();
void addButton (char text [],int espaceApresfleche);
void msgWelcom(char nom[],char prenom[]);
void nejma (int i);
void retourLigne (int i);
void printTaskIntrouvable();
void deleteTask(int i);
void updateTask(int index);
void home();
void sinscrire(char *username,char *password,char *nom ,char *prenom,FILE *fp,int *isRegistered);
int isVide(FILE* fichier);
void printUserNotFound();
void printAlreadyExists();
void printWrongPassword();




//faire class des Tasks
struct Task {
    char title [50];
    char task [1000] ;
    _Bool isDone ;
}todos[100];



int main()
{
    int isRegistered = 0;
    int *isRegisteredPtr = &isRegistered;
    FILE *fp =NULL;
    printf("\n");
    int temp =0 ; //tous les boucles while

    char nom[50],prenom[50],username[50],password[50];
    int choix,choix2,numTask,choix3;
    int *pChoix,*pChoix2 ,*pChoix3,*pNumTask;
    char *pNom ,*pPrenom,*pUsername,*pPassword;
    pChoix= &choix;
    pChoix2= &choix2;
    pNumTask = &numTask;
    pChoix3 = &choix3;
    pNom = &nom;
    pPrenom = &prenom;
    pUsername = &username;
    pPassword = &password;

    printTODO();

    printf("\n");
    backToHome:
    home();
    espace(30);
    char enterYourChoise [100] = "Enter your choice please : ";
    printf("%s",enterYourChoise);
    scanf("%d",pChoix);

    do{
        switch(choix){
            case 1 :
                seConnecter(pUsername,pPassword,fp,isRegisteredPtr,pNom,pPrenom);
                if (permission ==0){
                    printf("\n");
                    temp = 0;
                    goto backToHome;
                }else {
                    printf("\n");
                    msgWelcom(nom,prenom);
                    printf("\n");
                    temp = 1;
                    goto there;
                }
                break;


            case 2:
                sinscrire(pUsername,pPassword,pNom,pPrenom,fp,isRegisteredPtr);
                if (permission == 1){
                    printf("\n");
                    msgWelcom(nom,prenom);
                    printf("\n");
                    temp = 1;
                    goto there;
                }else {
                    temp = 0;

                    goto backToHome;

                }
                break;


            case 3:
                return 0;
            default:
                espace(30);
                printf("Please enter an integer between 1 or 3 :");
                scanf("%d",&choix);
                if (choix != 1 && choix != 2)
                    temp = 0;
                break;

        }
    }while ( temp == 0  );
    //choix == 1 =>
    there :
    afficheMenu();
    espace(30);
    printf("%s",enterYourChoise);
    scanf("%d",pChoix);


    do{
        switch(choix){
            case 1 :
                addTask();
                printf("\n");
                goto there;
                break;
            case 2:
                printf("\n");
                printf("\n");
                afficheAllTasks();
                if (nbrTasks == 0){
                    goto there;
                }
                espace(30);
                printf("%s",enterYourChoise);
                scanf("%d",pChoix2);

                do{
                    switch(choix2){
                        case 1 :
                            espace(30);
                            printf("Enter the number of Task : ");
                            scanf("%d",pNumTask);
                            if(numTask>nbrTasks){
                                printTaskIntrouvable();
                                goto there;
                            }
                            afficheTask(numTask-1);
                            espace(30);
                            printf("%s",enterYourChoise);
                            scanf("%d",pChoix3);
                            do{
                                switch(choix3){
                                    case 1 :
                                        updateTask(numTask);
                                        goto there;
                                    case 2:
                                        deleteTask(numTask);
                                        goto there;
                                    case 3:

                                    default:
                                        espace(30);
                                        printf("Veuiller Saisir un entier entre 1 et 3 .");
                                        scanf("%d",&choix3);
                                        break;

                                }
                            }while ( choix3 != 1 && choix3 != 2 && choix3 != 3 );


                        case 2:
                            addTask();
                            printf("\n");
                            goto there;
                        case 3:
                            goto there;
                        default:
                            espace(30);
                            printf("Please enter an integer between 1 and 3 :");
                            scanf("%d",&choix2);
                            break;

                    }
                }while ( choix2 != 1 && choix2 != 2 && choix2 != 3 );




            case 3 :
                goto backToHome;
                break;

            default:
                espace(30);
                printf("Please enter an integer between 1 and 2 :");
                scanf("%d",&choix);
                break;

        }
    }while ( choix != 1 );







    return 0;
}

void addTask(){
    printf("\n");
    int i;
    //ligne1

    for (i=0;i<84;i++)
    {
        flecheHorizontale();
    }

    printf("\n");





    char text[1000] ;
    char titre[50] ;
    //entrer titre
    espace(30);
    printf("Enter the title of the task :");
    scanf(" %[^\n]s",&titre);
    printf("\n");
    //entrer texte
    espace(30);
    printf("Enter the note :");
    scanf(" %[^\n]s",&text);

    printf("\n");
    for (i=0;i<84;i++)
    {
        flecheHorizontale();
    }

    strcpy(todos[nbrTasks].task,text);
    strcpy(todos[nbrTasks].title,titre);
    nbrTasks ++;
}

void deleteTask(int i){
    int j;
    for(j=i-1;j<nbrTasks;j++){
        strcpy(todos[j].task,todos[j+1].task);
        strcpy(todos[j].title,todos[j+1].title);
    }
    nbrTasks--;
}

void updateTask(int index){
    printf("\n");
    int i;
    //ligne1

    for (i=0;i<84;i++)
    {
        flecheHorizontale();
    }

    printf("\n");





    char text[1000] ;
    char titre[50] ;
    //entrer titre
    espace(30);
    printf("Enter the new title :");
    scanf(" %[^\n]s",&titre);
    printf("\n");
    //entrer texte
    espace(30);
    printf("Enter the new note :");
    scanf(" %[^\n]s",&text);

    printf("\n");
    for (i=0;i<84;i++)
    {
        flecheHorizontale();
    }

    strcpy(todos[index-1].task,text);
    strcpy(todos[index-1].title,titre);




}

void printUserNotFound(){
    int i;
        espace(40);
        for (i=0;i<40;i++)
        {
            flecheHorizontale();
        }
        printf("\n");

        for (i= 0 ;i<5;i++){
            espace(40);
            flecheVerticale();
            espace(78);
            flecheVerticale();
            retourLigne(1);
        }
        espace(40);
        flecheVerticale();
        espace(28);
        printf(">>> User Not Found <<< ");
        espace(27);
        flecheVerticale();
        printf("\n");
        for (i= 0 ;i<5;i++){
            espace(40);
            flecheVerticale();
            espace(78);
            flecheVerticale();
            retourLigne(1);
        }
        espace(40);
        for (i=0;i<40;i++)
        {
            flecheHorizontale();
        }
        printf("\n");
        printf("\n");
}


void printAlreadyExists(){
    int i;
        espace(40);
        for (i=0;i<40;i++)
        {
            flecheHorizontale();
        }
        printf("\n");

        for (i= 0 ;i<5;i++){
            espace(40);
            flecheVerticale();
            espace(78);
            flecheVerticale();
            retourLigne(1);
        }
        espace(40);
        flecheVerticale();
        espace(28);
        printf(">>> Already Exists <<< ");
        espace(27);
        flecheVerticale();
        printf("\n");
        for (i= 0 ;i<5;i++){
            espace(40);
            flecheVerticale();
            espace(78);
            flecheVerticale();
            retourLigne(1);
        }
        espace(40);
        for (i=0;i<40;i++)
        {
            flecheHorizontale();
        }
        printf("\n");
        printf("\n");
}


void printWrongPassword(){
    printf("\n");
    int i;
        espace(40);
        for (i=0;i<40;i++)
        {
            flecheHorizontale();
        }
        printf("\n");

        for (i= 0 ;i<5;i++){
            espace(40);
            flecheVerticale();
            espace(78);
            flecheVerticale();
            retourLigne(1);
        }
        espace(40);
        flecheVerticale();
        espace(28);
        printf(">>> Wrong Password <<< ");
        espace(27);
        flecheVerticale();
        printf("\n");
        for (i= 0 ;i<5;i++){
            espace(40);
            flecheVerticale();
            espace(78);
            flecheVerticale();
            retourLigne(1);
        }
        espace(40);
        for (i=0;i<40;i++)
        {
            flecheHorizontale();
        }
        printf("\n");
        printf("\n");
}

void printTaskIntrouvable(){
    int i;
        espace(40);
        for (i=0;i<40;i++)
        {
            flecheHorizontale();
        }
        printf("\n");

        for (i= 0 ;i<5;i++){
            espace(40);
            flecheVerticale();
            espace(78);
            flecheVerticale();
            retourLigne(1);
        }
        espace(40);
        flecheVerticale();
        espace(28);
        printf(">>> Task Unavailable <<< ");
        espace(25);
        flecheVerticale();
        printf("\n");
        for (i= 0 ;i<5;i++){
            espace(40);
            flecheVerticale();
            espace(78);
            flecheVerticale();
            retourLigne(1);
        }
        espace(40);
        for (i=0;i<40;i++)
        {
            flecheHorizontale();
        }
        printf("\n");
        printf("\n");
}


void afficheAllTasks(){

    int i, j;






    if(nbrTasks==0){
        espace(40);
        for (i=0;i<40;i++)
        {
            flecheHorizontale();
        }
        printf("\n");

        for (i= 0 ;i<5;i++){
            espace(40);
            flecheVerticale();
            espace(78);
            flecheVerticale();
            retourLigne(1);
        }
        espace(40);
        flecheVerticale();
        espace(28);
        printf(">>> There is no tasks <<<");
        espace(25);
        flecheVerticale();
        printf("\n");
        for (i= 0 ;i<5;i++){
            espace(40);
            flecheVerticale();
            espace(78);
            flecheVerticale();
            retourLigne(1);
        }
        espace(40);
        for (i=0;i<40;i++)
        {
            flecheHorizontale();
        }
        printf("\n");
        printf("\n");





    }else {
        espace(25);
        for (j = 0 ; j < 110 ;j++){
            printf("%c",178);
        }
        printf("\n");
        for (i=0 ;i<nbrTasks;i++){


            espace(25);
            flecheVerticale();
            espace(108);
            flecheVerticale();
            printf("\n");
            espace(25);
            flecheVerticale();
            printf(" Task %d :",i+1);
            printf("%s",todos[i].title);
            printf("\n");
            espace(25);
            flecheVerticale();
            printf(" ");
            for(j=0;j<7;j++){
                printf("%c",223);
            }
            espace(100);
            flecheVerticale();
            printf("\n");

        }
            espace(25);
            flecheVerticale();
            espace(108);
            flecheVerticale();
            printf("\n");
            espace(25);
            flecheVerticale();
            espace(108);
            flecheVerticale();
            printf("\n");
            espace(25);
            for (j = 0 ; j < 110 ;j++){
                printf("%c",178);
            }
            printf("\n");



            addButton("1.Show Task",13);
            addButton("2.Add Task",14);
            addButton("3.Back  ",16);


            espace(60);
            for (i=0;i<20;i++)
            {
                flecheHorizontale();
            }
            printf("\n");




    }

}

void afficheTask(int i){


    char title = todos[i].title;
    char task = todos[i].task;


    //int long1 = strlen(title);
    //int long2 = strlen(task);

    int j;
    espace(25);
    for (j = 0 ; j < 110 ;j++){
        printf("%c",178);
    }

    printf("\n");
    espace(25);
    flecheVerticale();
    espace(108);
    flecheVerticale();
    printf("\n");
    espace(25);
    flecheVerticale();
    printf(" Title :");
    printf("%s",todos[i].title);
    printf("\n");
    espace(25);
    flecheVerticale();
    printf(" ");
    for(j=0;j<7;j++){
        printf("%c",223);
    }
    espace(100);
    flecheVerticale();

    printf("\n");
    espace(25);
    flecheVerticale();
    printf(" Text  :");
    printf("%s",todos[i].task);
    printf("\n");
    espace(25);
    flecheVerticale();
    printf(" ");
    for(j=0;j<7;j++){
        printf("%c",223);
    }
    espace(100);
    flecheVerticale();

    printf("\n");
    espace(25);
    flecheVerticale();
    espace(108);
    flecheVerticale();

    printf("\n");
    espace(25);
    flecheVerticale();
    espace(108);
    flecheVerticale();
    printf("\n");
    espace(25);
    for (j = 0 ; j < 110 ;j++){
        printf("%c",178);
    }
    printf("\n");



    addButton("1.Edit",18);
    addButton("2.Delete",16);
    addButton("3.Back",18);


    espace(60);
    for (i=0;i<20;i++)
    {
        flecheHorizontale();
    }
    printf("\n");



}

void printTODO (){
    int i ;


    for ( i = 0 ; i<33;i++){
        flecheHorizontale();
    }
    printf(" WELCOME TO ") ;
    for ( i = 0 ; i<35;i++){
        flecheHorizontale();
    }
    printf("\n");


    //ligne 1*
    flecheVerticale();
    espace(146);
    flecheVerticale();
    printf("\n");
    flecheVerticale();
    espace(20);
    //N
    printf("%c",219);
    espace(6);
    printf("%c",219);
    espace(7);

    //O

    for ( i = 0 ; i<10;i++){
        printf("%c",219);
    }
    espace(5);
    //T
    for ( i = 0 ; i<13;i++){
        printf("%c",219);
    }
    espace(3);
    //E
    for ( i = 0 ; i<12;i++){
        printf("%c",219);
    }
    espace(3);
    espace(4);
    //app
     for ( i = 0 ; i<12;i++){
        printf("%c",219);
        }
    espace(3);
     for ( i = 0 ; i<12;i++){
        printf("%c",219);
        }
    espace(3);
     for ( i = 0 ; i<12;i++){
        printf("%c",219);
    }
    espace(19);
    flecheVerticale();
    printf("\n");
    flecheVerticale();
    espace(20);
    //ligne2
    //N
    printf("%c",219);
    printf("%c",219);
    espace(5);
    printf("%c",219);
    espace(7);
    //O
    printf("%c",219);
    espace(8);
    printf("%c",219);
    espace(3);
    //T
    espace(8);
    printf("%c",219);
    espace(9);
    //E
    printf("%c",219);
    printf("%c",219);
    espace(13);
    espace(4);
    //app
    printf("%c",219);
    espace(10);
    printf("%c",219);
    espace(3);
    printf("%c",219);
    espace(10);
    printf("%c",219);
    espace(3);
    printf("%c",219);
    espace(10);
    printf("%c",219);
    espace(19);
    flecheVerticale();
    //linge3
    printf("\n");
    flecheVerticale();
    espace(20);
    //N
    printf("%c",219);
    espace(1);
    printf("%c",219);
    espace(4);
    printf("%c",219);
    espace(7);
    //O
     printf("%c",219);
    espace(8);
    printf("%c",219);
    espace(3);
    //T
    espace(8);
    printf("%c",219);
    espace(9);
    //E
    printf("%c",219);
    printf("%c",219);
    espace(13);
    espace(4);
    //app
    printf("%c",219);
    espace(10);
    printf("%c",219);
    espace(3);
    printf("%c",219);
    espace(10);
    printf("%c",219);
    espace(3);
    printf("%c",219);
    espace(10);
    printf("%c",219);
    espace(19);
    flecheVerticale();
     //linge4
    printf("\n");
    flecheVerticale();
    espace(20);
    //N
    printf("%c",219);
    espace(2);
    printf("%c",219);
    espace(3);
    printf("%c",219);
    espace(7);
    //O
    printf("%c",219);
    espace(8);
    printf("%c",219);
    espace(3);
    //T
    espace(8);
    printf("%c",219);
    espace(9);
    //E
    for ( i = 0 ; i<12;i++){
        printf("%c",219);
    }
    espace(4);
    //APP
    espace(3);
    for ( i = 0 ; i<12;i++){
        printf("%c",219);
    }
    espace(3);
    for ( i = 0 ; i<12;i++){
        printf("%c",219);
    }
    espace(3);
    for ( i = 0 ; i<12;i++){
        printf("%c",219);
    }
    espace(19);
    flecheVerticale();
      //linge5
    printf("\n");
    flecheVerticale();
    espace(20);
    //N
    printf("%c",219);
    espace(3);
    printf("%c",219);
    espace(2);
    printf("%c",219);
    espace(7);
    //O
    printf("%c",219);
    espace(8);
    printf("%c",219);
    espace(3);
    //T
    espace(8);
    printf("%c",219);
    espace(9);
    //E
    printf("%c",219);
    printf("%c",219);
    espace(13);
    espace(4);
    //APP
    printf("%c",219);
    espace(10);
    printf("%c",219);
    espace(3);
    printf("%c",219);
    espace(10);
    espace(4);
    printf("%c",219);
    espace(30);
    flecheVerticale();
     //linge6
    printf("\n");
    flecheVerticale();
    espace(20);
    //N
    printf("%c",219);
    espace(4);
    printf("%c",219);
    espace(1);
    printf("%c",219);
    espace(7);
    //O
    printf("%c",219);
    espace(8);
    printf("%c",219);
    espace(3);
    //T
    espace(8);
    printf("%c",219);
    espace(9);
    //E
    printf("%c",219);
    printf("%c",219);
    espace(13);
    espace(4);
     //APP
    printf("%c",219);
    espace(10);
    printf("%c",219);
    espace(3);
    printf("%c",219);
    espace(10);
    espace(4);
    printf("%c",219);
    espace(30);
    flecheVerticale();
     //linge7
    printf("\n");
    flecheVerticale();
    espace(20);
    //N
    printf("%c",219);
    espace(5);
    printf("%c",219);
    printf("%c",219);
    espace(7);
    //O
    printf("%c",219);
    espace(8);
    printf("%c",219);
    espace(3);
    //T
    espace(8);
    printf("%c",219);
    espace(9);
    //E
    printf("%c",219);
    printf("%c",219);
    espace(13);
    espace(4);
     //APP
    printf("%c",219);
    espace(10);
    printf("%c",219);
    espace(3);
    printf("%c",219);
    espace(10);
    espace(4);
    printf("%c",219);
    espace(30);
    flecheVerticale();
      //linge8
    printf("\n");
    flecheVerticale();
    espace(20);
    //N
    printf("%c",219);
    espace(6);
    printf("%c",219);
    espace(7);
    //O
     for ( i = 0 ; i<10;i++){
        printf("%c",219);
        }
        espace(3);
    //T
    espace(8);
    printf("%c",219);
    espace(9);
    //E
     for ( i = 0 ; i<12;i++){
        printf("%c",219);}
        espace(3);
        espace(4);
     //APP
    printf("%c",219);
    espace(10);
    printf("%c",219);
    espace(3);
    printf("%c",219);
    espace(10);
    espace(4);
    printf("%c",219);
    espace(30);
    flecheVerticale();
    printf("\n");
    flecheVerticale();
    espace(146);
    flecheVerticale();
    printf("\n");
     for ( i = 0 ; i<74;i++){
        flecheHorizontale();
    }





}

void espace (int nSpace){
    for (int i = 0 ; i< nSpace;i++){
        printf(" ");
    }
}

void msgWelcom(char nom[],char prenom[]){
    espace(30);
    printf("Hello %s %s",nom,prenom);
}

void flecheHorizontale(){

    //printf("%c",16);
    //printf("%c",17);
    printf("%c",178);
    printf("%c",178);
}

void flecheVerticale(){
    printf("%c",178);
}


void buttons1(){
    int i;
    //ligne1
    espace(60);

    for (i=0;i<20;i++)
    {
        flecheHorizontale();
    }
    printf("\n");
    //ligne 2
    addButton("1.Log in",10);

    addButton("2.Exit",16);
    //ligne 13

    espace(60);
    for (i=0;i<20;i++)
    {
        flecheHorizontale();
    }
    printf("\n");


}



void home(){
    printf("\n");
    int i;
    //ligne1
    espace(60);

    for (i=0;i<20;i++)
    {
        flecheHorizontale();
    }
    printf("\n");
    //ligne 2
    addButton("1.Login",17);

    addButton("2.Sign Up",15);

    addButton("3.Exit",18);

    //ligne +00

    espace(60);
    for (i=0;i<20;i++)
    {
        flecheHorizontale();
    }
    printf("\n");
}

void afficheMenu(){
    printf("\n");
    int i;
    //ligne1
    espace(60);

    for (i=0;i<20;i++)
    {
        flecheHorizontale();
    }
    printf("\n");
    //ligne 2
    addButton("1.Add note",14);

    addButton("2.Show all the notes",4);

    addButton("3.Sign Out",14);

    //ligne +00

    espace(60);
    for (i=0;i<20;i++)
    {
        flecheHorizontale();
    }
    printf("\n");
}

void seConnecter (char *username,char *password,FILE *fp,int *isRegistered,char *nom,char *prenom){

    retourLigne(15);
    int i;
    //ligne1
    espace(60);

    for (i=0;i<20;i++)
    {
        flecheHorizontale();
    }
    printf("\n");
    //ligne 2
    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();

    printf("\n");
    //lign3
    espace(60);
    flecheVerticale();
    espace(10);
    for (i=0;i<20;i++)
    {
        printf("%c",22);
    }

    espace(8);
    flecheVerticale();
    printf("\n");
    //ligne4
    espace(60);
    flecheVerticale();
    espace(10);
    flecheVerticale();
    espace(1);
    printf("Username:");
    scanf(" %s",username);





    //ligne5

    espace(60);
    flecheVerticale();
    espace(10);
    for (i=0;i<20;i++)
    {
        printf("%c",22);
    }
    espace(8);
    flecheVerticale();
    printf("\n");

    //ligne6

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");

    //ligne7

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");

    //ligne 8

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");

    //ligne 9

    espace(60);
    flecheVerticale();
    espace(10);

    //Prenom
    for (i=0;i<20;i++)
    {
        printf("%c",22);
    }
    espace(8);
    flecheVerticale();


    printf("\n");

    //ligne 10

    espace(60);
    flecheVerticale();
    espace(10);

    printf("%c",178);
    printf("Password :");
    scanf(" %s",password);





    //ligne 11

    espace(60);
    flecheVerticale();
    espace(10);
    for (i=0;i<20;i++)
    {
        printf("%c",22);
    }
    espace(8);
    flecheVerticale();
    printf("\n");

    //ligne 12

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");

    //ligne 13

    espace(60);
    for (i=0;i<20;i++)
    {
        flecheHorizontale();
    }
    printf("\n");

    //
    //

    char filename[100];
    strcpy(filename,username);
    strcat(filename,".txt");
    fp=fopen(filename,"r");
    if (!fp){
        isRegistered = 0;
        printUserNotFound();
        permission = 0;
    }else{
        isRegistered = 1;
        char tempPassword [100];
        fscanf(fp,"%s",tempPassword);

        if (strcmp(tempPassword,password)!=0){
            printWrongPassword();
            permission = 0;
        }else{
            fscanf(fp,"%s",nom);
            fscanf(fp,"%s",prenom);
            permission = 1;
        }




    }


}

void sinscrire(char *username,char *password,char *nom ,char *prenom,FILE *fp,int *isRegistered){
    retourLigne(15);
    int i;
    //ligne1
    espace(60);

    for (i=0;i<20;i++)
    {
        flecheHorizontale();
    }
    printf("\n");
    //ligne 2
    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();

    printf("\n");
    //lign3
    espace(60);
    flecheVerticale();
    espace(10);
    for (i=0;i<20;i++)
    {
        printf("%c",22);
    }

    espace(8);
    flecheVerticale();
    printf("\n");
    //ligne4
    espace(60);
    flecheVerticale();
    espace(10);
    flecheVerticale();
    espace(1);
    printf("First name:");
    scanf(" %s",nom);





    //ligne5

    espace(60);
    flecheVerticale();
    espace(10);
    for (i=0;i<20;i++)
    {
        printf("%c",22);
    }
    espace(8);
    flecheVerticale();
    printf("\n");

    //ligne6

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");

    //ligne7

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");

    //ligne 8

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");

    //ligne 9

    espace(60);
    flecheVerticale();
    espace(10);

    //Prenom
    for (i=0;i<20;i++)
    {
        printf("%c",22);
    }
    espace(8);
    flecheVerticale();


    printf("\n");

    //ligne 10

    espace(60);
    flecheVerticale();
    espace(10);

    printf("%c",178);
    printf("Last name:");
    scanf(" %s",prenom);







    //ligne5

    espace(60);
    flecheVerticale();
    espace(10);
    for (i=0;i<20;i++)
    {
        printf("%c",22);
    }
    espace(8);
    flecheVerticale();
    printf("\n");

    //ligne6

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");

    //ligne7

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");

    //ligne 8

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");

    //ligne 9

    espace(60);
    flecheVerticale();
    espace(10);

    //Prenom
    for (i=0;i<20;i++)
    {
        printf("%c",22);
    }
    espace(8);
    flecheVerticale();


    printf("\n");

    //ligne 10

    espace(60);
    flecheVerticale();
    espace(10);

    printf("%c",178);
    printf("Username :");
    scanf(" %s",username);







    //ligne5

    espace(60);
    flecheVerticale();
    espace(10);
    for (i=0;i<20;i++)
    {
        printf("%c",22);
    }
    espace(8);
    flecheVerticale();
    printf("\n");

    //ligne6

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");

    //ligne7

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");

    //ligne 8

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");

    //ligne 9

    espace(60);
    flecheVerticale();
    espace(10);

    //Prenom
    for (i=0;i<20;i++)
    {
        printf("%c",22);
    }
    espace(8);
    flecheVerticale();


    printf("\n");

    //ligne 10

    espace(60);
    flecheVerticale();
    espace(10);

    printf("%c",178);
    printf("Password:");
    scanf("%s",password);





    //ligne 11

    espace(60);
    flecheVerticale();
    espace(10);
    for (i=0;i<20;i++)
    {
        printf("%c",22);
    }
    espace(8);
    flecheVerticale();
    printf("\n");

    //ligne 12

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");

    //ligne 13

    espace(60);
    for (i=0;i<20;i++)
    {
        flecheHorizontale();
    }
    printf("\n");
    //ligne 14

    char filename[100];
    strcpy(filename,username);
    strcat(filename,".txt");
    fp=fopen(filename,"r");
    if(!fp){
        isRegistered = 0;
        fp=fopen(filename,"w");
        permission= 1;
        fprintf(fp,"%s\n",password);
        fprintf(fp,"%s\n",nom);
        fprintf(fp,"%s\n",prenom);
        fclose(fp);

    }
    else{
        // printf("Username already exist");
        printAlreadyExists();
        isRegistered=1;
        permission = 0;
    }
}



void addButton (char text [],int espaceApresfleche){
    int longuerText = strlen(text);
    int i;
    //ligne 2
    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();

    printf("\n");
    //lign3
    espace(60);
    flecheVerticale();
    espace(10);
    for (i=0;i<longuerText+4;i++)
    {
        printf("%c",22);
    }

    espace(28-longuerText-4);
    flecheVerticale();
    printf("\n");
    //ligne4
    espace(60);
    flecheVerticale();
    espace(10);
    flecheVerticale();
    espace(1);
    printf(text);
    espace(1);
    flecheVerticale();
    espace(espaceApresfleche);
    flecheVerticale();
    printf("\n");

    //ligne5

    espace(60);
    flecheVerticale();
    espace(10);
    for (i=0;i<longuerText+4;i++)
    {
        printf("%c",22);
    }
    espace(28-longuerText-4);
    flecheVerticale();
    printf("\n");

    //ligne6

    espace(60);
    flecheVerticale();
    espace(38);
    flecheVerticale();
    printf("\n");



}

void nejma (int i){
    int j ;
    for (j =0 ; j<i;j++){
        printf("*");
    }
}
void retourLigne (int i){
    int j ;
    for (j =0 ; j<i;j++){
        printf("\n");
    }

}


int isVide(FILE* fichier)
{
    int caracterePremier = 0;

    //On lit le prmeier caractère du fichier
    caracterePremier = fgetc(fichier);
    if(caracterePremier==EOF)
    {
        return 1;//le fichier est vide donc on retourne 1
    }
    return 0;//le fichier n'est pas vide donc on retourne 0
}





