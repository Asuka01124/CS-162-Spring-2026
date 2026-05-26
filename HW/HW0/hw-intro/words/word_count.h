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

/*
word_count provides lists of words and associated count
word_count 提供用于保存单词及其出现次数的链表。

Functional methods take the head of a list as first arg.
Mutators take a reference to a list as first arg.
函数式方法把链表头作为第一个参数。
会修改链表的方法把链表引用作为第一个参数。
*/



#ifndef word_count_h
#define word_count_h

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Representation of a word count object.
   Includes next field for constructing singly linked list
   单词计数对象的表示。
   包含 next 字段，用于构造单向链表。 */
struct word_count {
    char *word;
    int count;
    struct word_count *next;
};

/* Introduce a type name for the struct
   为该结构体引入一个类型名。 */
typedef struct word_count WordCount;

/* Initialize a word count list, updating the reference to the list
   初始化单词计数链表，并更新链表引用。 */
int init_words(WordCount **wclist);

/* Length of a word count list
   返回单词计数链表的长度。 */
ssize_t len_words(WordCount *wchead);

/* Find a word in a word_count list
   在 word_count 链表中查找指定单词。 */
WordCount *find_word(WordCount *wchead, char *word);

/* Insert word with count=1, if not already present; increment count if present.
   如果单词不存在，则以 count=1 插入；如果已经存在，则将计数加一。 */
int add_word(WordCount **wclist, char *word);

//static int wordcntcmp(const WordCount *wc1, WordCount *wc2);

/* print word counts to a file
   将单词计数结果打印到文件。 */
void fprint_words(WordCount *wchead, FILE *ofile);

/* Inserts a word into the list in order. Assumes the existing list is already sorted
   按顺序把一个单词节点插入链表。假设现有链表已经排好序。 */
void wordcount_insert_ordered(WordCount **wclist, WordCount *elem, bool less(const WordCount *, const WordCount *));

/* Sort a word count list in place
   原地排序单词计数链表。 */
void wordcount_sort(WordCount **wclist, bool less(const WordCount *, const WordCount *));

#endif /* word_count_h */

