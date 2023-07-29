def path_finder(maze):

    size = len(maze[0])


    checked = []
    queue = [[0,0]]


    for element in queue:

        print(queue)

        if element == [size - 1, size - 1]:
            return True

        if (element[0] + 1) < size:
            if maze[(element[0] + 1)][element[1]] != "W":
                if [(element[0] + 1), element[1]] not in checked:
                    queue.append([element[0] + 1, element[1]])

        if (element[1] + 1) < size:
            if maze[(element[0])][(element[1] + 1)] != "W":
                if [(element[0] ), element[1] + 1] not in checked:
                    queue.append([element[0], element[1] + 1])

        if (element[0] - 1) < 0:
            if maze[(element[0] - 1)][element[1]] != "W":
                if [(element[0] - 1), element[1]] not in checked:
                    queue.append([element[0] - 1, element[1]])

        if (element[0] + 1) < size:
            if maze[(element[0])][element[1] - 1] != "W":
                if [(element[0]), element[1] - 1] not in checked:
                    queue.append([element[0], element[1] - 1])

        checked.append(element)
        queue.pop(0)

    return False

aa = [
    ".W...",
    ".W...",
    ".W.W.",
    "...WW",
    "...W."]
print(path_finder(aa))