#include <iostream>
#define CATCH_CONFIG_MAIN
#include <Catch2d/catch.hpp>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;

    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) 
            throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) 
            throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

//------------------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Empty", "[list]") 
{
    List list;
    SECTION("Созданный список пуст") 
    {
        CHECK(list.Empty() == true);
    }

    SECTION("После добавления элемента список не пуст", "[list]") 
    {
        list.PushFront(1);
        CHECK(list.Empty() == false);
    }

    SECTION("Список пустпосле удаления объектов", "[list]")
    {
        list.PushFront(1);
        list.Clear();
        CHECK(list.Empty() == true);
    }
}

TEST_CASE("List Size", "[list]") 
{
    List list;

    SECTION("размер нового списка == 0")
    {
        CHECK(list.Size() == 0);
    }

    SECTION("Размер увеличевается после добавления элемента") 
    {
        list.PushFront(1);
        CHECK(list.Size() == 1);
        list.PushBack(2);
        CHECK(list.Size() == 2);
    }

    SECTION("размер == 0 после отчистки списка ")
    {
        list.PushFront(1);
        list.PushBack(2);
        list.Clear();
        CHECK(list.Size() == 0);
    }
}

TEST_CASE("List Clear", "[list]") 
{
    List list;
    list.PushFront(1);
    list.PushBack(2);
    list.Clear();

    SECTION("список  пуст после отчистки") 
    {
        CHECK(list.Empty() == true);
    }

    SECTION("размер == 0 после отчистки") 
    {
        CHECK(list.Size() == 0);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
   
    return Catch::Session().run();
}