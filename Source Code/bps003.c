// BPS003: Generate Report
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <time.h>

#define MAX_LINE_LENGTH 500
#define MAX_PATH_LENGTH 100

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("[***WARN***]Please check the data file of Branch: %s.\n",argv[1]);
        return 1;
    }

    printf("*===========================================================*\n");        
    printf("*=== Program Generate Report for Branch: [%s] Start     ===*\n",argv[1]);        
    printf("*===========================================================*\n");        


    char inpath[MAX_PATH_LENGTH] = "/home/parallels/Documents/project/bankdata/";
    strcat(inpath, argv[1]);
    strcat(inpath, "/transaction");

    FILE *infile = fopen(inpath, "r");
    if (infile == NULL) {
        printf("[***WARN***}Could not open data file of Branch %s.\n",argv[1]);
        printf("<Debug> the file path: %s\n",inpath);
        return 1;
    }

    srand(time(NULL));
    int randTime = 0;
    randTime = rand() % 5;
    sleep(randTime);
    printf("[%s Report-Step-1] Read Input Data Successfully!\n",argv[1]);        


    char outpath[MAX_PATH_LENGTH] = "/home/parallels/Documents/project/bankdata/";
    strcat(outpath, argv[1]);
    strcat(outpath, "/report");

    FILE *outfile = fopen(outpath, "w");
    if (outfile == NULL) {
        printf("[***WARN***}Error opening Report file of Branch %s.\n",argv[1]);
        printf("<Debug> the file path: %s\n",outpath);
        return 1;
    }

    randTime = rand() % 5;
    sleep(randTime);
    printf("[%s Report-Step-2] Set Output File Ready!\n",argv[1]);        

    time_t nowtime = time(NULL);
    struct tm *local = localtime(&nowtime);
    char timestamp[22];

    strftime(timestamp, sizeof(timestamp), "%Y/%m/%d", local);    

    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    int firstLine = 1;
    
    while(fgets(line, sizeof(line), infile)!=NULL){
        if (firstLine) {
            firstLine = 0;
            continue;
        }
	line_count++;
    }

    randTime = rand() % 5;
    sleep(randTime);

    fprintf(outfile, "=============================================================\n");
    fprintf(outfile, "    S BANK Transaction Report of branch [%s]    \n",argv[1]);
    fprintf(outfile, "=============================================================\n");
    fprintf(outfile, "Report Date: %s      Print Location: address of [%s]",timestamp,argv[1]);
    fprintf(outfile, "\n");
    fprintf(outfile, "\n");
    fprintf(outfile, "ITEM      CLASS     TYPE   AMOUNT    BALANCE        REMARK   \n");
    fprintf(outfile, "--------  --------  -----  --------  -------------  ---------\n");
    fprintf(outfile, "XXXXXXXX  XXXXXXXX  XXXXX  99999.99  9999999999.99  XXXXXXXXX\n");
    fprintf(outfile, "XXXXXXXX  XXXXXXXX  XXXXX  99999.99  9999999999.99  XXXXXXXXX\n");
    fprintf(outfile, "XXXXXXXX  XXXXXXXX  XXXXX  99999.99  9999999999.99  XXXXXXXXX\n");
    fprintf(outfile, "XXXXXXXX  XXXXXXXX  XXXXX  99999.99  9999999999.99  XXXXXXXXX\n");
    fprintf(outfile, "XXXXXXXX  XXXXXXXX  XXXXX  99999.99  9999999999.99  XXXXXXXXX\n");
    fprintf(outfile, "XXXXXXXX  XXXXXXXX  XXXXX  99999.99  9999999999.99  XXXXXXXXX\n");
    fprintf(outfile, "\n");
    fprintf(outfile, "\n");
    fprintf(outfile, "----------------------  End of List    ----------------------\n");
    fprintf(outfile, "                                       Totol Records: %d\n", line_count);
    fprintf(outfile, "\n");
    fprintf(outfile, "\n");
    fprintf(outfile, "======================  End of Report  ======================\n");

    randTime = rand() % 5;
    sleep(randTime);
    printf("[%s Report-Step-3] Generating Report Completed!\n",argv[1]);        
    printf("[%s's Report Path] %s\n",argv[1],outpath);        

    fclose(infile);
    fclose(outfile);
 
    randTime = rand() % 2;
    sleep(randTime);

    printf("*-----------------------------------------------------------*\n");        
    printf("*--- Program Generate Report for Branch: [%s] End       ---*\n",argv[1]);        
    printf("*----------------------------------------------------------*\n");        

    return 0;
}
