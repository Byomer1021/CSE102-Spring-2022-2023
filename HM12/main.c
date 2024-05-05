#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct {
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;

typedef struct {
    char type[20];
    double svals[2];
    int ivals[2];
} Asset2;

typedef struct {
    char type[20];
    char string1[50];
    char string2[50];
} Asset3;

typedef struct {
    char type[20];
    double value1;
    float value2;
    double value3;
} Asset4;

void fillLinkedList(struct Node** head) {
    srand(time(NULL));
    int numAssets = rand() % 11 + 10; // Generate a random number of assets between 10 and 20

    *head = NULL;
    struct Node* current = NULL;

    for (int i = 0; i < numAssets; i++) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->next = NULL;

        int assetType = rand() % 4; // Generate a random asset type

        switch (assetType) {
            case 0: {
                Asset1* asset = (Asset1*)malloc(sizeof(Asset1));
                strcpy(asset->type, "Asset1");
                asset->ivals[0] = rand() % 100; // Random integer value
                asset->svals[0] = (double)(rand() % 10000) / 100.0; // Random double value
                newNode->data = asset;
                break;
            }
            case 1: {
                Asset2* asset = (Asset2*)malloc(sizeof(Asset2));
                strcpy(asset->type, "Asset2");
                asset->svals[0] = (double)(rand() % 10000) / 100.0; // Random double value
                asset->svals[1] = (double)(rand() % 10000) / 100.0; // Random double value
                asset->ivals[0] = rand() % 100; // Random integer value
                asset->ivals[1] = rand() % 100; // Random integer value
                newNode->data = asset;
                break;
            }
            case 2: {
                Asset3* asset = (Asset3*)malloc(sizeof(Asset3));
                strcpy(asset->type, "Asset3");
                sprintf(asset->string1, "String1-%d", i); // Assign a string with a specific format
                sprintf(asset->string2, "String2-%d", i); // Assign a string with a specific format
                newNode->data = asset;
                break;
            }
            case 3: {
                Asset4* asset = (Asset4*)malloc(sizeof(Asset4));
                strcpy(asset->type, "Asset4");
                asset->value1 = (double)(rand() % 10000) / 100.0; // Random double value
                asset->value2 = (float)(rand() % 1000) / 10.0; // Random float value
                asset->value3 = (double)(rand() % 10000) / 100.0; // Random double value
                newNode->data = asset;
                break;
            }
        }

        if (*head == NULL) {
            *head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }
}

void serializeLinkedList(struct Node* head) {
    FILE* file = fopen("linkedlist.bin", "wb"); // Open the binary file for writing

    struct Node* current = head;
    while (current != NULL) {
        if (strcmp(((Asset1*)current->data)->type, "Asset1") == 0) {
            fwrite(((Asset1*)current->data), sizeof(Asset1), 1, file); // Write the data of Asset1 to the file
        } else if (strcmp(((Asset2*)current->data)->type, "Asset2") == 0) {
            fwrite(((Asset2*)current->data), sizeof(Asset2), 1, file); // Write the data of Asset2 to the file
        } else if (strcmp(((Asset3*)current->data)->type, "Asset3") == 0) {
            fwrite(((Asset3*)current->data), sizeof(Asset3), 1, file); // Write the data of Asset3 to the file
        } else if (strcmp(((Asset4*)current->data)->type, "Asset4") == 0) {
            fwrite(((Asset4*)current->data), sizeof(Asset4), 1, file); // Write the data of Asset4 to the file
        }

        current = current->next;
    }

    fclose(file); // Close the file
}

void deserializeLinkedList(struct Node** head) {
    FILE* file = fopen("linkedlist.bin", "rb"); // Open the binary file for reading

    *head = NULL;
    struct Node* current = NULL;

    while (!feof(file)) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->next = NULL;

        char assetType[20];
        fread(assetType, sizeof(assetType), 1, file); // Read the asset type from the file

        if (strcmp(assetType, "Asset1") == 0) {
            Asset1* asset = (Asset1*)malloc(sizeof(Asset1));
            fread(asset, sizeof(Asset1), 1, file); // Read the data of Asset1 from the file
            newNode->data = asset;
        } else if (strcmp(assetType, "Asset2") == 0) {
            Asset2* asset = (Asset2*)malloc(sizeof(Asset2));
            fread(asset, sizeof(Asset2), 1, file); // Read the data of Asset2 from the file
            newNode->data = asset;
        } else if (strcmp(assetType, "Asset3") == 0) {
            Asset3* asset = (Asset3*)malloc(sizeof(Asset3));
            fread(asset, sizeof(Asset3), 1, file); // Read the data of Asset3 from the file
            newNode->data = asset;
        } else if (strcmp(assetType, "Asset4") == 0) {
            Asset4* asset = (Asset4*)malloc(sizeof(Asset4));
            fread(asset, sizeof(Asset4), 1, file); // Read the data of Asset4 from the file
            newNode->data = asset;
        }

        if (*head == NULL) {
            *head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    fclose(file); // Close the file
}

void printLinkedList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        if (strcmp(((Asset1*)current->data)->type, "Asset1") == 0) {
            Asset1* asset = (Asset1*)current->data;
            printf("Asset1: Type=%s, ivals=%d, svals=%.2lf\n", asset->type, asset->ivals[0], asset->svals[0]);
        } else if (strcmp(((Asset2*)current->data)->type, "Asset2") == 0) {
            Asset2* asset = (Asset2*)current->data;
            printf("Asset2: Type=%s, svals=%.2lf, %.2lf, ivals=%d, %d\n", asset->type, asset->svals[0], asset->svals[1], asset->ivals[0], asset->ivals[1]);
        } else if (strcmp(((Asset3*)current->data)->type, "Asset3") == 0) {
            Asset3* asset = (Asset3*)current->data;
            printf("Asset3: Type=%s, string1=%s, string2=%s\n", asset->type, asset->string1, asset->string2);
        } else if (strcmp(((Asset4*)current->data)->type, "Asset4") == 0) {
            Asset4* asset = (Asset4*)current->data;
            printf("Asset4: Type=%s, value1=%.2lf, value2=%.1f, value3=%.2lf\n", asset->type, asset->value1, asset->value2, asset->value3);
        }

        current = current->next;
    }
}

int main() {
    struct Node* head = NULL;

    fillLinkedList(&head); // Generate and fill the linked list with random assets
    printf("Linked List (Original):\n");
    printLinkedList(head); // Print the original linked list

    serializeLinkedList(head); // Serialize and write the linked list to a binary file

    struct Node* reconstructedHead = NULL;
    deserializeLinkedList(&reconstructedHead); // Read and reconstruct the linked list from the binary file
    // printf("\nLinked List (Reconstructed):\n");
    printLinkedList(reconstructedHead); // Print the reconstructed linked list

    return 0;
}
