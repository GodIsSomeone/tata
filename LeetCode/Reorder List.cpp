用辅助栈或者vector都可以实现
```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        if (NULL == head || NULL == head->next)
        {
            return;
        }
        vector<ListNode*> vNode;
        ListNode* temp = head;
        while (temp)
        {
            vNode.push_back(temp);
            temp = temp->next;
        }
        temp = head;
        int count = 0;
        int length = vNode.size();
        while (count <= length/2)
        {
            ListNode* next = vNode.back();
            vNode.back()->next = temp->next;
            temp->next = next;
            vNode.pop_back();
            temp = next->next;
            count++;
        }
        temp->next = NULL;
    }
};
```
