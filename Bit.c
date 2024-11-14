#include <stdio.h>
#include <string.h>

void bitStuff(char data[], char stuffedData[]) {
    int count = 0, j = 0;
    for (int i = 0; i < strlen(data); i++) {
        stuffedData[j++] = data[i];

        if (data[i] == '1') {
            count++;
        } else {
            count = 0;
        }

        if (count == 5) {
            stuffedData[j++] = '0';
            count = 0;
        }
    }
    stuffedData[j] = '\0'; 
}

int main() {
    char data[100], stuffedData[200];

    printf("Enter binary data: ");
    scanf("%s", data);

    bitStuff(data, stuffedData);

    printf("Stuffed data: %s\n", stuffedData);

    return 0;
}