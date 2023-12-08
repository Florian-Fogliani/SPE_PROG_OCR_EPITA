#include "hough.h"
#include "stdlib.h"
#include <err.h>
#include <unistd.h>
#include <sys/wait.h>

SDL_Surface* load_image(const char* path)
{
    SDL_Surface* temp = IMG_Load(path);
    if (temp == NULL) errx(EXIT_FAILURE,"%s",SDL_GetError());
    SDL_Surface* res = SDL_ConvertSurfaceFormat(temp,SDL_PIXELFORMAT_RGB888,0);
    if (res==NULL) errx(EXIT_FAILURE,"%s",SDL_GetError());
    SDL_FreeSurface(temp);
    return res;
}


void Clean()
{
	char path[1024];
	getcwd(path,sizeof(path));
	pid_t pid=fork();
	if (pid==0)
	{
		char nb[]={'/','m','a','t','_',48,'_',48,'\0'};
		char* arg[] = {"rm",strcat(path,nb),NULL};
		execvp("rm",arg);
		return 0;
	}
	else
	{
		wait(NULL);
	}
	for (int i=1;i<=9;i++)
	{
		for (int y=1;y<=9;y++)
		{
			pid_t pid=fork();
			if(pid==0)
			{
				char nb[]={'/','m','a','t','_',i+48,'_',y+48,'\0'};
				char* arg[] = {"rm",strcat(path,nb),NULL};
				execvp("rm",arg);
				return 0;
			}
			else if (pid>0)
			{
				wait(NULL);
			}
		}
	}
}
char* Cutter(char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) !=0)
	{
		errx(EXIT_FAILURE,"%s",SDL_GetError());
	}
	SDL_Surface* to_analyze = load_image(argv[0]);
	if (surface == NULL)
	{
		errx(EXIT_FAILURE, "%s",SDL_GetError());
	}

	//HOUGH CALL
	int diag_size = (int)Calculate_Diagonal(to_analyze);
	int* mat = Init_Mat((const int)diag_size);
	int max = Fill_Mat(to_analyze,mat,(const int)diag_size);

	//PREPARATION OF CUTTER
	struct Line* horizontals = calloc(1,sizeof(struct Line));
	struct Line* verticals = calloc(1,sizeof(struct Line));
	int size_h=1;
	int size_v=1;
	GetLines
		    (mat, diag_size,max,&horizontals, &verticals,
		     &size_h, &size_v,to_analyze);
	SDL_Surface* to_cut = load_image(argv[1]);
	Cut(&horizontals,&verticals,&size_h,&size_v,to_cut);
	to_cut = load_image("mat_0_0");
	CutFinale(to_cut);
	Free_Mat(mat);
	Free_Lines(horizontals,verticals);
	SDL_FreeSurface(to_cut);
	SDL_FreeSurface(to_analyze);
	SDL_Quit();

	char path[1024];
	getcwd(path,sizeof(path));
	char file = "/result";
	return path+file;
}

void print_param(struct Line* l, int s)
{
    int i=0;
    while (i<s)
    {
        printf("Rho %i, Theta %i \n", l[i].rho, l[i].theta);
        i++;
    }
}
