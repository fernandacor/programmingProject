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
    if (mode == 0) {
        printf("Judge Mode.\n");
        scanf("%d", num);
        if (*num <= 0) {
            return;
        }
        for(int id = 0; id < *num; id++){
            tasks[id].id = id;
            do {
                scanf("%d", &tasks[id].duration);

                if (tasks[id].duration <= 0 || tasks[id].duration > 1000) {
                    return;
                }
            } while (tasks[id].duration <= 0);

            do {
                scanf("%d", &tasks[id].priority);
                if (tasks[id].priority < 0 || tasks[id].priority > 25) {
                    return;
                }
            } while (tasks[id].priority < 1 || tasks[id].priority > 25);

            tasks[id].status = "Pending";
        }

        for (int i = 0; i < *num; i++) {
            tasks[i].dependencies = 0;
            while (1) {
                int dep;
                scanf("%d", &dep);
                if (dep == -1) {
                    break; 
                }
                if (dep >= 0 && dep < *num) {
                    tasks[i].dependencies++;
                } else {
                    return;
                }   
            }
        }

        printf("For debugging POST-dependencies: \n");
        for (int i = 0; i < *num; i++) {
            printf("Task #%d - Duration: %d sec, Priority %d, Status: %s, Dependencies: %d\n", 
                tasks[i].id, tasks[i].duration, tasks[i].priority, tasks[i].status, tasks[i].dependencies);
        }
    }
    else {
        printf("Enter the total number of tasks: ");
        scanf("%d", num);

        if (*num <= 0) {
            printf("Invalid number of tasks.\n");
            return;
        }

        for(int id = 0; id < *num; id++){
            tasks[id].id = id;
            printf("For task with ID #%d:\n", id);

            do {
                printf("Enter the duration of the task: ");
                scanf("%d", &tasks[id].duration);

                if (tasks[id].duration <= 0 || tasks[id].duration > 1000) {
                    printf("Invalid duration. Please try again.\n");
                }
            } while (tasks[id].duration <= 0);

            do {
                printf ("Enter the priority of the task: ");
                scanf("%d", &tasks[id].priority);
                if (tasks[id].priority < 0 || tasks[id].priority > 25) {
                    printf("Invalid priority. Please try again.\n");
                }
            } while (tasks[id].priority < 1 || tasks[id].priority > 25);

            tasks[id].status = "Pending";
        }

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
}

void executeTaskScheduling(struct scheduler tasks[], int num) {
    int completedTasks[num];
    int completedCount = 0; //cambiar a count
    int totalTime = 0;

    while (completedCount < num) {
        int selectedTask = -1; // cambiar a currentTask

        for (int i = 0; i < num; i++) {
            if (tasks[i].status == "Pending" && tasks[i].dependencies == 0) {
                if (selectedTask == -1 || 
                    tasks[i].priority < tasks[selectedTask].priority ||
                    (tasks[i].priority == tasks[selectedTask].priority && tasks[i].duration < tasks[selectedTask].duration) ||
                    (tasks[i].priority == tasks[selectedTask].priority && tasks[i].duration == tasks[selectedTask].duration && tasks[i].id < tasks[selectedTask].id)) {
                        selectedTask = i;
                }
            }
        }

        if (selectedTask == -1) {
            break; // No executable tasks due to unmet dependencies
        }

        printf("Task %d started...\n", tasks[selectedTask].id);
        totalTime += tasks[selectedTask].duration;
        printf("\t Task %d completed in %d seconds\n", tasks[selectedTask].id, totalTime);

        tasks[selectedTask].status = "Completed";
        completedTasks[completedCount] = tasks[selectedTask].id;

        for (int i = 0; i < num; i++) {
            if (tasks[i].status == "Pending") {
                tasks[i].dependencies--;
            }
        }

        printf("Task scheduling completed.\n");
    }
    //Starts executing tasks, respecting dependencies and prioritizing urgency (lower priority values indicate higher urgency).
    //The program should identify tasks with no pending dependencies and, among those, select the highest-priority task to execute.
    //If multiple tasks share the same priority and can be executed, it selects the one with the shortest duration; 
    //if the tie persists, it chooses the one with the smallest task_id.
    //During execution in user mode, the program should print a message indicating the start and completion of each task, including the cumulative time up to that point  
}

void showStatus(struct scheduler tasks[], int num) {
    printf("Showing status of all tasks...\n");
    for (int i = 0; i < num; i++) {
        printf("Task #%d - Duration: %d sec, Priority %d, Status: %s, Dependencies: %d\n", tasks[i].id, tasks[i].duration, tasks[i].priority, tasks[i].status, tasks[i].dependencies);
    }
}

void viewResults(struct scheduler tasks[], int num) {
    int totalTime = 0;
    int completedTasks[num];
    int completedCount = 0;
    int failedTasks[num];
    int failedCount = 0;

    for (int i = 0; i < num; i++) {
        if (tasks[i].status == "Completed") {
            completedTasks[completedCount++] = tasks[i].id;
            totalTime += tasks[i].duration;
        } else if (tasks[i].status == "Pending") {
            failedTasks[failedCount++] = tasks[i].id;
        }
    }

    printf("Total time taken: %d\n", totalTime);

    printf("Completed tasks: ");
    for (int i = 0; i < completedCount; i++) {
        printf("%d ", completedTasks[i]);
    }
    printf("\n");

    if (failedCount > 0) {
        printf("Uncompleted tasks due to unmet dependencies: ");
        for (int i = 0; i < failedCount; i++) {
            printf("%d ", failedTasks[i]);
        }
        printf("\n");
    } else {
        printf("All tasks were completed successfully.\n");
    }
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
                viewResults(tasks, num);
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