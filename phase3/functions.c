#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

FILE *fp;

// Input student information
void student_info(student *stu, int n)
{
    for (int i = 0; i < n; i++)
    {
        stu[i].name = malloc(30 * sizeof(char));
        stu[i].roll_no = malloc(20 * sizeof(char));
        if (stu[i].name == NULL || stu[i].roll_no == NULL)
        {
            printf("Error allocating memory\n");
            exit(1);
        }
        printf("-----------------    Data of Student %d    -----------------\n", i + 1);
        printf("Enter the name: ");
        scanf("%s", stu[i].name);
        printf("Enter the roll number: ");
        scanf("%s", stu[i].roll_no);
        printf("Enter the semester: ");
        scanf("%d", &stu[i].sem);

        // Initialize subjects and credits for each student
        Subjects(&stu[i]);
        Credits(&stu[i]);
    }
    printf("-----------------------------------------------------------\n");
}

// Input subject names
void Subjects(student *stu)
{
    for (int i = 0; i < 3; i++)
    {
        printf("Enter subject %d: ", i + 1);
        scanf("%s", stu->sub[i]);
    }
    printf("-----------------------------------------------------------\n");
}

// Input subject credits
void Credits(student *stu)
{
    for (int i = 0; i < 3; i++)
    {
        printf("Enter the credits of subject %d: ", i + 1);
        scanf("%d", &stu->credit[i]);
    }
    printf("-----------------------------------------------------------\n");
}

// Input ISA1 marks
void ISA1(student *stu, int n)
{
    for (int i = 0; i < n; i++)
    {
        stu[i].isa1 = malloc(3 * sizeof(int));
        printf("Enter the ISA 1 marks(out of 40) of student %d for the 3 subjects: ", i + 1);
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &stu[i].isa1[j]);
        }
    }
    printf("-----------------------------------------------------------\n");
}

// Input ISA2 marks
void ISA2(student *stu, int n)
{
    for (int i = 0; i < n; i++)
    {
        stu[i].isa2 = malloc(3 * sizeof(int));
        printf("Enter the ISA 2 marks(out of 40) of student %d for the 3 subjects: ", i + 1);
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &stu[i].isa2[j]);
        }
    }
    printf("-----------------------------------------------------------\n");
}

//Input Internal marks
void Internals(student *stu, int n)
{
    for (int i = 0; i < n; i++)
    {
        stu[i].internals = malloc(3 * sizeof(int));
        printf("Enter the internal marks(out of 10) of student %d for the 3 subjects: ", i + 1);
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &stu[i].internals[j]);
        }
    }
    printf("-----------------------------------------------------------\n");
}

// Input ESA marks
void ESA(student *stu, int n)
{
    for (int i = 0; i < n; i++)
    {
        stu[i].esa = malloc(3 * sizeof(int));
        printf("Enter the ESA marks of student(out of 100) %d for the 3 subjects: ", i + 1);
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &stu[i].esa[j]);
        }
    }
    printf("-----------------------------------------------------------\n");
}

// Calculating total marks
void total_marks(student *stu, int n)
{
    for (int i = 0; i < n; i++)
    {
        stu[i].tot_marks = malloc(3 * sizeof(float));
        for (int j = 0; j < 3; j++)
        {
            stu[i].tot_marks[j] = ((stu[i].isa1[j] * 0.5) + (stu[i].isa2[j] * 0.5) + (stu[i].esa[j] * 0.5) + stu[i].internals[j]);
        }
    }
}

// Calculating SGPA
void SGPA(student *stu, int n)
{
    int total_credits = 0;
    for (int i = 0; i < 3; i++)
    {
        total_credits += stu->credit[i];
    }
    for (int i = 0; i < n; i++)
    {
        stu[i].sgpa = 0;
        for (int j = 0; j < 3; j++)
        {
            if (stu[i].tot_marks[j] > 90 && stu[i].tot_marks[j] <= 100)
            {
                stu[i].sgpa += 10 * stu->credit[j];
            }
            else if (stu[i].tot_marks[j] > 80 && stu[i].tot_marks[j] <= 90)
            {
                stu[i].sgpa += 9 * stu->credit[j];
            }
            else if (stu[i].tot_marks[j] > 70 && stu[i].tot_marks[j] <= 80)
            {
                stu[i].sgpa += 8 * stu->credit[j];
            }
            else if (stu[i].tot_marks[j] > 60 && stu[i].tot_marks[j] <= 70)
            {
                stu[i].sgpa += 7 * stu->credit[j];
            }
            else if (stu[i].tot_marks[j] > 50 && stu[i].tot_marks[j] <= 60)
            {
                stu[i].sgpa += 6 * stu->credit[j];
            }
            else if (stu[i].tot_marks[j] > 40 && stu[i].tot_marks[j] <= 50)
            {
                stu[i].sgpa += 5 * stu->credit[j];
            }
            else
            {
                stu[i].sgpa += 4 * stu->credit[j];
            }
        }
        stu[i].sgpa /= total_credits;
    }
}

//Writing the data to the file
void WriteToFile(student *stu, int n)
{
    fp = fopen("student_data.csv", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "Name,Roll_Number,Sem,ISA1_S1,ISA2_S1,Internals_S1,ESA_S1,ISA1_S2,ISA2_S2,Internals_S2,ESA_S2,ISA1_S3,ISA2_S3,Internals_S3,ESA_S3,SGPA\n");

    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f\n",
                stu[i].name, stu[i].roll_no, stu[i].sem,
                stu[i].isa1[0], stu[i].isa2[0], stu[i].internals[0], stu[i].esa[0],
                stu[i].isa1[1], stu[i].isa2[1], stu[i].internals[1], stu[i].esa[1],
                stu[i].isa1[2], stu[i].isa2[2], stu[i].internals[2], stu[i].esa[2],
                stu[i].sgpa);
    }
    printf("Written to file\n");
    fclose(fp);
}

// Display gradecard
void display_gradecard(student *stu, int n)
{
    int input;
    printf("Choose the grade card to be printed (1 - %d):\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("%d. %s\n", i + 1, stu[i].name);
    }
    scanf("%d", &input);
    if (input >= 1 && input <= n)
    {
        input--;
        printf("\n");
        printf("====================================================================\n");
        printf("\t\t\t    GRADE CARD\n");
        printf("Name: %-30s\n", stu[input].name);
        printf("Semester: %-10d\n", stu[input].sem);
        printf("Roll No.: %-20s\n", stu[input].roll_no);
        printf("--------------------------------------------------------------------\n");
        printf("SGPA: %.2f\n", stu[input].sgpa);
        printf("--------------------------------------------------------------------\n");
        printf("Subject\t\tISA1\tISA2\tInternals\tESA\n");
        printf("--------------------------------------------------------------------\n");
        for (int i = 0; i < 3; i++)
        {
            printf("%s\t\t%d\t%d\t%d\t\t%d\n", stu[input].sub[i], stu[input].isa1[i], stu[input].isa2[i], stu[input].internals[i], stu[input].esa[i]);
        }
        printf("====================================================================\n");
    }
    else
    {
        printf("Invalid number! Please enter a valid number\n");
    }
}

// Function to detect file type and call the respective parsing function
void ReadFromFile(const char *filename, student *stu, int *n)
{
    char *ext = strrchr(filename, '.');
    printf(*filename);
    if (ext != NULL)
    {
        if (strcmp(ext, ".csv") == 0)
        {
            ReadFromFileCSV(stu, *n, filename);
        }
        else if (strcmp(ext, ".json") == 0)
        {
            ReadFromFileJSON(stu, n, filename);
        }
        else if (strcmp(ext, ".xml") == 0)
        {
            ReadFromFileXML(stu, n, filename);
        }
        else
        {
            printf("Unsupported file format!\n");
        }
    }
    else
    {
        printf("File format not recognized!\n");
    }
}

// CSV Parsing
void ReadFromFileCSV(student *stu, int n, const char *filename)
{
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char buffer[1024];
    int row = 0;

    fgets(buffer, sizeof(buffer), fp);

    while (fgets(buffer, sizeof(buffer), fp) && row < n)
    {
        stu[row].name = malloc(30 * sizeof(char));
        stu[row].roll_no = malloc(20 * sizeof(char));
        stu[row].isa1 = malloc(3 * sizeof(int));
        stu[row].isa2 = malloc(3 * sizeof(int));
        stu[row].internals = malloc(3 * sizeof(int));
        stu[row].esa = malloc(3 * sizeof(int));
        stu[row].tot_marks = malloc(3 * sizeof(float));

        sscanf(buffer, "%29[^,],%19[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f",
               stu[row].name,
               stu[row].roll_no,
               &stu[row].sem,
               &stu[row].isa1[0], &stu[row].isa2[0], &stu[row].internals[0], &stu[row].esa[0],
               &stu[row].isa1[1], &stu[row].isa2[1], &stu[row].internals[1], &stu[row].esa[1],
               &stu[row].isa1[2], &stu[row].isa2[2], &stu[row].internals[2], &stu[row].esa[2],
               &stu[row].sgpa);
        row++;
    }

    fclose(fp);
}

void parse_json_field(const char *json, const char *key, char *output, size_t max_size) {
    char *found = strstr(json, key);
    if (found) {
        found = strchr(found, ':');  // Find the colon after the key
        if (found) {
            found++;  // Move past the colon
            while (*found == ' ' || *found == '\"') found++;  // Skip spaces and quotes
            sscanf(found, "%[^\"]", output);  // Extract value into output (assumes string without nested quotes)
            if (strlen(output) > max_size - 1) {
                output[max_size - 1] = '\0';  // Null terminate if too long
            }
        }
    }
}

void parse_json_int_field(const char *json, const char *key, int *output) {
    char *found = strstr(json, key);
    if (found) {
        found = strchr(found, ':');  // Find the colon after the key
        if (found) {
            found++;  // Move past the colon
            sscanf(found, "%d", output);  // Extract the integer value
        }
    }
}

void parse_json_double_field(const char *json, const char *key, double *output) {
    char *found = strstr(json, key);
    if (found) {
        found = strchr(found, ':');  // Find the colon after the key
        if (found) {
            found++;  // Move past the colon
            sscanf(found, "%lf", output);  // Extract the double value
        }
    }
}

void parse_json_array(const char *json, const char *key, int *array, int size) {
    char *found = strstr(json, key);
    if (found) {
        found = strchr(found, '[');  // Find the opening bracket of the array
        if (found) {
            for (int i = 0; i < size; i++) {
                found++;  // Move past commas and spaces
                sscanf(found, "%d", &array[i]);
                found = strchr(found, ',');  // Move to next element
                if (!found) break;  // If no comma found, end of array
            }
        }
    }
}

void ReadFromFileJSON(student *stu, int *n, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *data = malloc(length + 1);  // +1 for null terminator
    fread(data, 1, length, fp);
    data[length] = '\0';  // Ensure the data is null-terminated
    fclose(fp);

    char student_block[1024];
    *n = 0;

    char *start = strstr(data, "{");  // Start of the first student block
    while (start && *n < 100) {  // Loop through each student object in the array
        // Extract the block of one student (naively assuming each block is under 1024 characters)
        char *end = strstr(start, "},");
        if (end) {
            strncpy(student_block, start, end - start + 1);
            student_block[end - start + 1] = '\0';  // Null-terminate the student block
        } else {
            break;
        }

        // Parse student fields from the block
        char buffer[100];
        parse_json_field(student_block, "\"name\"", buffer, sizeof(buffer));
        stu[*n].name = strdup(buffer);

        parse_json_field(student_block, "\"roll_no\"", buffer, sizeof(buffer));
        stu[*n].roll_no = strdup(buffer);

        parse_json_int_field(student_block, "\"sem\"", &stu[*n].sem);

        parse_json_array(student_block, "\"isa1\"", stu[*n].isa1, 3);
        parse_json_array(student_block, "\"isa2\"", stu[*n].isa2, 3);
        parse_json_array(student_block, "\"internals\"", stu[*n].internals, 3);
        parse_json_array(student_block, "\"esa\"", stu[*n].esa, 3);

        parse_json_double_field(student_block, "\"sgpa\"", &stu[*n].sgpa);

        // Move to the next student object
        start = strstr(end, "{");
        (*n)++;
    }

    free(data);
}

char *find_tag_content(const char *data, const char *tag) {
    char open_tag[50], close_tag[50];
    sprintf(open_tag, "<%s>", tag);
    sprintf(close_tag, "</%s>", tag);

    char *start = strstr(data, open_tag);
    char *end = strstr(data, close_tag);
    if (start && end) {
        start += strlen(open_tag);
        size_t length = end - start;
        char *content = (char *)malloc(length + 1);
        strncpy(content, start, length);
        content[length] = '\0';
        return content;
    }
    return NULL;
}

void parse_xml_field(const char *student_block, const char *tag, char **output) {
    char *content = find_tag_content(student_block, tag);
    if (content) {
        *output = strdup(content);
        free(content);
    }
}

void parse_xml_int_field(const char *student_block, const char *tag, int *output) {
    char *content = find_tag_content(student_block, tag);
    if (content) {
        *output = atoi(content);
        free(content);
    }
}

void parse_xml_array(const char *student_block, const char *tag, int *array, int size) {
    char *content = find_tag_content(student_block, tag);
    if (content) {
        char *token = strtok(content, " ");
        for (int i = 0; i < size && token; i++) {
            array[i] = atoi(token);
            token = strtok(NULL, " ");
        }
        free(content);
    }
}

void parse_xml_double_field(const char *student_block, const char *tag, double *output) {
    char *content = find_tag_content(student_block, tag);
    if (content) {
        *output = atof(content);
        free(content);
    }
}

void ReadFromFileXML(student *stu, int *n, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *data = malloc(length + 1);
    if (data == NULL) {
        printf("Memory allocation failed!\n");
        fclose(fp);
        return;
    }
    fread(data, 1, length, fp);
    data[length] = '\0';  
    fclose(fp);

    *n = 0;

    char *start = strstr(data, "<student>");
    while (start) {
        (*n)++;
        start = strstr(start + 1, "<student>");
    }

    start = strstr(data, "<student>");
    int i = 0;
    while (start && i < *n) {
        char *end = strstr(start, "</student>");
        if (end) {
            end += strlen("</student>");
            size_t block_len = end - start;

            char *block = (char *)malloc(block_len + 1);
            if (block == NULL) {
                printf("Memory allocation failed!\n");
                free(data);
                return;
            }
            strncpy(block, start, block_len);
            block[block_len] = '\0';

            parse_xml_field(block, "name", &stu[i].name);
            parse_xml_field(block, "roll_no", &stu[i].roll_no);
            parse_xml_int_field(block, "sem", &stu[i].sem);

            stu[i].isa1 = malloc(3 * sizeof(int));
            stu[i].isa2 = malloc(3 * sizeof(int));
            stu[i].internals = malloc(3 * sizeof(int));
            stu[i].esa = malloc(3 * sizeof(int));

            if (stu[i].isa1 == NULL || stu[i].isa2 == NULL || stu[i].internals == NULL || stu[i].esa == NULL) {
                printf("Memory allocation failed!\n");
                free(block);
                free(data);
                return;
            }

            parse_xml_array(block, "isa1", stu[i].isa1, 3);
            parse_xml_array(block, "isa2", stu[i].isa2, 3);
            parse_xml_array(block, "internals", stu[i].internals, 3);
            parse_xml_array(block, "esa", stu[i].esa, 3);

            parse_xml_double_field(block, "sgpa", &stu[i].sgpa);

            free(block);

            start = strstr(end, "<student>");
            i++;
        } else {
            break;
        }
    }

    free(data);
}