```
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <xutility>
#include <string>
#include<algorithm>
#include <list>
#include <queue>
using namespace std;

class CSort
{
public:
    void printArray(int arr[], int length) {
        for (int i = 0; i < length; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    /*
    第i轮：
    倒叙比较，最后一个如果小，则冒泡交换，否则，下一个比较
    */
    void BubbleSort(int arr[], int length)
    {
        if (arr == NULL || length == 0) return ;

        for (int i = 0; i< length; i++)
        {
            for (int j= length-1; j>i; j--)
            {
                if (arr[j]<arr[j-1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j - 1];
                    arr[j - 1] = temp;
                }
            }
        }
        printArray(arr, length);
    }

    void InsortSort(int arr[], int length)
    {
        if (arr == NULL || length == 0) return;

        for (int i = 1; i < length; i++)
        {
            int tar = arr[i];//保存当前变量

            int j = i - 1;
            if (arr[i] < arr[i-1])
            {
                for ( ; j>0; j--)
                {
                    arr[j + 1] = arr[j];
                }
                arr[j+1] = tar;
            }
        }
        printArray(arr, length);
    }


private:
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

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
            next->next = temp->next;
            temp->next = vNode.back();
            vNode.pop_back();
            temp = next->next;
            count++;
        }
        temp->next = NULL;
    }


    ListNode* insertionSortList(ListNode* head) {
        if (head == NULL || head->next == NULL)
        {
            return head;
        }
        ListNode*cur, *ret, *pre;
        cur = head;
        ret = head;
        pre = head->next;
        while (cur)
        {
            /*if not equal*/
            if (cur->next && cur->val > pre->val)
            {
                while (pre && cur->val > pre->val)
                {
                    pre = pre->next;
                }

                /*swap*/
                ListNode* temp = pre->next;
                pre->next = cur->next;
                cur->next = cur->next->next;
                pre->next->next = temp;
                pre = head;
            }
            else
            {
                cur = cur->next;
            }
        }
        return ret;
    }
};



int main() {
    int a[] = { 1,5,7,6,8,2,4,6 };
    int length = sizeof(a) / sizeof(a[0]);
    CSort().BubbleSort(a,length);
    CSort().InsortSort(a,length);
    return 0;
}

```
