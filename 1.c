#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��������� ������������� �������
typedef struct {
    int* data;       // ��������� �� ������
    size_t size;     // ������� ������ �������
    size_t capacity; // ����������� �������
} DynamicArray;

// ������� ������������� �������
void initArray(DynamicArray* arr, size_t initialCapacity) {
    arr->data = (int*)malloc(initialCapacity * sizeof(int));
    if (arr->data == NULL) {
        printf("������ ��������� ������!\n");
        exit(EXIT_FAILURE);
    }
    arr->size = 0;
    arr->capacity = initialCapacity;

}

// ������� ���������� ��������
void addElement(DynamicArray* arr, int value, int position) {
    if (arr->size == arr->capacity) {
        size_t oldCapacity = arr->capacity;
        arr->capacity *= 2; // ��������� �����������
        void* temp = realloc(arr->data, arr->capacity * sizeof(int));
        if (temp == NULL) {
            printf("������ ��������� ������!\n");
            exit(EXIT_FAILURE);
        }
        arr->data = (int*)temp;

    }

    if (position == -1 || position >= arr->size) {
        arr->data[arr->size++] = value; // ��������� � �����
    }
    else {
        for (size_t i = arr->size; i > position; --i) {
            arr->data[i] = arr->data[i - 1];
        }
        arr->data[position] = value;
        arr->size++;
    }
}

// ������� �������� ��������
void deleteElement(DynamicArray* arr, int position) {
    if (position < 0 || position >= arr->size) {
        printf("������������ �������!\n");
        return;
    }

    for (size_t i = position; i < arr->size - 1; ++i) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
}

// ������� ��������� ������� �������
void resizeArray(DynamicArray* arr, int change) {
    if (change > 0) { // ���������� �������
        size_t oldCapacity = arr->capacity;
        arr->capacity += change;
        int* temp = (int*)realloc(arr->data, arr->capacity * sizeof(int));
        if (temp == NULL) {
            printf("������ ��������� ������!\n");
            exit(EXIT_FAILURE);
        }
        arr->data = temp;
    }
    else { // ���������� �������
        size_t newCapacity = arr->capacity + change;
        if (newCapacity < (int)arr->size) {
            printf("����� ����������� ������ �������� �������. ���������� �������� ������!\n");
            return;
        }
        int* temp = (int*)realloc(arr->data, newCapacity * sizeof(int));
        if (temp == NULL) {
            printf("������ ��������� ������!\n");
            exit(EXIT_FAILURE);
        }
        arr->data = temp;
        arr->capacity = newCapacity;
    }
}

// ������� ����������� �������
void displayArray(DynamicArray* arr) {
    printf("������: ");
    for (size_t i = 0; i < arr->size; ++i) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

// ������������ ������
void freeArray(DynamicArray* arr) {
    if (arr->data != NULL) {
        free(arr->data);
        arr->data = NULL;
    }
    arr->size = arr->capacity = 0;
}

int main() {
    // ��������� �������� ����� � ������� Visual Studio
#ifdef _WIN32
    system("chcp 1251 > nul");
#endif

    DynamicArray arr;
    initArray(&arr, 2); // ������������� ������� � ������������ 2

    int choice;
    do {
        printf("\n���� ������ � ������������ ��������:\n");
        printf("1. �������� �������\n");
        printf("2. ������� �������\n");
        printf("3. �������� ������ �������\n");
        printf("4. �������� ������\n");
        printf("5. �����\n");
        printf("������� ��� �����: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1: {
            int value, position;
            printf("������� �������� ��� ����������: ");
            scanf_s("%d", &value);
            printf("������� ������� ��� ������� (-1 ��� �����): ");
            scanf_s("%d", &position);
            addElement(&arr, value, position);
            break;
        }
        case 2: {
            int position;
            displayArray(&arr);
            printf("������� ������� ��� ��������: ");
            scanf_s("%d", &position);
            deleteElement(&arr, position);
            break;
        }
        case 3: {
            int change;
            printf("������� ��������� ����������� (������������� ��� ����������, ������������� ��� ����������): ");
            scanf_s("%d", &change);
            resizeArray(&arr, change);
            break;
        }
        case 4:
            displayArray(&arr);
            break;
        case 5:
            printf("�����...\n");
            break;
        default:
            printf("������������ �����. ���������� �����.\n");
        }
    } while (choice != 5);

    freeArray(&arr); // ������������ ������ ����� �������
    return 0;
}
