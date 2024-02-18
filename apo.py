def aprior(vdf, minimum_support):
    trans = set(sum(list(vdf.values()), []))
    minimum_support_count = len(trans) * minimum_support

    def support(items):
        intersection_transactions = set()
        for index, item in enumerate(items):
            if index == 0:
                intersection_transactions = intersection_transactions.union(set(vdf[item]))
            else:
                intersection_transactions = intersection_transactions.intersection(set(vdf[item]))
        return len(intersection_transactions)
    
    def generate_itemsets(itemsets, n):
        new_itemsets = []
        for i in range(len(itemsets)):
            for j in range(i + 1, len(itemsets)):
                i_itemset = itemsets[i]
                j_itemset = itemsets[j]
                if n == 2:
                    new_item = [i_itemset[0], j_itemset[0]]
                    new_itemsets.append(new_item)
                elif i_itemset[-n+2:] == j_itemset[:n-2]:
                    new_item = i_itemset + j_itemset[n-2:]
                    new_itemsets.append(new_item)
        return new_itemsets
    
    supportMap = []

    bestSoFar = []
    c_itemsets = [[x] for x in vdf.keys()]
    N = 2
    while True:
        # Minimum Support Elimination
        l_itemsets = list(filter(lambda x: support(x) >= minimum_support_count, c_itemsets))

        if len(l_itemsets) == 0:
            for item in bestSoFar:
                print(item, support(item))
            break

        # Generate Next Itemsets
        bestSoFar = l_itemsets
        c_itemsets = generate_itemsets(l_itemsets, N)
        N += 1
