//Login Functions
//For login
#define DIVISOR 10000
//Function to generate OTP
int gen_otp()
{
    int otp;
    srand((unsigned int) time(NULL));
    otp=rand()%DIVISOR;
    return otp;
}

//Function to check the presence of mobile number in records
int check_mobileno(char *mobno)
{
    char filename[30],buffer[160];
    strcpy(filename,"customers2.txt");

    FILE *f;
    f=fopen(filename,"r");
    while (fgets(buffer,150,f) != NULL)
    {
        char* token = strtok(buffer, "^");
        if (strcmp(token,mobno) == 0)
        {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return -1;
}

//Function to enable passenger signup
void passenger_signup(){

char ch,pname[30],email[50],pass_age[3],pass_phNo[11];

     FILE *f;
    f=fopen("customers2.txt","a");

    //for (int i=0;i<13;i++)
     while (true)
        {printf("\n\t\tPlease input your phone number :"); // 11 characters
        scanf("%s",pass_phNo);
        //scanf("%c",&ch);

        if (check_mobileno(pass_phNo)==1)
                printf("\t\tPhone number already exists. Please enter a new number!\n ");
        else
            break;}

        printf("\n\t\tPlease input passenger name: " ); // 30 characters
        scanf("%c",&ch);
        scanf("%[^\n]",pname);
        printf("\n\t\tPlease input age of %s:",pname); // 3 characters
        scanf("%c",&ch);
        scanf("%s",pass_age);
        printf("\n\t\tPlease input Email address of %s:",pname); // 50 characters
        scanf("%c",&ch);
        scanf("%[^\n]s",email);

        fprintf(f,"\t\t%s^%s^%s^%s^\n",
                pass_phNo,pname,pass_age,email);
    //} // end for

    fclose(f);
    //printf("Database updated successfully! ");
}

// To get the current hour
int getCurrHour(){
    time_t now;
    struct tm *now_tm;
    int hour;

    now = time(NULL);
    now_tm = localtime(&now);
    hour = now_tm->tm_hour;
    return hour;
    //printf("the hour is %d\n", hour);
}
