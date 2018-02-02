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
    int search(const K& theKey);//�����ض�Ӧ���±�
public:
    HashTable(int theDivisor);//�����ǳ���
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
int HashTable<K, V>::search(const K& theKey)//����ҵ��ˣ��򷵻��ҵ���ֵ�����������û�ҵ����򷵻�Ĭ�ϵ�����
{
    int origionalPosition = (int)hash(theKey) / divisor;
    int position = origionalPosition;
    int loopLimit = 0;
    while ((table[position]->key != theKey) && (table[position] != nullptr))
    {
        position = (position + 1) % divisor;
        //��û��ע�⵽��������жϲ��ɹ���һֱѭ��
        loopLimit++;//����ѭ��������������һȦ
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
    //û�ҵ���ԭ��
    //1.��λ��Ϊnullptr������û�ж�Ӧ��value
    //2.����
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
//������������Ӧ��Keyֵ�Ѿ���������ô�滻Ϊ�µ������������
template <class K, class V>
void HashTable<K, V>::insert(const pair_rewrite<K, V>& thePair)
{
    ////��Ϊû�����search���������ã�������������д��һ�飬���´���ܶ඼�Ǻ�search�ظ���
    //int position = (int)(thePair.key) / divisor;
    ////�����Ƿ���ֱ�Ӽ���
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
    //position = (position + 1) / divisor;//����̽�鷨�����ͻ
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
    throw "��ϣ������";
}
template <class K, class V>
void earse(const K& theKey)
{
    int position = search(theKey);
    if (table[position] == nullptr)
        return;
    if (table[position]->key == theKey)//�ҵ��˶�Ӧλ��
    {
        int origionalPosition = position;
        int movePosition = position = (position + 1) % divisor;
        while(position != origionalPosition)//��ֹѭ������һȦ��position�ǵ�ǰλ�ã�movePosition����һ��hash��key�����±겻ƥ���λ��
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