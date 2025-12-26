#include "defaults.hpp"

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

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x),
          left(left),
          right(right) {
    }
};

class Solution {
    TreeNode* valsToBST(const vector<int>& vals, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        assert(mid >= 0 && mid < vals.size());

        TreeNode* pRoot = new TreeNode(vals[mid]);

        pRoot->left = valsToBST(vals, start, mid - 1);
        pRoot->right = valsToBST(vals, mid + 1, end);

        return pRoot;
    }

    TreeNode* listToBSTRec(ListNode* start, ListNode* end) {
        if (start == end) {
            return nullptr;
        }

        /* Find the mid with the fast/slow approach. */
        ListNode* fast = start;
        ListNode* slow = start;

        while (fast != end && fast->next != end) {
            fast = fast->next->next;
            slow = slow->next;
        }

        TreeNode* pRoot = new TreeNode(slow->val);

        pRoot->left = listToBSTRec(start, slow);
        pRoot->right = listToBSTRec(slow->next, end);

        return pRoot;
    }

public:
    TreeNode* sortedListToBST(ListNode* head) {
        vector<int> vals;
        ListNode* it = head;
        while (it != nullptr) {
            vals.push_back(it->val);
            it = it->next;
        }

        return valsToBST(vals, 0, vals.size() - 1);
    }
};
