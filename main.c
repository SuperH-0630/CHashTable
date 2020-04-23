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

unsigned int time33(char *key){
    unsigned int hash = 5381;
    while(*key){
        hash += (hash << 5 ) + (*key++);
    }
    return (hash & 0x7FFFFFFF) % MAX_SIZE;
}

int login_node(HashTable *ht, HashNode *hn){
    if(hn == NULL){
        return 1;
    }
    else if(ht == NULL){
        return 1;
    }

    unsigned int index = time33(hn->key);
    HashNode *base_node = ht->HashNode[index];  // 根据下标拿base节点

    if(base_node == NULL){
        ht->HashNode[index] = hn;
    }
    else{
        while(1){
            if(base_node->next == NULL){  // 迭代找到最后一个节点
                break;
            }
            base_node = base_node->next;
        }
        base_node->next = hn;
    }
    return 0;
}

HashNode *find_node(HashTable *ht, char *key){
    if(ht == NULL){
        return NULL;
    }

    unsigned int index = time33(key);
    HashNode *base_node = ht->HashNode[index];  // 根据下标拿base节点

    if(base_node == NULL){  // 没有节点
        return NULL;
    }
    else{
        while(1){
            if(base_node->key == key){  // 找到节点
                return base_node;
            }
            else if(base_node->next == NULL){  // 迭代找到最后一个节点->没有节点
                return NULL;
            }
            base_node = base_node->next;
        }
    }
    return NULL;
}
