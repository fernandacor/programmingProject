// Group 7: Fernanda Cantú Ortega, Cristina Alessandra González, Iker García Germán

#include <stdio.h>
#include <stdbool.h>

// Struct definition for elements of task
struct task {
    int task_id;
    int duration;
    int priority;
    char *status;
    int dependencies;
    int dependencyList[100];
};

// Global variables
int mode, *num, completedCount;
int completedTasks[500]; // System can support up to 500 tasks

// Function to enter tasks
void enterTasks(struct task taskList[], int *num) {
    if (mode == 0) { // Judge mode
        scanf("%d", num);

        if (*num <= 0)
            return; // Invalid number of tasks

        // Iterate through number of tasks to enter corresponding information
        for(int i = 0; i < *num; i++){
            taskList[i].task_id = i;
            do { // Duration
                scanf("%d", &taskList[i].duration);
                if (taskList[i].duration <= 0 || taskList[i].duration > 1000)
                    return;
            } while (taskList[i].duration <= 0);

            do { // Priority
                scanf("%d", &taskList[i].priority);
                if (taskList[i].priority < 0 || taskList[i].priority > 25)
                    return;
            } while (taskList[i].priority < 1 || taskList[i].priority > 25);

            taskList[i].status = "Pending"; // Set status to pending
            taskList[i].dependencies = -1; // No dependencies by default
        }

        // Iterate through number of tasks to enter dependencies
        for (int i = 0; i < *num; i++) {
            while (1) { // Infinite loop until broken by input -1
                int dependency;
                scanf("%d", &dependency);
                if (dependency == -1) {
                    break; 
                }
                if (dependency >= 0 && dependency < *num) {
                    // If no dependencies, set to 0 (for showing status purposes)
                    if (taskList[i].dependencies == -1) {
                        taskList[i].dependencies = 0;
                    }
                    taskList[i].dependencyList[taskList[i].dependencies++] = dependency; // Dependencies added to list
                } else {
                    return;
                }   
            }
        }
    } else { // User mode
        printf("Enter the total number of tasks: ");
        scanf("%d", num);

        if (*num <= 0) { // Check if number of tasks is valid
            printf("Invalid number of tasks.\n");
            return;
        }

        // Iterate through number of tasks to enter corresponding information
        for(int task_id = 0; task_id < *num; task_id++){
            taskList[task_id].task_id = task_id;
            printf("For task with ID #%d:\n", task_id);

            // Ask for duration and check if it's invalid
            do {
                printf("\tEnter the duration of the task in seconds: ");
                scanf("%d", &taskList[task_id].duration);

                if (taskList[task_id].duration <= 0 || taskList[task_id].duration > 1000) {
                    printf("Invalid duration.\n");
                }
            } while (taskList[task_id].duration <= 0);

            // Ask for priority and check if it's invalid
            do {
                printf ("\tEnter the priority of the task: ");
                scanf("%d", &taskList[task_id].priority);
                if (taskList[task_id].priority < 0 || taskList[task_id].priority > 25) {
                    printf("Invalid priority.\n");
                }
            } while (taskList[task_id].priority < 1 || taskList[task_id].priority > 25);

            taskList[task_id].status = "Pending"; // Set status to pending
            taskList[task_id].dependencies = -1; // No dependencies by default
            printf("\n");
        }

        // Iterate through number of tasks to enter dependencies
        for (int i = 0; i < *num; i++) {
            printf("Enter dependencies for task #%d (end with -1): ", i);
            while (1) { // Infinite loop until broken by input -1
                int dependency;
                scanf("%d", &dependency);
                if (dependency == -1) {
                    break; 
                }
                if (dependency >= 0 && dependency < *num) {
                    // If no dependencies, set to 0 (for showing status purposes)
                    if (taskList[i].dependencies == -1) {
                        taskList[i].dependencies = 0;
                    }
                    taskList[i].dependencyList[taskList[i].dependencies++] = dependency; // Dependencies added to list
                } else {
                    printf("Invalid dependency.\n");
                }   
            }
        }
    }
}

// Function to check if a task can be executed depending on its dependencies
bool canExecute(struct task checkTask, struct task taskList[]) {
    for (int i = 0; i < checkTask.dependencies; i++) {
        if (taskList[checkTask.dependencyList[i]].status != "Completed") { // If any dependency is not completed, the task can not be completed
            return false;
        }
    }
    return true;
}

// Function to execute task scheduling
void executeTaskScheduling(struct task taskList[], int num) {
    int totalTime = 0;

    while (completedCount < num) {
        int currentTask = -1;

        // Iterate through all tasks to find the next task to execute
        for (int i = 0; i < num; i++) {
            if (taskList[i].status == "Pending" && canExecute(taskList[i], taskList)) {
                // Check if everything is in order to execute the task
                if (currentTask == -1 || 
                    taskList[i].priority < taskList[currentTask].priority ||
                    (taskList[i].priority == taskList[currentTask].priority && taskList[i].duration < taskList[currentTask].duration) ||
                    (taskList[i].priority == taskList[currentTask].priority && taskList[i].duration == taskList[currentTask].duration && taskList[i].task_id < taskList[currentTask].task_id)) {
                        currentTask = i;
                }
            }
        }

        // If no task can be executed, break the loop
        if (currentTask == -1)
            break;
        
        if (mode == 0) { // Judge mode
            totalTime += taskList[currentTask].duration;
            taskList[currentTask].status = "Completed";
            completedTasks[completedCount++] = taskList[currentTask].task_id;
        } else { // User mode
            printf("Task %d started...\n", taskList[currentTask].task_id);
            totalTime += taskList[currentTask].duration;
            printf("\t Task %d completed in %d seconds\n", taskList[currentTask].task_id, totalTime);

            taskList[currentTask].status = "Completed";
            completedTasks[completedCount++] = taskList[currentTask].task_id;

            printf("Task scheduling completed.\n");  
        }
    }
    
}

// Function to show the status of all tasks
void showStatus(struct task taskList[], int num) {
    if (mode == 0) { // Judge mode (does not print anything)
        return;
    } else { // User mode
        printf("Status of all tasks:\n");
        for (int i = 0; i < num; i++) { // Iterate through existing tasks
            printf("\tTask #%d - Duration: %d sec, Priority %d, Status: %s, Dependencies: ", taskList[i].task_id, taskList[i].duration, taskList[i].priority, taskList[i].status);
            
            // If no dependencies print "None", else print the dependencies
            if (taskList[i].dependencies == -1) {
                printf("None\n");
            } else {
                for (int j = 0; j < taskList[i].dependencies; j++) {
                    printf("%d ", taskList[i].dependencyList[j]);
                }
                printf("\n");
            }
        }   
    }
}

// Function to show results report (total time, completed tasks, uncompleted tasks if any)
void viewResults(struct task taskList[], int num) {
    int totalTime = 0;
    int failedTasks[num];
    int failedCount = 0;

    // Iterates through all tasks to calculate total time of completed tasks and failed tasks
    for (int i = 0; i < num; i++) {
        if (taskList[i].status == "Completed"){
            totalTime += taskList[i].duration;
        } else if (taskList[i].status == "Pending") {
            failedTasks[failedCount++] = taskList[i].task_id;
        }
    }

    if (mode == 0) { // Judge mode (only prints numbers)
        printf("%d \n", totalTime);
        for (int i = 0; i < completedCount; i++) {
            printf("%d ", completedTasks[i]);
        }
        if (failedCount > 0) {
            for (int i = 0; i < failedCount; i++) {
                printf("%d ", failedTasks[i]);
            }
            printf("\n");
        }
        
    printf("\n");
    } else { // User mode
        printf("Total time taken: %d\n", totalTime);

        printf("Completed tasks: ");
        for (int i = 0; i < completedCount; i++) {
            printf("%d ", completedTasks[i]);
        }
        
        printf("\n");

        if (failedCount > 0) {
            printf("Uncompleted tasks: ");
            for (int i = 0; i < failedCount; i++) {
                printf("%d ", failedTasks[i]);
            }
            printf("\n");
        }
    }
}

// Main function
void main () {
    int choice;
    int num = 0;
    struct task taskList[500];

    scanf("%d", &mode); // Reads integer for mode

    do {
        if (mode != 0) { // Print menu if on user mode
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
                enterTasks(taskList, &num);
                break;
            case 2:
                executeTaskScheduling(taskList, num);
                break;
            case 3:
                showStatus(taskList, num);
                break;
            case 4:
                viewResults(taskList, num);
                break;
            case 5:
                if (mode == 0) {
                    break;
                } else {
                    printf("----Exiting program----\n");
                    break;
                }
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 5);
}