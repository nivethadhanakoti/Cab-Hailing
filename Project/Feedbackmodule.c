//Structure for storing feedback from passenger

struct Feedback {
    float rating;
    char comments[100];

};

//Function to input feedback from passenger
void getFeedback(struct Feedback *feedback) {
    printf("\t\tPlease provide your feedback:\n");
    printf("\t\tPlease Give us your Rating\n\t\t1-Bad\n\t\t2-Not Satisfied\n\t\t3-Average\n\t\t4-Good\n\t\t5-Excellent\n\n");

    printf("\t\tRating (1-5): ");
    scanf("%f", &feedback->rating);

    printf("\t\tComments (up to 100 characters): ");
    scanf(" %[^\n]", feedback->comments);
}

//Function to display the feedback on screen again
void displayFeedback(const struct Feedback *feedback) {
    printf("\t\tRating  : %.2f\n", feedback->rating);
    printf("\t\tComments: %s\n", feedback->comments);
}
