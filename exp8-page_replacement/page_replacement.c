#include <stdio.h>
#include <stdlib.h>

void fifo(int pages[], int n, int frame_size)
{
    int frames[frame_size];
    int frame_index = 0;
    int page_faults = 0;
    int hits = 0;

    for (int i = 0; i < frame_size; i++)
    {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int page_found = 0;

        for (int j = 0; j < frame_size; j++)
        {
            if (frames[j] == page)
            {
                page_found = 1;
                hits++;
                printf("Page %d found in frame %d (FIFO)\n", page, j);
                break;
            }
        }

        if (!page_found)
        {
            printf("Page %d caused a page fault (FIFO)\n", page);
            int replaced_page = frames[frame_index];
            frames[frame_index] = page;
            frame_index = (frame_index + 1) % frame_size;
            page_faults++;

            printf("Current frames (FIFO): ");
            for (int j = 0; j < frame_size; j++)
            {
                printf("%d ", frames[j]);
            }
            printf(" Replaced page: %d\n", replaced_page);
        }
    }

    printf("Total page faults (FIFO): %d\n", page_faults);
    printf("Total hits (FIFO): %d\n", hits);
}

void lru(int pages[], int n, int frame_size)
{
    int frames[frame_size];
    int frame_index = 0;
    int page_faults = 0;
    int hits = 0;
    int last_used[frame_size];

    for (int i = 0; i < frame_size; i++)
    {
        frames[i] = -1;
        last_used[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int page_found = 0;

        for (int j = 0; j < frame_size; j++)
        {
            if (frames[j] == page)
            {
                page_found = 1;
                hits++;
                printf("Page %d found in frame %d (LRU)\n", page, j);
                last_used[j] = i;
                break;
            }
        }

        if (!page_found)
        {
            printf("Page %d caused a page fault (LRU)\n", page);
            int lru_frame = 0;
            int min_last_used = last_used[0];
            for (int j = 1; j < frame_size; j++)
            {
                if (frames[j] == -1)
                {
                    lru_frame = j;
                    break;
                }
                if (last_used[j] < min_last_used)
                {
                    min_last_used = last_used[j];
                    lru_frame = j;
                }
            }

            int replaced_page = frames[lru_frame];
            frames[lru_frame] = page;
            last_used[lru_frame] = i;
            page_faults++;

            printf("Current frames (LRU): ");
            for (int j = 0; j < frame_size; j++)
            {
                printf("%d ", frames[j]);
            }
            printf(" Replaced page: %d\n", replaced_page);
        }
    }

    printf("Total page faults (LRU): %d\n", page_faults);
    printf("Total hits (LRU): %d\n", hits);
}

int main()
{
    int n, frame_size;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];

    printf("Enter the pages: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter frame size: ");
    scanf("%d", &frame_size);

    fifo(pages, n, frame_size);
    printf("\n");
    lru(pages, n, frame_size);

    return 0;
}