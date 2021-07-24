#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

struct Item {

    uint value;
    uint weight;
};

typedef struct Item Item;

Item** new_items(uint length) {

    return (Item**)malloc(sizeof(Item*) * length);
} // end of new_items(uint)

void input_items(Item **items, uint length) {

    Item *item;
    int i = 0;

    for (; i < length; i++) {

        item = (Item*)malloc(sizeof(Item));

        printf("Enter value of item %d: ", (i + 1));
        scanf("%d", &item->value);
        printf("Enter weight of item %d: ", (i + 1));
        scanf("%d", &item->weight);

        *(items + i) = item;
    }
} // end of input_items(Item**, uint)

void display_item(Item *item) {

    printf("{ value: %d, weight: %d }", item->value, item->weight);
} // end of display_item(Item*)

void display_items(Item **items, uint length) {

    int i = 0;
    for (; i < length; i++) {

        printf("Item %d: ", (i + 1));
        display_item(*(items + i));
        printf("\n");
    }
} // end of display_items(Item**, uint)


void ratio_sort(Item **items, uint length) {
            
    // sorting according to ratio in descending :-
    Item *tempBlock;
    double ratio1, ratio2;
    int i, j, f;
        
    for (i = 0; i < length - 1; i++) { // of course, the good old Bubble Sort

        f = 0;

        for (j = 0; j < length - i - 1; j++) {

            ratio1 = (1.0 * (*(items + j))->value) / (*(items + j))->weight;
            ratio2 = (1.0 * (*(items + j + 1))->value) / (*(items + j + 1))->weight;
                
            if (ratio1 < ratio2) {

                f = 1;
                    
                tempBlock = *(items + j);
                *(items + j) = *(items + j + 1);
                *(items + j + 1) = tempBlock;
            } // end of if block
        } // end of inner for loop

        if (!f) return;
    } // end of outer for loop

} // end of ratioSort(Item**, uint)

double fractional_knapsack(uint capacity, Item **items, uint length) {
        
    // calculating the max possible profit :-
    uint weight = 0; 
    double profit = 0.0;

    for (int i = 0; i < length; i++) {
            
        if (weight < capacity) {
                
            if ((capacity - weight) >= (*(items + i))->weight) {
                    
                weight += (*(items + i))->weight;
                profit += (*(items + i))->value;
            }
            else {
                    
                profit += (capacity - weight) * ((1.0 * (*(items + i))->value) / (*(items + i))->weight);
                break;
            }
        } // end of outer if block
    } // end of outer for loop
        
    return profit;
} // end of fractionalKnapsack(unsigned int, Item[], unsigned int)


int main() {

    uint length;
    uint capacity;

    printf("Enter the number of items: ");
    scanf("%d", &length);

    Item **items = new_items(length);

    input_items(items, length);
    display_items(items, length);

    printf("Enter capacity of Knapsack: ");
    scanf("%d", &capacity);

    ratio_sort(items, length);

    double profit = fractional_knapsack(capacity, items, length);

    printf("Maximum possible profit: %.2f\n", profit);

    return 0;
} // end of main()