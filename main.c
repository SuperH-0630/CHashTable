#include <stdio.h>
#include "table.h"
#include <stdlib.h>

int main(){
    HashTable *ht = make_HashTable();
    HashNode *tmp1 = make_HashNode("YY","Hello"), *tmp2 = make_HashNode("ZZ","World");
    login_node(ht, tmp1);
    login_node(ht, tmp2);
    printf("YY = %s, ZZ = %s\n", find_node(ht, "YY")->value, find_node(ht, "ZZ")->value);
    return 0;
}

HashTable *make_HashTable(){  // 生成并初始化
    HashTable *tmp = NULL;
    size_t size = sizeof(HashNode) * MAX_SIZE;
    tmp = malloc(sizeof(HashTable));
    tmp->HashNode = malloc(size);
    for(int i = 0; i < MAX_SIZE; i++){
        tmp->HashNode[i] = NULL;  // 初始化
    }
    return tmp;
}

HashNode *make_HashNode(char *key, char *value){  // 生成并初始化
    HashNode *tmp = NULL;
    tmp = malloc(sizeof(HashNode));
    tmp->key = key;
    tmp->value = value;
    tmp->next = NULL;
    return tmp;
}

// 使用time33算法，把key换算成为索引，生成索引的范围在0-MAX_SIZE上[因为有 % MAX_SIZE]
unsigned int time33(char *key){
    unsigned int hash = 5381;
    while(*key){
        hash += (hash << 5 ) + (*key++);
    }
    return (hash & 0x7FFFFFFF) % MAX_SIZE;
}

// 添加一个桶
int login_node(HashTable *ht, HashNode *hn){
    // 检查数据是否合法
    if(hn == NULL){
        return 1;
    }
    else if(ht == NULL){
        return 1;
    }

    // 计算下标
    unsigned int index = time33(hn->key);
    HashNode *base_node = ht->HashNode[index];  // 根据下标拿base节点

    if(base_node == NULL){
        ht->HashNode[index] = hn;  // 无冲突
    }
    else{
        // 有冲突
        while(1){
            if(base_node->next == NULL){  // 迭代找到最后一个节点
                break;
            }
            base_node = base_node->next;  // 迭代
        }
        base_node->next = hn;  // 给链表赋值
    }
    return 0;
}

HashNode *find_node(HashTable *ht, char *key){
    // 检查数据是否合法
    if(ht == NULL){
        return NULL;
    }

    // 计算索引
    unsigned int index = time33(key);
    HashNode *base_node = ht->HashNode[index];  // 根据下标拿base节点

    if(base_node == NULL){  // 没有节点
        return NULL;  // 返回NULL表示无数据
    }
    else{
        while(1){
            if(strcmp(base_node->key, key)){  // 比较字符串的值，不可以直接使用 == [char *是指针，==只是比较俩字符串的指针是否一致]
                return base_node;
            }
            else if(base_node->next == NULL){  // 迭代找到最后一个节点，依然没有节点
                return NULL;
            }
            base_node = base_node->next;
        }
    }
    return NULL;
}
