// Agregar comments al final
// Todos los comments que hay currently son sobre cosas que faltan
// Falta agregar que cheque todo en plan si son mas de 500 tasks o si el numero de tasks es negativo o asi

#include <stdio.h>

struct scheduler {
    int id;
    int duration;
    int priority;
    char *status;
    int dependencies;
};

int mode, *num;

void enterTasks(struct scheduler tasks[], int *num) {
    // 1. The program will ask for the total number of tasks
        printf("Enter the total number of tasks: ");
        scanf("%d", num);

    // Then, for each task:
        for(int id = 0; id < *num; id++){
            // Assigns a unique ID
            tasks[id].id = id;
            printf("For task with ID #%d:\n", id);

            // Request duration of the task 
            do {
                printf("Enter the duration of the task: ");
                scanf("%d", &tasks[id].duration);
                if (tasks[id].duration <= 0 || tasks[id].duration > 1000) {
                    printf("Invalid duration. Please try again.\n");
                }
            } while (tasks[id].duration <= 0);

            // Request priority of the task
            do {
                printf ("Enter the priority of the task: ");
                scanf("%d", &tasks[id].priority);
                if (tasks[id].priority < 0 || tasks[id].priority > 25) {
                    printf("Invalid priority. Please try again.\n");
                }
            } while (tasks[id].priority < 1 || tasks[id].priority > 25);

            // Default status of each task is pending
            tasks[id].status = "Pending";
        }

        // Dependency list for each task
        for (int i = 0; i < *num; i++) {
            tasks[i].dependencies = 0;
            printf("Enter dependencies for task #%d (end with -1): ", i);
            while (1) {
                int dep;
                scanf("%d", &dep);
                if (dep == -1) {
                    break; 
                }
                if (dep >= 0 && dep < *num) {
                    tasks[i].dependencies++;
                } else {
                    printf("Invalid dependency. Please try again.\n");
                }   
            }
        }

        printf("For debugging POST-dependencies: \n");
        for (int i = 0; i < *num; i++) {
            printf("Task #%d - Duration: %d sec, Priority %d, Status: %s, Dependencies: %d\n", 
                tasks[i].id, tasks[i].duration, tasks[i].priority, tasks[i].status, tasks[i].dependencies);
        }
    }

void executeTaskScheduling(struct scheduler tasks[], int num) {
    printf("Executing task scheduling...\n");
}

void showStatus(struct scheduler tasks[], int num) {
    // Falta que si no hay dependencias, salga None en vez de 0
    printf("Showing status of all tasks...\n");
    for (int i = 0; i < num; i++) {
        printf("Task #%d - Duration: %d sec, Priority %d, Status: %s, Dependencies: %d\n", tasks[i].id, tasks[i].duration, tasks[i].priority, tasks[i].status, tasks[i].dependencies);
    }
}

void viewResults() {
    printf("Viewing results report...\n");
    printf("Total time: %d\n", 0);
    printf("Completed tasks: %d\n", 0);
}

void main () {
    int choice;
    int num = 0;
    struct scheduler tasks[500];

    printf("Mode: ");
    scanf("%d", &mode);

    do {
        if (mode != 0) {
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
                enterTasks(tasks, &num);
                break;
            case 2:
                executeTaskScheduling(tasks, num);
                break;
            case 3:
                showStatus(tasks, num);
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