#### 链表排序:采用分开排序，然后合并的手段

快慢指针

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
    ListNode* sortList(ListNode* head) {
        if (head == NULL || head->next ==NULL)
        {
            return head;
        }
        ListNode* slow = head;
        ListNode* fast = head;
        
        /*快慢指针的用法，fast到结尾，slow到中间*/
        while (fast->next &&fast->next->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        
        ListNode* rightNode = slow->next;
        slow->next = NULL;
        return mergeList(sortList(head), sortList(rightNode));
    }

    ListNode * mergeList(ListNode* l1, ListNode* l2) {

        ListNode* retListNode = new ListNode(0);
        ListNode* curNode = retListNode;
        while (l1 && l2)
        {
            if (l1->val > l2->val)
            {
                curNode->next = l2;
                l2 = l2->next;
            }
            else
            {
                curNode->next = l1;
                l1 = l1->next;
            }
            curNode = curNode->next;
        }
        if (l1)
        {
            curNode->next = l1;
        }
        else
        {
            curNode->next = l2;
        }
        return retListNode->next;
    }
};

int main() {
    ListNode *head = NULL;
    ListNode tmpNode(1);
    ListNode tmpNode2(4);
    ListNode tmpNode3(2);
    ListNode tmpNode4(5);
    head = &tmpNode;
    head->next = &tmpNode2;
    tmpNode2.next = &tmpNode3;
    tmpNode3.next = &tmpNode4;
/*    cout << Solution().sortList(head) << endl;*/
    ListNode * result = Solution().sortList(head);
    while (result)
    {
        cout << result->val << endl;
        result = result->next;
    }
    return 0;
}

```

