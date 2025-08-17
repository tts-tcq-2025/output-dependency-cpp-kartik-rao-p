#include <stdio.h>
#include <string.h>
#include "misaligned.h"

// Buffer to capture printColorMap() output
static char capturedOutput[2048];

// Capture function to be passed to printColorMap()
static void captureOutput(const char* text) {
    strncpy(capturedOutput, text, sizeof(capturedOutput) - 1);
    capturedOutput[sizeof(capturedOutput) - 1] = '\0';
}

// Expected correct output (without bug)
static const char* expectedOutput =
    "1 | White | Blue\n"
    "2 | White | Orange\n"
    "3 | White | Green\n"
    "4 | White | Brown\n"
    "5 | White | Slate\n"
    "6 | Red | Blue\n"
    "7 | Red | Orange\n"
    "8 | Red | Green\n"
    "9 | Red | Brown\n"
    "10 | Red | Slate\n"
    "11 | Black | Blue\n"
    "12 | Black | Orange\n"
    "13 | Black | Green\n"
    "14 | Black | Brown\n"
    "15 | Black | Slate\n"
    "16 | Yellow | Blue\n"
    "17 | Yellow | Orange\n"
    "18 | Yellow | Green\n"
    "19 | Yellow | Brown\n"
    "20 | Yellow | Slate\n"
    "21 | Violet | Blue\n"
    "22 | Violet | Orange\n"
    "23 | Violet | Green\n"
    "24 | Violet | Brown\n"
    "25 | Violet | Slate\n";

// Helper function to print comparison result
static void reportTestResult(int passed) {
    if (passed) {
        printf("TEST PASSED: No bug detected.\n");
    } else {
        printf("TEST FAILED: Bug detected in color map generation.\n");
        printf("\n--- Actual Output ---\n%s", capturedOutput);
        printf("\n--- Expected Output ---\n%s", expectedOutput);
    }
}

int main(void) {
    // Arrange
    memset(capturedOutput, 0, sizeof(capturedOutput));

    // Act: Call the only public function
    printColorMap(captureOutput);

    // Assert: Compare actual vs expected
    int passed = (strcmp(capturedOutput, expectedOutput) == 0);
    reportTestResult(passed);

    return passed ? 0 : 1;
}
