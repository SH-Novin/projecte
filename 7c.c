#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct human
{
    int id, parent_id;
    double height;
    char name[500];
    char eye_color[500];

    int childrens_id[1000];
    int child_count;
} human;

typedef struct color_count
{
    char color[500];
    int frq;
} colors;

int Anncests(int index_A, int index_B, human *People, int first_id) // A jad B ast ya na
{
    int id_A = index_A + first_id;
    while (People[index_B].parent_id != -1)
    {
        if (People[index_B].parent_id == id_A)
        {
            return 1;
        }
        index_B = People[index_B].parent_id - first_id;
    }
    return 0;
}

void Sort_By_ID(int *nums, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; i < n; i++)
        {
            if (nums[j] < nums[i])
            {
                int temp = nums[j];
                nums[j] = nums[i];
                nums[i] = temp;
            }
        }
    }
    return;
}

void Print_Tree(human *People, int id, int first_id, int com)
{
    for (int i = 0; i < com; i++)
    {
        printf("\t");
    }
    human the_Guy = People[id - first_id];
    printf("%s\n", the_Guy.name);
    for (int i = 0; i < the_Guy.child_count; i++)
    {
        Print_Tree(People, the_Guy.childrens_id[i], first_id, com + 1);
    }
}

int distance(int id, int first_id, human *people)
{
    int distance = 0;

    int index = id - first_id;
    while (people[index].parent_id != -1)
    {
        distance++;

        index = people[index].parent_id - first_id;
    }
    return distance;
}

int main()
{
    human *People = malloc(1005 * sizeof(human));
    int people_count = 0;
    int first_id = -1;
    char cmd[1000];
    while (1)
    {
        scanf("%s", cmd);
        if (strcmp(cmd, "add") == 0)
        {
            int id, parrent_id;
            double height;
            char name[2000];
            char eye_color[2000];
            scanf("%d %s %d %lf %s", &id, name, &parrent_id, &height, eye_color);
            if (parrent_id != -1 && (parrent_id < first_id || id <= parrent_id))
            {
                printf("Parent doesn't exist!\n");
            }
            else
            {
                first_id = (first_id == -1) ? id : first_id;
                int index = id - first_id;
                human *the_Guy = &People[index];
                the_Guy->id = id;
                strcpy(the_Guy->name, name);
                strcpy(the_Guy->eye_color, eye_color);
                the_Guy->parent_id = parrent_id;
                the_Guy->height = height;
                the_Guy->child_count = 0;

                if (parrent_id != -1) // if has parrent
                {
                    human *father = &People[the_Guy->parent_id - first_id];
                    father->childrens_id[father->child_count++] = People[index].id;
                    Sort_By_ID(father->childrens_id, father->child_count);
                    // add him to list of his parrent childs
                }

                people_count++;
            }
        }

        else if (strcmp(cmd, "lca") == 0)
        {
#pragma region lca_ghadimi

// int id_A, id_B;

// scanf("%d %d", &id_A, &id_B);

// int index_A = id_A - first_id;
// int index_B = id_B - first_id;

// int Index_Ajdad_A[1000];
// int dA = 0;
// int Index_Ajdad_B[1000];
// int dB = 0;

// int B_Jad_A = 0, A_Jad_B = 0; // booleans
// while (People[index_A].parent_id != -1)
// {
//     Index_Ajdad_A[dA++] = People[index_A].parent_id - first_id;
//     if (People[index_A].parent_id == id_B)
//     {
//         B_Jad_A = 1;
//         break;
//     }

//     index_A = People[index_A].parent_id - first_id;
// }

// while (People[index_B].parent_id != -1)
// {
//     Index_Ajdad_B[dB++] = People[index_B].parent_id - first_id;

//     if (People[index_B].parent_id == id_A)
//     {
//         A_Jad_B = 1;
//         break;
//     }

//     index_B = People[index_B].parent_id - first_id;
// }

// if (B_Jad_A)
// {
//     index_B = id_B - first_id;
//     printf("ID: %d NAME: %s\n", id_B, People[index_B].name);
// }
// else if (A_Jad_B)
// {
//     index_A = id_A - first_id;
//     printf("ID: %d NAME: %s\n", id_A, People[index_A].name);
// }
// else if (People[index_A].id != People[index_B].id)
// {
//     printf("No common ancestor exists!\n");
// }
// else
// {
//     int found = 0;
//     for (int i = 1; i < dA && i < dB; i++)
//     {
//         if (Index_Ajdad_A[dA - i - 1] != Index_Ajdad_B[dB - i - 1])
//         {
//             printf("ID: %d NAME: %s\n", People[Index_Ajdad_A[dA - i]].id, People[Index_Ajdad_A[dA - i]].name);
//             found = 1;
//         }
//     }
//     if (!found) // jad gheir moshtarak nadran : sibilings
//     {
//         human *father = &People[People[id_A - first_id].parent_id - first_id];
//         printf("ID: %d NAME: %s\n", father->id, father->name);
//     }
// }
#pragma endregion

            int id_A, id_B;

            scanf("%d %d", &id_A, &id_B);

            int index_A = id_A - first_id;
            int index_B = id_B - first_id;

            int com_A = distance(id_A, first_id, People);
            int com_B = distance(id_B, first_id, People);

            //printf("com A:%d\n",com_A);
            //printf("com B:%d\n",com_B);

            if (com_B < com_A)
            {
                while (com_B < com_A)
                {
                    index_A = People[index_A].parent_id - first_id;
                    com_A--;
                    //printf("new com_A:%d id_A:%d\n",com_A,id_A);
                }
            }
            else if (com_A < com_B)
            {
                while (com_A < com_B)
                {
                    index_B = People[index_B].parent_id - first_id;
                    com_B--;
                    //printf("new com_B:%d id_B:%d\n",com_B,id_B);
                }
            }

            //printf("now com_A:%d ==com_B:%d ,id_A:%d id_B:%d ",com_A,com_B,id_A,id_B);
            
            // we are sure com_A now eqs to com_B
            while (1)
            {
                if ((com_A == 0 || People[index_A].parent_id == -1) && index_A != index_B)
                {
                    printf("No common ancestor exists!\n");//no lca
                    break;
                }
                else if (index_A == index_B)
                {
                    printf("ID: %d NAME: %s\n", People[index_A].id, People[index_B].name);
                    break;
                }

                index_A = People[index_A].parent_id-first_id;
                com_A--;
                index_B = People[index_B].parent_id-first_id;
                com_B--;
                //printf("now com_A:%d ==com_B:%d ,id_A:%d id_B:%d ",com_A,com_B,id_A,id_B);

            }
        }
        else if (strcmp(cmd, "switch") == 0)
        {
            int id_A, id_B;
            scanf("%d %d", &id_A, &id_B);

            int index_A = id_A - first_id;
            int index_B = id_B - first_id;

            if (People[index_A].parent_id == -1 && People[index_B].parent_id == -1)
            {
                printf("The given IDs are both roots!\n");
            }
            else if (Anncests(index_A, index_B, People, first_id) ||
                     Anncests(index_B, index_A, People, first_id))
            {
                printf("You can't switch with an ancestor!\n");
            }
            else if (People[index_A].parent_id == People[index_B].parent_id)
            {
                printf("The given IDs are already siblings!\n");
            }
            else
            {
                // we have id_A
                human *Father_A = &People[People[index_A].parent_id - first_id];
                human *Father_B = &People[People[index_B].parent_id - first_id];

                for (int i = 0; i < Father_A->child_count; i++)
                {
                    if (Father_A->childrens_id[i] == id_A)
                    {
                        Father_A->childrens_id[i] = id_B;
                    }
                }
                for (int i = 0; i < Father_B->child_count; i++)
                {
                    if (Father_B->childrens_id[i] == id_B)
                    {
                        Father_B->childrens_id[i] = id_A;
                    }
                }

                int temp = People[index_A].parent_id;
                People[index_A].parent_id = People[index_B].parent_id;
                People[index_B].parent_id = temp;

                // edit list of father children now a is son of b father
                //  swap father id's of a and b
            }
        }
        else if (strcmp(cmd, "print") == 0)
        {
            int id;
            scanf("%d", &id);
            Print_Tree(People, id, first_id, 0);
        }
        else if (strcmp(cmd, "predict") == 0)
        {
            int id;
            scanf("%d", &id);

            int com = distance(id, first_id, People) + 1;
            // DEBUG("com id:%d = %d\n", id, com);

            int sumWeigh = 0;
            double sum = 0;

            int buffer_size = 10;
            colors *cc = malloc(buffer_size * sizeof(colors));
            int c_counter = 0; // for rang

            for (int i = com; i > 0; i--)
            {
                sumWeigh += i;
                human the_Guy = People[id - first_id];

                // DEBUG("id:%d,name:%s sum += eye-color: %s * t:%d\n", the_Guy.id, the_Guy.name, the_Guy.eye_color, i);
                sum += the_Guy.height * i;
                id = the_Guy.parent_id;

                int found = 0;
                for (int j = 0; j < c_counter; j++)
                {
                    if (strcmp(cc[j].color, the_Guy.eye_color) == 0)
                    {
                        found = 1;
                        cc[j].frq += i;
                        break;
                    }
                }

                if (!found)
                {
                    if (c_counter + 1 >= buffer_size)
                    {
                        buffer_size *= 2;
                        cc = realloc(cc, buffer_size * sizeof(colors));
                    }

                    strcpy(cc[c_counter].color, the_Guy.eye_color);
                    cc[c_counter].frq = i;
                    c_counter++;
                }
            }


            int max_frq = 0;
            int max_frq_i;
            for (size_t i = 0; i < c_counter; i++)
            {
                // DEBUG("eye color[%d]:%s, frq: %d\n",i,cc[i].color,cc[i].frq);

                if (cc[i].frq > max_frq)
                {
                    max_frq = cc[i].frq;
                    max_frq_i = i;
                }
            }


            int predict_cm = (sum * 100) / sumWeigh;
            double predict_height_floor = (double)predict_cm / 100;

            int eye_probability = (max_frq * 100 * 100) / sumWeigh;
            double eye_probability_floor = (double)eye_probability / 100;


            //double predict_height = sum / sumWeigh;
            //double predict_height_floor = floor(predict_height*100) / 100;

            //double eye_probability = max_frq / sumWeigh;
            //double eye_probability_floor = floor(eye_probability*100*100) / 100;


            printf("eye color: %s %0.2lf%%\n", cc[max_frq_i].color, eye_probability_floor);
            printf("height: %0.2lf\n", predict_height_floor);
            free(cc);
        }

        else if (strcmp(cmd, "end") == 0)
        {
            break;
        }
        else if (strcmp(cmd, "pp") == 0)
        {
            printf("     List start:\n");
            for (int i = 0; i < people_count; i++)
            {
                printf("id:%d name:%s father id:%d  height: %0.2lf eye-color: %s\n", People[i].id, People[i].name, People[i].parent_id, People[i].height, People[i].eye_color);
            }
            printf("     List end:\n");
        }
        else if (strcmp(cmd, "print_children") == 0)
        {
            int id;
            scanf("%d", &id);
            human the_guy = People[id - first_id];
            for (int i = 0; i < the_guy.child_count; i++)
            {
                int child_id = the_guy.childrens_id[i];
                human the_child = People[child_id - first_id];
                printf("id:%d name:%s\n", the_child.id, the_child.name);
            }
        }
    }

    free(People);
}