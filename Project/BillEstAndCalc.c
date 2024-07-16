//For bill calculation
#define fixedCharge 60
#define fixedKM 3
#define chargePerKm 6
#define timePerKm 2
#define AdvanceFee 50

//Function to estimate the bill amount
float billEst(int dist)
{   float estBill;
    if (dist<=fixedKM)
{
    estBill=fixedCharge;
}
    else
    {estBill = fixedCharge+chargePerKm*(dist-fixedKM);}

    return estBill;
}

//Function to calculate waiting charges based on input waiting time
float calculateWaitingCharges(float waitingTime)
{
    float waitingChargesPerThreeMinutes = 2.0;
    float waitingCharges = (waitingTime / 3.0) * waitingChargesPerThreeMinutes;
    return waitingCharges;
}

//Function to calculate the final bill after journey completion
float calculateFinalBill(float billEstimate, float waitingCharges, float surgeFee)
{
    float finalBill = billEstimate + waitingCharges + surgeFee;
    return finalBill;
}
