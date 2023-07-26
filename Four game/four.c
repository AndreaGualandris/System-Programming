#include <stdlib.h>
#include <stdio.h>
#include "four.h"

struct game
{
    int columns;
    int rows;
    char first_player;
    char **matrix;
};

struct game *create(int columns, int rows, char first_player)
{
    struct game *this = malloc(sizeof(struct game));

    if (this)
    {
        this->columns = columns;
        this->rows = rows;
        this->first_player = first_player;
        this->matrix = malloc(sizeof(char *) * columns);

        for (int i = 0; i < columns; ++i)
        {
            this->matrix[i] = malloc(sizeof(char) * rows);
        }

        for (int i = 0; i < columns; ++i)
        {
            for (int j = 0; j < rows; ++j)
            {
                this->matrix[i][j] = EMPTY;
            }
        }
    }
    return this;
};

void destroy(struct game *g)
{
    for (int i = 0; i < g->columns; ++i)
    {
        free(g->matrix[i]);
    }
    free(g->matrix);
    free(g);
};

void restart(struct game *g, char first_player)
{
    g->first_player = first_player;

    for (int i = 0; i < g->columns; ++i)
    {
        for (int j = 0; j < g->rows; ++j)
        {
            g->matrix[i][j] = EMPTY;
        }
    }
};

int move(struct game *g, int column)
{
    if (column >= 0 && column <= get_columns(g))
    {
        if (!is_full_column(g, column))
        {
            for (int i = 0; i < g->rows; ++i)
            {
                if (g->matrix[column][i] == EMPTY)
                {
                    g->matrix[column][i] = get_next_player(g);

                    if (get_next_player(g) == PLAYER_X)
                    {
                        g->first_player = PLAYER_O;
                    }
                    else if (get_next_player(g) == PLAYER_O)
                    {
                        g->first_player = PLAYER_X;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
};

int is_full_column(const struct game *g, int column)
{
    for (int j = 0; j < g->rows; ++j)
    {
        if (g->matrix[column][j] == EMPTY)
            return 0;
    }
    return 1;
};

char get_cell(const struct game *g, int column, int row)
{
    return g->matrix[column][row];
};

char get_next_player(const struct game *g)
{
    return g->first_player;
};

int get_columns(const struct game *g)
{
    return g->columns;
};
int get_rows(const struct game *g)
{
    return g->rows;
};

int board_full(const struct game *g)
{
    for (int i = 0; i < g->columns; ++i)
    {
        for (int j = 0; j < g->rows; ++j)
        {
            if (g->matrix[i][j] == EMPTY)
                return 0;
        }
    }
    return 1;
};

char outcome(const struct game *g)
{

    //4 in colonna

    for (int j = 0; j < g->columns; ++j)
    {
        for (int i = 0; i < g->rows; ++i)
        {
            if (g->matrix[j][i] == PLAYER_X)
            {
                if (
                    g->matrix[j][i + 1] == PLAYER_X &&
                    g->matrix[j][i + 2] == PLAYER_X &&
                    g->matrix[j][i + 3] == PLAYER_X)
                    return PLAYER_X;
            }
            else if (g->matrix[j][i] == PLAYER_O)
            {
                if (
                    g->matrix[j][i + 1] == PLAYER_O &&
                    g->matrix[j][i + 2] == PLAYER_O &&
                    g->matrix[j][i + 3] == PLAYER_O)
                    return PLAYER_O;
            }
            else if (g->matrix[j][i] == EMPTY)
            {
                break;
            }
        }
    }

    //4 in riga
    for (int j = 0; j < g->columns; ++j)
    {
        for (int i = 0; i < g->rows; ++i)
        {
            if (j < 3 && g->columns - j >= 4) //parete sinistra
            {
                //controlla solo a destra
                if (g->matrix[j][i] == PLAYER_X)
                {
                    if (
                        g->matrix[j + 1][i] == PLAYER_X &&
                        g->matrix[j + 2][i] == PLAYER_X &&
                        g->matrix[j + 3][i] == PLAYER_X)
                        return PLAYER_X;
                }
                else if (g->matrix[j][i] == PLAYER_O)
                {
                    if (
                        g->matrix[j + 1][i] == PLAYER_O &&
                        g->matrix[j + 2][i] == PLAYER_O &&
                        g->matrix[j + 3][i] == PLAYER_O)
                        return PLAYER_O;
                }
                else if (g->matrix[j][i] == EMPTY)
                {
                    break;
                }
            }
            else if (j >= 3 && ((g->columns - 1) - j) >= 3) //posizioni centralli
            {
                if (g->matrix[j][i] == PLAYER_X)
                {

                    if (
                        (
                            g->matrix[j + 1][i] == PLAYER_X &&
                            g->matrix[j + 2][i] == PLAYER_X &&
                            g->matrix[j + 3][i] == PLAYER_X) ||
                        (g->matrix[j - 1][i] == PLAYER_X &&
                         g->matrix[j - 2][i] == PLAYER_X &&
                         g->matrix[j - 3][i] == PLAYER_X))
                        return PLAYER_X;
                }

                if (g->matrix[j][i] == PLAYER_O)
                {
                    if (
                        (
                            g->matrix[j + 1][i] == PLAYER_O &&
                            g->matrix[j + 2][i] == PLAYER_O &&
                            g->matrix[j + 3][i] == PLAYER_O) ||
                        (g->matrix[j - 1][i] == PLAYER_O &&
                         g->matrix[j - 2][i] == PLAYER_O &&
                         g->matrix[j - 3][i] == PLAYER_O))
                        return PLAYER_O;
                }
                else if (g->matrix[j][i] == EMPTY)
                {
                    break;
                }
            }
            else if (j >= 3) //parete destra
            {
                //controlla solo a sinistra
                if (g->matrix[j][i] == PLAYER_X)
                {
                    if (
                        g->matrix[j - 1][i] == PLAYER_X &&
                        g->matrix[j - 2][i] == PLAYER_X &&
                        g->matrix[j - 3][i] == PLAYER_X)
                        return PLAYER_X;
                }
                else if (g->matrix[j][i] == PLAYER_O)
                {
                    if (
                        g->matrix[j - 1][i] == PLAYER_O &&
                        g->matrix[j - 2][i] == PLAYER_O &&
                        g->matrix[j - 3][i] == PLAYER_O)
                        return PLAYER_O;
                }
                else if (g->matrix[j][i] == EMPTY)
                {
                    break;
                }
            }
        }
    }

    //4 in diagonale
    for (int j = 0; j < g->columns; ++j)
    {
        for (int i = 0; i <= g->rows - 4; ++i) //position 0 1 2 3 visited if 7 is numb of rows
        {
            if (j < 3 && g->columns - j >= 4) //parete sinistra
            {
                //controlla solo a destra
                if (g->matrix[j][i] == PLAYER_X)
                {
                    //controlla se le diagonali sono playerX
                    if (
                        g->matrix[j + 1][i + 1] == PLAYER_X &&
                        g->matrix[j + 2][i + 2] == PLAYER_X &&
                        g->matrix[j + 3][i + 3] == PLAYER_X)
                        return PLAYER_X;
                }
                else if (g->matrix[j][i] == PLAYER_O)
                {
                    //UGUALE A SOPRA CON PLAYER 0
                    if (
                        g->matrix[j + 1][i + 1] == PLAYER_O &&
                        g->matrix[j + 2][i + 2] == PLAYER_O &&
                        g->matrix[j + 3][i + 3] == PLAYER_O)
                        return PLAYER_O;
                }
                else if (g->matrix[j][i] == EMPTY)
                {
                    break;
                }
            }

            else if (j >= 3 && ((g->columns - 1) - j) >= 3) //posizioni centralli
            {
                //controlla sia a destra che a sinistra
                if (g->matrix[j][i] == PLAYER_X)
                {
                    //controlla se le diagonali sono playerX
                    if (
                        (
                            g->matrix[j + 1][i + 1] == PLAYER_X &&
                            g->matrix[j + 2][i + 2] == PLAYER_X &&
                            g->matrix[j + 3][i + 3] == PLAYER_X) ||
                        (g->matrix[j - 1][i - 1] == PLAYER_X &&
                         g->matrix[j - 2][i - 2] == PLAYER_X &&
                         g->matrix[j - 3][i - 3] == PLAYER_X))
                        return PLAYER_X;
                }
                else if (g->matrix[j][i] == PLAYER_O)
                {
                    //UGUALE A SOPRA CON PLAYER 0
                    if (
                        (
                            g->matrix[j + 1][i + 1] == PLAYER_O &&
                            g->matrix[j + 2][i + 2] == PLAYER_O &&
                            g->matrix[j + 3][i + 3] == PLAYER_O) ||
                        (g->matrix[j - 1][i - 1] == PLAYER_O &&
                         g->matrix[j - 2][i - 2] == PLAYER_O &&
                         g->matrix[j - 3][i - 3] == PLAYER_O))
                        return PLAYER_O;
                }
                else if (g->matrix[j][i] == EMPTY)
                {
                    break;
                }
            }
            else //if (j >= 3) //parete destra
            {
                //controlla solo a sinistra
                if (g->matrix[j][i] == PLAYER_X)
                {
                    //controlla se le diagonali sono playerX
                    if (
                        g->matrix[j - 1][i + 1] == PLAYER_X &&
                        g->matrix[j - 2][i + 2] == PLAYER_X &&
                        g->matrix[j - 3][i + 3] == PLAYER_X)
                        return PLAYER_X;
                }
                else if (g->matrix[j][i] == PLAYER_O)
                {
                    //UGUALE A SOPRA CON PLAYER 0
                    if (
                        g->matrix[j - 1][i + 1] == PLAYER_O &&
                        g->matrix[j - 2][i + 2] == PLAYER_O &&
                        g->matrix[j - 3][i + 3] == PLAYER_O)
                        return PLAYER_O;
                }
                else if (g->matrix[j][i] == EMPTY)
                {
                    break;
                }
            }
        }
    }
    return 0;
};
