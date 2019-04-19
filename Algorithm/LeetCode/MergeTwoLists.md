

```   
class Solution {
public:
    ListNode * mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode * retList;
        ListNode *tempNode;
        if (!l1)
        {
            return l2;
        }
        if (!l2)
        {
            return l1;
        }
         /*确定链表头结点，谁小谁是头结点*/
        if (l1->val < l2->val)
        {
            retList = l1;
            l1 = l1->next;
        }
        else
        {
            retList = l2;
            l2 = l2->next;
        }
        tempNode = retList;

        while (l1 &&  l2)
        {
            if (l1->val < l2->val)
            {
                tempNode->next = l1;
                l1 = l1->next;
            }
            else
            {
                tempNode->next = l2;
                l2 = l2->next;
            }

            tempNode = tempNode->next;
        }

        //while中如果没有进行完，则补上
        if (!l1)
        {
            tempNode->next = l2;
        }
        else
        {
            tempNode->next = l1;
        }
        return retList;
    }
};

int main() {
    ListNode* head = new ListNode(1);
    ListNode temp(2);
    head->next = &temp;

    ListNode* tail = new ListNode(3);
    ListNode tmp(4);
    tail->next = &tmp;
    ListNode* temp2 = Solution().mergeTwoLists(head, tail);
    while (temp2)
    {
        cout <<temp2->val << endl;
        temp2 = temp2->next;
    }
    delete head;
    head = NULL;

    delete temp2;
    temp2 = NULL;
    //cout << Solution().threeSum(nums)<<endl;
    return 0;
}

```         

