#include <stdlib.h>
#include <stdio.h>
#include "four.h"

void stamp_matrix(struct game *g, int n)
{
    if (n != 0)
        printf("\n");

    for (int i = 0; i < get_columns(g); i++)
    {
        printf("-");
    }

    printf("\n");

    for (int i = get_rows(g) - 1; i >= 0; --i)
    {
        for (int j = 0; j < get_columns(g); j++)
        {
            printf("%c", get_cell(g, j, i));
        }
        printf("\n");
    }

    for (int i = 0; i < get_columns(g); ++i)
    {
        printf("-");
    }
    printf("\n");

    int complete_cycle = get_columns(g) / 10;
    int half_cycle = get_columns(g) % 10;
    for (int i = 0; i < complete_cycle; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            printf("%d", j);
        }
    }
    for (int i = 0; i < half_cycle; ++i)
    {
        printf("%d", i);
    }

    printf("\n");
    if (!board_full(g) && (outcome(g) != PLAYER_X && outcome(g) != PLAYER_O))
        printf("Player '%c' to move:\n", get_next_player(g));
}

void stamp_indicator(struct game *g, int choose)
{

    for (int i = 0; i < get_columns(g); i++)
    {
        if (i == choose)
        {
            printf("%c", get_next_player(g));
            break;
        }
        else
            printf(" ");
    }

    printf("\n");

    for (int i = 0; i < get_columns(g); i++)
    {
        if (i == choose)
        {
            printf("v");
            break;
        }
        else
            printf(" ");
    }
}

int main(int argc, char **argv)
{
    struct game *g;

    if (argc == 1)
    {
        g = create(7, 7, PLAYER_O);
    }
    else if (argc == 2)
    {
        g = create(atoi(argv[1]), 7, PLAYER_O);
    }
    else if (argc == 3)
    {
        g = create(atoi(argv[1]), atoi(argv[2]), PLAYER_O);
    }
    else if (argc == 4)
    {
        g = create(atoi(argv[1]), atoi(argv[2]), *(argv[3]));
    }

    stamp_matrix(g, 0);
    int choose;
    char choose2;
    char choose3;

    do
    {
        if (scanf("%d", &choose) == 1)
        {

            if (choose >= 0 && choose < get_columns(g))
            {
                if (!is_full_column(g, choose))
                    stamp_indicator(g, choose);

                if (move(g, choose))
                {
                    stamp_matrix(g, 1);
                }
                else
                {
                    printf("Illegal move.\n");
                }
            }
            else
            {
                printf("Illegal move.\n");
            }

            if (outcome(g) == PLAYER_O)
                printf("Player 'o' wins!\n");

            if (outcome(g) == PLAYER_X)
                printf("Player 'x' wins!\n");

            if (board_full(g))
            {
                printf("Game over.\n");
                destroy(g);
                return 0;
            }
        }
        else if (scanf("%c\n", &choose2) == 1)
        {
            switch (choose2)
            {
            case 'q':
                destroy(g);
                return 0;

            case 'r':
                    //printf("\n");
                if (scanf("%c", &choose3))
                {
                    if (choose3 == 'x')
                    {
                        restart(g, PLAYER_X);
                        stamp_matrix(g, 0);
                    }

                    else if (choose3 == 'o')
                    {
                        restart(g, PLAYER_O);
                        stamp_matrix(g, 0);
                    }
                }
                break;

            default:
                printf("Unknown command.\n");
            }
        }
        else if (choose2 == EOF)
        {
            destroy(g);
            return 0;
        }
        else
        {
            destroy(g);
            return 0;
        }

    } while ((outcome(g) != PLAYER_X && outcome(g) != PLAYER_O) || board_full(g));

    destroy(g);
    return 0;
}
