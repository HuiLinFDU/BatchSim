// BPS002: Data Update
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <time.h>
#include <fcntl.h>
#include <sys/file.h>

#define MAX_LINE_LENGTH 500
#define MAX_PATH_LENGTH 100

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("[***WARN***]Please check the data file of Branch: %s.\n",argv[1]);
        return 1;
    }

    printf("*===========================================================*\n");        
    printf("*=== Program Data update and accounting for [%s] Start  ===*\n",argv[1]);        
    printf("*===========================================================*\n");        


    char inpath[MAX_PATH_LENGTH] = "/home/parallels/Documents/project/bankdata/";
    strcat(inpath, argv[1]);
    strcat(inpath, "/transaction");

    FILE *infile = fopen(inpath, "r");
    if (infile == NULL) {
        printf("[***WARN***]Could not open data file of Branch %s.\n",argv[1]);
        printf("<Debug> the file path: %s\n",inpath);
        return 1;
    }


    char outpath[MAX_PATH_LENGTH] = "/home/parallels/Documents/project/bankdata/transaction";

    FILE *outfile = fopen(outpath, "a");
    if (outfile == NULL) {
        printf("[***WARN***}Error opening output file.\n");
        printf("<Debug> the file path: %s\n",outpath);
        return 1;
    }

    printf("[%s Update-Step-1] Open file to be updated.\n",argv[1]);


// get file descriptor
    int fd = fileno(outfile);
    if (fd == -1) {
        printf("[***WARN***]Error getting file descriptor.\n");
//        perror("Error getting file descriptor");
        fclose(outfile);
        return 1;
    }

    printf("[%s Update-Step-2] Get file descriptor successfully.\n",argv[1]);

    if (flock(fd, LOCK_EX) == -1) {
        printf("[***WARN***]Error locking file.\n");
        fclose(outfile);
        return 1;
    }

    printf("[%s Update-Step-3] Get file lock successfully.\n",argv[1]);

    srand(time(NULL));
    int randTime = 0;
    time_t nowtime = time(NULL);
    struct tm *local = localtime(&nowtime);
    char timestamp[22];

    strftime(timestamp, sizeof(timestamp), "%Y/%m/%d - %H:%M:%S", local);    
    printf("[%s Update-Step-4] Update begin At timestamp:    %s\n",argv[1],timestamp);

    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    int firstLine = 1;
    
    while(fgets(line, sizeof(line), infile)!=NULL){
        if (firstLine) {
            firstLine = 0;
            continue;
        }
        fputs(line, outfile);
	line_count++;
    }

// release file lock
    if (flock(fd, LOCK_UN) == -1) {
        printf("[***WARN***]Error unlocking file.\n");
//        perror("Error unlocking file");
    }


    randTime = rand() % 10;
    randTime += 5;
    sleep(randTime);

    nowtime = time(NULL);
    local = localtime(&nowtime);
    strftime(timestamp, sizeof(timestamp), "%Y/%m/%d - %H:%M:%S", local);    
    printf("[%s Update-Step-5] Update finished At timestamp: %s\n",argv[1],timestamp);

    printf("[%s Update-Step-6] File lock released! Data updated Completed! Total records: %d\n",argv[1],line_count);        

    fclose(infile);
    fclose(outfile);

    printf("*-----------------------------------------------------------*\n");        
    printf("*--- Program Data update and accounting for [%s] End    ---*\n",argv[1]);        
    printf("*-----------------------------------------------------------*\n");        

    return 0;
}
