#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void FormulaVerify(char formula[], int *form_count, int *max_depth);
void LetterInit(char formula[], char letter_list[], int *letter_count, int *form_length, int *row_length);
void TruthAllocate(int **ref_list, char **truth_table, int letter_count, int form_count, int form_length, int row_length);
void TruthInit(char truth_table[], char letter_list[], int letter_count, int form_length, int row_length);
void FormulaWrite(int ref_list[], char truth_table[], char formula[], char letter_list[], int letter_count, int form_length, int row_length, int max_depth);
void TableSolver(int ref_list[], char truth_table[], int letter_count, int form_count, int form_length, int row_length);
void Logic(char dest[], char src1[], char src2[], int ops[], int truth_length);
int main(int argc, char *argv[]){
char *truth_table = NULL,  letter_list[26] = {0};
int *ref_list = NULL, letter_count, form_count, form_length, row_length, max_depth;
if(argc < 2) return 0;
FormulaVerify(argv[1], &form_count, &max_depth);
//LetterInit(argv[1], letter_list, &letter_count, &row_length, &form_length);
//TruthAllocate(&ref_list, &truth_table, letter_count, form_count, row_length);
//TruthInit(truth_table, letter_list, letter_count, form_length, row_length);
//FormulaWrite(ref_list, truth_table, argv[1], letter_count, row_length);
//TableSolver(ref_list, truth_table, letter_count, row_length);
printf("%s\nform_count: %d\nmax_depth:%d\n", argv[1], form_count, max_depth);//printf("%s", truth_table);
//free(truth_table);
//free(ref_list);
//truth_table = NULL;
//ref_list = NULL
return 0;}
void LetterInit(char formula[], char letter_list[], int *letter_count, int *form_length, int *row_length){
*letter_count = 0; *form_length = 0;
for(int letter_dex = 0; formula[*form_length] != 0; *form_length++){
letter_dex                     = (formula[*form_length] - 'A')*(formula[*form_length] >= 'A' && formula[*form_length] <= 'Z');
*letter_count                 += (formula[*form_length] >= 'A' && formula[*form_length] <= 'Z' && letter_list[letter_dex] == 0);
letter_list[letter_dex]       += formula[*form_length]*(formula[*form_length] >= 'A' && formula[*form_length] <= 'Z' && letter_list[letter_dex] == 0);
}
*row_length = (1 << *letter_count) + 2 + *form_length; //2 for letter and \n
return;}
void TruthInit(char truth_table[], char letter_list[], int letter_count, int form_length, int row_length){
int truth_half = 1 << letter_count; char truth = 1;
for(int letter_dex = -1, i = 0; i < letter_count; i++){
	truth_half /= 2;
	do letter_dex++; while(letter_list[letter_dex] == 0);
	truth_table[i*row_length] = letter_dex + 'A';
	letter_list[letter_dex] = (char)i;
	for(int j = 0, truth = 1; j < (1 << letter_count); j++){
		truth_table[i*row_length + form_length + j] = '0' + truth;
		truth = truth*(((j + 1) % truth_half) != 0) + (1 - truth)*(((j + 1) % truth_half) == 0);
	}
}
return;}
void FormulaWrite(int ref_list[], char truth_table[], char formula[], char letter_list[], int letter_count, int form_length, int row_length, int max_depth){
int index = letter_count*row_length, ref_point = index + form_length;
for(int line = 0; max_depth >= 0; max_depth--){
  for(int depth = -1, sym = 0, i = 0, j = 0; formula[i] != 0; i++){
    depth += (formula[i] == '(') - (formula[i] == ')');
    if(depth + (formula[i] == ')') >= max_depth)
    	{truth_table[index + j] = formula[i]; j++;}
    if(formula[i] == ')' && depth == max_depth - 1)
    	{index += row_length; line++; j = 0; sym = 0;}
    else if(formula[i] == '(' && depth == max_depth + 1)
    	{ref_list[5*line + 0 + sym] = ref_point; ref_point += row_length;}
    else if(formula[i] >= 'A' || formula[i] <= 'Z' && depth == max_depth)
    	{ref_list[5*line + 0 + sym] = form_length + row_length*(int)letter_list[formula[i] - 'A'];}
    else if(formula[i] == '!' && depth == max_depth)
    	{ref_list[5*line + 2 + sym] = 1;}
    else if(formula[i] != '!' && formula[i] != ' ' && formula[i] != '(' && formula[i] != ')' && (formula[i] < 'A' || formula[i] > 'Z'))
    	{ref_list[5*line + 4] = formula[i]; sym = 1;}
  }
}
memcpy(&truth_table[index], &truth_table[index - row_length], (size_t) row_length);
truth_table[index + row_length] = 0;
return;}
void TableSolver(int ref_list[], char truth_table[], int letter_count, int form_count, int form_length, int row_length){
for(int i = 0, j = letter_count*row_length + form_length; i < form_count; i++, j += row_length){
  Logic(&truth_table[j], &truth_table[ref_list[5*i + 0]], &truth_table[ref_list[5*i + 1]], &ref_list[5*i + 2], 1 << letter_count);
}
return;}
void Logic(char dest[], char src1[], char src2[], int ops[], int truth_length){
for(int i = 0; i < truth_length && ops[2] == '|'; i++){
dest[i] =
(src1[i]*(1 - ops[0]) + (~src1[i] & 1 | 48)*ops[0])
|
(src2[i]*(1 - ops[1]) + (~src2[i] & 1 | 48)*ops[1]);
}
for(int i = 0; i < truth_length && ops[2] == '&'; i++){
dest[i] =
(src1[i]*(1 - ops[0]) + (~src1[i] & 1 | 48)*ops[0])
&
(src2[i]*(1 - ops[1]) + (~src2[i] & 1 | 48)*ops[1]);
}
for(int i = 0; i < truth_length && ops[2] == '>'; i++){
dest[i] =
(src1[i]*ops[0] + (~src1[i] & 1 | 48)*(1 - ops[0])) //reverse negate status
|
(src2[i]*(1 - ops[1]) + (~src2[i] & 1 | 48)*ops[1]);
}
return;}
void FormulaVerify(char formula[], int *form_count, int *max_depth){
int part_depth[100] = {0}, error = 0, depth = 0, i; *form_count = 2; *max_depth = 0;
for(i = 1, depth = 0; formula[i] != 0 && error == 0; i++){
	formula[i] += ('A' - 'a')*(formula[i] >= 'a' && formula[i] <= 'z');
	error += 1*(formula[i] != ' ' && formula[i] != '!' && formula[i] != '>' && formula[i] != '&' && formula[i] != '|' && formula[i] != '(' && formula[i] != ')' && (formula[i] < 'A' || formula[i] > 'Z'));
	part_depth[(2*depth) + 0] += (formula[i] == '>' || formula[i] == '&' || formula[i] == '|');
	part_depth[(2*depth) + 1] += (formula[i] == '(' || (formula[i] >= 'A' && formula[i] <= 'Z'));
	error += 32*((formula[i] == '>' || formula[i] == '&' || formula[i] == '|') && part_depth[(2*depth) + 1] != 1);
	error += 64*(formula[i] == '!' && formula[i + 1] != '>' && formula[i + 1] != '&' && formula[i + 1] != '|' && formula[i - 1] != '>' && formula[i - 1] != '&' && formula[i - 1] != '|');
	if(formula[i] == ')'){
	error += 128 * (part_depth[(2*depth) + 0] != 1);  // connective count
	error += 256 * (part_depth[(2*depth) + 1] != 2);  //formula count, ( or A,B,C
	part_depth[(2*depth) + 0] = 0;
	part_depth[(2*depth) + 1] = 0;
	}
	*form_count += (formula[i] == '(');
	*max_depth  += (depth > *max_depth);
	depth       += (formula[i] == '(') - (formula[i] == ')');
	error       += 2*(depth == -1 && formula[i + 1] != 0);
}
error += 4*(formula[0] != '(') + 8*(formula[i] == 0 && formula[i - 1] != ')') + 16*(formula[i] == 0 && depth != -1);
if(error != 0){printf("error code is: %d\n", error); exit(0);}
return;}
void TruthAllocate(int **ref_list, char **truth_table, int letter_count, int form_count, int form_length, int row_length){
 *ref_list = malloc(5*form_count * sizeof(int));
 *truth_table = malloc(((form_count + letter_count)*row_length + 1)*sizeof(char));
 if(*truth_table == NULL || *ref_list == NULL){printf("allocation failed, exiting...\n"); exit(0);}
 for(int i = 0; i < (form_count + letter_count)*row_length + 1; i++)*(*truth_table + i) = ' ' + ('\n' - ' ')*((i + 1) % row_length == 0);
 for(int i = 0; i < 5*(form_count - 1); i++)                        *(*ref_list + i) = 0;
 *(*ref_list + 5*(form_count - 1) + 0) = form_length + (letter_count + form_count - 2)*row_length;
 *(*ref_list + 5*(form_count - 1) + 1) = form_length + (letter_count + form_count - 2)*row_length;
 *(*ref_list + 5*(form_count - 1) + 2) = 1;
 *(*ref_list + 5*(form_count - 1) + 3) = 1;
 *(*ref_list + 5*(form_count - 1) + 4) = '&';
return;}
