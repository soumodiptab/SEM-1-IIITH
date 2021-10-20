def helloworld():
    print("Hello")
def gradeValue(marks):
    if marks > 90:
        return 'A'
    elif marks > 80 and marks <=90:
        return 'B'
    else:
        return 'C'

print(gradeValue(68))