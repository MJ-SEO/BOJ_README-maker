#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <vector>
#include <iostream>
#include <algorithm>

int main(){	
	// TODO Read current REEAME.md file and save BOJ problem number
	
	FILE* README_f;
	
	fclose(README_f);

	// TODO Open Current DIR
	
	DIR * cur_dir; 
	struct dirent* dp;

	if((cur_dir = opendir("./")) == NULL){
		perror("DIR path error");
		exit(1);
	}

	
	// TODO If there isn't problem that are not added in READMEM, append data with format
	
	while((dp = readdir(cur_dir)) != NULL){
		if(dp->d_type == 8){
			printf("[FILE] %s\n", dp->d_name);
		}
	}
	
}
