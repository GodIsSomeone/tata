
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
    bool isPalindrome(ListNode* head) {
        if (head == NULL || head->next ==NULL)
        {
            return true;
        }
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next &&fast->next->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        ListNode* rightNode = slow->next;
        rightNode = reverseList(rightNode);
        while (rightNode && rightNode->val == head->val)
        {
            if (rightNode->next == NULL)
            {
                return true;
            }
            rightNode = rightNode->next;
            head = head->next;
        }
        return false;
    }
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
    ListNode tmpNode3(2);
    ListNode tmpNode4(1);
    head = &tmpNode;
    head->next = &tmpNode2;
    tmpNode2.next = &tmpNode3;
    tmpNode3.next = &tmpNode4;
    cout << Solution().isPalindrome(head) << endl;
//     ListNode * result = Solution().reverseList(head);
//     while (result)
//     {
//         cout << result->val << endl;
//         result = result->next;
//     }
    return 0;
}
```
