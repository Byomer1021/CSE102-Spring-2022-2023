#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_WORD_SIZE 13
#define MAX_WORD_COUNT 1500
#define MAX_NUM_WORDS 100

// int read_dict();
int read_dict(const char *file_name, char dict[][MAX_WORD_SIZE]);
int read_text(const char *text_file, const char *ignore_file, char words[][MAX_WORD_SIZE]);
int find_occurences(char *word, char words[][MAX_WORD_SIZE]);

double dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], float threshold);

int histogram(const char words[][MAX_WORD_SIZE + 15], int occurrences[], char hist[][MAX_WORD_SIZE + 5 + 20], int num_words);

// int histogram(const char words[][MAX_WORD_SIZE], const int occurrences[], const char hist[][MAX_WORD_SIZE + 5 + 20]);

int mystrlen(const char *str)
{
	int i = -1;
	while (str[++i] != 0)
		;
	return i;
}
float values[MAX_WORD_COUNT][400] = {};
int dictxt_word_count = 0;
int num_words, vector_size;
int inputxt_word_count = 0;
int main()
{

	int threshold = 1.7;
	char text_file[] = "input.txt";
	char ignore_file[] = "ignore.txt";

	char(*words)[MAX_WORD_SIZE] = (char(*)[MAX_WORD_SIZE])calloc(300000, sizeof(char[MAX_WORD_SIZE]));

	inputxt_word_count = read_text(text_file, ignore_file, words);

	char dict_file[] = "dictionary.txt";
	char dict[MAX_WORD_COUNT][MAX_WORD_SIZE];

	char user_words[MAX_NUM_WORDS][MAX_WORD_SIZE + 15];
	int num_words = 0;
	dictxt_word_count = read_dict(dict_file, dict);
	// while(getchar() !='\n');

	printf("Enter word(s):");
	char temp;
	for (int i = 0; (temp = getchar()) != '\n'; i++)
	{
		if (temp == ' ')
		{

			user_words[num_words][i] = '\0';
			i = -1;
			num_words++;
		}
		else
		{

			user_words[num_words][i] = temp;
		}
	}

	num_words++;

	// printf("You entered %d words:\n", num_words);
	//  for (int i = 0; i < num_words; i++)
	//  {
	//  	printf("%s\n", user_words[i]);
	//  }

	int occarr[num_words];
	char histog[num_words][MAX_WORD_SIZE + 5 + 20];

	for (int i = 0; i < num_words; i++)
	{
		char temp[] = "";
		int how_much = 0;

		for (int j = 0; j < inputxt_word_count; j++)
		{

			if (strcmp(words[j], user_words[i]) == 0)
			{
				how_much++;
				// printf("22222222222222\n");
			}
		}

		if (num_words == 1)
		{
			if (how_much != 0)
				printf(" "
					   "%s"
					   " appears in "
					   "input.txt"
					   " %d times ",
					   user_words[i], how_much);
			else
			{
				double closeness = 9999.0;
				char closest[MAX_WORD_SIZE];
				double temp;
				// printf("%d", dictxt_word_count);
				for (int a = 0; a < dictxt_word_count; a++)
				{
					temp = dissimilarity(user_words[i], dict[a], dict, threshold);
					if (temp < closeness && temp <= threshold)
					{
						closeness = temp;
						strcpy(closest, dict[a]);
					}

					// printf("asdasd  %s adasdsad\n",dict[a]);
					// printf("%.2f  ---- %s\n", closeness, closest);
				}
				int occ = find_occurences(closest, words);
				if (occ == 0)
					printf("\"%s\" doesn't appear in \"%s\" ", user_words[i], text_file);
				else
					printf("\"%s\" doesn't appear in \"%s\" but \"%s\" appears %d times.", user_words[i], text_file, closest, occ);
			}
		}

		else
		{

			if (how_much != 0)
				occarr[i] = find_occurences(user_words[i], words);
			else
			{

				double closeness = 9999.0;
				char closest[MAX_WORD_SIZE];
				double temp;
				int occ, inDict = 0;
				// printf("%d", dictxt_word_count);
				for (int a = 0; a < dictxt_word_count; a++)
				{
					//printf("%s------%s\n", user_words[i], dict[a]);
					if (strcmp(user_words[i], dict[a]) == 0)
					{
						inDict = 1;
						//printf("---%s----", user_words[i]);
					}
				}
				for (int a = 0; a < dictxt_word_count; a++)
				{

					temp = dissimilarity(user_words[i], dict[a], dict, 1.7);
					if (temp < closeness && inDict == 1)
					{
						closeness = temp;
						strcpy(closest, dict[a]);
					}

					// printf("asdasd  %s adasdsad\n",dict[a]);
					// printf("%.2f  ---- %s\n", closeness, closest);
				}

				char strr[] = "+";
				if (inDict == 0)
					strcat(user_words[i], strr);
				else
				{
					char str[] = "->";
					strcat(user_words[i], str);
					strcat(user_words[i], closest);
				}

				occ = find_occurences(closest, words);
				occarr[i] = occ;
			}
		}
	}

	if (num_words > 1)
	{
		int scale = histogram(user_words, occarr, histog, num_words);

		printf("scale %d\n", scale);

		for (int i = 0; i < num_words; i++)
		{
			printf("---%s   ---  %d\n", histog[i], occarr[i]);
		}
	}

	printf("\n");

	free(words);

	return 0;
}

int read_dict(const char *file_name, char dict[MAX_WORD_COUNT][MAX_WORD_SIZE])
{

	// char banned_words[50][12];
	//  char dict[MAX_WORD_COUNT][MAX_WORD_SIZE];

	FILE *dictionary;

	dictionary = fopen(file_name, "r");

	if (dictionary == NULL)
	{
		printf("ERROR\n");
		return 1;
	}

	char first_line[50];

	fgets(first_line, 100, dictionary);

	char *r;
	r = strchr(first_line, '=');
	num_words = atoi(r + 1);
	vector_size = atoi(strchr(r + 1, '=') + 1);

	// printf("num words: %d, vector size: %d\n", num_words, vector_size);

	for (int i = 0; i < num_words; i++)
	{
		char temp[100];
		fscanf(dictionary, "%s", dict[i]);
		// printf("___%s____", dict[i]);
		for (int j = 0; j < vector_size; j++)
		{
			fscanf(dictionary, "%s", temp);
			values[i][j] = atof(temp);
		}
		char dump;
		do
		{
			dump = getc(dictionary);
		} while (dump != '\n');
	}

	// printf("%s", first_line);

	fclose(dictionary);

	return num_words;
}

int read_text(const char *text_file, const char *ignore_file, char words[][MAX_WORD_SIZE])
{

	char ignored_words[9375][MAX_WORD_SIZE];
	int word_count = 0, index = 0, flag = 0;

	FILE *input, *ignore;

	input = fopen(text_file, "r");
	ignore = fopen(ignore_file, "r");

	for (int i = 0; !feof(ignore); i++)
	{
		fgets(ignored_words[i], MAX_WORD_SIZE, ignore);
	}

	while (!feof(input))
	{

		// printf("aaaa");
		char ch;
		// printf("     bbbbb    ");

		ch = getc(input);

		if (!(ch <= 90 && ch >= 65) && !(ch <= 122 && ch >= 97))
		{

			if (flag == 0)
			{

				words[word_count][index] = '\0';

				word_count++;
			}

			flag = 1;
			index = 0;
		}
		else
		{
			words[word_count][index++] = ch;
			flag = 0;
		}
	}

	// for (int i = 0; i < word_count; i++)
	// {
	// 	printf("%s %d\n", words[i], strlen(words[i]));
	// }

	fclose(input);
	fclose(ignore);

	return word_count;
}

double dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], float threshold)
{

	double sum = 0.0;
	int w1_i = 0, w2_i = 0;

	// printf("%s----%s\n\n", w1, w2);

	for (int i = 0; i < dictxt_word_count; i++)
	{
		if (strcmp(w1, dict[i]) == 0)
		{
			w1_i = i;
		}
		else if (strcmp(w2, dict[i]) == 0)
		{
			w2_i = i;
		}
	}
	// printf("%d..... %d\n", w1_i, w2_i);

	for (int i = 0; i < vector_size; i++)
	{
		sum += pow((values[w1_i][i] - values[w2_i][i]), 2.0);

		// printf("%f\n",sum);
	}
	// printf("\n");

	return sum;
}

int find_occurences(char *word, char words[][MAX_WORD_SIZE])
{

	int counter = 0;

	for (int i = 0; i < inputxt_word_count; i++)
		if (strcmp(word, words[i]) == 0)
			counter++;

	return counter;
}

int histogram(const char words[][MAX_WORD_SIZE + 15], int occurrences[], char hist[][MAX_WORD_SIZE + 5 + 20], int num_words)
{
	int max = occurrences[0];
	int scale;

	for (int i = 1; i < num_words; i++)

		if (occurrences[i] > max)
			max = occurrences[i];

	if (max % 20 != 0)
		scale = (max / 20) + 1;
	else
		scale = max / 20;

	for (int i = 0; i < num_words; i++)
	{

		int plus = 0, match = 1;

		hist[i][0] = '"';
		for (int j = 1; j < MAX_WORD_SIZE + 15; j++)
		{
			hist[i][j] = ' ';
			if (j < mystrlen(words[i]) + 1)
				hist[i][j] = words[i][j - 1];
		}

		for (int h = 0; h < MAX_WORD_SIZE + 15; h++)
		{
			if (words[i][h] == '-')
				plus = 1;
			if (words[i][h] == '+')
				match = 0;
		}

		//printf("\n%d\n", match);

		char str_[] = "NO MATCHES";

		if (occurrences[i] <= 20)
		{

			for (int k = MAX_WORD_SIZE; k < MAX_WORD_SIZE + occurrences[i]; k++)
			{

				if (match == 0){
					hist[i][MAX_WORD_SIZE +0] = '"';
					hist[i][MAX_WORD_SIZE +1] = 'N';
					hist[i][MAX_WORD_SIZE +2] = 'O';
					hist[i][MAX_WORD_SIZE +3] = ' ';
					hist[i][MAX_WORD_SIZE +4] = 'M';
					hist[i][MAX_WORD_SIZE +5] = 'A';
					hist[i][MAX_WORD_SIZE +6] = 'T';
					hist[i][MAX_WORD_SIZE +7] = 'C';
					hist[i][MAX_WORD_SIZE +8] = 'H';
					hist[i][MAX_WORD_SIZE +9] = 'E';
					hist[i][MAX_WORD_SIZE +10] = 'S';
					hist[i][MAX_WORD_SIZE +11] = '"';
					hist[i][MAX_WORD_SIZE +12] = '\0';
					printf("--%s--", hist[i]);
				}
				else if (plus == 0)
					hist[i][k] = '*';
				else
					hist[i][k] = '+';
				if (k == MAX_WORD_SIZE + occurrences[i] - 1)
					hist[i][k + 1] = '\0';
			}
		}
		else
		{
			for (int k = MAX_WORD_SIZE; k < MAX_WORD_SIZE + occurrences[i] / scale + 1; k++)
			{

				if (match == 0){
					hist[i][MAX_WORD_SIZE +0] = '"';
					hist[i][MAX_WORD_SIZE +1] = 'N';
					hist[i][MAX_WORD_SIZE +2] = 'O';
					hist[i][MAX_WORD_SIZE +3] = ' ';
					hist[i][MAX_WORD_SIZE +4] = 'M';
					hist[i][MAX_WORD_SIZE +5] = 'A';
					hist[i][MAX_WORD_SIZE +6] = 'T';
					hist[i][MAX_WORD_SIZE +7] = 'C';
					hist[i][MAX_WORD_SIZE +8] = 'H';
					hist[i][MAX_WORD_SIZE +9] = 'E';
					hist[i][MAX_WORD_SIZE +10] = 'S';
					hist[i][MAX_WORD_SIZE +11] = '"';
					hist[i][MAX_WORD_SIZE +12] = '\0';
					printf("--%s--", hist[i]);
				}	
				else if (plus == 0) hist[i][k] = '*';
				else hist[i][k] = '+';
				if (k == MAX_WORD_SIZE + occurrences[i] / scale) hist[i][k + 1] = '\0';
			}
		}

		hist[i][mystrlen(words[i]) + 1] = '"';
	}

	return scale;
}
