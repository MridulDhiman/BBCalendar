#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//colors 
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define BWHT "\e[1;37m"
#define UWHT "\e[4;37m"
#define REDB "\e[41m"
#define CYNB "\e[46m"
#define UYEL "\e[4;33m"
#define BBLU "\e[1;34m"
#define BLUB "\e[44m"


//inputing string in C
void flush()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int isLeapYear( int year );        
void monthlyCalendar(int m, int y);     
int getDayNumber(int d,int m,int y);
char *getName(int day);
 void yearlyCalendar(int y);


//typedef structure
 typedef struct {
  int day;
  int month;
  int year;
  char note[255];
} Note;

int main(){
   Note note;
    FILE *fp;


    fp = fopen("note.txt", "r");
    if (fp == NULL) {
      fp = fopen("note.txt", "w");
    } 
    fclose(fp);
   time_t t = time(NULL);
  struct tm tm = *localtime(&t);

    int year,month, day;
    int choice;
printf(" --------------------------------------------------------------------------------------------------\n|                                     WELCOME TO BB CALENDAR APP                                   |\n --------------------------------------------------------------------------------------------------");


 printf("\n\n --------------------------------------------------------------------------------------------------\n|                                           INTRODUCTION                                           |");
  printf("\n --------------------------------------------------------------------------------------------------\n\n");

printf(ANSI_COLOR_GREEN "\n SUBMITTED BY: MRIDUL DHIMAN" ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "\n ROLL NO.    :  21103096" ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "\n SUBMITTED TO: MS. SHEFALI ARORA\n" ANSI_COLOR_RESET);
printf(ANSI_COLOR_RED "\n NOTE: THE DATE HAS TO BE ENTERED IN THE DD MM YYYY FORMAT\n" ANSI_COLOR_RESET);


//  printf("\n\n--------------------------------------------------------------------------------------------------\n");
//   printf("--------------------------------------------------------------------------------------------------\n\n");
    while(1) {
        printf("\n\n --------------------------------------------------------------------------------------------------\n|                                           STARTING PAGE                                          |");
  printf("\n --------------------------------------------------------------------------------------------------\n\n");
     printf(ANSI_COLOR_CYAN "\n1. Yearly Calendar\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_YELLOW "2. Add notes  \n" ANSI_COLOR_RESET);
      printf(ANSI_COLOR_BLUE"3. Print calendar of a particular month \n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "4. Find the day\n" ANSI_COLOR_RESET);
      printf(ANSI_COLOR_RED "5. Exit the app  \n" ANSI_COLOR_RESET);
      
  

         printf(UWHT "\nEnter your choice: " ANSI_COLOR_RESET);
      scanf("\n%d", &choice);
      switch(choice) {
        case 4:
         printf(" ------------------------------------------------------\n|                    GET WEEK DAY PANEL                |\n ------------------------------------------------------\n\n");
        printf(UWHT "Enter the date to get the weekday: " ANSI_COLOR_RESET);
        scanf("%d %d %d", &day, &month, &year);
        printf( "The day is : "BBLU "%s\n" ANSI_COLOR_RESET, getName(getDayNumber(day, month, year)));
        break;
        case 3:
 printf("\n ------------------------------------------------------\n|                MONTHLY CALENDAR  PANEL               |\n ------------------------------------------------------\n\n");
        printf(ANSI_COLOR_CYAN "1. Calendar with current date \n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_BLUE "2. Random month \n" ANSI_COLOR_RESET);
        
        printf(UWHT "\nEnter your choice:" ANSI_COLOR_RESET);
         int  ch;
       scanf("%d",&ch);
        switch(ch){
       case 2:
        printf("\n ------------------------------------------------------\n|                PRINT ANY RANDOM MONTH                |\n ------------------------------------------------------\n");
              printf(UWHT "\nEnter month and year: " ANSI_COLOR_RESET);
               scanf("%d %d", &month, &year);

               monthlyCalendar(month,year);
               
        break;
       case 1:
       printf("\n ------------------------------------------------------\n|                CURRENT DATE CALENDAR                 |\n ------------------------------------------------------\n");
        printf("\nTHE CURRENT DATE IS : %02d-%02d-%d\n", tm.tm_mday , tm.tm_mon + 1,tm.tm_year + 1900);
        printf(ANSI_COLOR_YELLOW "Calendar according to current date: \n" ANSI_COLOR_RESET);
        monthlyCalendar(tm.tm_mon + 1,tm.tm_year + 1900);
       break;
       default: printf("error in input");
       break;
        }
        break;
        case 1:
        printf("\n ------------------------------------------------------\n|              YEARLY CALENDAR  PANEL                  |\n ------------------------------------------------------\n\n");
        printf(UWHT "\nEnter your desired year: " ANSI_COLOR_RESET);
        scanf("%d",&year);
        yearlyCalendar(year);
        
        break;
         case 2:
          printf("\n ------------------------------------------------------\n|                     ADD NOTES PANEL                  |\n ------------------------------------------------------\n\n");
        printf(UWHT "Enter the date to add the note:  " ANSI_COLOR_RESET);
        scanf("%d %d %d", &note.day, &note.month, &note.year);
        flush();
        printf(ANSI_COLOR_YELLOW "Enter the note: " ANSI_COLOR_RESET);
        fgets(note.note, 255, stdin);
        //opening file in append+ (i.e. append and read)
        fp = fopen("note.txt", "a+");
        if (fp == NULL) {
          printf(ANSI_COLOR_RED "FILE NOTE.TXT CAN'T BE OPENED, THUS NOTE CANNOT BE ADDED\n" ANSI_COLOR_RESET);
          exit(1);
        }
        fwrite(&note, sizeof(Note), 1, fp);
        printf(ANSI_COLOR_GREEN "\n-------NOTE ADDED SUCCESSFULLY--------\n"ANSI_COLOR_RESET);
        fclose(fp);
        break;
        case 5:
        printf("Thank You! :D");
        exit(0);
        break;
        default:
        printf("Not a valid option\n");
        break;
      }
    }
    return 0;
}
 //check for a leap year
int isLeapYear( int y ){
    return(y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0));
}
 //Sakamoto Algorithm (reference: https://www.quora.com/How-does-Tomohiko-Sakamotos-Algorithm-work)
int getDayNumber(int d, int m, int y){ //returns the day number

//month codes involving the leap years
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    //from march 1 to february 28/29
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

 
void monthlyCalendar(int m, int y){
 FILE *fp;
    Note* notes, note;
    int len, j, hasNote = 0;
     char *NameOfMonth[] = { NULL/*dummp*/,
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct",
"Nov", "Dec"
    };
    char Week[] = " Sun  Mon  Tue  Wed  Thu  Fri  Sat";
    int DayOfMonth[] =
        { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
    int weekOfTopDay;
    int i,day;
 
    
fp = fopen("note.txt", "rb");
    if (fp == NULL) {
      printf("Couldn't read notes\n");
    }
    
    len = 0;
    while(fread(&note, sizeof(Note), 1, fp)) {
      if (note.year == y && note.month == m) {
          //checking the no. of notes, so that new memory can be allocated dynamically
        len++;
      }
    }
    
  //moves the file pointer at beginning of the file, so that it could start reading again.
    rewind(fp);


    //dynamic memory allocation where all the new notes get allocated.
    j = 0;
    notes = (Note*) malloc (sizeof(Note) * len);
    while(fread(&note, sizeof(Note), 1, fp)) {
        //Searching for the data, if matching to the input 
        
      if (note.year == y && note.month == m) {
          //adding the note which fulfills the condition to the notes(structure) array
        notes[j] = note;
        j++;
      }
    }

    fclose(fp);
    if(isLeapYear(y))
        DayOfMonth[2] = 29;
      printf("\n ------------" ANSI_COLOR_CYAN "%s %d" ANSI_COLOR_RESET "---------------\n|" ANSI_COLOR_RED "%s" ANSI_COLOR_RESET " |\n -----------------------------------\n", NameOfMonth[m], y, Week);
 
 //index of the 1st day of the month
 weekOfTopDay = getDayNumber(1,m,y);


 //printing the empty spaces 
    for(i=0;i<weekOfTopDay;i++)
       printf("     ");


//printing the dates
for(i=weekOfTopDay,day=1;day <= DayOfMonth[m];i++,day++){
      hasNote = 0;
      
      //searches for day in a month which has note with it
      for (j = 0; j < len; j++) {
          if (notes[j].day == day) {
            //it highlights the date and declares that it has a note
            printf(" |%2d|",day);
            hasNote = 1;
           
          }
        }
        
        //rest with no notes.
    if(i%7 != 0 && hasNote ==0)
        printf( ANSI_COLOR_YELLOW "%5d" ANSI_COLOR_RESET,day);
        //for sundays
    if(i%7 == 0 && hasNote == 0)
        printf("|" ANSI_COLOR_GREEN "  %2d" ANSI_COLOR_RESET,day);
    //for some formatting
    if(i % 7 == 6 && hasNote == 0)
        printf(" |\n");
    }   


    ////View Notes
    printf("\n------------------------------------\n" ANSI_COLOR_CYAN "\nEnter a to see the notes:\nPress any key to move to next section\n" ANSI_COLOR_RESET);
    printf( UWHT "\nEnter your choice: " ANSI_COLOR_RESET);
    char ch;
 scanf("\n%c", &ch);
    if (ch == 'a') {
      printf(ANSI_COLOR_YELLOW "Here are list of notes for %s %d\n" ANSI_COLOR_RESET, NameOfMonth[m], y);
      for (j = 0; j < len; j++) {
     //searches for details from the structure pointer
       if(notes[j].month == m && notes[j].year == y)
       { printf(ANSI_COLOR_GREEN "%d: %s" ANSI_COLOR_RESET, notes[j].day, notes[j].note);}
    else{
        printf(ANSI_COLOR_RED "-------NO NOTES FOR THIS MONTH-------" ANSI_COLOR_RESET);
    }

      }
    } else {
      return;
    }
    
    //for previous and next months 
    void changingCalendar(){
           printf("\n ------------" ANSI_COLOR_CYAN "%s %d" ANSI_COLOR_RESET "---------------\n|" ANSI_COLOR_RED "%s" ANSI_COLOR_RESET " |\n -----------------------------------\n", NameOfMonth[m], y, Week);
 weekOfTopDay = getDayNumber(1,m,y);
    for(i=0;i<weekOfTopDay;i++)
       printf("     ");


for(i=weekOfTopDay,day=1;day <= DayOfMonth[m];i++,day++){
      hasNote = 0;
      for (j = 0; j < len; j++) {
          //searches for day in a month which has note
          if (notes[j].day == day && notes[j].month == m) {
            printf(" |%2d|",day);
            hasNote = 1;
           
          }
        }
        
        //rest with no notes.
    if(i%7 != 0 && hasNote ==0)
        printf( ANSI_COLOR_YELLOW "%5d" ANSI_COLOR_RESET,day);
    if(i%7 == 0 && hasNote == 0)
        printf("|" ANSI_COLOR_GREEN "  %2d" ANSI_COLOR_RESET,day);
    if(i % 7 == 6 && hasNote == 0)
        printf(" |\n");
    } 

    //view notes 
  printf("\n------------------------------------\n" ANSI_COLOR_CYAN "\nEnter a to see the notes:\nPress any key to move to next section\n" ANSI_COLOR_RESET);
   printf(UWHT "\nEnter your choice: ");
   char ch;
   
 scanf("\n%c", &ch);
 if (ch == 'a') {
     
      printf(ANSI_COLOR_YELLOW "Here are list of notes for %s %d\n" ANSI_COLOR_RESET, NameOfMonth[m], y);
     
      for (j = 0; j < len; j++) {
          //searches for details from the structure pointer
     if(notes[j].month == m && notes[j].year == y)
       { printf(ANSI_COLOR_GREEN "%d: %s\n" ANSI_COLOR_RESET, notes[j].day, notes[j].note);}
    else{
        printf(ANSI_COLOR_RED "----------NO NOTES FOR THIS MONTH!--------" ANSI_COLOR_RESET);
    }
      }
    } else {
      return;}
    }
    

    //the monthly calendar subsection (more options) 
    
    
    while(1){
    int x;
     printf("\n ------------------------------------------------------\n|             MONTHLY CALENDAR  SUBSECTION             |\n ------------------------------------------------------\n");
    printf(ANSI_COLOR_CYAN "\n 0. Show PREVIOUS month\n 1. Show NEXT month\n 2. Delete notes\n 3. Update notes\n 4. EXIT \n" ANSI_COLOR_RESET);
    printf(UWHT "\nEnter your choice: " ANSI_COLOR_RESET);
    scanf("%d",&x);

    //next month
     if(x == 1)          
    {
        //increasing the index of month 
        m++;
        if(m > 12)
        {
            
            m = 1;
            
            // if m >12 , increasing the index of year.
            y++;
        }
        changingCalendar();
    }
    
//previous month
    else if(x == 0)            
    {
        //decreasing the index of month
        m--;
        if(m < 1)
        {
            m = 12;
            // if m<1, i.e. by january -1, previous year starts printing.
            y--;
        }
        changingCalendar();
    }
    
    //delete notes 
     else if(x==2) {
       printf("\n ------------------------------------------------------\n|                   DELETE NOTES PANEL                 |\n ------------------------------------------------------\n\n");
    FILE *fp1, *fp2;
    Note n;
    int x,mon, y;
   
    fp1 =  fopen("note.txt","r");
    fp2 = fopen("temp.txt","w");
     printf(UWHT "Enter the date for which note has to be deleted: " ANSI_COLOR_RESET);
    scanf("%d %d %d", &x, &mon, &y);
    int found = 0;
    while(fread(&n,sizeof(Note),1,fp1)){
        //searches for the element to be deleted
        
        if(n.day == x && n.month == mon && n.year == y){
          found = 1;
        }
        
        //rest of the elements written to the temp.txt file
        else{
             fwrite(&n,sizeof(Note),1,fp2);
        }
    }
   
  
    
    fclose(fp1);
    fclose(fp2);
     
   
  if(found){
        fp2 = fopen("temp.txt","r");
        fp1 = fopen("note.txt","w");
        
        //reading the contents of temp.txt and overwriting the original content of note.txt 
        while(fread(&n, sizeof(Note),1,fp2)){
            fwrite(&n, sizeof(Note),1,fp1);
        }
        fclose(fp1);
        fclose(fp2);
        
     
        
        printf( ANSI_COLOR_GREEN "\n--------NOTE DELETED SUCCESSFULLY--------\n" ANSI_COLOR_RESET);
    }
else{
    printf(ANSI_COLOR_RED "\n--------NO NOTE FOUND TO BE DELETED!---------\n" ANSI_COLOR_RESET);
}
    
     remove("temp.txt");
   
    }
    
    //update notes
    else if(x == 3){
       printf("\n\n ------------------------------------------------------\n|                  UPDATE NOTES PANEL                  |\n ------------------------------------------------------\n\n");
     Note n1;
     FILE *fp1, *fp2;
     int x,mon, y;
   
    int found = 0;
       fp1 = fopen("note.txt","r");
       fp2 = fopen("temp.txt","w");
    printf(UWHT "Enter the date for which note has to be updated: " ANSI_COLOR_RESET);
    scanf("%d %d %d", &x, &mon, &y);
    
    //reading through the note.txt
       while(fread(&n1,sizeof(Note),1,fp1)){
           
           //searching for the element to be updated 
          if(n1.day == x && n1.month == mon && n1.year == y){
              found =1;
              flush();
              printf(ANSI_COLOR_YELLOW "Enter the new note: " ANSI_COLOR_RESET);
              scanf("%[^\n]", n1.note);

          }
          //adding to temp.txt (the new note as well)
           fwrite(&n1,sizeof(Note),1,fp2);
       }
  
   
  
    fclose(fp1);
    fclose(fp2);
    if(found){
        fp2 = fopen("temp.txt","r");
        fp1 = fopen("note.txt","w");
        //reading the contents of temp.txt and overwriting the original content of note.txt 
        while(fread(&n1, sizeof(Note),1,fp2)){
            fwrite(&n1, sizeof(Note),1,fp1);
        }
        fclose(fp1);
        fclose(fp2);
        
      
        printf( ANSI_COLOR_GREEN "\n------NOTE UPDATED SUCCESSFULLY------\n" ANSI_COLOR_RESET);
    }
else{
    printf(ANSI_COLOR_RED "\n-------NO NOTES FOUND TO BE UPDATED!------\n" ANSI_COLOR_RESET);
}
    remove("temp.txt");
    }
        
    
    else if(x==4) {
       break;
    }
    
    }
}



 
char *getName(int day){ //returns the name of the day
   switch(day){
      case 0 :return("Sunday\n");
      case 1 :return("Monday\n");
      case 2 :return("Tuesday\n");
      case 3 :return("Wednesday\n");
      case 4 :return("Thursday\n");
      case 5 :return("Friday\n");
      case 6 :return("Saturday\n");
      default:return("Error: Invalid Argument Passed");
   }
}


void yearlyCalendar(int y){
     int m,i,day,weekOfTopDay;
 char *NameOfMonth[] = { NULL/*dummp*/,
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct",
"Nov", "Dec"
    };
    char Week[] = " Sun  Mon  Tue  Wed  Thu  Fri  Sat";
    int DayOfMonth[] =
        { -1,31,28,31,30,31,30,31,31,30,31,30,31 };


   char *months_full[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};



   if(isLeapYear(y)){
        DayOfMonth[2] = 29;
        printf("\n---------%d IS A LEAP YEAR!!!!!!-----------\n",y);
   }
printf("\n-------%d YEARLY CALENDAR---------\n",y);
//loops through each month
   for(m=0;m<12;m++){
    //index of the 1st day of the month.
      weekOfTopDay=getDayNumber(1,m+1,y);
   
   
    
 printf("\n ------------" ANSI_COLOR_CYAN "%s %d" ANSI_COLOR_RESET "---------------\n|" ANSI_COLOR_RED "%s" ANSI_COLOR_RESET " |\n -----------------------------------\n", NameOfMonth[m+1], y, Week);
     
     //before the index of the 1st day of the month, empty spaces are printed 
      for(int i=0;i<weekOfTopDay;i++)
       printf("     ");


//at the index, it loops from 1 to no. of days in a month, by checking through DaysOfMonth array
      for (i = weekOfTopDay, day = 1; day <= DayOfMonth[m+1]; i++, day++){
          
         
       if (i % 7 != 0)
	    printf (ANSI_COLOR_YELLOW "%5d" ANSI_COLOR_RESET, day);
	    
	    //for sundays 
	  if (i % 7 == 0)
	    printf ("|" ANSI_COLOR_GREEN "  %2d" ANSI_COLOR_RESET, day);
	    
	  if (i % 7 == 6)
	    printf (" |\n");
        }
        printf ("\n------------------------------------");
      }
      
      
      //holidays in a month
  while (1)
    {
      int holiday;
      printf (UWHT "\n\nCheck for Holidays in a given month" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\n\n 1. January\n 2. February\n 3. March\n 4. April\n 5. May\n 6. June\n 7. July\n 8. August\n 9.September\n 10.October\n 11.November\n 12. December\n -1. EXIT\n" ANSI_COLOR_RESET);
    printf(UWHT "\nEnter your choice: " ANSI_COLOR_RESET);
      scanf ("%d", &holiday);
      
      //if -1 is pressed, breaks the statement.
       if(holiday == -1){
          break;
          }
      printf (ANSI_COLOR_YELLOW "\nGazetted holidays of NITJ %d for %s month:\n" ANSI_COLOR_RESET,
	      y,months_full[holiday - 1]);
      
//Holidays of a given year for 1-12 months
          if(y == 2022 && holiday != -1){
      switch (holiday)
	{
	case 1:
	  printf (ANSI_COLOR_GREEN " 26th January : Republic Day" ANSI_COLOR_RESET);
	  break;
	case 2:
	  printf (ANSI_COLOR_RED "no holiday in February :(" ANSI_COLOR_RESET);
	  break;
	case 3:
	  printf (ANSI_COLOR_GREEN " 1st March : Maha Shivratri\n 18th March : Holi" ANSI_COLOR_RESET);
	  break;
	case 4:
	  printf (ANSI_COLOR_GREEN " 14th April : Mahavir Jayanti \n 15th April : Good Friday" ANSI_COLOR_RESET);
	  break;
	case 5:
	  printf (ANSI_COLOR_GREEN " 3rd May: Id-ul-fitr \n16th May: Buddha Purnima" ANSI_COLOR_RESET);
	  break;
	case 6:
	  printf (ANSI_COLOR_RED "no holiday in June :(" ANSI_COLOR_RESET);
	  break;
	case 7:
	  printf (ANSI_COLOR_GREEN " 10th July: Id'ul Juha(Bakrid)" ANSI_COLOR_RESET);
	  break;
	case 8:
	  printf(ANSI_COLOR_GREEN " 9th August : Muharram \n 15th August : Independence Day \n 19th August : Janmasthmi" ANSI_COLOR_RESET);
	  break;
	case 9:
	  printf (ANSI_COLOR_RED "no holiday in September :(" ANSI_COLOR_RESET);
	  break;
	case 10:
	  printf( ANSI_COLOR_GREEN " 2nd October : Mahatma Gandhi's Birthday \n 5th October : Dussehra \n 9th October : Id-e-Milad \n 24th October : Diwali" ANSI_COLOR_RESET);
	  break;
	case 11:
	  printf (ANSI_COLOR_GREEN " 8th November : Guru Nanak's birthday" ANSI_COLOR_RESET);
	  break;
	case 12:
	  printf (ANSI_COLOR_GREEN " 25th December : Christmas Day" ANSI_COLOR_RESET);
	  break;

	default: printf ("Error: Invalid Argument Passed");
break;
	}
    }
    else if(y == 2021 && holiday != -1 ){
          switch (holiday)
	{
	case 1:
	  printf (ANSI_COLOR_GREEN " 26th January : Republic Day" ANSI_COLOR_RESET);
	  break;
	case 2:
	  printf (ANSI_COLOR_RED "no holiday in February :(" ANSI_COLOR_RESET);
	  break;
	case 3:
	  printf (ANSI_COLOR_GREEN " 11st March : Maha Shivratri\n 29th March : Holi" ANSI_COLOR_RESET);
	  break;
	case 4:
	  printf (ANSI_COLOR_GREEN " 2nd April : Good Friday \n 25th April : Mahavir Jayanti " ANSI_COLOR_RESET);
	  break;
	case 5:
	  printf (ANSI_COLOR_GREEN " 14th May: Id-ul-fitr \n26th May: Buddha Purnima" ANSI_COLOR_RESET);
	  break;
	case 6:
	  printf (ANSI_COLOR_RED "no holiday in June :(" ANSI_COLOR_RESET);
	  break;
	case 7:
	  printf (ANSI_COLOR_GREEN " 21st July: Id'ul Juha(Bakrid)" ANSI_COLOR_RESET);
	  break;
	case 8:
	  printf(ANSI_COLOR_GREEN " 15th August : Independence Day \n 19th August : Muharram \n Janmasthmi : 30th August" ANSI_COLOR_RESET);
	  break;
	case 9:
	  printf (ANSI_COLOR_RED "no holiday in September :(" ANSI_COLOR_RESET);
	  break;
	case 10:
	  printf( ANSI_COLOR_GREEN " 2nd October : Mahatma Gandhi's Birthday \n 15th October : Dussehra \n 19th October : Id-e-Milad" ANSI_COLOR_RESET);
	  break;
	case 11:
	  printf (ANSI_COLOR_GREEN " 4th October : Diwali\n 19th November : Guru Nanak's birthday" ANSI_COLOR_RESET);
	  break;
	case 12:
	  printf (ANSI_COLOR_GREEN " 25th December : Christmas Day" ANSI_COLOR_RESET);
	  break;

	default: printf ("Error: Invalid Argument Passed");
break;
	}
    }
    else if(y == 2020 && holiday != -1 ){
          switch (holiday)
	{
	case 1:
	  printf (ANSI_COLOR_GREEN " 26th January : Republic Day" ANSI_COLOR_RESET);
	  break;
	case 2:
	  printf (ANSI_COLOR_RED "no holiday in February :(" ANSI_COLOR_RESET);
	  break;
	case 3:
	  printf (ANSI_COLOR_GREEN " 11st March : Maha Shivratri\n 29th March : Holi" ANSI_COLOR_RESET);
	  break;
	case 4:
	  printf (ANSI_COLOR_GREEN " 2nd April : Good Friday \n 25th April : Mahavir Jayanti " ANSI_COLOR_RESET);
	  break;
	case 5:
	  printf (ANSI_COLOR_GREEN " 14th May: Id-ul-fitr \n26th May: Buddha Purnima" ANSI_COLOR_RESET);
	  break;
	case 6:
	  printf (ANSI_COLOR_RED "no holiday in June :(" ANSI_COLOR_RESET);
	  break;
	case 7:
	  printf (ANSI_COLOR_GREEN " 21st July: Id'ul Juha(Bakrid)" ANSI_COLOR_RESET);
	  break;
	case 8:
	  printf(ANSI_COLOR_GREEN " 15th August : Independence Day \n 19th August : Muharram \n Janmasthmi : 30th August" ANSI_COLOR_RESET);
	  break;
	case 9:
	  printf (ANSI_COLOR_RED "no holiday in September :(" ANSI_COLOR_RESET);
	  break;
	case 10:
	  printf( ANSI_COLOR_GREEN " 2nd October : Mahatma Gandhi's Birthday \n 15th October : Dussehra \n 19th October : Id-e-Milad" ANSI_COLOR_RESET);
	  break;
	case 11:
	  printf (ANSI_COLOR_GREEN " 4th October : Diwali\n 19th November : Guru Nanak's birthday" ANSI_COLOR_RESET);
	  break;
	case 12:
	  printf (ANSI_COLOR_GREEN " 25th December : Christmas Day" ANSI_COLOR_RESET);
	  break;

	default: printf ("Error: Invalid Argument Passed");
break;
	}
    }
    
   
}
}

