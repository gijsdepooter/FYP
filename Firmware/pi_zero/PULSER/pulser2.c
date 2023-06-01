#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

// Define the pulse duration in microseconds
#define PULSE_DURATION 5
#define SIZE 3
#define ROWS 3
int main()
{
    // Initialize the GPIO pins
    int pulseA = 3; // GPIO pin 22 (wiringPi pin 3)
    int pulseB = 4; // GPIO pin 23 (wiringPi pin 4)
    int pulseC = 5; // GPIO pin 24 (wiringPi pin 5)

    // Initialize the wiringPi library
    if (wiringPiSetup() == -1)
    {
        printf("Error: Failed to initialize wiringPi library!\n");
        return 1;
    }

    // Set the GPIO pins to output mode
    pinMode(pulseA, OUTPUT);
    pinMode(pulseB, OUTPUT);
    pinMode(pulseC, OUTPUT);

    FILE *file = fopen("pulsestring.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return 1;
    }

    char str[SIZE + 1];
    int pulseSequences[ROWS][SIZE];
    int i = 0;

    while (fgets(str, SIZE + 1, file) != NULL) {
        for (int j = 0; j < SIZE; j++) {
            pulseSequences[i][j] = str[j] - '0'; // Convert char to int
        }
        i++;
        fgetc(file); // To skip the newline character
    }
    fclose(file);

    int numberOfSequences = sizeof(pulseSequences) / sizeof(pulseSequences[0]);

    // Generate the pulses based on the sequences
    printf("Generating pulses...\n");
    for (int i = 0; i < numberOfSequences; i++) {
        digitalWrite(pulseA, pulseSequences[i][0]);
        digitalWrite(pulseB, pulseSequences[i][1]);
        digitalWrite(pulseC, pulseSequences[i][2]);
        delayMicroseconds(PULSE_DURATION);
    }

    return 0;
}
