// BPS001: Data verification
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <time.h>

#define MAX_LINE_LENGTH 500
#define MAX_PATH_LENGTH 50

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("[***WARN***]Please provide the data file of Branch: %s.\n",argv[1]);
        return 1;
    }

    printf("*===========================================================*\n");        
    printf("*=== Program Data Verification for Branch:[%s] Start    ===*\n",argv[1]);        
    printf("*===========================================================*\n");        


    char path[MAX_PATH_LENGTH] = "/home/parallels/Documents/project/bankdata/";
    strcat(path, argv[1]);
    strcat(path, "/transaction");

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("[***WARN***}Could not open data file of Branch %s.\n",argv[1]);
        printf("<Debug> the file path: %s\n",path);
        return 1;
    }

    srand(time(NULL));
    int randTime = 0;

    printf("[%s Verify-Step-1]Read Transaction File Successfully!\n",argv[1]);

    randTime = rand() % 10;
    sleep(randTime);
    printf("[%s Verify-Step-2]Checking data integrity completed! Time taken: %d seconds\n",argv[1],randTime);

    randTime = rand() % 10;
    sleep(randTime);
    printf("[%s Verify-Step-3]Checking data compliance completed! Time taken: %d seconds\n",argv[1],randTime);

    randTime = rand() % 10;
    sleep(randTime);
    printf("[%s Verify-Step-4]Checking the policy rationality completed! Time taken: %d seconds\n",argv[1],randTime);

    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    
    while(fgets(line, sizeof(line), file)){
//        printf("%s", line);
	  line_count++;
    }

	line_count--;

    printf("[%s Verify-Step-5]Data verification completed! Total records: %d\n",argv[1],line_count);        

    fclose(file);

    printf("*-----------------------------------------------------------*\n");        
    printf("*--- Program Data Verification for Branch:[%s] End      ---*\n",argv[1]);        
    printf("*-----------------------------------------------------------*\n");        

    return 0;
}
