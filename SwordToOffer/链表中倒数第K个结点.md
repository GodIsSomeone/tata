/*
输入一个链表，输出该链表中倒数第k个结点。
*/

```
/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        ListNode *p1, *p2;
        p1 = p2 = pListHead;
        unsigned int count = 0;
        while(p1)
        {
            if(count>=k)
                p2 = p2->next;
            p1 = p1->next;
            count++;
        }
        return count < k ? NULL : p2;
    }
};

```
