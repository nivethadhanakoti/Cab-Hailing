//Function to compare, helps in sorting of drivers

//Structure for storing filtered driver database
typedef struct {
    char name[50];
    char phoneNumber[20];
    char vehicleNumber[20];
    char vehicleBrand[20];
    char vehicleModel[20];
    float ratings;
    char location[100];
    int distance;
    int availability;
} details2;


int compareDetails2(const void *a, const void *b) {
    const details2 *detailsA = (const details2 *)a;
    const details2 *detailsB = (const details2 *)b;

    // Compare based on the distance member
    if (detailsA->distance < detailsB->distance) {
        return -1;
    } else if (detailsA->distance > detailsB->distance) {
        return 1;
    } else {
        return 0;
    }
}

int compareRatings2(const void *a, const void *b) {
    const details2 *detailsA = (const details2 *)a;
    const details2 *detailsB = (const details2 *)b;

    // Compare based on the distance member
    if (detailsA->ratings > detailsB->ratings) {
        return -1;
    } else if (detailsA->ratings < detailsB->ratings) {
        return 1;
    } else {
        return 0;
    }
}




