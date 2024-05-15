/* include <ext/pb_ds/assoc_container.hpp> and <ext/pb_ds/tree_policy.hpp>,
   namespace [__gnu_pbds] for multiset: less_equal<T>, for map: null_type change to T2
   [find_by_order] (int -> int*) and  [order_of_key] (int -> int) */
template <class T> using ordered_set = 
    tree <T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;