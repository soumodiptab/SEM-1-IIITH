import requests


def menu():
    print("1. Add student")
    print("2. Fetch all students")
    print("3. Update student")
    print("4. Delete student")
    print("5. Exit")
    print()


while(True):
    menu()
    c = int(input(""))
    if(c == 5):
        break
    elif(c == 1):
        id = input('Id: ')
        name = input('Name: ')
        stream = input('Stream: ')
        data = {"id": id, "name": name, "stream": stream}
        response = requests.post(
            'http://localhost:8000/create', json=data).content
        print(response.decode('ascii'))
    elif(c == 2):
        response = requests.get('http://localhost:8000/read')
        json_data = response.json()
        for i in json_data:
            print(f"Name: {json_data[i]['name']} Stream: {json_data[i]['stream']}")
        print()
    elif(c == 3):
        id = input('Id: ')
        name = input('Name: ')
        stream = input('Stream: ')
        data = {"id": id, "name": name, "stream": stream}
        response = requests.put(
            'http://localhost:8000/update', json=data).content
        print(response.decode('ascii'))
    elif(c == 4):
        id = input('Id: ')
        data = {"id": id}
        response = requests.delete(
            'http://localhost:8000/delete/{}'.format(id)).content
        print(response.decode('ascii'))
