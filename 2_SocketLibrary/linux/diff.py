server = open('.out/server.txt', 'r')
client = open('.out/client.txt', 'r')

server_lines = server.readlines()
client_lines = client.readlines()

assert(len(server_lines) == len(client_lines))

count = 0
for i in range(11):
    num = int(server_lines[i].strip("Server: "))-int(client_lines[i].strip("Client: "))
    print(num)
    count += num

print(count/11)

count = 0
for i in range(11,22):
    num = int(server_lines[i].strip("Server: "))-int(client_lines[i].strip("Client: "))
    print(num)
    count += num

print(count/11)
