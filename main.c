#include <stdio.h>

struct scheduler {
    int id; // Task ID
    int duration; // Duration of task
    int priority; // Priority of task
    char status; // Status (pending, running, completed)
    int dependencies; // Dependencies of task
};

int mode, *num;

void enterTasks() {
    int num = &num;

    if (mode == 0) {
        printf("Judge Mode\n");
    } else {
        printf("Enter the total number of tasks: ");
        scanf("%d", &num);

        if (num <= 0) { 
            printf("Invalid number of tasks. Please try again.\n");
        }

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

            tasks[id].status = 'P';

            printf("Tasks entered: \n");
            for (int i = 0; i < num; i++) {
                // printf("%d\t%d\t\t%d\t\t%c\n", tasks[i].id, tasks[i].duration, tasks[i].priority, tasks[i].status);
                printf("Task #%d - Duration: %d sec, Priority %d, Status: %c, Dependencies: %d\n", tasks[i].id, tasks[i].duration, tasks[i].priority, tasks[i].status, tasks[i].dependencies);
            }
        }
    }
}

void executeTaskScheduling() {
    printf("Executing task scheduling...\n");
    if (mode == 0) {
        printf("Judge mode\n");
    } else {
        // tiene que buscar priority y acomodarlo en orden de menor a mayor
        // si hay dos con la misma prioridad, entonces se acomoda por el que tenga menos duracion
        // si hay dos con el mismo tiempo, entonces se acomoda por el que tenga menos id
    }   
}

void showStatus() {
    int num = &num;
    if (mode == 0) {
        printf("Judge mode\n");
    } else {
        printf("Showing status of all tasks...\n");
        for (int i = 0; i < &num; i++) {
            printf("Task #%d - Duration: %d sec, Priority %d, Status: %c, Dependencies: %d\n", tasks[i].id, tasks[i].duration, tasks[i].priority, tasks[i].status, tasks[i].dependencies);
        }
    }

}

void viewResults() {
    printf("Viewing results report...\n");
}

void main () {
    int choice;
    printf("Mode: ");
    scanf("%d", &mode);

    do {
        if (mode != 0) { //Show menu only if in User Mode
            printf("\nWelcome to the Task Scheduling Simulation\n");
            printf("Please select an option:\n");
            printf("1. Enter tasks\n");
            printf("2. Execute task scheduling\n");
            printf("3. Show the status of all tasks\n");
            printf("4. View results report\n");
            printf("5. Exit\n");
            printf("Choose an option: ");
        }
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                enterTasks();
                break;
            case 2:
                executeTaskScheduling();
                break;
            case 3:
                showStatus();
                break;
            case 4:
                viewResults();
                break;
            case 5:
                if (mode == 0) {
                    break;
                } else {
                    printf("---Exiting program---\n");
                    break;
                }
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (choice != 5);
}