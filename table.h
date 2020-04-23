#ifndef MAX_SIZE
#define MAX_SIZE (1024 ^ 2)
//  定义哈系表的范围(也就是通过time_33哈系后的值在跟MAX_SIZE整除，从而限定了范围)

// 一个捅，由key和value组成，同时next为链表所用[解决哈系冲突]
typedef struct HashNode
{
    char *key;
    char *value;
    struct HashNode *next;  // Hash冲突

} HashNode;

// 一张哈希表，由一个指针组成，该指针起数组作用，内部存储捅的指针
typedef struct HashTable{
    struct HashNode **HashNode;  // 这是一个指针数组
} HashTable;

HashTable *make_HashTable();
HashNode *make_HashNode(char *key, char *value);
int login_node(HashTable *ht, HashNode *hn);
HashNode *find_node(HashTable *ht, char *key);

#endif