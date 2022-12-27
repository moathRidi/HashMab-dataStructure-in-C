#include <stdio.h>
#include <process.h>
#include <string.h>
#include <stdlib.h>
#include <Math.h>

#define NUMBER_OF_STRING 30
#define MAX_STRING_SIZE 50
static int NUMBER_OF_COURSES=0;
static int SIZE_OF_TABLE=23;
static int colisionInDouble=0;
static int colisionInQuad=0;
static double load_Factor=0.0;
typedef struct Course
{
    char courseName[40];
    int courseHours;
    char courseCode[10 ];
    char courseDep[40];
    char courseTopics[NUMBER_OF_STRING][MAX_STRING_SIZE];
    int sizeofTopics;
}Course;

typedef struct Array
{
    Course * course;
    int status;

}Array;

typedef struct File File;



void compare();
void ReadCorse(Array * [],Array*[]);
int first_prime(int );
int StringHash(char*  );
int isFull(Array * hashArray[] );
int hash1(char []);
int hash2(char []);
void insertDouble(struct Array *[],char [], int ,char [],char [], char [][MAX_STRING_SIZE],int ) ;
void hashArray_quadrti(struct Array *[],char [], int ,char [],char [], char [][MAX_STRING_SIZE],int ) ;
void AddingCourse(Array * [],Array *[]);
void createmptyArray(Array* []);
int FirstPrime(int );
int IsPrime(int );
int arraySize(int );
int courseCount();
Array *Double_Search(Array* [],char [40]);
Array *Quad_Search(Array* [],char [40]);
void Double_Delete(Array* [SIZE_OF_TABLE],char [40]);
void Quad_Delete(Array* [SIZE_OF_TABLE],char [40]);
void saveInfile(Array* [SIZE_OF_TABLE]);
Array *Double_rehash(Array* [SIZE_OF_TABLE]);
Array *Quad_rehash(Array* [SIZE_OF_TABLE]);
void printAlldata(Array* [SIZE_OF_TABLE],Array*[SIZE_OF_TABLE]);

int main() {
    NUMBER_OF_COURSES=courseCount() ;
    SIZE_OF_TABLE= arraySize(NUMBER_OF_COURSES);
    Array * hashArray_Double[SIZE_OF_TABLE];
    Array * hashArray_Quadrtic[SIZE_OF_TABLE];

    char fin[10];
    char name[40];
    char dep[40];
    char  h;
    Array* fond;
    createmptyArray(hashArray_Double);
    createmptyArray(hashArray_Quadrtic);
    ReadCorse(hashArray_Double,hashArray_Quadrtic);
    int choice;
    do {

        printf("\n 1. Print hashed tables .\n"
               " 2. Print out table size and the load factor.\n"
               " 3. Print out the used hash functions. \n"
               " 4. Insert a new record to hash table.\n"
               " 5. Search for a specific word \n"
               " 6. Delete a specific record.\n"
               " 7. Compare between the two methods in terms of number of "
               "collisions occurred.\n"
               " 8. Save hash table back to a file .\n"
               "Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printAlldata(hashArray_Double,hashArray_Quadrtic);

                break;
            case 2:

                printf("Table size is : %d\nLoad Factor is : 2/3\n",SIZE_OF_TABLE);

                break;
            case 3:
                printf("_________________________________________________________________________\n");
                printf("Double hash function if h(x) = (x %% table_Size) + i * ( R - (x %% R )) \n");
                printf("_________________________________________________________________________\n");

                printf("Quadratic hash function if h(x) = (x + i^2) %% table_Size \n");
                printf("_________________________________________________________________________\n");

                break;
            case 4:
                AddingCourse(hashArray_Double,hashArray_Quadrtic);
                break;
            case 5:

                printf("Enter Course Name to find :\n");
                scanf("%c",&h);
                gets(name);
                printf("Which table do you search in ?\n1: Double Table\n2: Quadratic Table\n");
                int x;
                scanf("%d",&x);
                switch (x) {
                    case 1:
                     fond = Double_Search(hashArray_Double,name);
                     if(fond!=NULL) {
                         printf("\n   %s     |    %d    |   %s    |    %s    |    %d \n",
                                fond->course->courseName, fond->course->courseHours, fond->course->courseCode,
                                fond->course->courseDep, fond->course->sizeofTopics);
                     }
                     else
                         printf(" Name is Not founded!!");
                        break;
                    case 2:

                        fond = Quad_Search(hashArray_Quadrtic,name);
                        if(fond!=NULL) {
                            printf("\n   %s     |    %d    |   %s    |    %s    |    %d \n",
                                   fond->course->courseName, fond->course->courseHours, fond->course->courseCode,
                                   fond->course->courseDep, fond->course->sizeofTopics);
                        }
                        else
                            printf(" Name is Not founded!!");
                        break;
                    default:
                        printf("Please try again");
                        break;
                }

                break;
            case 6:
                printf("Enter Course number to delete :\n");
                scanf("%c",&h);
                gets(dep);
                Quad_Delete(hashArray_Quadrtic,dep);
                Double_Delete(hashArray_Double,dep);

                break;
            case 7:
                compare();
                break;
            case 8:
                saveInfile(hashArray_Double);
                printf("Data saved successfully at {saved_courses.txt}! ");
                break;

            default:
                printf("Please try again");
                break;
        }

    } while (choice != 10);




    return 0;
}
void ReadCorse(Array * hashArrayDouble[],Array *hashArray_Quadrtic[]){//read courses file and lode it to an AVL tree.

    FILE * fin;
    fin = fopen("offered_courses", "r");
    if (fin == NULL)
    {
        printf( "Error! File cannot be read");
        exit (1);
    }
    char line[300];
    char * sr;
    char* ret;
    printf("      Course Name \t             C_Hours      C_Code          C_Department\t          #Topics\n");
    while (fgets(line, 300, fin))
    {
        char courseName[40];
        int courseHours;
        char courseCode[10];
        char courseDep[40];
        char courseTopics[NUMBER_OF_STRING][MAX_STRING_SIZE];
        // Remove trailing newline
        line[strcspn(line, "\n")] = 0;

        sr = strtok(line, ":");
        strcpy(courseName,sr);


        sr = strtok(NULL, "#");
        courseHours= atoi(sr);

        sr = strtok(NULL, "#");
        strcpy(courseCode, sr);
        if(courseCode==' '){
            for (int e = 0; e < strlen(courseCode); e++) {
                courseCode[e]=courseCode[e+1];
            }
        }

        sr = strtok(NULL, "/");
        strcpy(courseDep, sr);
        if(courseDep[0]==' '){
            for (int e = 0; e < strlen(courseDep); e++) {
                courseDep[e]=courseDep[e+1];
            }
        }


        sr = strtok(NULL, "\n");
        ret = strtok(sr, ",");

        int size =0;
        for (int w = 0; w < NUMBER_OF_STRING; w++) {
            if (ret!=NULL) {
                strcpy(courseTopics[w], ret);
                if (courseTopics[w][0] == ' ') {
                    for (int e = 0; e < strlen(courseTopics[w]); e++) {
                        courseTopics[w][e] = courseTopics[w][e + 1];
                    }
                }
                ret = strtok(NULL, ",");
                size=w+1;

            }
        }
        printf("*------------------------------------------------------------------------------------------------------*\n");
        printf("  %-27s     |   %-2d   |   %-10s |   %-19s   |       %-15d \n",courseName,courseHours,courseCode,courseDep,size);


        insertDouble(hashArrayDouble,courseName,courseHours,courseCode,courseDep,courseTopics,size);
        hashArray_quadrti(hashArray_Quadrtic,courseName,courseHours,courseCode,courseDep,courseTopics,size);

        load_Factor=(1.0*NUMBER_OF_COURSES)/SIZE_OF_TABLE;
        if(load_Factor>=0.5){
            SIZE_OF_TABLE = FirstPrime(2 * SIZE_OF_TABLE);
           hashArrayDouble= Double_rehash(hashArrayDouble);
           hashArray_Quadrtic=Quad_rehash(hashArray_Quadrtic);
        }


    }
    fclose(fin);

}




int StringHash(char* key){//calculate the string the key value
    int hashValue = 0;
    while( *key != '\0'){
        hashValue = ( hashValue << 5 ) + *key++;
    }
    return abs(hashValue) ;
}

int isFull(Array *hashArray[SIZE_OF_TABLE]){
    //check if the table is full
    int counter=0;
    for (int i = 0; i < SIZE_OF_TABLE; i++) {
        if (hashArray[i]->status!=0||hashArray[i]->status!=-1)
            counter++;
    }
    return (counter == SIZE_OF_TABLE);
}



// Calculating the first hash.
int hash1(char key[40])
{
    return abs((StringHash(key) % SIZE_OF_TABLE));
}

// Calculating the second hash.
int hash2(char key[40]){
    int prim =first_prime(SIZE_OF_TABLE);
    return abs( prim- (StringHash(key) % prim));
}



int first_prime(int table_size){//find the first prime number before size

    for(int i = table_size - 1; i >= 2; i--) {
        int prime=1;
        for(int j = 2; j <= sqrt(i); j++ ) {
            if(i % j == 0){
                prime=0;
                break;
            }
        }
        if(prime ==1){
            return i;
        }
    }
    return 2;
}

void insertDouble(struct Array * hashArray[SIZE_OF_TABLE],char courseName[40], int courseHours,char courseCode[10],char courseDep[40], char courseTopics[][MAX_STRING_SIZE],int size) {
   // if (isFull(hashArray)) {


        //rehash

  //  }
    int d = 0;
    int hash3;
    int hash_1 = hash1(courseName);
    int hash_2 = hash2(courseName);
    hash3 = hash_1 + (d * hash_2);


    struct Course *course = (struct Course *)
            malloc(sizeof(struct Course));
    strcpy(course->courseName, courseName);
    course->courseHours = courseHours;
    strcpy(course->courseCode, courseCode);
    strcpy(course->courseDep, courseDep);
    course->sizeofTopics = size;

    for (int i = 0; i < size; i++) {
        if (courseTopics[i] != NULL)
            strcpy(course->courseTopics[i], courseTopics[i]);
    }


    if (hashArray[hash3]->status==0||hashArray[hash3]->status==-1) {
        hashArray[hash3]->course = course;
        hashArray[hash3]->status=2;
    }

    //move in array until an empty or deleted cell
   else {
        while (hashArray[hash3]->status == 2) {//&& hashArray[hash3]->courseCode != -1
            //go to next cell
            d++;
            hash3 = (hash_1 + (d * hash_2)) % SIZE_OF_TABLE;
            //wrap around the table
            colisionInDouble++;
        }
        hashArray[hash3]->course=course;
        hashArray[hash3]->status=2;
    }

}



void hashArray_quadrti(struct Array * hashArray[SIZE_OF_TABLE],char courseName[40], int courseHours,char courseCode[10],char courseDep[40], char courseTopics[][MAX_STRING_SIZE],int size) {
    // if (isFull(hashArray)) {


    //rehash

    //  }
    int d = 0;
    int hash3;
    int hash = StringHash(courseName);
   hash3=hash%SIZE_OF_TABLE;



    struct Course *course = (struct Course *)
            malloc(sizeof(struct Course));
    strcpy(course->courseName, courseName);
    course->courseHours = courseHours;
    strcpy(course->courseCode, courseCode);
    strcpy(course->courseDep, courseDep);
    course->sizeofTopics = size;

    for (int i = 0; i < size; i++) {
        if (courseTopics[i] != NULL)
            strcpy(course->courseTopics[i], courseTopics[i]);
    }


    if (hashArray[hash3]->status==0||hashArray[hash3]->status==-1) {
        hashArray[hash3]->course = course;
        hashArray[hash3]->status=2;
    }

        //move in array until an empty or deleted cell
    else {
        while (hashArray[hash3]->status == 2) {//&& hashArray[hash3]->courseCode != -1
            //go to next cell
            d++;
            hash3 = (hash+ (int)pow(d,2)) % SIZE_OF_TABLE;
            //wrap around the table
            colisionInQuad++;
        }
        hashArray[hash3]->course=course;
        hashArray[hash3]->status=2;
    }

}

void AddingCourse(Array * hashArrayDouble[],Array *hashArray_Quadrtic[]){//adding a new course
    char courseName[40];
    int courseHours;
    char courseCode[10];
    char courseDep[40];
    char courseTopics[NUMBER_OF_STRING][MAX_STRING_SIZE];
    char h;
    char c[50];


    printf("Please Enter Course Name : \n");
    scanf("%c",&h);
    gets(c);
    strcpy(courseName,c);
    printf("Please Enter Course Hours : \n");
    scanf("%d",&courseHours);
    printf("Please Enter course Code .exp(Comp133): \n");
    scanf("%c",&h);
    gets(c);
    strcpy(courseCode,c);
    printf("Please Enter Course Department: \n");
    gets(c);
    strcpy(courseDep,c);
    printf("Please Enter Course Topics and then write Stop: \n");
    scanf("%c",&h);
    gets(c);
    int s=0;
    for (int i = 0; i <NUMBER_OF_STRING; i++) {
        if (strcmp(c, "Stop") != 0) {
            s++;
            strcpy(courseTopics[i], c);
            gets(c);

        }
    }
    insertDouble(hashArrayDouble,courseName,courseHours,courseCode,courseDep,courseTopics,s);
    hashArray_quadrti(hashArray_Quadrtic,courseName,courseHours,courseCode,courseDep,courseTopics,s);


    printf("   %s     |    %d    |   %s    |    %s    |    %d \n",courseName,courseHours,courseCode,courseDep,s);

}
void createmptyArray(Array* hashArray[]){
    for (int z = 0; z < SIZE_OF_TABLE; z++) {
        hashArray[z]=(Array*) malloc(sizeof (Array));

    }
    for (int i = 0; i < SIZE_OF_TABLE; ++i) {
        hashArray[i]->status=0;
    }
}


int arraySize(int x){
    int newS=FirstPrime(x*2);
    return newS;
}



int FirstPrime(int n)
{
    while( !IsPrime(n) )
        n++;
    return n;
}
int IsPrime(int n)
{
    int i;
    for( i=2; i <= n/i; i++)
        if( n%i == 0 ) return 0;
    return 1;
}
int courseCount(){

    FILE * fin;
    int count = 0;
    char c;
    fin = fopen("offered_courses", "r");
    if (fin == NULL)
    {
        printf( "Error! File cannot be read");
        exit (1);
    }
    for (c = getc(fin); c != EOF; c = getc(fin))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    fclose(fin);

    return count;
}
Array *Double_Search(Array* hashDouble[],char courseName[40]){
    int d=0;
    int hash_1 = hash1(courseName);
    int hash_2 = hash2(courseName);
   int hash3 = hash_1 + (d * hash_2);

    if(strcmp(hashDouble[hash3]->course->courseName , courseName)==0)//if the course at the first index found then return it
        return hashDouble[hash3];
    else {//if tha first index doesn't match then increment d for next index
        while (hashDouble[hash3]->status == 2) {
            d++;  //go to next cell
            hash3 = (hash_1 + (d * hash_2)) % SIZE_OF_TABLE;
            if (strcmp(hashDouble[hash3]->course->courseName, courseName) == 0) {

                return hashDouble[hash3];
            }
        }

    }
    return NULL;
}

Array *Quad_Search(Array* hashQuad[],char courseName[40]){
    int d=0;
    int hash3;
    int hash = StringHash(courseName);
    hash3=hash%SIZE_OF_TABLE;


    if(strcmp(hashQuad[hash3]->course->courseName , courseName)==0)//if the course at the first index found then return it
        return hashQuad[hash3];
    else {//if tha first index doesn't match then increment d for next index
        while (hashQuad[hash3]->status == 2) {
            d++;  //go to next cell
            hash3 = (hash+ (int)pow(d,2)) % SIZE_OF_TABLE;
            if (strcmp(hashQuad[hash3]->course->courseName, courseName) == 0) {

                return hashQuad[hash3];
            }
        }

    }
    return NULL;
}

void Double_Delete(Array* hashArray[SIZE_OF_TABLE],char item[40]){

int flag=0;
    int d=0;
    int hash_1 = hash1(item);
    int hash_2 = hash2(item);
    int hash3 = hash_1 + (d * hash_2);
//if the course at the first index found then delete it
    if(strcmp(hashArray[hash3]->course->courseName , item)==0){
         hashArray[hash3]->status=-1;
        free(hashArray[hash3]->course);
        flag=1;
    }

    else {//if tha first index doesn't match then increment d for next index
        while (hashArray[hash3]->status == 2) {
            d++;  //go to next cell
            hash3 = (hash_1 + (d * hash_2)) % SIZE_OF_TABLE;
            if(strcmp(hashArray[hash3]->course->courseName , item)==0){
                hashArray[hash3]->status = -1;
                free(hashArray[hash3]->course);
                flag=1;
            }
        }

    }
    if (flag==0){
        printf(" this course not founded!!");
    }
}
void Quad_Delete(Array* hashArray[SIZE_OF_TABLE],char item[40]){

    int d=0;
    int hash3;
    int hash = StringHash(item);
    hash3=hash%SIZE_OF_TABLE;

//if the course at the first index found then delete it
    if(strcmp(hashArray[hash3]->course->courseName , item)==0) {
        hashArray[hash3]->status=-1;
        free(hashArray[hash3]->course);
    }
    else {//if tha first index doesn't match then increment d for next index
        while (hashArray[hash3]->status == 2) {
            d++;  //go to next cell
            hash3 = (hash+ (int)pow(d,2)) % SIZE_OF_TABLE;
            if (strcmp(hashArray[hash3]->course->courseName, item) == 0) {
                hashArray[hash3]->status = -1;
                free(hashArray[hash3]->course);
            }
        }

    }

}
void compare(){
    printf("\nNumber of Collision in Double Table is : %d\n ",colisionInDouble);
    printf("\nNumber of Collision in Quadratic Table is : %d\n",colisionInQuad);
    if (colisionInDouble>colisionInDouble){
        printf("\n the Double Table has more collision than Quadratic Table \n");
    } else
        printf(" \nthe Quadratic Table has more collision than Quadratic Table \n");
}
void saveInfile(Array* hashArray[SIZE_OF_TABLE]){
    FILE *out;
    out=fopen("saved_courses","w");
    for (int i = 0; i < SIZE_OF_TABLE; i++) {
        if(hashArray[i]->status==2){
            fprintf(out,"%s:%d#%s#%s/",hashArray[i]->course->courseName, hashArray[i]->course->courseHours, hashArray[i]->course->courseCode,
                    hashArray[i]->course->courseDep);

            for (int c = 0; c < hashArray[i]->course->sizeofTopics; c++) {//printing topics
                fprintf(out,"%s", hashArray[i]->course->courseTopics[c]);
                if(c<hashArray[i]->course->sizeofTopics-1){
                    fprintf(out,", ");
                }

            }
            fprintf(out,"\n");
        }

    }
    fclose(out);
}

Array *Double_rehash(Array* array[])
{
colisionInDouble=0;

    //array variable is assigned with newly created Hash Table
        //with double of previous array size
    Array * newHash[SIZE_OF_TABLE];
    createmptyArray(newHash);
    for (int i = 0; i < SIZE_OF_TABLE; i++) {
        if(array[i]->status==2)
        insertDouble(newHash,array[i]->course->courseName,array[i]->course->courseHours,array[i]->course->courseCode,array[i]->course->courseDep,array[i]->course->courseTopics,array[i]->course->sizeofTopics);

    }
    return newHash;

}
Array *Quad_rehash(Array* array[])
{
    colisionInQuad=0;

    //array variable is assigned with newly created Hash Table
    //with double of previous array size
    Array * newHash[SIZE_OF_TABLE];
    createmptyArray(newHash);
    for (int i = 0; i < SIZE_OF_TABLE; i++) {
        if(array[i]->status==2)
            hashArray_quadrti(newHash,array[i]->course->courseName,array[i]->course->courseHours,array[i]->course->courseCode,array[i]->course->courseDep,array[i]->course->courseTopics,array[i]->course->sizeofTopics);

    }
    return newHash;

}
void printAlldata(Array* double_hash[SIZE_OF_TABLE],Array*quad_hash[SIZE_OF_TABLE]){

    printf("\n****************************************- Double Table -******************************************\n\n");
    for (int i = 0; i < SIZE_OF_TABLE; i++) {
        if (double_hash[i]->status == 0) {
            printf("                                       --- Empty ---       \n");
            printf("*------------------------------------------------------------------------------------------------------*\n");

        }
        else if (double_hash[i]->status == -1){
            printf("                                       --- Deleted ---       \n");
            printf("*------------------------------------------------------------------------------------------------------*\n");

        }
        else {
            printf("      %-27s     |   %-2d   |   %-10s |   %-19s   |       %-15d \n", double_hash[i]->course->courseName,
                   double_hash[i]->course->courseHours, double_hash[i]->course->courseCode,
                   double_hash[i]->course->courseDep, double_hash[i]->course->sizeofTopics);
            printf("*------------------------------------------------------------------------------------------------------*\n");
        }
        }
    printf("\n                                Number of Collision is : %d           \n ",colisionInDouble);


    printf("Number of Collision is : %d\n",colisionInQuad);
    printf("\n\n****************************************- Quadratic Table -******************************************\n\n");

    for (int i = 0; i < SIZE_OF_TABLE; i++) {
        if (quad_hash[i]->status == 0) {
            printf("                                                    --- Empty ---       \n");
            printf("*------------------------------------------------------------------------------------------------------*\n");

        }
        else if (quad_hash[i]->status == -1){
            printf("                                       --- Deleted ---       \n");
            printf("*------------------------------------------------------------------------------------------------------*\n");

        }
        else {
            printf("      %-27s     |   %-2d   |   %-10s |   %-19s   |       %-15d \n", quad_hash[i]->course->courseName,
                   quad_hash[i]->course->courseHours, quad_hash[i]->course->courseCode, quad_hash[i]->course->courseDep,
                   quad_hash[i]->course->sizeofTopics);
            printf("*------------------------------------------------------------------------------------------------------*\n");
        }
    }

    printf("\n                                Number of Collision is : %d\n",colisionInQuad);



}