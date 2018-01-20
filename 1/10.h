#pragma once
template <class K, class V>
struct pair
{
    K key;
    V value;
    pair(K theKey = 0, V theValue = 0) :key(theKey), value(theValue) {}
    pair(const pair& thePair);
};
template <class K, class V>
pair<K, V>::pair(const pair& thePair)
{
    key = thePair.key;
    value = thePair.value;
}
template<class K, class V>
class HashTable
{
private:
    pair<K, V> ** table;
    int divisor;
    int search(const K& theKey);//�����ض�Ӧ���±�
public:
    HashTable(int theDivisor);//�����ǳ���
    pair<K, V>* find(const K& theKey);
    void insert(const pair<K, V>& thePair);
    earse(const K& theKey);
};
template<class K, class V>
HashTable<K, V>::HashTable(int theDivisor)
{
    divisor = theDivisor;
    table = new pair<K, V>[divisor];
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
pair<K, V>* HashTable<K, V>::find(const K& theKey)
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
void HashTable<K, V>::insert(const pair<K, V>& thePair)
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
    //    position = (position + 1) / divisor;
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
