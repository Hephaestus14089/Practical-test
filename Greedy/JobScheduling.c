#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

struct Job {

    char id;
    uint deadline;
    uint profit;
};

typedef struct Job Job;

Job* new_job() {

    Job *job = (Job*)malloc(sizeof(Job));

    job->id = '\0';
    job->deadline = 0;
    job->profit = 0;

    return job;
} // end of new_job()

void profit_sort(Job **jobs, uint len) {
            
    // sorting according to ratio in descending :-
    Job *tempBlock;
    int i, j, f;
        
    for (i = 0; i < len - 1; i++) { // of course, the good old Bubble Sort

        f = 0;

        for (j = 0; j < len - i - 1; j++) {
                
            if ((*(jobs + j))->profit < (*(jobs + j + 1))->profit) {

                f = 1;
                    
                tempBlock = *(jobs + j);
                *(jobs + j) = *(jobs + j + 1);
                *(jobs + j + 1) = tempBlock;
            } // end of if block
        } // end of inner for loop

        if (!f) return;
    } // end of outer for loop

} // end of ratioSort(struct job*, uint)

void display(char *id, int len) {

    printf("Schedule ids: ");

    int i = 0;
    for (; i < len; i++) {
        printf("%c ", *(id + i));
    }
} // end of display(char[], int)

int *get_schedule(Job **jobs, uint len) {

    int *schedule = (int*)malloc(sizeof(int) * len);
    char *id = (char*)malloc(sizeof(char) * len);
    int deadline;

    int i = 0;
    for (; i < len; i++) { *(schedule + i) = 0; } // initialising schedule

    for (i = 0; i < len; i++) {

        deadline = (*(jobs + i))->deadline - 1;

        while (deadline >= 0) {

            if (!(*(schedule + deadline))) {

                *(schedule + deadline) = (*(jobs + i))->profit;
                *(id + deadline) = (*(jobs + i))->id;
                break;
            }
                 
            deadline--;
        } // end of inner while loop
    } // end of outer for loop

    display(id, len);

    return schedule;
} // end of get_schedule(struct job*, uint)

int schedule_sum(int *schedule, uint len) {

    uint sum = 0;
    uint i = 0;

    for (; i < len; i++) {
        sum += *(schedule + i);
    }
    
    return sum;
} // end of schedule_sum(int*, uint)

void display_schedule(int *schedule, uint len) {

    int i = 0;
    for (; i < len; i++) {
        if (*(schedule + i)) {
            printf("%d ", *(schedule + i));
        }
    } // end of for loop
    
    printf("\n");
} // end of display_schedule(int*, uint)

void input(Job **jobs, uint len) {

    Job *job;
    char id = 'A';

    for (int i = 0; i < len; i++) {

        job = new_job();

        job->id = id;
        printf("Enter profit for job %c: ", id);
        scanf("%d", &job->profit);
        printf("Enter deadline for job %c: ", id);
        scanf("%d", &job->deadline);

        *(jobs + i) = job;

        id++;
    }
} // end of input(Item[], uint)

int main() {

    uint len;

    printf("Enter the number of jobs: ");
    scanf("%d", &len);

    Job **jobs = (Job**)malloc(sizeof(Job*) * len);
    
    input(jobs, len);

    profit_sort(jobs, len);

    printf("\n");

    int *schedule = get_schedule(jobs, len);

    uint total_profit = schedule_sum(schedule, len);

    printf("\nSchedule profits: ");
    display_schedule(schedule, len);

    printf("\nTotal profit: %d\n", total_profit);

    return 0;
} // end of main()
