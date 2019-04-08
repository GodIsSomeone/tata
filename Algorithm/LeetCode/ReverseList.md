翻转链表
```
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <xutility>
#include <string>
#include<algorithm>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode * reverseList(ListNode* head) {
        if (head == NULL || head->next ==NULL)
        {
            return head;
        }
        ListNode *preNode = NULL;
        ListNode *curNode = head;
        while (curNode)
        {
            ListNode* nextNode = curNode->next;
            
            curNode->next = preNode;
            preNode = curNode;
            curNode = nextNode;
        }
        return preNode;
    }
};

int main() {
    ListNode *head = NULL;
    ListNode tmpNode(1);
    ListNode tmpNode2(2);
    ListNode tmpNode3(3);
    ListNode tmpNode4(4);
    head = &tmpNode;
    head->next = &tmpNode2;
    tmpNode2.next = &tmpNode3;
    tmpNode3.next = &tmpNode4;
    ListNode * result = Solution().reverseList(head);
    while (result)
    {
        cout << result->val << endl;
        result = result->next;
    }
    return 0;
}
```
