#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура динамического массива
typedef struct {
    int* data;       // Указатель на массив
    size_t size;     // Текущий размер массива
    size_t capacity; // Вместимость массива
} DynamicArray;

// Функция инициализации массива
void initArray(DynamicArray* arr, size_t initialCapacity) {
    arr->data = (int*)malloc(initialCapacity * sizeof(int));
    if (arr->data == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(EXIT_FAILURE);
    }
    arr->size = 0;
    arr->capacity = initialCapacity;

}

// Функция добавления элемента
void addElement(DynamicArray* arr, int value, int position) {
    if (arr->size == arr->capacity) {
        size_t oldCapacity = arr->capacity;
        arr->capacity *= 2; // Удваиваем вместимость
        void* temp = realloc(arr->data, arr->capacity * sizeof(int));
        if (temp == NULL) {
            printf("Ошибка выделения памяти!\n");
            exit(EXIT_FAILURE);
        }
        arr->data = (int*)temp;

    }

    if (position == -1 || position >= arr->size) {
        arr->data[arr->size++] = value; // Добавляем в конец
    }
    else {
        for (size_t i = arr->size; i > position; --i) {
            arr->data[i] = arr->data[i - 1];
        }
        arr->data[position] = value;
        arr->size++;
    }
}

// Функция удаления элемента
void deleteElement(DynamicArray* arr, int position) {
    if (position < 0 || position >= arr->size) {
        printf("Недопустимая позиция!\n");
        return;
    }

    for (size_t i = position; i < arr->size - 1; ++i) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
}

// Функция изменения размера массива
void resizeArray(DynamicArray* arr, int change) {
    if (change > 0) { // Увеличение массива
        size_t oldCapacity = arr->capacity;
        arr->capacity += change;
        int* temp = (int*)realloc(arr->data, arr->capacity * sizeof(int));
        if (temp == NULL) {
            printf("Ошибка выделения памяти!\n");
            exit(EXIT_FAILURE);
        }
        arr->data = temp;
    }
    else { // Уменьшение массива
        size_t newCapacity = arr->capacity + change;
        if (newCapacity < (int)arr->size) {
            printf("Новая вместимость меньше текущего размера. Невозможно изменить размер!\n");
            return;
        }
        int* temp = (int*)realloc(arr->data, newCapacity * sizeof(int));
        if (temp == NULL) {
            printf("Ошибка выделения памяти!\n");
            exit(EXIT_FAILURE);
        }
        arr->data = temp;
        arr->capacity = newCapacity;
    }
}

// Функция отображения массива
void displayArray(DynamicArray* arr) {
    printf("Массив: ");
    for (size_t i = 0; i < arr->size; ++i) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

// Освобождение памяти
void freeArray(DynamicArray* arr) {
    if (arr->data != NULL) {
        free(arr->data);
        arr->data = NULL;
    }
    arr->size = arr->capacity = 0;
}

int main() {
    // Установка русского языка в консоли Visual Studio
#ifdef _WIN32
    system("chcp 1251 > nul");
#endif

    DynamicArray arr;
    initArray(&arr, 2); // Инициализация массива с вместимостью 2

    int choice;
    do {
        printf("\nМеню работы с динамическим массивом:\n");
        printf("1. Добавить элемент\n");
        printf("2. Удалить элемент\n");
        printf("3. Изменить размер массива\n");
        printf("4. Показать массив\n");
        printf("5. Выйти\n");
        printf("Введите ваш выбор: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1: {
            int value, position;
            printf("Введите значение для добавления: ");
            scanf_s("%d", &value);
            printf("Введите позицию для вставки (-1 для конца): ");
            scanf_s("%d", &position);
            addElement(&arr, value, position);
            break;
        }
        case 2: {
            int position;
            displayArray(&arr);
            printf("Введите позицию для удаления: ");
            scanf_s("%d", &position);
            deleteElement(&arr, position);
            break;
        }
        case 3: {
            int change;
            printf("Введите изменение вместимости (положительное для увеличения, отрицательное для уменьшения): ");
            scanf_s("%d", &change);
            resizeArray(&arr, change);
            break;
        }
        case 4:
            displayArray(&arr);
            break;
        case 5:
            printf("Выход...\n");
            break;
        default:
            printf("Недопустимый выбор. Попробуйте снова.\n");
        }
    } while (choice != 5);

    freeArray(&arr); // Освобождение памяти перед выходом
    return 0;
}
