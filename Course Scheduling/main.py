

n = int(input())

course_to_names = {}
for _ in range(n):
    first, last, course = input().split()
    if course not in course_to_names:
        course_to_names[course] = set()
    course_to_names[course].add(first + '-' + last)

ans = sorted([(k, len(v)) for k, v in course_to_names.items()])
for code, cnt in ans:
    print(code, cnt)
