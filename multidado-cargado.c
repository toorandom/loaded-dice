/*
Loaded dice which can be configured with the desired probabilities


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>


#define UNIVERSO 1000

unsigned int
dame_random ()
{
  unsigned int r;
  struct timeval tv;
  struct timezone tz;
  struct tm *tm;
  gettimeofday (&tv, &tz);
  tm = (struct tm *) localtime (&tv.tv_sec);
  srand (tv.tv_usec);
  r = rand () % UNIVERSO;
  return r;
}

typedef struct simbolo
{
  int sym;
  unsigned int prob;
} simbolo_t;


void
obten_args (char *str, simbolo_t * s, int sympos)
{

  char val[12];
  int i, j = 0;
  s->sym = sympos;
  memset (&val, 0, sizeof (val));
  for (i = 0; i < strlen (str); i++)
    if (str[i] == ':')
      break;
  for (i; i < strlen (str); i++)
    {
      val[j] = str[i + 1];
      j++;
    }
  s->prob = atoi ((char *) val);
}

unsigned int rinteger= 0;
int
main (int argc, char **argv)
{
  int i, j, k = 0, u = 0;
  unsigned char univ[UNIVERSO];
  char *res;
  unsigned int pindex;
  simbolo_t **s;
  if (argc < 2)
    {
      printf
	("Debes de darme n argumentos de la forma Simbolo:probabilidad\n");
      exit (EXIT_FAILURE);
    }

  s = calloc (sizeof (void *), argc);
  for (i = 1; i < argc; i++)
    {
      s[i - 1] = calloc (sizeof (struct simbolo), 1);
      obten_args (argv[i], s[i - 1], i);
      u += s[i - 1]->prob;
    }

  if (u != 100)
    {
      printf ("Error, las probabilidades no suman 100%%\n");
      exit (EXIT_FAILURE);
    }
  for (j = 0; j < argc - 1; j++)
    {
      k += (j < 1) ? 0 : s[j - 1]->prob * 10;
      for (i = k; i < s[j]->prob * 10 + k; i++)
	univ[i] = j;
    }
  rinteger=dame_random();

  pindex = univ[rinteger];
  res = calloc (strlen (argv[pindex + 1]), 1);
  for (i = 0; i < strlen (argv[pindex + 1]); i++)
    {
      res[i] = argv[pindex + 1][i];
      if (argv[pindex + 1][i] == ':')
	break;
    }
  res[strlen (res) - 1] = 0;
  printf ("%s(%d)\n", res,rinteger);


}
