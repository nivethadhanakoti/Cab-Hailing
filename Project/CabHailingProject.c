
//Importing libraries and defining constants
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

#include "Login functions.c"
#include "Feedbackmodule.c"
#include "BillEstAndCalc.c"
#include "DistanceFunctions.c"
#include "SortingFunctions.c"


//For file processing
#define MAX_LINE_LENGTH 1000
#define MAX_FIELD_LENGTH 8


//Structure for importing driver database from the file
typedef struct {
    char name[50];
    char age[5];
    char phoneNumber[20];
    char address[250];
    char vehicleNumber[20];
    char vehicleType[20];
    char vehicleBrand[20];
    char vehicleModel[20];
    float ratings;
    char vaccinated[2];
} details1;

//Main Function Begins

int main() {

    //Login or Signup of Customer

    printf("\t\t-----------------------------------------------------------------------------------------------------------------\n");
    printf("\n\n");
    printf("\t\t\t\t\t\tWelcome to Ola Inspired- Cab Booking Services!\n");
    printf("\n\n");
    printf("\t\t-----------------------------------------------------------------------------------------------------------------\n");

    int choice=0;
    int otp,otpEntered,phCheck;
    char phNo[11];
    while (choice != 3)
    {
        printf("\n\t\t--------------------------------------------------  MAIN MENU  --------------------------------------------------\n");
        printf("\t\tOption 1: Passenger Login\n");
        printf("\t\tOption 2: Passenger Setup\n");
        printf("\t\tOption 3: Exit\n");
        printf("\t\t-----------------------------------------------------------------------------------------------------------------\n");
        printf("\t\tPlease input your choice: ");
        scanf("%d",&choice);

        if (choice < 1 || choice > 3)
        {
            printf("\t\tInvalid choice. Please input a value between 1 and 3\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("\t\tPlease input your phone number: ");
            scanf("%s",phNo);
            if (strlen(phNo)==10)
            {
            phCheck=check_mobileno(phNo);
            if (phCheck==1)
            {
            otp=gen_otp();
            printf("\t\tPlease input %d OTP to continue\n", otp);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------\n");
            printf("\t\tInput the OTP to login: ");
            scanf("%d",&otpEntered);
            while (true)
            {if (otp==otpEntered)
            {
                printf("\t\tWelcome !");
                goto afterLogin;
                processRestarts:
                break;
            }
            else{
                printf("\t\tThis is not the otp entered. Kindly enter the correct otp.\n");
                scanf("%d",&otpEntered);
            }
            }
            }
            else
            printf("\t\tThis phone number does not exist in the application database. Kindly enter a valid number! ");
        }

            else
            printf("\t\tPhone number doesn't have 10 digits! Please enter a valid one! ") ;

            break;

        case 2:
            passenger_signup();
            break;

        case 3:
            printf("\t\tLooking forward to seeing you soon!\n\n\n");
            exit(1);
        }
    }

    afterLogin:
    {
    int x=0;
    details1 drivers[30];
    details2 availableDrivers1[30], availableDrivers2[30], availableDrivers3[30];

    FILE *file;
    char line[MAX_LINE_LENGTH];
    char *field;
    char temp[10];

    // Open the Driver Database file
    file = fopen("drivers.txt", "r");
    if (file == NULL) {
        printf("\t\tError opening file.\n");
        return 1;
    }

    // Read and process each line of the CSV file
    while (fgets(line, sizeof(line), file) != NULL) {

        // Split the line into fields and append field data into structure

        field = strtok(line, "^");
        if (field != NULL) {
            strcpy(drivers[x].name, field);
        }

        field = strtok(NULL, "^");
        if (field != NULL) {
            strcpy(drivers[x].age, field);
        }

        field = strtok(NULL, "^");
        if (field != NULL) {
            strcpy(drivers[x].phoneNumber, field);
        }

        field = strtok(NULL, "^");
        if (field != NULL) {
            strcpy(drivers[x].address, field);
        }

        field = strtok(NULL, "^");
        if (field != NULL) {
            strcpy(drivers[x].vehicleNumber, field);
        }

        field = strtok(NULL, "^");
        if (field != NULL) {
            strcpy(drivers[x].vehicleType, field);
        }

        field = strtok(NULL, "^");
        if (field != NULL) {
            strcpy(drivers[x].vehicleBrand, field);
        }

        field = strtok(NULL, "^");
        if (field != NULL) {
            strcpy(drivers[x].vehicleModel, field);
        }

        field = strtok(NULL, "^");
        if (field != NULL) {
            drivers[x].ratings = atof(field);
        }

        field = strtok(NULL, "^");
        if (field != NULL) {
            strcpy(drivers[x].vaccinated, field);
        }

        x++;

        if (x>=MAX_LINE_LENGTH) break;
    }

    // Close the file
    fclose(file);

    //Map and distance details

    // Assign points with coordinates
    int points[V][2] = {{1, 2}, {3, 3}, {3, 1}, {3, 4}, {2, 6}, {4, 1}, {2, 3}, {6, 1}, {5, 5}, {0, 0}};

    // Assign point names
    char* pointNames[V] = {"Adyar", "Avadi", "Tambaram", "Chrompet", "Perungalathur", "Velachery", "Guindy", "Airport", "Kolathur", "Porur"};

    // Create the graph adjacency matrix
    int graph[V][V];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = (points[i][0] - points[j][0]) * (points[i][0] - points[j][0]) +
                              (points[i][1] - points[j][1]) * (points[i][1] - points[j][1]);
        }
    }


    //BOOKING STARTS HERE

    char mode[20];

    //Obtaining user inputs for travel initialization

    printf("\n\n");
    printf("\t\t-------------------------------------------  USER INPUT FOR BOOKING  -------------------------------------------- \n");

    printf("\t\tVehicle Modes Available: \n");
    printf("\t\tAuto\n\t\tSedan\n\t\tMini Sedan\n\t\tSUV\n\t\tInnova\n");

    printf("\t\tPlease input the mode of travel you prefer: ");
    scanf("\n");
    scanf("%[^\n]s", mode);

    int bookch;
    printf("\n\t\t1. Instant Booking\n\t\t2. Scheduled Booking (Scheduled atleast 30 minutes ahead of current time)\n");
    printf("\t\tDo you want to do a scheduled booking or an instant booking: ");
    scanf("%d",&bookch);
    if (bookch==2){
        int hr,min;
        char dayhalf[3],pickupPt[15],dropPt[15];
        printf("\n\t\tPlease input what time you would like to schedule your ride(hour:minute am/pm): ");
        scanf("%d:%d %s",&hr,&min,dayhalf);
        printf("\t\t1.Adyar       2.Avadi          3.Tambaram\n");
        printf("\t\t4.Chrompet    5.Perungalathur  6.Velachery\n");
        printf("\t\t7.Guindy      8.Airport        9.Kolathur\n\t\t10.Porur\n\n");
        printf("\t\tPlease input your pick-up point: ");
        scanf("%s",pickupPt);
        printf("\t\tPlease input your drop-point: ");
        scanf("%s",dropPt);
        printf("\n");
        printf("\t\tBooking confirmed!\n\n");
        printf("\t\tAn advance booking fee of %d rupees will apply for this ride\n",AdvanceFee);
        printf("\t\tThe driver details will be sent to you 15 minutes before your ride!\n");
        goto processRestarts;
    }
    int hour=getCurrHour();
    printf("\n");
    printf("\t\tTransport Services Available at:\n");
    printf("\t\t1.Adyar       2.Avadi          3.Tambaram\n");
    printf("\t\t4.Chrompet    5.Perungalathur  6.Velachery\n");
    printf("\t\t7.Guindy      8.Airport        9.Kolathur\n\t\t10.Porur\n\n");

    // Source and destination input
    int source, destination , distances[V];
    printf("\n\t\tPlease input your pick-up point: ");
    scanf("%d", &source);
    source--;
    printf("\t\tPlease input your drop-point: ");
    scanf("%d", &destination);
    destination--;

    // Perform Dijkstra's algorithm
    dijkstra(graph, source, destination, pointNames, distances);

    // Print the minimum distance
    printf("\n\t\tMinimum Distance between %s and %s is %d km\n", pointNames[source], pointNames[destination], distances[destination]);


    int y=0;
    int locationIndex=0, free=0;
    srand(time(NULL));


    //Filtering driver records and storing relevant details in an other structure

    for(int i = 0; i < x; i++) {
        if (stricmp(mode, drivers[i].vehicleType) == 0 ) {
            strcpy(availableDrivers1[y].name, drivers[i].name);
            strcpy(availableDrivers1[y].phoneNumber, drivers[i].phoneNumber);
            strcpy(availableDrivers1[y].vehicleNumber, drivers[i].vehicleNumber);
            strcpy(availableDrivers1[y].vehicleBrand, drivers[i].vehicleBrand);
            strcpy(availableDrivers1[y].vehicleModel, drivers[i].vehicleModel);
            availableDrivers1[y].ratings = drivers[i].ratings;
            locationIndex = rand() % 10;
            strcpy(availableDrivers1[y].location, pointNames[locationIndex]);
            availableDrivers1[y].distance = distances[locationIndex];
            free = rand() % 2;
            availableDrivers1[y].availability = free;
        y++;

        }
    }

    printf("\n\t\tMatching Mode Drivers: \n");
    for (int i = 0; i < y; i++) {
        printf("\t\tName:%s,Ph No.:%s,Vehicle No.:%s,Location:%s,Away by:%dkm,Ratings:%.2f,Availability: %d\n", availableDrivers1[i].name, availableDrivers1[i].phoneNumber, availableDrivers1[i].vehicleNumber, availableDrivers1[i].location, availableDrivers1[i].distance, availableDrivers1[i].ratings, availableDrivers1[i].availability);
    }
    printf("\n\n");

    //Separating out free drivers
    int z=0;
    for (int i=0; i < y; i++) {
    if (availableDrivers1[i].availability == 1) {
            strcpy(availableDrivers2[z].name, availableDrivers1[i].name);
            strcpy(availableDrivers2[z].phoneNumber, availableDrivers1[i].phoneNumber);
            strcpy(availableDrivers2[z].vehicleNumber, availableDrivers1[i].vehicleNumber);
            strcpy(availableDrivers2[z].vehicleBrand, availableDrivers1[i].vehicleBrand);
            strcpy(availableDrivers2[z].vehicleModel, availableDrivers1[i].vehicleModel);
            availableDrivers2[z].ratings = availableDrivers1[i].ratings;
            strcpy(availableDrivers2[z].location, availableDrivers1[i].location);
            availableDrivers2[z].distance = availableDrivers1[i].distance;
            z++;
    }

    }

    if (sizeof(availableDrivers2) == 0) {
       printf("\t\tSorry we couldn't find any available drivers! Please try again after some time! \n");
        goto processEnd;
    }

    printf("\t\tFree and Available Drivers: \n");
    for (int i = 0; i < z; i++) {

        printf("\t\tName: %s, Ph. No.: %s, Vehicle No.: %s, Location: %s, Away by: %d km, Ratings: %.2f", availableDrivers2[i].name, availableDrivers2[i].phoneNumber, availableDrivers2[i].vehicleNumber, availableDrivers2[i].location, availableDrivers2[i].distance, availableDrivers2[i].ratings);
        printf("\n");
    }
    printf("\n\n");

    //Sorting the driver records based on the distance between driver and passenger

    qsort(availableDrivers2, z, sizeof(details2), compareDetails2);

    printf("\t\tDrivers sorted based on distance first: \n");
    for (int i = 0; i < z; i++) {
        printf("\t\tName: %s, Ph. No: %s, Vehicle No.: %s, Location: %s, Away by: %d km, Ratings: %.2f\n", availableDrivers2[i].name, availableDrivers2[i].phoneNumber, availableDrivers2[i].vehicleNumber, availableDrivers2[i].location, availableDrivers2[i].distance, availableDrivers2[i].ratings);
        //printf("\n");
    }
    printf("\n\n");


    int count = 0;
    int minDistance = availableDrivers2[0].distance;
    for (int i=0; i < z; i++) {
        if (availableDrivers2[i].distance == minDistance) count++;
    }
    
    int w=0;
    if (count > 1) {

        for (int i=0; i < z; i++) {
            if (availableDrivers2[i].distance == minDistance) {
                strcpy(availableDrivers3[w].name, availableDrivers2[i].name);
                strcpy(availableDrivers3[w].phoneNumber, availableDrivers2[i].phoneNumber);
                strcpy(availableDrivers3[w].vehicleNumber, availableDrivers2[i].vehicleNumber);
                strcpy(availableDrivers3[w].vehicleBrand, availableDrivers2[i].vehicleBrand);
                strcpy(availableDrivers3[w].vehicleModel, availableDrivers2[i].vehicleModel);
            availableDrivers3[w].ratings = availableDrivers2[i].ratings;
                strcpy(availableDrivers3[w].location, availableDrivers2[i].location);
            availableDrivers3[w].distance = availableDrivers2[i].distance;
                w++;
            }
        }

    //Sorting the driver records based on the ratings

    qsort(availableDrivers3, w, sizeof(details2), compareRatings2);

    printf("\t\tDrivers sorted based on ratings next: \n");
    for (int i = 0; i < w; i++) {
        printf("\t\tName: %s, Phone No.: %s, Vehicle No.: %s, Location: %s, Away by: %d km, Ratings: %.2f\n", availableDrivers3[i].name, availableDrivers3[i].phoneNumber, availableDrivers3[i].vehicleNumber, availableDrivers3[i].location, availableDrivers3[i].distance, availableDrivers3[i].ratings);
    }
    printf("\n\n");

    }

    //Displaying allotted driver and bill estimate for passenger verification

    printf("\n\t\t---------------------------------------------  DRIVER AVAILABILITY  ---------------------------------------------\n");
    printf("\n");
    if (minDistance >= distances[destination]){
        printf("\t\tSorry we couldn't find any driver in the vicinity! Please try again after some time! \n");
        goto processEnd;
    }

    else{
    if (count = 1) {
    printf("\t\tWe have found a driver nearby!\n\n");
    printf("\t\t------------------------------------------------  DRIVER DETAILS ------------------------------------------------\n");
    printf("\t\tDriver Name     : %s\n\t\tPhone Number    : %s\n\t\tVehicle Number  : %s\n\t\tVehicle Brand   : %s\n\t\tVehicle Model   : %s\n\t\tRatings         : %.2f\n\t\tCurrent Location: %s\n\t\tAway by         : %d km\n\n",
           availableDrivers2[0].name, availableDrivers2[0].phoneNumber, availableDrivers2[0].vehicleNumber, availableDrivers2[0].vehicleBrand, availableDrivers2[0].vehicleModel,
           availableDrivers2[0].ratings, availableDrivers2[0].location, availableDrivers2[0].distance);
    }
    else if (count > 1){
    printf("\t\tWe have found a driver nearby!\n\n");
    printf("\t\t------------------------------------------------  DRIVER DETAILS ------------------------------------------------\n");
    printf("\t\tDriver Name     : %s\n\t\tPhone Number    : %s\n\t\tVehicle Number  : %s\n\t\tVehicle Brand   : %s\n\t\tVehicle Model   : %s\n\t\tRatings         : %.2f\n\t\tCurrent Location: %s\n\t\tAway by         : %d km\n\n",
           availableDrivers3[0].name, availableDrivers3[0].phoneNumber, availableDrivers3[0].vehicleNumber, availableDrivers3[0].vehicleBrand, availableDrivers3[0].vehicleModel,
           availableDrivers3[0].ratings, availableDrivers3[0].location, availableDrivers3[0].distance);
    }
    }

    float billEstimate;

    printf("\t\t------------------------------------------------ BILL ESTIMATION  -----------------------------------------------\n");
    printf("\n");
    billEstimate=billEst(distances[destination]);
    int estArriv=availableDrivers2[0].distance*timePerKm;
    printf("\t\tEstimated time of arrival: %d minutes\n", estArriv);
    printf("\t\tEstimated Bill           : %.2lf rupees\n\n",billEstimate);


    //Confirmation of Booking
    //The passenger can choose to accept or decline the ride

    char userResponse[10];

    printf("\t\t------------------------------------------  CONFIRMATION OF BOOKING  --------------------------------------------\n");
    printf("\n");
    if (estArriv>15){
        printf("\t\tWaiting time is more than 15 minutes. Would you like to accept this ride (yes/no)? ");
    }
    else{
    printf("\t\tWould you like to accept this ride (yes/no)? ");
    }
    scanf("%s", userResponse);
    printf("\n");

    if (stricmp(userResponse, "yes") != 0) {
        printf("\t\tWe are sorry that we couldn\'t find you a suitable ride.\n");
        printf("\t\tLooking forward to seeing you soon!\n\n\n");
        goto processEnd;
    }

    printf("\t\tYou have successfully completed booking your ride!\n");
    printf("\t\tThe booking request will be forwarded to the driver and you can expect the driver anytime now!\n\n");

    //Driver reaches the passenger

    printf("\n\n");
    printf("\t\t------------------------------------------------  DRIVER ARRIVES ------------------------------------------------\n");
    sleep(3);

    //Travelling from source to destination

    printf("\t\t---------------------------------------  OTP VALIDATED. TRAVEL IN PROCESS  --------------------------------------\n");
    sleep(3);
    printf("\t\t----------------------------------------------  REACHED DESTINATION  --------------------------------------------\n\n");

    //Waiting charges and final bill

    printf("\t\t----------------------------------------------  FINAL BILL GENERATION -------------------------------------------\n\n");

    float waitingTime;
    waitingTime=rand()%10;
    //scanf("%f",&waitingTime);

    float surgeFee=0;
    if ((hour>=8 && hour<=10) || (hour>=18 && hour<=20)){
        surgeFee=0.2*billEstimate;
    }
    float waitingCharges = calculateWaitingCharges(waitingTime);
    float bill = calculateFinalBill(billEstimate, waitingCharges,surgeFee);
    printf("\t\tThe waiting charges for %.2f minutes is: %.2f rupees\n", waitingTime, waitingCharges);
    if (surgeFee!=0){
        printf("\t\tThe surge fee is                       : %.2f rupees\n",surgeFee);
    }
    else{
        printf("\t\tThere is no surge fee.\n");
    }
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\tThe final bill amount to be paid is    : %.2f rupees\n", bill);
    printf("\t\t-----------------------------------------------------\n\n");

    //Confirmation of payment completion

    char filler[1];
    printf("\t\tPress any key to verify payment completion!");
    scanf(" %[^\n]", filler);

    printf("\n\t\t----------------------------------------------  PAYMENT COMPLETED  ----------------------------------------------\n\n");

    //Feedback from passenger

    printf("\t\t---------------------------------------------------  FEEDBACK  --------------------------------------------------\n\n");

    struct Feedback feedback;

    getFeedback(&feedback);

    printf("\n\t\tThank you for your valuable feedback\n");
    displayFeedback(&feedback);


    //Journey and Process Completion

    printf("\n\t\t---------------------------------------------------  THE END  ---------------------------------------------------\n");
    printf("\t\t\t\t\t\t\tLooking forward to seeing you soon!\n\n\n");
    printf("\t\t-----------------------------------------------------------------------------------------------------------------\n");
    }


    processEnd:
        goto processRestarts;

    return 0;

}
