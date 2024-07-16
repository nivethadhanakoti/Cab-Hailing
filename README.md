# Cab-Hailing
Cab Hailing Project [Description of files, programs and executables]

drivers.txt and customer.txt are the database text files for storing driver and customer database.

CabHailingProject.c, Login functions.c, DistanceFunctions.c, SortingFunctions.c, BillEstAndCalc.c and Feedbackmodule.c are the 6 C programming files that our project comprises of. 
    ->Login Functions.c contains the functions for the login, otp and mobile number verification, and signup of passengers.
    ->DistanceFunctions.c contains the code for the Dijsktra algorithm implemented to find the minimum distance between two coordinates on the map.
    ->SortingFunctions.c contains the sorting algorithms for sorting driver records based on distance from passenger (ascending) and driver ratings (descending).
    ->BillEstAndCalc.c contains code for calculating the estimated bill amount based on ride distance, waiting charges and final bill amount.
    ->Feedbackmodule.c contains functions for receiving feedback (star rating and comments) from the passenger.

Of these, CabHailingProject.c is the main file which contains the input and output statements. The remaining files are linked to this file internally. Thus it will be enough to compile this one file and run the executable version.

CabHailing.exe is the executable file of CabHailingProject.c

