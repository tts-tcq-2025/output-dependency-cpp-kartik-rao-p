#include "misaligned.h"
#include <stdio.h>
#include <string.h>

#define MAJOR_COLORS 5
#define MINOR_COLORS 5

struct Colors {
    int index;
    const char* major;
    const char* minor;
};

static void generateColorMap(struct Colors colorMap[]) {
    const char* majorColor[MAJOR_COLORS] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[MINOR_COLORS] = {"Blue", "Orange", "Green", "Brown", "Slate"};

    int count = 0;
    for (int i = 0; i < MAJOR_COLORS; i++) {
        for (int j = 0; j < MINOR_COLORS; j++) {
            colorMap[count].index = count + 1;
            colorMap[count].major = majorColor[i];
            colorMap[count].minor = minorColor[i]; // <-- BUG
            count++;
        }
    }
}

static void generateOutputString(char *buffer, size_t bufSize, struct Colors colorMap[]) {
    buffer[0] = '\0';
    char line[50];
    for (int i = 0; i < MAJOR_COLORS * MINOR_COLORS; i++) {
        snprintf(line, sizeof(line), "%d | %s | %s\n",
                 colorMap[i].index, colorMap[i].major, colorMap[i].minor);
        strncat(buffer, line, bufSize - strlen(buffer) - 1);
    }
}

int printColorMap(void (*outputFunc)(const char*)) {
    struct Colors colorMap[MAJOR_COLORS * MINOR_COLORS];
    char buffer[1024];

    generateColorMap(colorMap);
    generateOutputString(buffer, sizeof(buffer), colorMap);

    outputFunc(buffer);
    return MAJOR_COLORS * MINOR_COLORS;
}
