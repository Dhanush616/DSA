#include <stdio.h>
#include <string.h>

// Function to compute the pi (partial match) array for the pattern
void computePiTable(char* pattern, int patternLength, int* pi) {
    int length = 0; // Length of the previous longest prefix suffix
    pi[0] = 0; // pi[0] is always 0

    int i = 1;
    while (i < patternLength) {
        if (pattern[i] == pattern[length]) {
            length++;
            pi[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = pi[length - 1];
            } else {
                pi[i] = 0;
                i++;
            }
        }
    }
}

// Function to perform KMP search
void KMPSearch(char* text, char* pattern) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);

    // Create the pi array and compute the partial match values
    int pi[patternLength];
    computePiTable(pattern, patternLength, pi);

    int i = 0; // Index for text[]
    int j = 0; // Index for pattern[]
    int found = 0; // Flag to check if any match was found

    while (i < textLength) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == patternLength) {
            printf("Pattern found at index %d\n", i - j);
            found = 1;
            j = pi[j - 1]; // Continue to find further matches
        } else if (i < textLength && pattern[j] != text[i]) {
            if (j != 0) {
                j = pi[j - 1];
            } else {
                i++;
            }
        }
    }

    if (!found) {
        printf("Pattern not found in the text.\n");
    }
}

// Main function to test the KMP search function
int main() {
    char text[1000];
    char pattern[100];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline character

    printf("Enter the pattern to search: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0'; // Remove newline character

    KMPSearch(text, pattern);

    return 0;
}
