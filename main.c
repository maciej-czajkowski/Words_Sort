#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char **split_words(const char *text);

int sort_words(char **words);

void destroy(char **words);

int main()
{
    char **texts;
    char *input;

    input = (char *) malloc(1000 * sizeof(char));
    if (input == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Enter text");
    scanf("%999[^\n]s", input);


    int i = 0;
    int letters = 0;
    while ( *(input+i) != '\0')
    {
        if ( isalpha(*(input + i) ) != 0)
        {
            letters++;
        }
        i++;
    }
    i = 0;
    if (letters == 0)
    {
        printf("Nothing to show");
    }
    else
    {
        texts = split_words(input);

        if (texts != NULL)
        {
            sort_words(texts);
            while (*(texts + i) != NULL)
            {
                printf("%s\n", *(texts + i));
                i++;
            }
            if (i == 0)
            {
                printf("Nothing to show");
            }
        } else
        {
            printf("Failed to allocate memory");
            free(input);
            return 8;
        }


        destroy(texts);

    }
    free(input);
    return 0;
}

char **split_words(const char *text)
{
    if (text == NULL)
    {
        return NULL;
    }


    // counting the number of words
    int spc_counter = 0;

    for (unsigned int i = 0; i < strlen(text); i++)
    {
        if (isalpha(*(text + i)) != 0)
        {
            spc_counter++;
            while (isalpha(*(text + i)) != 0 && i < strlen(text))
            {

                i++;
            }
        }
    }
    if (spc_counter == 0)
    {
        return NULL;
    }

//    printf("spc_counter %d\n", spc_counter);


////     allocating memory for array of words
    char **split;

    split = (char **) malloc((spc_counter + 1) * sizeof(char *)); // 19*4
    if (split == NULL)
    {
        return NULL;
    }

    int i = 0;

    // iterating through starting spaces
    while (*(text + i) == ' ')
    {
        i++;
    }

    int i_arrays = 0;
    int k = 0;

    unsigned int len = 0;

    for (unsigned int j = (unsigned int) i; j < strlen(text) + 1; j++)
    {
        if (isalpha(*(text + j)) != 0)
        {
            len = j;
            while (isalpha(*(text + len)) != 0 && len < strlen(text) + 1)
            {
                len++;
            }
            *(split + i_arrays) = (char *) malloc((len - j + 1) * sizeof(char));  //
            if (*(split + i_arrays) == NULL)
            {
                destroy(split);
                return NULL;
            }
            while (isalpha(*(text + j)) != 0 && j < strlen(text) + 1)
            {
                *(*(split + i_arrays) + k) = *(text + j);
                k++;
                j++;
            }
            *(*(split + i_arrays) + k) = '\0';
            i_arrays++;
            k = 0;
        }
    }
    *(split + i_arrays) = NULL;


    return split;

}

int sort_words(char **words)
{
    if (words == NULL)
    {
        return 1;
    }

    int i = 0, j = 0;
    char *temp;
    char *min = *words;
    *min = **words;

    int Upper_Letters = 0;
    while (*(words + i) != NULL)
    {
        if (*(*(words + i)) < 'a') // duza litera
        {
            temp = *(words + i);
            *(words + i) = *(words + Upper_Letters);
            *(words + Upper_Letters) = temp;
            Upper_Letters++;
        }
        i++;
    }
    for (i = 0; i < Upper_Letters; i++)
    {
        for (j = 0; j < Upper_Letters - 1 ; j++)
        {
            if ((*(*(words + j)) >= *(*(words + j + 1))))
            {

                int len1 = strlen(*(words + j)), len2 = strlen(*(words + j + 1));
                int len3;
                if (len1 >= len2)
                {
                    len3 = len2;
                } else
                {
                    len3 = len1;
                }
                for (int m = 0; m < len3; m++)
                {
                    if (*(*(words + j) + m) > *(*(words + j + 1) + m) )
                    {
                        temp = *(words + j);
                        *(words + j) = *(words + j + 1);
                        *(words + j + 1) = temp;
                        break;
                    }
                    else if (*(*(words + j) + m) < *(*(words + j + 1) + m) )
                    {
                        break;
                    }
                    if (m == len3 - 1)
                    {
                        if (len3 == len2)
                        {
                            temp = *(words + j);
                            *(words + j) = *(words + j + 1);
                            *(words + j + 1) = temp;
                        }

                    }
                }
            }
        }
    }

    int end = Upper_Letters;
    while (*(words + end ) != NULL)
    {
        end++;
    }

    for (i = Upper_Letters; i < end +2 ; i++)
    {
        for (j = Upper_Letters; j < end-1; j++)
        {
            if ((*(*(words + j)) >= *(*(words + j + 1))))
            {

                int len1 = strlen(*(words + j)), len2 = strlen(*(words + j + 1));
                int len3;
                if (len1 >= len2)
                {
                    len3 = len2;
                } else
                {
                    len3 = len1;
                }
                for (int m = 0; m < len3; m++)
                {
                    if (*(*(words + j) + m) > *(*(words + j + 1) + m) )
                    {
                        temp = *(words + j);
                        *(words + j) = *(words + j + 1);
                        *(words + j + 1) = temp;
                        break;
                    }
                    else if (*(*(words + j) + m) < *(*(words + j + 1) + m) )
                    {
                        break;
                    }
                    if (m == len3 - 1)
                    {
                        if (len3 == len2)
                        {
                            temp = *(words + j);
                            *(words + j) = *(words + j + 1);
                            *(words + j + 1) = temp;
                        }

                    }
                }
            }
        }
    }



    return 0;
}

void destroy(char **words)
{
    if (words != NULL)
    {
        int i = 0;
        while (*(words + i) != NULL)
        {
            free(*(words + i));
            i++;
        }

        free(words);
    }
}

