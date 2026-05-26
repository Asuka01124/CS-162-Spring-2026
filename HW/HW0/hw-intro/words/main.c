/*

  Word Count using dedicated lists
  使用专用链表实现单词计数

*/

/*
Copyright © 2019 University of California, Berkeley

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include <assert.h>
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "word_count.h"

/* Global data structure tracking the words encountered
   全局数据结构，用于记录已经遇到的单词。 */
WordCount *word_counts = NULL;

/* The maximum length of each word in a file
   文件中每个单词的最大长度。 */
#define MAX_WORD_LEN 64

/*
 * 3.1.1 Total Word Count
 * 3.1.1 单词总数统计
 *
 * Returns the total amount of words found in infile.
 * Useful functions: fgetc(), isalpha().
 * 返回在 infile 中找到的单词总数。
 * 可用函数：fgetc()、isalpha()。
 */
int num_words(FILE* infile) {
  int num_words = 0;
  int c;
  while ((c = fgetc(infile)) != EOF) {
      if (isalpha(c)) {
          num_words++;
          while ((c = fgetc(infile)) != EOF && isalpha(c));
      }
  }
  return num_words;
}

/*
 * 3.1.2 Word Frequency Count
 * 3.1.2 单词频率统计
 *
 * Given infile, extracts and adds each word in the FILE to `wclist`.
 * Useful functions: fgetc(), isalpha(), tolower(), add_word().
 * 给定 infile，从 FILE 中提取每个单词并加入 `wclist`。
 * 可用函数：fgetc()、isalpha()、tolower()、add_word()。
 * 
 * As mentioned in the spec, your code should not panic or
 * segfault on errors. Thus, this function should return
 * 1 in the event of any errors (e.g. wclist or infile is NULL)
 * and 0 otherwise.
 * 正如说明文档中提到的，你的代码在遇到错误时不应该崩溃或段错误。
 * 因此，如果发生任何错误（例如 wclist 或 infile 为 NULL），
 * 该函数应返回 1；否则返回 0。
 */
int count_words(WordCount **wclist, FILE *infile) {
  return 0;
}

/*
 * Comparator to sort list by frequency.
 * Useful function: strcmp().
 * 用于按频率排序链表的比较器。
 * 可用函数：strcmp()。
 */
static bool wordcount_less(const WordCount *wc1, const WordCount *wc2) {
  return 0;
}

// In trying times, displays a helpful message.
// 在需要帮助时，显示一条有用的提示信息。
static int display_help(void) {
	printf("Flags:\n"
	    "--count (-c): Count the total amount of words in the file, or STDIN if a file is not specified. This is default behavior if no flag is specified.\n"
	    "--frequency (-f): Count the frequency of each word in the file, or STDIN if a file is not specified.\n"
	    "--help (-h): Displays this help message.\n");
	return 0;
}

/*
 * Handle command line flags and arguments.
 * 处理命令行标志和参数。
 */
int main (int argc, char *argv[]) {

  // Count Mode (default): outputs the total amount of words counted
  // 计数模式（默认）：输出统计到的单词总数
  bool count_mode = true;
  int total_words = 0;

  // Freq Mode: outputs the frequency of each word
  // 频率模式：输出每个单词的出现频率
  bool freq_mode = false;

  FILE *infile = NULL;

  // Variables for command line argument parsing
  // 用于命令行参数解析的变量
  int i;
  static struct option long_options[] =
  {
      {"count", no_argument, 0, 'c'},
      {"frequency", no_argument, 0, 'f'},
      {"help", no_argument, 0, 'h'},
      {0, 0, 0, 0}
  };

  // Sets flags
  // 设置标志位
  while ((i = getopt_long(argc, argv, "cfh", long_options, NULL)) != -1) {
      switch (i) {
          case 'c':
              count_mode = true;
              freq_mode = false;
              break;
          case 'f':
              count_mode = false;
              freq_mode = true;
              break;
          case 'h':
              return display_help();
      }
  }

  if (!count_mode && !freq_mode) {
    printf("Please specify a mode.\n");
    return display_help();
  }

  /* Create the empty data structure
     创建空的数据结构。 */
  init_words(&word_counts);

  if ((argc - optind) < 1) {
    // No input file specified, instead, read from STDIN instead.
    // 没有指定输入文件，因此改为从标准输入 STDIN 读取。
    infile = stdin;
    if (count_mode) {
      total_words += num_words(infile);
    } else {
      if (count_words(&word_counts, infile) != 0) {
        return 1;
      }
    }
  } else {
    // At least one file specified. Useful functions: fopen(), fclose().
    // The first file can be found at argv[optind]. The last file can be
    // found at argv[argc-1].
    // 至少指定了一个文件。可用函数：fopen()、fclose()。
    // 第一个文件位于 argv[optind]，最后一个文件位于 argv[argc-1]。
    for (int i = optind; i < argc; i++) {
      infile = fopen(argv[i], "r");
      if (infile == NULL) {
        return 1; 
      }
      if (count_mode) {
        total_words += num_words(infile);
      } else {
        if (count_words(&word_counts, infile) != 0) {
          return 1;
        }
      }
      fclose(infile);
    }
  }

  if (count_mode) {
    printf("The total number of words is: %i\n", total_words);
  } else {
    wordcount_sort(&word_counts, wordcount_less);
    printf("The frequencies of each word are: \n");
    fprint_words(word_counts, stdout);
  }
  return 0;
}
