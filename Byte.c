#include <stdio.h>
#include <string.h>

#define FLAG 'F'
#define ESCAPE 'E'

void byteStuff(const char* data, char* stuffedData) {
    int j = 0;
    for (int i = 0; i < strlen(data); i++) {
        char currentChar = data[i];

        if (currentChar == FLAG || currentChar == ESCAPE) {
            stuffedData[j++] = ESCAPE;
        }

        stuffedData[j++] = currentChar;
    }
    stuffedData[j] = '\0'; 
}

int main() {
    char data[100], stuffedData[200];

    printf("Enter data: ");
    scanf("%s", data);

    byteStuff(data, stuffedData);

    printf("Stuffed data: %s\n", stuffedData);

    return 0;
}