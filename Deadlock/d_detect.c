#include <stdio.h>
int main()
{
	int n, m, i, j, k;
	n = 5; 
	m = 3; 
	int alloc[5][3] = { { 0, 0, 1 }, 
						{ 1, 3, 6 }, 
						{ 9, 5, 1 }, 
						{ 2, 1, 1 }, 
						{ 0, 0, 2 } }; 

	int request[5][3] = { { 0, 0, 0 }, 
					 	  { 0, 0, 0 }, 
						  { 9, 5, 1 }, 
						  { 1, 0, 0 }, 
						  { 0, 0, 2 } }; 
	int avail[3] = { 0, 0, 0 }; 

	int finish[n], ans[n], ind = 0;
	for (k = 0; k < n; k++) {
		if(request[k][0] == 0 && request[k][1] == 0 && request[k][2] == 0){
			finish[k] = 1;
			for(j = 0; j<m; j++)
				avail[j] += alloc[k][j];
		}
		else{
			finish[k] = 0;
		}
	}

	int y = 0;
	for (k = 0; k < 5; k++) {
        int flagie = 1;
		for (i = 0; i < n; i++) {

			 if(finish[i]==0){
                if(request[i][0] <= avail[0] && request[i][1] <= avail[1] && request[i][2] <= avail[2]){
                    finish[i] = 1;
					for(int k=0;k<n;k++){
                        avail[k] =avail[k]+alloc[i][k];
                    }
				}
			 }
		}
        if(flagie == 1)
            break;
	}

	int flag = 1;
	for(int i=0;i<n;i++){
        if(finish[i]==0){
            flag=0;
            printf("The following system causes deadlock\n");           
            break;
        }
	}
    
	if(flag==1){
        printf("System is deadlock free.");
	}

    printf("Processes which causing deadlock are: ");
    for (int i = 0; i < n; i++){
        if(finish[i]==0)
           printf("P%d  ", i);
    }

	return (0);
}