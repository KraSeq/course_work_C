#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

struct server_platforms {
    char manufacturer[20];
    char form_factor[20];
    char socket[20];
    int max_cpu;
    double max_ram;
};

int read_file()
{
    FILE* fp = fopen("coursework.txt", "r");
    if (fp == NULL) {
        return 1;
    }

    fclose(fp);

    return 0;
}

void fill_platforms(struct server_platforms* platforms, int k)
{
    for (int i = 0; i < k; i++) {
        printf("Производитель: ");
        if (scanf("%19s", platforms[i].manufacturer) != 1)
            puts("Ошибка формата");

        printf("Форм-фактор сервера: ");
        if (scanf("%19s", platforms[i].form_factor) != 1)
            puts("Ошибка формата");

        printf("Сокет: ");
        if (scanf("%19s", platforms[i].socket) != 1)
            puts("Ошибка формата");

        printf("Максимальное кол-во CPU: ");
        if (scanf("%d", &platforms[i].max_cpu) != 1)
            puts("Ошибка формата");

        printf("Объем оперативной памяти: ");
        if (scanf("%lf", &platforms[i].max_ram) != 1)
            puts("Ошибка формата");


        printf("\n");
    }
}

int write_file(struct server_platforms* platforms, int k)
{
    FILE* fp = fopen("coursework.txt", "w");
    if (fp == NULL) {
        puts("Error func write_file");
        return 1;
    }

    for (int i = 0; i < k; i++) {
        if (fprintf(fp, "Производитель: %s\n", platforms[i].manufacturer) < 0 ||
            fprintf(fp, "Форм-фактор сервера: %s\n", platforms[i].form_factor) < 0 ||
            fprintf(fp, "Сокет: %s\n", platforms[i].socket) < 0 ||
            fprintf(fp, "Максимальное кол-во CPU: %d\n", platforms[i].max_cpu) < 0 ||
            fprintf(fp, "Объем оперативной памяти: %f\n\n", platforms[i].max_ram) < 0) {
            fclose(fp);

            return 1;
        }
    }

    fclose(fp);

    return 0;
}

int* do_search(struct server_platforms* platforms, int k, char* socket, int max_CPU)
{
    int* indices = malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        indices[i] = -1;
    }

    if (socket[0] != '\0' && max_CPU != -1) {
        for (int i = 0; i < k; i++) {
            if (strcmp(platforms[i].socket, socket) == 0 && platforms[i].max_cpu == max_CPU)
                indices[i] = i;
        }
    }
    else if (socket[0] != '\0' && max_CPU == -1) {
        for (int i = 0; i < k; i++) {
            if (strcmp(platforms[i].socket, socket) == 0)
                indices[i] = i;
        }
    }
    else {
        for (int i = 0; i < k; i++) {
            if (platforms[i].max_cpu == max_CPU)
                indices[i] = i;
        }
    }

    return indices;
}

void print_platform(struct server_platforms platform)
{
    printf("Производитель: %s\n", platform.manufacturer);
    printf("Форм-фактор сервера: %s\n", platform.form_factor);
    printf("Сокет: %s\n", platform.socket);
    printf("Максимальное кол-во CPU: %d\n", platform.max_cpu);
    printf("Объем оперативной памяти: %f\n", platform.max_ram);
    printf("\n");
}

int compare_manufacturer(const void* var_1, const void* var_2)
{
    const struct server_platforms* platform_1 = (const struct server_platforms*)var_1;
    const struct server_platforms* platform_2 = (const struct server_platforms*)var_2;

    return strcmp(platform_1->manufacturer, platform_2->manufacturer);
}

int compare_form_factor(const void* var_1, const void* var_2)
{
    const struct server_platforms* platform_1 = (const struct server_platforms*)var_1;
    const struct server_platforms* platform_2 = (const struct server_platforms*)var_2;

    return strcmp(platform_1->form_factor, platform_2->form_factor);
}

void sort_platforms(struct server_platforms* platforms, int k, int choice)
{
     if (choice == 1)
         qsort(platforms, k, sizeof(struct server_platforms), compare_manufacturer);
     else if (choice == 2) {
         qsort(platforms, k, sizeof(struct server_platforms), compare_form_factor);
     }
     else if (choice == 3) {
         qsort(platforms, k, sizeof(struct server_platforms), compare_manufacturer);
         qsort(platforms, k, sizeof(struct server_platforms), compare_form_factor);
     }
     else
         puts("Неверный выбор");
}

void add_platform(struct server_platforms* platforms, int i)
{
    printf("Производитель: ");
    if (scanf("%19s", platforms[i].manufacturer) != 1)
        puts("Ошибка формата");

    printf("Форм-фактор сервера: ");
    if (scanf("%19s", platforms[i].form_factor) != 1)
        puts("Ошибка формата");

    printf("Сокет: ");
    if (scanf("%19s", platforms[i].socket) != 1)
        puts("Ошибка формата");

    printf("Максимальное кол-во CPU: ");
    if (scanf("%d", &platforms[i].max_cpu) != 1)
        puts("Ошибка формата");

    printf("Объем оперативной памяти: ");
    if (scanf("%lf", &platforms[i].max_ram) != 1)
        puts("Ошибка формата");

    printf("\n");
}

void del_platform(struct server_platforms* platforms, int k, int i)
{
    struct server_platforms* new_platforms = malloc(k * sizeof(struct server_platforms));

    for (int j = 0; j < k; ++j) {
        if (j < i)
            new_platforms[j] = platforms[j];
        else if (j > i)
            new_platforms[j - 1] = platforms[j];
    }

    platforms = realloc(platforms, k * sizeof(struct server_platforms));
    for (int y = 0; y < k; ++y)
        platforms[y] = new_platforms[y];
}

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);

    int k = 0;
    printf("Введите количество серверных платформ: ");
    if (scanf("%d", &k) != 1) {
        puts("Error");
        return 1;
    }

    struct server_platforms* platforms = malloc(k * sizeof(struct server_platforms));

    int error; // Для проверки на создание новой записи
    char socket[20] = {'\0'}; // Для выполнения функции поиска
    int max_CPU = -1; // Для выполнения функции поиска
    int* indices = malloc(k * sizeof(int));
    int count;
    struct server_platforms* new_platforms;

    int choice = 0;
    int in_choice; // Для вложенных выборок

    while (choice != 5) {
        printf("**************************************\n");
        printf("*                Меню                *\n");
        printf("**************************************\n");
        printf("* 1. Создание новой записи.          *\n");
        printf("* 2. Поиск записи.                   *\n");
        printf("* 3. Запись и чтение данных.         *\n");
        printf("* 4. Сортировка записей.             *\n");
        printf("* 5. Завершить работу.               *\n");
        printf("**************************************\n");

        printf("Сделайте выбор: ");
        if (scanf("%d", &choice) != 1) {
            puts("Error");
            return 1;
        }

        switch (choice) {
            case 1:
                fill_platforms(platforms, k);
                error = write_file(platforms, k);

                if (error)
                    puts("Ошибка создания записи\n");
                else
                    puts("Создание записи прошло успешно\n");

                break;

            case 2:
                printf("********************************************\n");
                printf("*                Поиск записи              *\n");
                printf("********************************************\n");
                printf("* 1. По сокету.                            *\n");
                printf("* 2. По максимальному кол-ву CPU.          *\n");
                printf("* 3. По сокету и максимальному кол-ву CPU. *\n");
                printf("* 4. Вернуться в меню.                     *\n");
                printf("********************************************\n");

                printf("Сделайте выбор: ");
                if (scanf("%d", &in_choice) != 1) {
                    puts("Некорректный формат");
                    return 1;
                }

                switch (in_choice) {
                    case 1:
                        printf("Введите название сокета: ");
                        getchar();
                        fgets(socket, sizeof(socket), stdin);
                        socket[strcspn(socket, "\n")] = '\0';
                        max_CPU = -1;
                        break;
                    case 2:
                        printf("Введите максимальное кол-во CPU: ");
                        scanf("%d", &max_CPU);
                        socket[0] = '\0';
                        break;
                    case 3:
                        printf("Введите название сокета: ");
                        getchar();
                        fgets(socket, sizeof(socket), stdin);
                        socket[strcspn(socket, "\n")] = '\0';
                        printf("Введите максимальное кол-во CPU: ");
                        scanf("%d", &max_CPU);
                        break;
                    default:
                        break;
                }
                indices = do_search(platforms, k, socket, max_CPU);
                for (int i = 0; i < k; ++i) {
                    if (indices[i] != -1)
                        print_platform(platforms[i]);
                }

                break;

            case 3:
                printf("*********************************\n");
                printf("*     Запись и чтение данных    *\n");
                printf("*********************************\n");
                printf("* 1. Добавить запись.           *\n");
                printf("* 2. Изменить записи.           *\n");
                printf("* 3. Удалить записи.            *\n");
                printf("* 4. Чтение файла.              *\n");
                printf("* 5. Вернуться в меню.          *\n");
                printf("*********************************\n");

                printf("Сделайте выбор: ");
                if (scanf("%d", &in_choice) != 1) {
                    puts("Некорректный формат");
                    return 1;
                }

                switch (in_choice) {
                    case 1:
                        error = read_file();
                        if (error == 1) {
                            puts("Ошибка чтения файла");
                            break;
                        }

                        printf("Введите кол-во добавления записей: ");
                        if (scanf("%d", &count) != 1) {
                            puts("Некорректный формат данных");
                            break;
                        }

                        k += count;

                        new_platforms = realloc(platforms, k * sizeof(struct server_platforms));
                        for (int i = 0; i < k - count; ++i)
                            new_platforms[i] = platforms[i];

                        for (int i = k - count; i < k; ++i)
                            add_platform(new_platforms, i);

                        platforms = malloc((k + count) * sizeof(struct server_platforms));
                        for (int i = 0; i < k + count; ++i)
                            platforms[i] = new_platforms[i];

                        error = write_file(platforms, k);
                        if (error)
                            puts("Ошибка добавления новых записей");
                        else
                            puts("Записи успешно добавлены");

                        break;

                    case 2:
                        printf("Введите номер серверной платформы, которую вы хотите изменить: ");
                        if (scanf("%d", &in_choice) != 1) {
                            puts("Некорректный формат данных");
                            break;
                        }

                        add_platform(platforms, in_choice-1);

                        error = write_file(platforms, k);
                        if (error)
                            puts("Ошибка изменения платформы");
                        else
                            puts("Данные платформы изменены");

                        break;

                    case 3:
                        printf("Введите номер серверной платформы, которую вы хотите удалить: ");
                        if (scanf("%d", &in_choice) != 1) {
                            puts("Некорректный формат данных");
                            break;
                        }

                        if (in_choice < 1 || in_choice > k) {
                            printf("Платформы под таким номером не существует");
                            break;
                        }

                        k -= 1;
                        in_choice -= 1;

                        del_platform(platforms, k, in_choice);

                        error = write_file(platforms, k);
                        if (error)
                            puts("Ошибка удаления платформы");
                        else
                            puts("Платформа успешно удалена");

                        break;

                    case 4:
                        error = read_file();
                        if (error) {
                            puts("Ошибка чтения файла");
                            break;
                        }

                        for (int i = 0; i < k; ++i)
                            print_platform(platforms[i]);
                        puts("Файл успешно прочитан");

                        break;

                    case 5:
                        break;
                    default:
                        puts("Неверный выбор");
                }
                break;

            case 4:
                printf("***********************************************\n");
                printf("*             Сортировка записей              *\n");
                printf("***********************************************\n");
                printf("* 1. По производителю.                        *\n");
                printf("* 2. По форм-фактору сервера.                 *\n");
                printf("* 3. По производителю и форм-фактору сервера. *\n");
                printf("* 4. Вернуться в меню.                        *\n");
                printf("***********************************************\n");

                printf("Сделайте выбор: ");
                if (scanf("%d", &in_choice) != 1) {
                    puts("Некорректный формат");
                    return 1;
                }

                if (in_choice != 4) {
                    sort_platforms(platforms, k, in_choice);
                    write_file(platforms, k);
                }
                puts("Файл успешно отсортирован");

                break;

            case 5:
                puts("Завершение работы...");
                break;
            default:
                puts("Неверный выбор");
        }
    }

    free(platforms);
    free(indices);

    return 0;
}
