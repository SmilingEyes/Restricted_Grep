#include <stdio.h>
#define MAXSIZE 4096

int matches_leading(char *line, char *pattern) {
	// this code checks only when the pattern and line sizes are the 1 and are the same. for example 
	// you the pattern can be 'a' and your input be 'a' and it will be match!
	// this is the easiest case you can test for. everything gets much harder from here
	if(line[0] == 0 && pattern[0] == 0){
		return 1; // passing true means there is a match
	}
	// by the properties of rgrep, the first characters of the string should not contain the + or ? cases
	// this function makes sure that these two cases do not occur
	if(line[0] == pattern[0] && pattern[1] != '+' && pattern[1] != '?'){
		if(line[1] != 0 && pattern[1] != 0)
		{
			int i=0;
			int j=0;
			char lineItem[MAXSIZE];
			char pat[MAXSIZE];

			for(int k = 0; k < MAXSIZE; k++){
				lineItem[k] = 0;
		}
			while(line[i+1] != 0){
				lineItem[i] = line[i+1];
				i++;
			}

			for(int k = 0; k < MAXSIZE; k++){
				pat[k] = 0;
			}

			while(pattern[j+1] != 0){
				pat[j] = pattern[j+1];
				j++;
			}

		int matches = -1;
		matches = matches_leading(lineItem, pat);

		if(matches == 0){
			return 0;
		}

		for(int k = 0; k < MAXSIZE; k++){
				lineItem[k] = 0;
				}

		}
		return 1;
	}


	if((line[0] == 0 && pattern[0] != 0) || (line[0] != 0 && pattern[0] == 0)){
		return 0;
	}

	if(line[0] != pattern[0] && pattern[0] != '.' && pattern[1] != '?' && pattern[0] != '\\'){
		return 0;
	}
	// this if statement checks for the case with + but not as a charater. 
	// examples of a + case 
	//	line: a+b
	//	printout: aaab, acdfsdab, ab
	if(pattern[1] == '+' && pattern[0] != '\\'){
		char pat[MAXSIZE];
		int i = 0;
		int matches = -1;

		while(matches != 1 && line[i] != 0){
			for(int k = 0; k < MAXSIZE; k++){
				pat[k] = 0;
			}

			int g = 0;
			int f = 0;

			for(g = 0; g < i; g++){
				pat[g] = pattern[0];
			}
			while(pattern[f] != 0){
				if(pattern[f] == '+'){
					f++;
					continue;
				}
				pat[g] = pattern[f];
				g++; f++;
			}
			matches = matches_leading(line, pat);
			i++;
		}
		if(matches == 1){
			return 1;
		}
		else 
			return 0;

	
}	// this is a check for if the case is '.' ! we make sure that no other cases in the same line
	// or pattern
	if(pattern[0] == '.' && pattern[1] != '+' && pattern[1] != '?' && pattern[0] != '\\'){
		char lineItem[MAXSIZE]; 
		char pat[MAXSIZE];
		int j = 0; 
		int matches = -1; 

		for(int k = 0; k < MAXSIZE; k++){
				lineItem[k] = 0;
		}
		while(line[j+1] != 0){
			lineItem[j] = line[j+1];
			j++;
		}
		for(int k = 0; k < MAXSIZE; k++){
			pat[k] = 0;
		}
		j = 0;
		while(pattern[j+1] != 0){
			pat[j] = pattern[j+1];
			j++;
		}
		matches = matches_leading(lineItem, pat);
		if(matches == 0){
			return 0;
		}
	}
	//this checks if the pattern is a question mark '?' and it checks against if the pattern does not contain any of the variables.
	if(pattern[1] == '?' && pattern[1] != '+' && pattern[1] != 0 && pattern[0] != '\\'){
		char pat1[MAXSIZE]; // we have to consider when the ? applies or doesn't apply
		char pat2[MAXSIZE]; // two arrays are used to accomodate both cases
		int j = 0; 
		int matches1 = -1; // match is -1 so that if it changes, we know that the patten changes
		int matches2 = -1; // if match is -1 , the if ststament will produce an error

		if(matches1 != 0){
			for(int k = 0; k < MAXSIZE; k++){
				pat1[k] = 0;
			}
			while(pattern[j+2] != 0){
				pat1[j] = pattern[j+2];
				j++;
			}
			matches1 = matches_leading(line, pat1);
		}
		if(matches2 != 0){
			for(int k = 0; k < MAXSIZE; k++){
				pat2[k] = 0;
			}
			pat2[0] = pattern[0]; j = 1;
			while(pattern[j+1] != 0){
				pat2[j] = pattern[j+1];
				j++;
			}
			matches2 = matches_leading(line, pat2);
		}
		if(matches1 == 0 && matches2 == 0){
			return 0;
		}
	}

	if(pattern[0] == '\\'){
		char lineItem[MAXSIZE]; char pat[MAXSIZE]; int j = 0; int matches = -1;
		if(line[0] == pattern[1]){
			while(pattern[j+2] != 0){
				pat[j] = pattern[j+2];
				j++;
			}
			j = 0;
			while(line[j] != 0){
				lineItem[j] = line[j+1];
				j++;
			}
			matches = matches_leading(lineItem, pat);
			if(matches == 0){
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	return 1;
}
/*
everytime rgrep_matches runs, I reset the variables that is used to traverse arrays
*/
int rgrep_matches(char *line, char *pattern) {
    int i = 0; 
    int j = 0; 
    int p = 0;
    int match;
    char lineItem[MAXSIZE];

	while(line[i+1] != 0){
		if(line[i] == pattern[j] || pattern[j] == '.'){
			int k = 0;
			while(line[i+1] != 0){
				lineItem[k] = line[i];
				if(line[i+1] == ' ' || line[i+1] == '\n') // this lince checks if the line has a null pointer 
					break;
				i++; k++;
			}
			lineItem[k+1] = 0;
			match = matches_leading(lineItem, pattern);
			for(p = 0; p < k+1; p++)
				lineItem[p] = 0;
			if(match == 1){
				return 1;
			}
			
		}
		i++;
	}
	
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }

    /* we're not going to worry about long lines */
    char buf[MAXSIZE];

    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }

    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }

    return 0;
}