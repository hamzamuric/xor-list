# XOR List

A doubly linked-list with one-link nodes.

### How it works?

Every node has a pointer which is result of previous xor next.

When we want to get next node, we can xor it's link with
the address of previous node.

When we want to get previous node, we can xor it's link with
the address of next node.

First and last nodes have links xor-ed with nullptr.

When we iterate from start of the list,
we xor first node's link with nullptr to get next node.
Similar is for reverse iteration. 

### Example

| Address | 0x123                   |
|---------|-------------------------|
| Data    |   1                     |
| Link    |  0x456 (0x456 ^ 0x000)  |

| Address | 0x456                   |
|---------|-------------------------|
| Data    |   2                     |
| Link    |  0x6AA (0x123 ^ 0x789)  |

| Address | 0x789                   |
|---------|-------------------------|
| Data    |   3                     |
| Link    |  0x701 (0x456 ^ 0x357)  |

| Address | 0x357                   |
|---------|-------------------------|
| Data    |   4                     |
| Link    |  0x789 (0x789 ^ 0x000)  |

Given a node, we can get next node by xor-ing it's link and address of previous node,
and we can get its previous node by xor-ing it's link with address of next node.