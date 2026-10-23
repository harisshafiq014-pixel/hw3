#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot)
{
    // Base case: no nodes remain.
    if(head == NULL) {
        smaller = NULL;
        larger = NULL;
        return;
    }

    // Remove the first node from the original list.
    Node* current = head;
    head = head->next;

    // Recursively split the remaining nodes.
    llpivot(head, smaller, larger, pivot);

    // Place current at the front of its appropriate result list.
    if(current->val <= pivot) {
        current->next = smaller;
        smaller = current;
    }
    else {
        current->next = larger;
        larger = current;
    }
}