# Trees and Hash Tables (Basics)

`std::map` and `std::set` use a **tree**. `std::unordered_map` and `std::unordered_set` use a **hash table**. Before using those containers, it helps to know what those structures do at a high level.

## Binary search tree (idea behind map and set)

A **binary search tree** (BST) stores nodes. Each node holds a **key** (and a value too for `map`).

Each node has up to two children: left and right.

**BST rule:** every key in the left subtree is smaller than the node's key. Every key in the right subtree is larger.

```
           10
          /  \
         5    20
        / \
       3   7
```

To find key `7`:

1. Start at `10`. `7 < 10`, go left to `5`.
2. `7 > 5`, go right to `7`. Found.

In a balanced tree with `n` keys, you take about **log n** steps, not `n` steps.

**In-order walk** (visit left subtree, then node, then right subtree) visits keys in **sorted order**. That is why iterating a `map` prints keys sorted.

Real library trees (red-black trees and similar) stay balanced so one bad insert order cannot turn the tree into a long chain.

> NOTE: `map` and `set` wrap a balanced tree so find, insert, and sorted iteration stay efficient.

## Hash table (idea behind unordered_map and unordered_set)

A [hash table](https://en.wikipedia.org/wiki/Hash_table) stores entries in an array of **buckets** (slots).

1. Run the key through a **hash function** to get an integer (the hash value).
2. Map that integer to a starting slot with `% bucket_count`.
3. Store the entry in that slot, or in another slot if the home slot is already taken.

If two keys map to the same starting slot, that is a **collision**. With **open addressing**, you **probe** forward through the array until you find an empty slot (insert) or a matching key (lookup). A common rule is **linear probing**: try the next index, then the next, wrapping at the end of the array.

Below, hash values are **made up for teaching**. Real `std::hash` uses different numbers, but the `% bucket_count` step is the same idea.

Suppose `bucket_count` is **4**. Insert in order: `"cat"`, `"car"`, `"dog"`.

| Key | Hash value | Home slot (`hash % 4`) | Where it ends up |
|-----|------------|------------------------|------------------|
| `"cat"` | 17 | 1 | slot 1 (empty) |
| `"car"` | 19 | 3 | slot 3 (empty) |
| `"dog"` | 21 | 1 | slot 1 full → probe slot 2 |

`"cat"` and `"dog"` share home slot **1**. `"dog"` cannot go there, so linear probing places it in slot **2**.

```
bucket_count = 4

Index:   [ 0 ]    [ 1 ]    [ 2 ]    [ 3 ]
         empty    "cat"    "dog"    "car"
                  ^home              ^home
                  for both           for "car"
                  "cat" & "dog"
```

To find `"dog"`: hash it (21), compute `21 % 4` (1), check slot 1 (`"cat"`, no match), probe slot 2 (`"dog"`, match).

When the table gets too full, it **rehashes**: grow `bucket_count`, recompute every home slot, and reinsert entries (probing again as needed). Iteration order can change after a rehash.

Average lookup is **O(1)** when keys spread out. Long probe runs from many collisions slow lookups toward **O(n)**.

> NOTE: Another collision strategy is **chaining**: each bucket keeps a linked list of every key that hashes there, instead of probing for another slot. The hash and `% bucket_count` steps are the same; only the collision step differs. Many library hash tables use chaining. Open addressing is shown here because one flat array of slots is easy to picture.

> NOTE: `unordered_map` and `unordered_set` trade sorted order for hash speed on average.

## Side-by-side mental model

| Step | Tree (`map`) | Hash table (`unordered_map`) |
|------|--------------|------------------------------|
| Find key `"moose"` | compare down left/right from root | hash → home slot with `% bucket_count`, probe until match |
| Print all keys sorted | walk tree in order | not built in; sort separately if needed (expensive) |
| Insert new key | place in tree, rebalance if needed | hash to bucket, maybe rehash later |

The next section shows the C++ containers built on these ideas.