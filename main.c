// Group 7: Fernanda Cantú Ortega, Cristina Alessandra González, Iker García Germán

// Agregar comments al final
// Todos los comments que hay currently son sobre cosas que faltan
// Falta agregar que cheque todo en plan si son mas de 500 tasks o si el numero de tasks es negativo o asi

#include <stdio.h>
#include <stdbool.h> // gpt

struct scheduler {
    int id;
    int duration;
    int priority;
    char *status;
    int dependencies;
    int dependencyList[100]; // gpt
};

int mode, *num, executionCount;
int executionOrder[500];

void enterTasks(struct scheduler tasks[], int *num) {
    if (mode == 0) {
        scanf("%d", num);

        if (*num <= 0)
            return;

        for(int id = 0; id < *num; id++){
            tasks[id].id = id;
            do {
                scanf("%d", &tasks[id].duration);
                if (tasks[id].duration <= 0 || tasks[id].duration > 1000)
                    return;
            } while (tasks[id].duration <= 0);

            do {
                scanf("%d", &tasks[id].priority);
                if (tasks[id].priority < 0 || tasks[id].priority > 25)
                    return;
            } while (tasks[id].priority < 1 || tasks[id].priority > 25);

            tasks[id].status = "Pending";
            tasks[id].dependencies = -1;
        }

        for (int i = 0; i < *num; i++) {
            while (1) {
                int dependency;
                scanf("%d", &dependency);
                if (dependency == -1) {
                    break; 
                }
                if (dependency >= 0 && dependency < *num) {
                    // Fix que me dio gepeto, a ver sicierto
                    if (tasks[i].dependencies == -1) {
                        tasks[i].dependencies = 0;
                    }
                    tasks[i].dependencyList[tasks[i].dependencies++] = dependency;
                } else {
                    return;
                }   
            }
        }
    } else {
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
                printf("\tEnter the duration of the task (in seconds, must be positive): ");
                scanf("%d", &tasks[id].duration);

                if (tasks[id].duration <= 0 || tasks[id].duration > 1000) {
                    printf("Invalid duration. Please try again.\n");
                }
            } while (tasks[id].duration <= 0);

            do {
                printf ("\tEnter the priority of the task (lower values indicate higer priority): ");
                scanf("%d", &tasks[id].priority);
                if (tasks[id].priority < 0 || tasks[id].priority > 25) {
                    printf("Invalid priority. Please try again.\n");
                }
            } while (tasks[id].priority < 1 || tasks[id].priority > 25);

            tasks[id].status = "Pending";
            tasks[id].dependencies = -1;
            printf("\n");
        }

        for (int i = 0; i < *num; i++) {
            printf("Enter dependencies for task #%d (end with -1): ", i);
            while (1) {
                int dependency;
                scanf("%d", &dependency);
                if (dependency == -1) {
                    break; 
                }
                if (dependency >= 0 && dependency < *num) {
                    // Fix que me dio gepeto, a ver sicierto
                    if (tasks[i].dependencies == -1) {
                        tasks[i].dependencies = 0;
                    }
                    tasks[i].dependencyList[tasks[i].dependencies++] = dependency;
                } else {
                    printf("Invalid dependency. Please try again.\n");
                }   
            }
        }
    }
}

//gpt
bool canExecute(struct scheduler task, struct scheduler tasks[]) {
    for (int i = 0; i < task.dependencies; i++) {
        if (tasks[task.dependencyList[i]].status != "Completed") {
            return false;
        }
    }
    return true;
}

void executeTaskScheduling(struct scheduler tasks[], int num) {
    int completedTasks[num];
    int completedCount = 0; //cambiar a count
    int totalTime = 0;

    while (completedCount < num) {
        int currentTask = -1;

        for (int i = 0; i < num; i++) {
            if (tasks[i].status == "Pending" && canExecute(tasks[i], tasks)) { //gpt
                if (currentTask == -1 || 
                    tasks[i].priority < tasks[currentTask].priority ||
                    (tasks[i].priority == tasks[currentTask].priority && tasks[i].duration < tasks[currentTask].duration) ||
                    (tasks[i].priority == tasks[currentTask].priority && tasks[i].duration == tasks[currentTask].duration && tasks[i].id < tasks[currentTask].id)) {
                        currentTask = i;
                }
            }
        }

        if (currentTask == -1)
            break;

        if (mode == 0) {
            totalTime += tasks[currentTask].duration;
            tasks[currentTask].status = "Completed";
            completedTasks[completedCount++] = tasks[currentTask].id;
            for (int i = 0; i < num; i++) {
                if (tasks[i].status == "pending") {
                    tasks[i].dependencies--;
                }
            }
        } else {
            printf("Task %d started...\n", tasks[currentTask].id);
            totalTime += tasks[currentTask].duration;
            printf("\t Task %d completed in %d seconds\n", tasks[currentTask].id, totalTime);

            tasks[currentTask].status = "Completed";
            completedTasks[completedCount++] = tasks[currentTask].id;

            for (int i = 0; i < num; i++) {
                if (tasks[i].status == "pending") {
                    tasks[i].dependencies--;
                }
            }

            printf("Task scheduling completed.\n");  
        }
    }
    
}

void showStatus(struct scheduler tasks[], int num) {
    if (mode == 0) {
        return;
    } else {
        printf("Task scheduling in user mode.\n");
        printf("Status of all tasks:\n");
        for (int i = 0; i < num; i++) {
            printf("\tTask #%d - Duration: %d sec, Priority %d, Status: %s, Dependencies: ", tasks[i].id, tasks[i].duration, tasks[i].priority, tasks[i].status);
            if (tasks[i].dependencies == -1) {
                printf("None\n");
            } else {
                for (int j = 0; j < tasks[i].dependencies; j++) {
                    printf("%d ", tasks[i].dependencyList[j]);
                }
                printf("\n");
            }
        }   
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

    // Falta que se imprima en el orden en el que se realizaron las tareas
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
    }
}

void main () {
    int choice;
    int num = 0;
    struct scheduler tasks[500];

    scanf("%d", &mode);

    do {
        if (mode != 0) {
            printf("\nMenu:\n");
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
                    printf("Thank you for using the task scheduling simulator..\n");
                    break;
                }
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (choice != 5);
}