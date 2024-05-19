#include<stdio.h>

void fifo(int totalPages, int pages[], int frameNo){
    int pointer=0;
    int pageMiss=0, pageHit=0;
    int pageFrame[frameNo];

        
    for (int i = 0; i < frameNo; i++)
    {    
        pageFrame[i] = 999;
    }

    for (int i = 0; i < totalPages; i++){
        int flag =0;

        //check if current item is already in pageframe or not.
        for (int j = 0; j < frameNo; j++){
            if (pageFrame[j]==pages[i]){
                pageHit++;
                flag=1;
                break;
            }
        }
        // if item is not in page frame then take to pageframe and increment page miss.
        if (flag==0)
        {
            pageFrame[pointer]=pages[i];
            pageMiss++;
            pointer= (pointer+1) % frameNo;
        }
    }

    printf("Pagemiss: %d\n", pageMiss);
    printf("PageHit: %d\n", pageHit);
    
}

int main(){
    int total_pages;
    int pages[20];
    int pageFrame;
    printf("Enter total no. of pages: ");
    scanf("%d", &total_pages);

    printf("Enter %d pages: \n",total_pages);
    for (int i = 0; i < total_pages; i++){
        scanf("%d", &pages[i]);
    }    

    printf("Enter size of page frame: ");
    scanf("%d", &pageFrame);

    fifo(total_pages, pages, pageFrame);

    return 0;
}