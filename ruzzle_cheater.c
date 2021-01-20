# include <stdio.h>
# include <string.h>
# define MAXD 4
# define MAXFILE 200

typedef struct point_{
	int i, j;
} point_t;

int search(char [][MAXD], int, char[], point_t *, point_t[], int);
int valid (point_t *, int);
int used(point_t *, point_t[], int);


int main (int argc,char*argv[])
{
	char namemat[MAXFILE+1], nameword[MAXFILE+1], matr[MAXD][MAXD], matr2[MAXD][MAXD], c, word[MAXD * MAXD];
	int i, j, h, k, found, dim, pos, len;
	FILE * fp;
	point_t path[MAXD * MAXD], p;
	
	printf("Name file mat\n");
	gets(namemat);
	printf("Name dictionary\n");
	gets(nameword);
	if((fp = fopen(namemat, "r"))){
		fscanf(fp, "%d", &dim);
		fscanf(fp, "%c", &c);
		for(i = 0; i < dim; i++){
			for(j = 0; j < dim; j++)
				fscanf(fp, "%c", &matr[i][j]);
			fscanf(fp, "%c", &c);
		}
		fclose(fp);
		if((fp = fopen(nameword, "r"))){
			fscanf(fp, "%s", word);
			pos = 0;
			while(!feof(fp)){
				for(i = 0; i < dim; i++){
					for(j = 0; j < dim; j++){
						p.i = i;
						p.j = j;
						found = search(matr, dim, word, &p, path, pos);
						if(found){
							for(h = 0; h < dim; h++)
								for(k = 0; k < dim; k++)
									matr2[h][k] = matr[h][k];
							len = (int)strlen(word);
							for(h = 0; h < len; h++)
								matr2[path[h].i][path[h].j] = '0' + h;
							
							printf("\n%s\n", word);
							for(h = 0; h < dim; h++){
								for(k = 0; k < dim; k++)
									printf("%c ", matr2[h][k]);
								printf("\n");
							}
						}
					}
				}
				fscanf(fp, "%s", word);
				pos = 0;
            }
			fclose(fp);
		}else
			printf("dictionary error");
	}else
        printf("error in opening the matrix file");
	return 0;
}


int search(char matr[][MAXD], int dim, char word[], point_t * p, point_t path[], int pos)
{	
	int test, h, k;
	point_t nextp;
	if(matr[p->i][p->j] != word[pos])
		return 0;
	path[pos].i = p->i;
	path[pos].j = p->j;
	if(pos + 1 == strlen(word))
		return 1;
	for(h = -1, test = 0; h < 2 && !test; h++)
		for(k = -1; k < 2 && !test; k++){
			nextp.i = p->i + h;
			nextp.j = p->j + k;
			if(valid(&nextp, dim) && !used(&nextp, path, pos + 1))
				test = search(matr, dim, word, &nextp, path, pos + 1);
		}
	return test;
}


int valid (point_t * p, int dim)
{	
	return (p->i < dim && p->i >= 0 && p->j < dim && p->j >= 0);
}


int used(point_t * p, point_t path[], int dim)
{	
	int found, i;
	for(i = 0, found = 0; i < dim && !found; i++)
		if(path[i].i == p->i && path[i].j == p->j)
			found = 1;
	return found;
}
