#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void FormulaVerify(char formula[]);
void LetterInit(int ref_list[], char formula[],  char letter_list[], int *letter_count, int *row_length, int *row_number);
void TruthAllocate(char **truth_table, int *row_space, int *row_length, int *letter_count);
int TruthInit(int ref_list[], char truth_table[], char letter_list[], int letter_count, int row_length);
void FormulaWrite(char truth_table[], char argv[], int index, int row_length);
void TableSolver(int ref_list[], char truth_table[], int letter_count, int row_length);
void Logic(char dest[], char src1[], char src2[], char ops[], int truth_length);
int main(int argc, char *argv[]){
char *truth_table = NULL,  letter_list[52] = {0};
int *ref_list = NULL; letter_count, form_count, row_length, form_length;
if(argc < 2) return 0;
FormulaVerify(argv[1], &form_count);
LetterInit(argv[1], letter_list, &letter_count, &row_length, &form_length);
TruthAllocate(&ref_list, &truth_table, letter_count, form_count, row_length);
TruthInit(truth_table, letter_list, letter_count, form_length, row_length);
FormulaWrite(ref_list, truth_table, argv[1], letter_count, row_length);
TableSolver(ref_list, truth_table, letter_count, row_length);
printf("%s", truth_table);
while(argc > 2){
if(fgets(buffer, sizeof(buffer)) == NULL)break;
for(index = 0, letter_count = 0; index < sizeof(buffer); index++){
	letter_count *= 10 - 9*(line_color != 0);
	leter_number += (buffer[index] - '0')*(line_color == 0);
	line_color = buffer[index]*(buffer[index] < '0' || buffer[index] > '9');
	buffer[index] = 0;
}
if(letter_count > row_space - row_length - 1 / row_length)break;
else if(line_color == 'r' || line_color == 'R')
else if(line_color == 'g' || line_color == 'G')
else if(line_color == 'b' || line_color == 'B')
else break;
}

free(truth_table);
truth_table = NULL;
return 0;}
int LetterInit(char formula[], char letter_list[], int *letter_count, int *row_length, int *form_length){
*letter_count = -1; *form_length = 0;
for(int letter_dex = 0; formula[*form_length] != 0; *form_length++){
letter_dex                     = (formula[*form_length] - 'A')*(formula[*form_length] >= 'A' && formula[*form_length] <= 'Z');
*letter_count                 += (formula[*form_length] >= 'A' && formula[*form_length] <= 'Z' && letter_list[2*letter_dex] == 0);
letter_list[2*letter_dex]     +=  formula[*form_length]*(formula[*form_length] >= 'A' && formula[*form_length] <= 'Z' && letter_list[2*letter_dex] == 0);
letter_list[2*letter_dex + 1] += *letter_count *(formula[*form_length] >= 'A' && formula[*form_length] <= 'Z' && letter_list[2*letter_dex + 1] == 0);
}
*row_length = (1 << *letter_count) + 5 + *form_length; //2 for letter and \n, 3 for !!>
return;}
void TruthInit(char truth_table[], char letter_list[], int letter_count, int form_length, int row_length){
int truth_half = 1 << letter_count; char truth = 1;
for(int letter_dex = -1, i = 0; i < letter_count; i++){
	truth_half /= 2;
	do letter_dex++; while(letter_list[2*letter_dex] == 0);
	truth_table[i*row_length] = letter_list[2*letter_dex];
	for(int j = 0, truth = 1; j < (1 << letter_count); j++){
		truth_table[i + form_length + j] = '0' + truth;
		truth = truth*(((j + 1) % truth_half) != 0) + (1 - truth)*(((j + 1) % truth_half) == 0);
	}
}
return;}
void FormulaWrite(int ref_list[], char letter_list[], char truth_table[], char formula[], int letter_count, int row_length, int max_depth){
int index = letter_count*row_length, ref_point = index;
for(int line = 0; max_depth > 0; max_depth--){
  for(int depth = 0, form_found = 0, neg_found = 0, i = 0, j = 0; formula[i] != 0; i++){
    depth += (formula[i] == '(');
    if(depth >= target_depth){truth_table[index + j] = formula[i]; j++;}
    if(depth == target_depth && formula[i] != ' '){
      if(formula[i] == ')')                          {index += row_length; j = 0; form_found = 0; neg_found = 0; line++;}
      else if(formula[i] == '(')		     {ref_list[line*5 + 0 + form_found] = ref_point; ref_point += row_length; form_found = 1;}
      else if(formula[i] >= 'A' || formula[i] <= 'Z'){ref_list[line*5 + 0 + form_found] = letter_list[2*(formula[i] - 'A') + 1]*row_length; form_found = 1;}
      else if(formula[i] == '!')                     {ref_list[line*5 + 2 + neg_found] = '!'; neg_found = 1;}
      else			                     {ref_list[line*5 + 4] = formula[i];}
    }
    depth -= (formula[i] == ')');
  }
}
memcpy(&truth_table[index], &truth_table[index - row_length], (size_t) row_length);
truth_table[index + row_length] = 0;
return;}
void TableSolver(int ref_list[], char truth_table[], int letter_count, int row_length){
int ref_offset = ((letter_count + 1) * row_length) - 6; //'A', 'B', refs, operator offset will be ref_off + 2;
int solve_offset = ref_list[0], truth_dex1 = 0, truth_dex2 = 0, i = 0;
for(i = ref_offset + 6; truth_table[i] != 0; i += row_length){
	truth_dex1 = ref_list[(truth_table[ref_offset] % 64) & 31]; //'A' yeilds position 1, whitespace 0
	truth_dex2 = ref_list[(truth_table[ref_offset + 1] % 64) & 31];
	truth_dex2 += row_length*(truth_table[ref_offset] == ' ' && truth_dex2 == truth_dex1);
	Logic(&truth_table[solve_offset], &truth_table[truth_dex1], &truth_table[truth_dex2], &truth_table[ref_offset + 2], 1 << letter_count);
	ref_list[0] += row_length*((truth_table[ref_offset] == ' ') + (truth_table[ref_offset + 1] == ' '));
	solve_offset += row_length;
	ref_offset += row_length;
}
for(i = 0, truth_dex1 = solve_offset, truth_dex2 = solve_offset - row_length; i < (1 << letter_count); i++){
	truth_table[truth_dex1 + i] = (~truth_table[truth_dex2 + i] & 1) | 48;
}
return;}
void Logic(char dest[], char src1[], char src2[], char ops[], int truth_length){
char place[4] = {0, 0, 0, 0}; int i;
for(i = 0; i < truth_length && ops[2] == '|'; i++){
place[0] = src1[i]; place[1] = (~src1[i] & 1) | 48;
place[2] = src2[i]; place[3] = (~src2[i] & 1) | 48;
dest[i] = place[0 + ops[0] - 32] | place[2 + ops[1] - 32];
}
for(i = 0; i < truth_length && ops[2] == '&'; i++){
place[0] = src1[i]; place[1] = (~src1[i] & 1) | 48;
place[2] = src2[i]; place[3] = (~src2[i] & 1) | 48;
dest[i] = place[0 + ops[0] - 32] & place[2 + ops[1] - 32];
}
for(i = 0; i < truth_length && ops[2] == '>'; i++){
place[0] = src1[i]; place[1] = (~src1[i] & 1) | 48;
place[2] = src2[i]; place[3] = (~src2[i] & 1) | 48;
dest[i] = (~place[0 + ops[0] - 32] & 1) | 48 | place[2 + ops[1] - 32];
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
void TruthAllocate(int **ref_list, char **truth_table, int letter_count, int form_count, int row_length){
 int j = (row_length * form_count) + (row_length * letter_count) + 1;
 *ref_list = malloc(5*(form_count - 1) * sizeof(int));
 *truth_table = malloc(j*sizeof(char));
 if(*truth_table == NULL || *ref_list == NULL){printf("allocation failed, exiting...\n"); exit(0);}
 *(*truth_table + j - 1) = 0;
 for(int i = 0; i < j - 1; i++)           *(*truth_table + i) = ' ' + ('\n' - ' ')*((i + 1) % row_length == 0);
 for(int i = 0; i < 5*form_count - 1; i++)*(*ref_list + i) = 0;
return;}
