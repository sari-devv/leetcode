
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {
    }
    ListNode(int x) : val(x), next(nullptr) {
    }
    ListNode(int x, ListNode* next) : val(x), next(next) {
    }
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* newHead = nullptr;
        ListNode* newTail = nullptr;

        ListNode* it = head;
        while (it != nullptr) {
            /* If the next is equal to the current node, keep iterating until
            we stop seeing this val. */
            if (it->next != nullptr && it->next->val == it->val) {
                int currVal = it->val;
                while (it != nullptr && it->val == currVal) {
                    it = it->next;
                }
                continue;
            }

            /* Else this node is unique, insert it to our new list. */
            ListNode* newNode = new ListNode(it->val);
            if (newHead == nullptr) {
                newHead = newNode;
                newTail = newNode;
            } else {
                newTail->next = newNode;
                newTail = newTail->next;
            }

            it = it->next;
        }

        return newHead;
    };
};
