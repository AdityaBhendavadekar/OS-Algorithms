#include<stdio.h>

int findNotRecent(int pageFrame[], int pages[], int index, int totalPages, int total_frames){
  int tempFrame[total_frames];
  int optind = 0;
  int count = total_frames;
  
  for(int i = 0; i < total_frames; i++){
    tempFrame[i] = pageFrame[i];
  }
  
  // checking which page is being not used in near future.
  for(int i = index; i < totalPages; i++){
    for(int k = 0; k < total_frames; k++){
      if(tempFrame[k] == pages[i] && count > 1){
        tempFrame[k] = -1;
        count--;
        break;
      }
    }
  }
  
  // checking index of which 1 page is remaining in page frame
  for(int i = 0; i < total_frames; i++){
    if(tempFrame[i] >= 0){
      optind = i;
      break;
    }
  }
  
  return optind;
}

void optimal(int total_pages, int pages[], int total_frames){
    int pagemiss = 0, pagehit = 0;
    int pageFrame[total_frames];
    int flag;
    
    for (int i = 0; i < total_frames; i++){    
        pageFrame[i] = 999;
    }

    for (int i = 0; i < total_pages; i++){
        flag = 0;

        // page hit if page is already in pageframe
        for (int j = 0; j < total_frames; j++){
            if(pageFrame[j] == pages[i]){
                pagehit++;
                flag = 1;
                break;
            }
        }
        
        // check if page frame is not filled
        if(flag == 0){
            for(int k = 0; k < total_frames; k++){
                if(pageFrame[k] == 999){
                    pageFrame[k] = pages[i];
                    pagemiss++;
                    flag = 1;
                    break;
                }
            }
        }
        
        // find index of not least recently used page and replace it.
        if(flag == 0){
            int pageIndex = findNotRecent(pageFrame, pages, i - 1, total_pages, total_frames);
            pageFrame[pageIndex] = pages[i];
            pagemiss++;
        }
    }
    
    printf("Page Miss: %d\n", pagemiss);
    printf("Page Hits: %d\n", pagehit);
}

int main(){
    int total_pages;
    int pages[20];
    int pageFrameSize;
    
    printf("Enter total no. of pages: ");
    scanf("%d", &total_pages);

    printf("Enter %d pages: \n", total_pages);
    for (int i = 0; i < total_pages; i++){
        scanf("%d", &pages[i]);
    }    

    printf("Enter size of page frame: ");
    scanf("%d", &pageFrameSize);

    optimal(total_pages, pages, pageFrameSize);

    return 0;
}
