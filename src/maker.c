#include "include/types.h"
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

void usage(){
	printf("Usage: ./a.out [title] [target_path] [Your github address for README]\n");
}

int problem_or_not(char* file_name){
	printf("Problem or not %s\n", file_name);
	char* delim = "_. ";
	
	char* ptr = strtok(file_name, delim);
	
	while(ptr != NULL){
		printf("problem tok test %s\n", ptr);
		ptr = strtok(NULL, delim);
	}

	return 0;
}

int add_list(char* file_name, readme_t* list, int index){
	strcpy(list[index].p_source, file_name);

	char* delim = "_. ";
	char* ptr = strtok(file_name, delim);
	int flag = 0;
	while(ptr != NULL){
		for(int i=0; i<strlen(ptr); i++){
			if(flag == 0 && isdigit(ptr[i]) == 0){
				return -1;
			}
		}
		if(flag == 0){
			list[index].pnum = atoi(ptr); 
		}
		else if(flag == 1){
			strcpy(list[index].p_title, ptr);
		}
		else{
			strcpy(list[index].elses, ptr);
		}
		
		ptr = strtok(NULL, delim);
		flag++;
	}
	return 1;
}

int make_readme(char* title, readme_t* content, char* address, int count){
	FILE* readme;
	// TODO target path

	readme = fopen("README.md", "w+");
	if(readme == NULL){
		perror("make_readme: File open error");
		exit(1);
	}

	fprintf(readme, "# %s\n\n", title);
	fprintf(readme, "## list\n");
	fprintf(readme, "| Number | Title | Answer |\n");
	fprintf(readme, "| :--: | :--: | :--: |\n");

	for(int i=0; i<count; i++){
		fprintf(readme, "| %d | [%s](https://www.acmicpc.net/problem/%d) | [Answer](%s/%s) |\n", content[i].pnum, content[i].p_title, content[i].pnum, address, content[i].p_source);
	}

	fclose(readme);
	return 0;
}

int main(int argc, char* argv[]){	
	if(argc < 4){
		usage();
		exit(1);
	}
	
	char* title = argv[1];
	char* target_path = argv[2];
	char* github_address = argv[3];

	DIR * target_dir; 
	struct dirent* dp;

	if((target_dir = opendir(target_path)) == NULL){
		perror("DIR path error");
		exit(1);
	}
	
	int num_of_files = CAPACIRY;  // TODO get_num(target_dir);
	readme_t* readme_list = (readme_t*)malloc(sizeof(readme_t) * num_of_files);
	
	int index = 0;				
	int added = 0;
	while((dp = readdir(target_dir)) != NULL){
		if(dp->d_type == 8){
			printf("[FILE] %s\n", dp->d_name);
			added = add_list(dp->d_name, readme_list, index);
			if(added == 1) index++;
			if(index > num_of_files){
				// TODO realloc
			}
		}
	}
	closedir(target_dir);
	
	make_readme(title, readme_list, github_address, index);

	free(readme_list);
	return 0;
}

