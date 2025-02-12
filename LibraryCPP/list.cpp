#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next = nullptr;
    ListItem* prev = nullptr;
    ListItem(Data data): data(data) {};
};

struct List
{
    ListItem* first = nullptr;
    ListItem* dummy = new ListItem(0); 
    List(){
        dummy->next = dummy;
        dummy->prev = dummy;
    }
};

//Создает новый список
List *list_create()
{
    return new List;
}

//Уничтожает список и освобождает память
void list_delete(List *list)
{
    ListItem*item=list->first;
    while(item){
        ListItem* del = item;
        item = item->next;
        delete del;
    }
    delete list;
}

//Извлекает первый элемент из списка
ListItem *list_first(List *list)
{
    return list->first;
}

//Извлекает данные из элемента списка
Data list_item_data(const ListItem *item)
{
    return item->data;
}

//Возвращает элемент списка, следующий за указанным
ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

//Возвращает предыдущий элемент для указанного элемента.
//Не применимо для односвязных списков.
ListItem *list_item_prev(ListItem *item)
{
    return item->prev;
}

//Вставляет новый элемент списка в начало
ListItem *list_insert(List *list, Data data)
{
    ListItem* item = new ListItem(data);
    list->first = item;
    list->dummy->prev = item;
    list->first->prev = list->dummy;
    list->dummy->next=list->first;
    return item;
}

//Вставляет новый элемент списка после указанного элемента
ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem* new_item = new ListItem(data);
    new_item->next=item->next;
    if (new_item->next){
        new_item->next->prev =new_item;
    }
    item->next=new_item;
    new_item->prev=item;
    return new_item;
}

//Удаляет указанный элемент списка.
//Не применимо для односвязных списков.
//Должно быть O(1)
ListItem *list_erase(List *list, ListItem *item)
{
    if(list->first == item){
        list->first = item->next;
    }
    if(item->next){
        item->next->prev=item->prev;
    }
    if(item->prev){
        item->prev->next=item->next;
    }
    ListItem*next=item->next;
    delete item;
    return next;
}


//Удаляет элемент списка, следующий за указанным
//Должно быть O(1)
ListItem *list_erase_next(List *list, ListItem *item)
{
    return list_erase(list,item->next);
}