#include <iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct ListNode {
    int val;           // 节点值
    ListNode *next;    // 指向下一个节点的指针
    // 三种构造函数
    ListNode() : val(0), next(nullptr) {}                      // 无参构造
    ListNode(int x) : val(x), next(nullptr) {}                 // 只传值
    ListNode(int x, ListNode *next) : val(x), next(next) {}    // 传值和下一个节点
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        while(list1->next != nullptr){
            if(list1->val >= list2->val){
                ListNode tmplist(list2->val,list1);//TODO
            }

            list1 = list1->next;
        }
    }
};