def partition(predicate, iterable):
    """
    https://stackoverflow.com/a/4578605/666907
    """
    trues = []
    falses = []

    for item in iterable:
        if predicate(item):
            trues.append(item)
        else:
            falses.append(item)

    return trues, falses
