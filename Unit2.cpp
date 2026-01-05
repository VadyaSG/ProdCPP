#include<iostream>
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
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
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

//----------------------------------------------------------------------------------------------------------------------------------
TEST_CASE("Push_back", "[List]")
{
    List list;
    CHECK(list.Empty() == true);
    list.PushBack(12);
    CHECK(list.Empty() == false);
    CHECK(list.Size() == 1);
}

TEST_CASE("Push_Front", "[list]")
{
    List list;
    CHECK(list.Empty() == true);
    list.PushFront(6);
    CHECK(list.Empty() == false);
    CHECK(list.Size() == 1);
}

TEST_CASE("Pop_back", "[list]")
{
    List list;
    SECTION("Pop_back на пустом списке")
    {
        REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);
    }
    SECTION("Pop_back на списке  с элементами")
    {
        list.PushBack(20);
        CHECK(list.PopBack() == 20);
        CHECK(list.Empty() == true);
    }
}

TEST_CASE("Pop_front", "[List]")
{
    List list;
    SECTION("Pop_front на пустом списке")
    {
        REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
    }
    SECTION("Pop_front на списке с элементами")
    {
        list.PushFront(15);
        CHECK(list.PopBack() == 15);
        CHECK(list.Empty() == true);
    }
}

TEST_CASE("несколько вызовов функций (сценарий сложнее)", "list")
{
    List list;
    list.PushBack(1);
    list.PushFront(2);
    list.PushBack(3);
    CHECK(list.Size() == 3);
    CHECK(list.PopFront() == 2);
    CHECK(list.PopBack() == 3);
    CHECK(list.Size() == 1);
    list.PushFront(4);
    CHECK(list.PopBack() == 1);
    CHECK(list.PopFront() == 4);
    CHECK(list.Empty() == true);
}

//----------------------------------------------------------------------------------------------------------------------------------

int main()
{
    return Catch::Session().run();
}