import socket

# Sample user data
users = {
    'user1': {'name': 'Alice', 'age': 30},
    'user2': {'name': 'Bob', 'age': 25},
    'user3': {'name': 'Charlie', 'age': 35},
}

def handle_get_request(request):
    # Parse the request and extract the requested user ID
    request_parts = request.split()
    if len(request_parts) >= 2:
        user_id = request_parts[1]

        if user_id in users:
            user_info = users[user_id]
            response = f"HTTP/1.1 200 OK\nContent-Type: application/json\n\n{user_info}"
        else:
            response = "HTTP/1.1 404 Not Found\n\nUser not found"

    return response

def handle_post_request(request):
    command = request.split(' ')
    name = command[1]
    age = command[2]
    users[f'user{len(users)+1}'] = {'name': name, 'age': int(age)}
    response = "HTTP/1.1 200 OK\n\nUser data updated"
    return response

def main():
    host = 'localhost'
    port = 8080

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)
    print(f"Server is listening on http://{host}:{port}")

    while True:
        client_socket, client_address = server_socket.accept()
        request = client_socket.recv(1024).decode()
        if "GET" in request:
            response = handle_get_request(request)
        elif "POST" in request:
            response = handle_post_request(request)
        else:
            response = "HTTP/1.1 400 Bad Request\n\nInvalid request"

        client_socket.sendall(response.encode())
        client_socket.close()

if __name__ == '__main__':
    main()
