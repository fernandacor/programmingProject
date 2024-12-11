#include <stdio.h>

struct scheduler {
    int id; // Task ID
    int duration; // Duration of task
    int priority; // Priority of task
    char status; // Status (pending, running, completed)
};

void enterTasks() {
    int num;
    printf("Enter the total number of tasks: ");
    scanf("%d", &num);

    if (num <= 0) { 
        printf("Invalid number of tasks. Please try again.\n");
    }

    //Array to store tasks
    struct scheduler tasks[num];

    for(int id = 0; id < num; id++){
        tasks[id].id = id;
        printf("For task with ID #%d:\n", id);

        do {
            printf("Enter the duration of the task: ");
            scanf("%d", &tasks[id].duration);
            if (tasks[id].duration <= 0) {
                printf("Invalid duration. Please try again.\n");
            }
        } while (tasks[id].duration <= 0);

        do {
            printf ("Enter the priority of the task: ");
            scanf("%d", &tasks[id].priority);
            if (tasks[id].priority <= 0) {
                printf("Invalid priority. Please try again.\n");
            }
        } while (tasks[id].priority < 1 || tasks[id].priority > 25);

        // Set initial status
        tasks[id].status = 'P';
    }

    // Display entered tasks
    printf("\nTasks entered:\n");
    printf("ID\tDuration\tPriority\tStatus\n");
    for (int i = 0; i < num; i++) {
        printf("%d\t%d\t\t%d\t\t%c\n", tasks[i].id, tasks[i].duration, tasks[i].priority, tasks[i].status);
    }
}

void main() {
    int choice;
    do {
        // Menu
        printf("\nWelcome to the Task Scheduling Simulation\n");
        printf("Please select an option:\n");
        printf("1. Enter tasks\n");
        printf("2. Execute task scheduling\n");
        printf("3. Show the status of all tasks\n");
        printf("4. View results report\n");
        printf("5. Exit\n");
        printf("Choose an option:");
        scanf("%d", &choice);

        // Options
        switch (choice) {
            case 1:
                enterTasks();
                break;
            
            case 2:
                printf("Execute task scheduling\n");
                break;

            case 3:
                printf("Show the status of all tasks\n");
                break;

            case 4:
                printf("View results report\n");
                break;

            case 5:
                printf("---Exiting program---\n");
                break;

            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (choice != 5);
}