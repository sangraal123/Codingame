#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Save humans, destroy zombies!
 **/

typedef struct {
    int creature_id;
    int creature_x;
    int creature_y;
} Coordinates;

Coordinates humans[100] = {0};
Coordinates zombies[100] = {0};
int nearX=0;
int nearY=0;

int main()
{

    // game loop
    while (1) {

    for (int i = 0; i < 100; i++) {
        humans[i].creature_id = 0;
        humans[i].creature_x = 0;
        humans[i].creature_y = 0;
    }

    for (int i = 0; i < 100; i++) {
        zombies[i].creature_id = 0;
        zombies[i].creature_x = 0;
        zombies[i].creature_y = 0;
    }

        int x;
        int y;
        scanf("%d%d", &x, &y);
        int human_count;
        scanf("%d", &human_count);
        for (int i = 0; i < human_count; i++) {
            scanf("%d%d%d", &humans[i].creature_id, &humans[i].creature_x, &humans[i].creature_y);
            fprintf(stderr, "human %d at (%d, %d)\n", humans[i].creature_id, humans[i].creature_x, humans[i].creature_y);
        }
        int zombie_count;
        scanf("%d", &zombie_count);
        for (int i = 0; i < zombie_count; i++) {
            int zombie_xnext;
            int zombie_ynext;
            scanf("%d%d%d%d%d", &zombies[i].creature_id, &zombies[i].creature_x, &zombies[i].creature_y, &zombie_xnext, &zombie_ynext);
            fprintf(stderr, "zombie %d at (%d, %d) moving to (%d, %d)\n", zombies[i].creature_id, zombies[i].creature_x, zombies[i].creature_y, zombie_xnext, zombie_ynext);
        }

        int distanceNearest=0;
        int distance=0;

        for (int i=0; i<100; i++) {
                if( humans[i].creature_id == 0 && humans[i].creature_x == 0 && humans[i].creature_y == 0 ) break;
                fprintf(stderr, "Player%d: %d %d\n", humans[i].creature_id, humans[i].creature_x, humans[i].creature_y);

            int distanceZombieNearest=0;
            int distanceZombie=0;

            for (int j=0; j<100; j++) {
                if( zombies[j].creature_id == 0 && zombies[j].creature_x == 0 && zombies[j].creature_y == 0 ) break;
                fprintf(stderr, "Zombie%d: %d %d\n", zombies[j].creature_id, zombies[j].creature_x, zombies[j].creature_y);

                distanceZombie = sqrt(pow((humans[i].creature_x - zombies[j].creature_x), 2) + pow((humans[i].creature_y - zombies[j].creature_y), 2));
                fprintf(stderr, "Distance between zombie %d and human %d is %d\n", j, i, distanceZombie);

                if ( j == 0 || distanceZombie < distanceZombieNearest ) {
                    distanceZombieNearest = distanceZombie;
                }
            }

            int distancePlayer=sqrt(pow(x-humans[i].creature_x,2)+pow(y-humans[i].creature_y,2));
            fprintf(stderr, "Distance from Player%d to human is %d\n", humans[i].creature_id, distancePlayer);

            distance = distancePlayer - distanceZombieNearest;
            fprintf(stderr, "Sum of Distance is %d\n", distance);

        if ( i == 0 || distance < distanceNearest) {
            distanceNearest = distance;
            nearX = humans[i].creature_x;
            nearY = humans[i].creature_y;
        }

        // Write an action using printf(). DON'T FORGET THE TRAILING \n
        // To debug: fprintf(stderr, "Debug messages...\n");
        }
        printf("%d %d\n", nearX, nearY); // Your destination coordinates        
    }

    return 0;
}
