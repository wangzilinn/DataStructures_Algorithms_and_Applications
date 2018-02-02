#pragma once
template <class K, class V>
struct pair_rewrite
{
    K key;
    V value;
    pair_rewrite(K theKey = 0, V theValue = 0) :key(theKey), value(theValue) {}
    pair_rewrite(const pair_rewrite& thePair);
};
template <class K, class V>
pair_rewrite<K, V>::pair_rewrite(const pair_rewrite& thePair)
{
    key = thePair.key;
    value = thePair.value;
}
template<class K, class V>
class HashTable
{
private:
    pair_rewrite<K, V> ** table;
    int divisor;
    int search(const K& theKey);//仅返回对应的下标
public:
    HashTable(int theDivisor);//参数是除数
    pair_rewrite<K, V>* find(const K& theKey);
    void insert(const pair_rewrite<K, V>& thePair);
    void earse(const K& theKey);
};
template<class K, class V>
HashTable<K, V>::HashTable(int theDivisor)
{
    divisor = theDivisor;
    table = new pair_rewrite<K, V>[divisor];
    fill(table, table + divisor, nullptr);
}

template<class K, class V>
int HashTable<K, V>::search(const K& theKey)//如果找到了，则返回找到的值得索引，如果没找到，则返回默认的索引
{
    int origionalPosition = (int)hash(theKey) / divisor;
    int position = origionalPosition;
    int loopLimit = 0;
    while ((table[position]->key != theKey) && (table[position] != nullptr))
    {
        position = (position + 1) % divisor;
        //错：没有注意到这里，导致判断不成功则一直循环
        loopLimit++;//限制循环次数，最多遍历一圈
        if (loopLimit >= divisor)
            break;
    }
    if (table[position] == nullptr)
    {
        return origionalPosition;
    }
    else
    {
        return position;
    }
    //没找到的原因：
    //1.该位置为nullptr，根本没有对应的value
    //2.表满
}
template <class K, class V>
pair_rewrite<K, V>* HashTable<K, V>::find(const K& theKey)
{
    int result = search(theKey);
    if (table[result]->key == theKey)
    {
        return table[result];
    }
    else
        return nullptr;
}
//插入规则：如果对应的Key值已经有数，那么替换为新的数，否则添加
template <class K, class V>
void HashTable<K, V>::insert(const pair_rewrite<K, V>& thePair)
{
    ////因为没有理解search函数的作用，所以这里又重写了一遍，以下代码很多都是和search重复的
    //int position = (int)(thePair.key) / divisor;
    ////检验是否能直接加入
    //if (table[position] == nullptr)
    //{
    //    table[position] = new pair<K, V>(thePair);
    //    return;
    //}
    //if (table[position]->key == thePair.key)
    //{
    //    table[position]->value = thePair.value;
    //    return;
    //}
    //position = (position + 1) / divisor;//线性探查法解决冲突
    //while (table[position] != nullptr)
    //{
    //    position = (position + 1) % divisor;
    //}
    //table[position]->key = thePair.key;
    //table[position]->value = thePair.value;
    int position = search(thePair.key);
    if (table[position] == nullptr)
    {
        table[position]->key = thePair.key;
        table[position]->value = thePair.value;
        return;
    }
    if (table[position]->key == thePair.key)
    {
        table[position]->value = thePair.value;
        return;
    }
    throw "哈希表已满";
}
template <class K, class V>
void earse(const K& theKey)
{
    int position = search(theKey);
    if (table[position] == nullptr)
        return;
    if (table[position]->key == theKey)//找到了对应位置
    {
        int origionalPosition = position;
        int movePosition = position = (position + 1) % divisor;
        while(position != origionalPosition)//防止循环超过一圈，position是当前位置，movePosition是下一个hash（key）和下标不匹配的位置
        {
            if (table[movePosition] == nullptr)
                break;
            while ((table[movePosition] != nullptr) && 
                  ((int)hash(table[movePosition]->key) == movePosition))
            {
                movePosition = (movePosition + 1) % divisor;

            }
            table[position]->value = table[movePosition]->value;
            position = movePosition;
            movePosition = (movePosition + 1) % divisor;
        }
    }
}