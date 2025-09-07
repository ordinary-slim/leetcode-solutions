/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(1), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
      ListNode* root = new ListNode();
      ListNode* tail = root;
      ListNode* l1_it = l1;
      ListNode* l2_it = l2;
      int carry_over = 0, l1val = 0, l2val = 0;
      while (true) {
        if (l1_it) {
          l1val = l1_it->val;
          l1_it = l1_it->next;
        } else {
          l1val = 0;
        }
        if (l2_it) {
          l2val = l2_it->val;
          l2_it = l2_it->next;
        } else {
          l2val = 0;
        }
        tail->val = l1val + l2val + carry_over;
        if (tail->val > 9) {
          tail->val -= 10;
          carry_over = 1;
        } else {
          carry_over = 0;
        }
        if (l1_it || l2_it || (carry_over > 0)) {
          tail->next = new ListNode();
        } else {
          break;
        }
        // Advance
        tail = tail->next;
      }
      return root;
    }
};
