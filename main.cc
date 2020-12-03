/* Sample implementation of wc utility. */

/* Based on https://www.gnu.org/software/cflow/manual/html_node/Source-of-wc-command.html
   This file (wc.cc) was tested on Ubuntu 14.04, and it worked fine.
   The changes are: including some c++ libraries and types of parameters
   in several functions so that it can be compiled by g++.
*/

#include <cstdlib>
#include <cctype>
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <algorithm>
#include <iostream>


typedef unsigned long count_t;  /* Counter type */

/* Current file counters: chars, words, lines */
count_t ccount;
count_t wcount;
count_t lcount;

/* Totals counters: chars, words, lines */
count_t total_ccount = 0;
count_t total_wcount = 0;
count_t total_lcount = 0;

/* Print error message and exit with error status. If PERR is not 0,
   display current errno status. */
static void
error_print (int perr, const char *fmt, va_list ap)
{
  vfprintf (stderr, fmt, ap);
  if (perr)
    perror (" ");
  else
    fprintf (stderr, "\n");
  exit (1);
}

/* Print error message and exit with error status. */
static void
errf (const char *fmt, ...)
{
  va_list ap;

  va_start (ap, fmt);
  error_print (0, fmt, ap);
  va_end (ap);
}

/* Print error message followed by errno status and exit
   with error code. */
static void
perrf (const char *fmt, ...)
{
  va_list ap;

  va_start (ap, fmt);
  error_print (1, fmt, ap);
  va_end (ap);
}

/* Output counters for given file */
void
report (const char *file, count_t ccount, count_t wcount, count_t lcount)
{
  printf ("%6lu %6lu %6lu %s\n", lcount, wcount, ccount, file);
}

/* Return true if C is a valid word constituent */
static int
isword (unsigned char c)
{
  return isalpha (c);
}

/* Increase character and, if necessary, line counters */
#define COUNT(c)       \
      ccount++;        \
      if ((c) == '\n') \
        lcount++;

/* Get next word from the input stream. Return 0 on end
   of file or error condition. Return 1 otherwise. */
int
getword (FILE *fp)
{
  int c;
  int word = 0;

  if (feof (fp))
    return 0;

  while ((c = getc (fp)) != EOF)
    {
      if (isword (c))
        {
          wcount++;
          break;
        }
      COUNT (c);
    }

  for (; c != EOF; c = getc (fp))
    {
      COUNT (c);
      if (!isword (c))
        break;
    }

  return c != EOF;
}

/* Process file FILE. */
unsigned long
counter (const char *file)
{
  FILE *fp = fopen (file, "r");

  if (!fp)
    perrf ("cannot open file `%s'", file);

  ccount = wcount = lcount = 0;
  while (getword (fp))
    ;
  fclose (fp);

  report (file, ccount, wcount, lcount);
  total_ccount += ccount;
  total_wcount += wcount;
  total_lcount += lcount;
  return ccount;
}
/*! \brief Finds length of string
 *
 * Finds the size of the string and returns that value in bytes (Since 1 char = 1 byte)
 *	@return size_t size of string in bytes
 */
size_t countChar(std::string s) {
  return s.size();
}
/*! \brief counts the amount of '\n' in provided string
 *
 * Uses count of algorithm to count all instances of '\n' from begining of string to the end
 *	@return size_t amount of '\n'
 */
size_t countLine(std::string s) {
  return std::count(s.begin(), s.end(), '\n');
}
/*! \brief driver function
 *
 * counts total args and executes the correlating functions
 *	@return int 0
 */
int
main (int argc, char **argv)
{
  int i;

  if (argc < 2)
    std::cout << countChar("Ohio University") << " ";
    std::cout << countLine("Athens") << std::endl;
    return 0;

  for (i = 1; i < argc; i++)
    counter (argv[i]);

  if (argc > 2)
    report ("total", total_ccount, total_wcount, total_lcount);
  return 0;
}
