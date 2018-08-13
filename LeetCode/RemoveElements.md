
删除某一个值的结点

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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode *pseudo_head = new ListNode(0);
        pseudo_head->next = head;
        ListNode *cur = pseudo_head;
        while(cur){
            if(cur->next && cur->next->val == val)   cur->next = cur->next->next;
            else    cur = cur->next;
        }
        return pseudo_head->next;
    }
};

int main() {
    ListNode *head = NULL;
    ListNode tmpNode(1);
    ListNode tmpNode2(3);
    ListNode tmpNode3(3);
    ListNode tmpNode4(4);
    head = &tmpNode;
    head->next = &tmpNode2;
    tmpNode2.next = &tmpNode3;
    tmpNode3.next = &tmpNode4;
    ListNode * result = Solution().removeElements(head, 3);
    while (result)
    {
        cout << result->val << endl;
        result = result->next;
    }
    return 0;
}
```
