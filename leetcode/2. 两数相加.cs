/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public int val;
 *     public ListNode next;
 *     public ListNode(int val=0, ListNode next=null) {
 *         this.val = val;
 *         this.next = next;
 *     }
 * }
 */
#nullable enable
public class Solution {
    static ListNode Append(ListNode? u, ListNode? v, ListNode last, int carry) {
        if (u == null && v == null && carry == 0) {
            return last;
        }
        int sum = (u?.val ?? 0) + (v?.val ?? 0) + carry;
        last.next = new ListNode(sum % 10);
        return Append(u?.next, v?.next, last.next, sum / 10);
    }

    public ListNode AddTwoNumbers(ListNode? u, ListNode? v) {
        var head = new ListNode();
        Append(u, v, head, 0);
        return head.next;
    }
}
