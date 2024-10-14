#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "utilities.c"

// Structs
typedef struct
{
    float x;
    float y;
} Axis;

// Plot Types
void plot_table(double x[], double y[], int size_arr, int SCREEN_H, int SCREEN_W)
{
    printf("%d Plots Total\n", size_arr);
    for (int i = 0; i < size_arr; i++)
    {
        printf("Plot %d: x = %.2f, y = %.2f\n", i, x[i], y[i]);
    }
}

void plot_scatter(double x[], double y[], int size_arr, int SCREEN_H, int SCREEN_W)
{
    double x_sort[size_arr], y_sort[size_arr];
    copy_array(x, x_sort, size_arr);
    copy_array(y, y_sort, size_arr);

    // # Sort array

    // printf("\nSorting ...\n");

    // printf("x sorted :\n");
    // print_double_array(x_sort, size_arr);
    bubble_sort(x_sort, size_arr);

    // int x_size_arr = removeDuplicates(x_sort, size_arr);
    // print_double_array(x_sort, x_size_arr);

    // printf("y sorted :\n");
    // print_double_array(y_sort, size_arr);
    bubble_sort(y_sort, size_arr);

    // int y_size_arr = removeDuplicates(y_sort, size_arr);
    // print_double_array(y_sort, y_size_arr);

    printf("\nInitialize Scatter Plot\n");

    Axis max;
    max.x = x_sort[size_arr - 1];
    max.y = y_sort[size_arr - 1];

    Axis graph_size;
    graph_size.x = 10;
    graph_size.y = 10;

    printf("%d Plots Total\n", size_arr);

    double graph_size_H = SCREEN_H - SCREEN_H % (int)graph_size.y;
    double graph_size_W = SCREEN_W - SCREEN_W % (int)graph_size.x;
    printf("Size :%lf %lf\n\n", graph_size_H, graph_size_W);

    double _y_sort[size_arr];
    copy_array(y_sort, _y_sort, size_arr);
    double _x_sort[size_arr];
    copy_array(x_sort, _x_sort, size_arr);
    int size__y = removeDuplicates(_y_sort, size_arr);
    int size__x = removeDuplicates(_x_sort, size_arr);

    printf("%d, %d", size__x, size__y);

    // Normalize plotting value
    double x_normalize[size_arr];
    double y_normalize[size_arr];
    double _y_normalize[size__y];
    double _x_normalize[size__x];

    for (int i = 0; i < size_arr; i++)
    {
        x_normalize[i] = normalize(graph_size_W, x[i], x_sort[0], x_sort[size_arr - 1]);
    }

    for (int i = 0; i < size_arr; i++)
    {
        y_normalize[i] = normalize(graph_size_H, y[i], y_sort[0], y_sort[size_arr - 1]); // From back to front
    }

    for (int i = 0; i < size__x; i++)
    {
        _x_normalize[i] = normalize(graph_size_W, _x_sort[i], _x_sort[0], _x_sort[size__x - 1]);
    }

    for (int i = 0; i < size__y; i++)
    {
        _y_normalize[i] = normalize(graph_size_H, _y_sort[i], _y_sort[0], _y_sort[size__y - 1]); // From back to front
    }

    print_double_array(_x_sort, size__x);
    print_double_array(_y_sort, size__y);
    print_double_array(_x_normalize, size__x);
    print_double_array(_y_normalize, size__y);

    // Debug Normalized Value
    printf("Normalized Values:\n");
    int temp_indent = nDigits(find_max(x_normalize, size_arr));
    for (int i = 0; i < size_arr; i++)
    {
        printf("x: %.2lf ->%.2lf", x[i], x_normalize[i]);
        for (int idx = nDigits(x_normalize[i]); idx < temp_indent + 1; idx++)
        {
            printf(" ");
        }
        printf("| y: %.2lf ->%.2lf\n", y[size_arr - i - 1], y_normalize[size_arr - i - 1]);
    }
    char scatter_flag = 'X';
    // --------------------------------------------------------------------------------
    // Plot Graph size
    // --------------------------------------------------------------------------------
    // Draw Y Axis

    int indent_y = nDigits(y_sort[size_arr - 1]);
    int partition = 0;
    for (int i = 0; i < graph_size_H + 1; i++)
    {

        int curr_number = -1;
        double match_pair_x[10][4]; // x values with same y
        int match_idx = 0;
        // printf("%d %d",graph_size_H - i,  _y_normalize[partition]);

        if (partition < size__y && graph_size_H - i <= _y_normalize[size__y - partition - 1])
        {

            printf("%.2lf", _y_sort[size__y - partition - 1]);
            curr_number = (double)_y_sort[size__y - partition - 1];
            //  ---
            // Get all x values that is same y

            for (int match_n = 0; match_n < size_arr; match_n++)
            {
                
                if (y[size_arr - match_n - 1] == curr_number)
                {
                    // printf("y: %d curr_num: %d |", (int) y[size_arr - match_n - 1], curr_number);
                    // Get x value
                    match_pair_x[match_idx][0] = x[match_n];
                    // Get y value
                    match_pair_x[match_idx][1] = y[size_arr - match_n - 1];
                    // Get x distance
                    match_pair_x[match_idx][2] = (double)round(x_normalize[match_n]);
                    match_pair_x[match_idx][3] = (double)round(y_normalize[size_arr - match_n - 1]);

                    // printf(" %d: [x: %d y: %d xn: %d yn: %d]", match_idx, match_pair_x[match_idx][0], match_pair_x[match_idx][1], match_pair_x[match_idx][2], match_pair_x[match_idx][3]);

                    match_idx += 1;
                    // printf(" %d", match_idx);
                }
            }
            // ---

            // size_x = (int) round(x_normalize[partition]);
            partition++;
        }

        // Make an indent from most digit number
        if (curr_number != -1)
        {
            for (int i = nDigits(curr_number); i < indent_y; i++)
            {
                // printf(" %d %d %d", indent_y, nDigits(curr_number), curr_number);
                printf(" ");
            }
        }
        else
        {
            // .2lf = 3 space ( . + decimal)
            printf("   ");
            for (int i = 0; i < indent_y; i++)
            {
                printf(" ");
            }
        }

        printf("|");

        int show_point_axis = 1;
        // Plot scatter point
        if (match_idx > 0)
        {
            // Sort Array by X Value
            for (int k = 0; k < match_idx - 1; k++)
            {
                for (int l = 0; l < match_idx - k - 1; l++)
                {
                    if (match_pair_x[l][0] > match_pair_x[l + 1][0])
                    {
                        for (int m = 0; m < 4; m++)
                        {
                            int temp = match_pair_x[l][m];
                            match_pair_x[l][m] = match_pair_x[l + 1][m];
                            match_pair_x[l + 1][m] = temp;
                        }
                    }
                }
            }

            // int _match_idx;
            // for(int _i = 0; _i < 3; _i++){
            //     _match_idx = removeDuplicates(match_pair_x[i], match_idx);
            // }
            // match_idx = _match_idx;
            
            // printf("match size : %d", match_idx);
            int last_pos = 0;
            int extra_length = 0;
            for (int num_pair = 0; num_pair < match_idx; num_pair++)
            {
                // printf("%d,%d", num_pair, match_idx);
                int pos = match_pair_x[num_pair][2] * 3;
                // printf("x: %d y: %d",match_pair_x[num_pair][2], match_pair_x[num_pair][3]);
                for (int j = last_pos; j < pos - extra_length; j++)
                {
                    printf(" ");
                }
                if (show_point_axis)
                {
                    // Plot scatter with color
                    printf("\033[1;31m");
                    printf("%c", scatter_flag);
                    printf("\033[1;32m");
                    printf(" (%.0lf, %.0lf)", match_pair_x[num_pair][0], match_pair_x[num_pair][1]);
                    printf("\033[0m");

                    extra_length += snprintf(NULL, 0, " (%.0lf, %.0lf)", match_pair_x[num_pair][0], match_pair_x[num_pair][1]);
                }

                last_pos = pos + 1;
            }
        }
        printf("\n");
    }

    // --------------------------------------------------------------------------------
    // Draw X Axis
    // indent space for x
    indent_y += 3;
    for (int i = 0; i < indent_y; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < graph_size_W + 1; i++)
    {
        printf("---");
    }
    printf("\n");

    // indent to match with ---
    int indent_x = 3;
    // . + 2 decimal
    int x_decimal = 3;

    // starter indent space for x
    for (int i = 0; i < indent_y - x_decimal; i++)
    {
        printf(" ");
    }

    partition = 0;
    for (int i = 0; i <= graph_size_W + 1; i++)
    {
        int curr_number = -1;

        if (partition < size__x && i >= _x_normalize[partition])
        {
            // printf("%d ", i);
            printf("%.2lf", _x_sort[partition]);
            curr_number = (int)_x_sort[partition];
            partition++;
        }

        int remove_indent = 0;
        if (curr_number != -1)
        {
            remove_indent = nDigits(curr_number);
            remove_indent += x_decimal;
        }
        for (int i = 0; i < indent_x - remove_indent; i++)
        {
            printf(" ");
        }
    }
}